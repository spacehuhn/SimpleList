/*
   ===========================================
      Copyright (c) 2018 Stefan Kremser
             github.com/spacehuhn
   ===========================================
 */

#include <SimpleList.h>

SimpleList<int>* list;

void printList() {
    Serial.print("=>");

    for (int i = 0; i < list->size(); i++) {
        Serial.print(list->get(i));
        Serial.print("->");
    }
    Serial.println("//");
}

void setup() {
    Serial.begin(115200);
    delay(200);

    // create new list
    list = new SimpleList<int>();

    Serial.println("Create list:");

    // add a bunch of numbers
    list->add(1);
    list->add(0);
    list->add(7);
    list->add(1);
    list->add(6);
    list->add(16);

    // print out the list
    printList();
    // => 1 -> 0 -> 7 -> 1 -> 6 -> 16 -> //

    // remove first and last
    Serial.println("Remove first and last:");
    list->remove(5); // remove node at index 5, alternative: removeNode(listSize-1);
    list->remove(0); // remove node at index 0
    printList();
    // => 0 -> 7 -> 1 -> 6 -> //

    // add number 4 at the end
    Serial.println("Add number 4 at the end:");
    list->add(4);
    printList();
    // => 0 -> 7 -> 1 -> 6 -> 4 -> //

    // replace number 0 with 3
    Serial.println("Replace number 0 with 3:");
    list->replace(0, 3);
    printList();
    // => 3 -> 7 -> 1 -> 6 -> 4 -> //

    // add a compare function to sort or search the list
    list->setCompare([](int& a, int& b) -> int {
        if (a < b) return -1;
        else if (a > b) return 1;
        else return 0;
    });

    // find the number 7 and replace it with a 2
    Serial.println("Replace number 7 with 2:");
    list->replace(list->search(7), 2);
    printList();
    // => 3 -> 2 -> 1 -> 6 -> 4 -> //

    // sort the list
    Serial.println("Sort list:");
    list->sort();
    printList();
    // => 1 -> 2 -> 3 -> 4 -> 6 -> //

    // perform a fast binary search (only works when the list is sorted!)
    Serial.println("1 at index (bin-search): " + (String)list->binSearch(1));
    Serial.println("6 at index (bin-search): " + (String)list->binSearch(6));
    Serial.println("3 at index (bin-search): " + (String)list->binSearch(3));

    // or do the slower sequential search (won't make a time difference in small lists like this)

    Serial.println("1 at index (seq-search): " + (String)list->search(1));
    Serial.println("6 at index (seq-search): " + (String)list->search(6));
    Serial.println("3 at index (seq-search): " + (String)list->search(3));

    // insert number 5 (which ist the list size) in the sorted list
    // note here that insert() will try to put the object in correct spot to keep the list sorted
    Serial.println("Insert number 5:");
    list->insert(list->size());
    printList();
    // => 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> //

    // empty the list
    Serial.println("Empty the list:");
    list->clear();
    // => Empty list :(
    printList();

    // add random numbers
    Serial.println("Add random numbers:");

    for (int i = 0; i < 10; i++) list->add(random(0, 9));
    printList();

    // with shift() you get and remove the first object from the list
    Serial.println("removed first object " + (String)list->shift());
    printList();

    // with pop() you get and remove the last object from the list
    Serial.println("removed last object " + (String)list->pop());
    printList();

    Serial.println("List sorted: " + String(list->isSorted() ? "true" : "false"));
    printList();
    list->sort();
    Serial.println("List sorted: " + String(list->isSorted() ? "true" : "false"));
    printList();

    Serial.println("Done");
}

void loop() {}