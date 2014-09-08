/* $Id: ArduinoMap.h 1198 2014-08-23 $
||
|| @author         Alexander Brevig <abrevig@wiring.org.co>
|| @url            http://wiring.org.co/
|| @url            http://alexanderbrevig.com/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | Implementation of a Map data structure.
|| |
|| | Wiring Cross-platform Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
||
|| Alright, so Joshua Yanchar got a little annoyed that they called this a hashmap,
|| given that they never touched hashing at all.  He went ahead and pulled all
|| references to 'hash' out...
*/

#ifndef MAP_H
#define MAP_H

//for convenience
#define CreateMap(mapInstance, ktype, vtype, capacity) Map<ktype,vtype,capacity> mapInstance
#define CreateComplexMap(mapInstance, ktype, vtype, capacity, comparator) Map<ktype,vtype,capacity> mapInstance(comparator)

template<typename K, typename V, unsigned int capacity>
class Map
{
  public:
    typedef bool (*comparator)(K, K);

    /*
    || @constructor
    || | Initialize this Map
    || #
    ||
    || @parameter compare optional function for comparing a key against another (for complex types)
    */
    Map(comparator compare = 0)
    {
      cb_comparator = compare;
      currentIndex = 0;
    }

    /*
    || @description
    || | Get the size of this Map
    || #
    ||
    || @return The size of this Map
    */
    unsigned int size() const
    {
      return currentIndex;
    }

    /*
    || @description
    || | Get a key at a specified index
    || #
    ||
    || @parameter idx the index to get the key at
    ||
    || @return The key at index idx
    */
    K keyAt(unsigned int idx)
    {
      return keys[idx];
    }

    /*
    || @description
    || | Get a value at a specified index
    || #
    ||
    || @parameter idx the index to get the value at
    ||
    || @return The value at index idx
    */
    V valueAt(unsigned int idx)
    {
      return values[idx];
    }

    /*
    || @description
    || | Check if a new assignment will overflow this Map
    || #
    ||
    || @return true if next assignment will overflow this Map
    */
    bool willOverflow()
    {
      return (currentIndex + 1 > capacity);
    }

    /*
    || @description
    || | An indexer for accessing and assigning a value to a key
    || | If a key is used that exists, it returns the value for that key
    || | If there exists no value for that key, the key is added
    || #
    ||
    || @parameter key the key to get the value for
    ||
    || @return The const value for key
    */
    const V& operator[](const K key) const
    {
      return operator[](key);
    }

    /*
    || @description
    || | An indexer for accessing and assigning a value to a key
    || | If a key is used that exists, it returns the value for that key
    || | If there exists no value for that key, the key is added
    || #
    ||
    || @parameter key the key to get the value for
    ||
    || @return The value for key
    */
    V& operator[](const K key)
    {
      if (contains(key))
      {
        return values[indexOf(key)];
      }
      else if (currentIndex < capacity)
      {
        keys[currentIndex] = key;
        values[currentIndex] = nil;
        currentIndex++;
        return values[currentIndex - 1];
      }
      return nil;
    }

    /*
    || @description
    || | Get the index of a key
    || #
    ||
    || @parameter key the key to get the index for
    ||
    || @return The index of the key, or -1 if key does not exist
    */
    unsigned int indexOf(K key)
    {
      for (int i = 0; i < currentIndex; i++)
      {
        if (cb_comparator)
        {
          if (cb_comparator(key, keys[i]))
          {
            return i;
          }
        }
        else
        {
          if (key == keys[i])
          {
            return i;
          }
        }
      }
      return -1;
    }

    /*
    || @description
    || | Check if a key is contained within this Map
    || #
    ||
    || @parameter key the key to check if is contained within this Map
    ||
    || @return true if it is contained in this Map
    */
    bool contains(K key)
    {
      for (int i = 0; i < currentIndex; i++)
      {
        if (cb_comparator)
        {
          if (cb_comparator(key, keys[i]))
          {
            return true;
          }
        }
        else
        {
          if (key == keys[i])
          {
            return true;
          }
        }
      }
      return false;
    }

    /*
    || @description
    || | Check if a key is contained within this Map
    || #
    ||
    || @parameter key the key to remove from this Map
    */
    void remove(K key)
    {
      int index = indexOf(key);
      if (contains(key))
      {
        for (int i = index; i < capacity - 1; i++)
        {
          keys[i] = keys[i + 1];
          values[i] = values[i + 1];
        }
        currentIndex--;
      }
    }

    void setNullValue(V nullv)
    {
      nil = nullv;
    }

  protected:
    K keys[capacity];
    V values[capacity];
    V nil;
    int currentIndex;
    comparator cb_comparator;
};

#endif
// MAP_H