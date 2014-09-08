/**
 * HelloMap
 * by BREVIG http://alexanderbrevig.com
 * 
 * Demonstrate the usage of a Map
 * This Map will pair a char* string to an integer and it has the capacity to hold three pairs
 * 
 * Joshua Yanchar removed all references to 'hash' in this example, because they were all lies.
 */

#include <ArduinoMap.h>

CreateMap(mapInstance, char*, int, 3); //create map that pairs char* to int and can hold 3 pairs

void setup()
{
  Serial.begin(9600);
  //add and store keys and values
  mapInstance["newKey"] = 12;
  mapInstance["otherKey"] = 13;
  
  //check if overflow (there should not be any danger yet)
  Serial.print("Will the map overflow now [after 2 assigns] ?: ");
  Serial.println(mapInstance.willOverflow());
  
  mapInstance["lastKey"] = 14;
  
  //check if overflow (this should be true, as we have added 3 of 3 pairs)
  Serial.print("Will the map overflow now [after 3 assigns] ?: ");
  Serial.println(mapInstance.willOverflow());
  
  //it will overflow, but this won't affect the code.
  mapInstance["test"] = 15;

  //change the value of newKey
  Serial.print("The old value of newKey: ");
  Serial.println(mapInstance["newKey"]);
  
  mapInstance["newKey"]++;
  
  Serial.print("The new value of newKey (after map['newKey']++): ");
  Serial.println(mapInstance["newKey"]);

  //remove a key from the map
  mapInstance.remove("otherKey");
  
  //this should work as there is now an available spot in the map
  mapInstance["test"] = 15;

  printMap();
}

void loop() {}

void printMap() 
{
  for (int i=0; i<mapInstance.size(); i++) 
  {
    Serial.print("Index: ");
    Serial.print(i);
    Serial.print(" Key: ");
    Serial.print(mapInstance.keyAt(i));
    Serial.print(" Value: ");
    Serial.println(mapInstance.valueAt(i));
  }
}
