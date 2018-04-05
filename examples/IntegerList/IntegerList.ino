 /*
  ===========================================
       Copyright (c) 2018 Stefan Kremser
              github.com/spacehuhn
  ===========================================
*/

#include "SimpleList.h" 
 
SimpleList<int>* list; 
 
void printList(){ 
  for(int i=0;i<list->size();i++){ 
    Serial.print(list->get(i));   
    if(i<list->size()-1) Serial.print("->"); 
  } 
  Serial.println(); 
} 
 
void setup() { 
  Serial.begin(115200); 
  delay(2000); 
 
  list = new SimpleList<int>; 
  list->add(1); 
  list->add(0); 
  list->add(7); 
  list->add(1); 
  list->add(6); 
  list->add(16); 
   
  printList(); 
  // => 1 -> 0 -> 7 -> 1 -> 6 -> 16 
   
  list->remove(5); // remove node at index 5, alternative: removeNode(listSize-1); 
  list->remove(0); // remove node at index 0 
  printList(); 
  // => 0 -> 7 -> 1 -> 6 
   
  list->add(4); 
  printList(); 
  // => 0 -> 7 -> 1 -> 6 -> 4 
   
  list->replace(0,3); 
  printList(); 
  // => 3 -> 7 -> 1 -> 6 -> 4 
   
  list->replace(list->search([](int &a) -> bool{ 
    return a == 7; 
  }),2); 
  printList(); 
  // => 3 -> 2 -> 1 -> 6 -> 4 
   
  list->sort([](int &a, int &b) -> bool { 
    return a > b; 
  }); 
  printList(); 
  // => 1 -> 2 -> 3 -> 4 -> 6 
 
  Serial.println(list->binSearch([](int &a) -> int{ 
    if(a == 1) return 0; 
    if(a < 1) return 1; 
    if(a > 1) return -1;   
  })); 
 
  Serial.println(list->binSearch([](int &a) -> int{ 
    if(a == 6) return 0; 
    if(a < 6) return 1; 
    if(a > 6) return -1;   
  })); 
 
  Serial.println(list->binSearch([](int &a) -> int{ 
    if(a == 3) return 0; 
    if(a < 3) return 1; 
    if(a > 3) return -1;   
  })); 
   
  list->add(list->size()-2, list->size()); 
  printList(); 
  // => 1 -> 2 -> 3 -> 4 -> 5 -> 6 
   
  list->clear(); 
  // => Empty list :( 
  printList(); 
 
  for(int i=0;i<10;i++) 
    list->add(random(0,3)); 
   
  printList(); 
   
  Serial.println(list->count([](int &a) -> bool{ 
    return a == 0; 
  })); 
 
  Serial.println("removed "+(String)list->shift()); 
  printList(); 
   
  Serial.println("removed "+(String)list->pop()); 
  printList(); 
} 
 
void loop() { 
  //list.add(int(1)); 
}
 