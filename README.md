# SimpleList

Nothing big, just my own implementation of a linked list in c++ for all kind of Arduino projects.  
This Arduino Library was inspired by the [LinkedList](https://github.com/ivanseidel/LinkedList) 
and is mostly compatible too it.   
I made it to get a deeper understanding of lists.  

## Installation

1) [Download](https://github.com/spacehuhn/SimpleList/archive/master.zip) the source code from GitHub.  
2) Unzip and rename the Folder name to "SimpleList".  
3) Paste it in your Library folder (Usually located somewhere at documents/Arduino/libraries).  
4) Restart the Arduino IDE.  

You can also just download the [SimpleList.h](https://github.com/spacehuhn/SimpleList/blob/master/src/SimpleList.h) 
file and paste it in your Arduino sketch folder.  

## Usage

### Include the library
```c++
#include <SimpleList.h>  
```

### Creating a SimpleList
```c++
// A list of integer
LinkedList<int> *myLinkedList = new LinkedList<int>();

// A list of 'MyClass'
SimpleList<MyClass> *mySimpleList = new SimpleList<MyClass>();
```

### Getting the list size
```c++
int theSize = myList->size();
```

### Adding elements
```c++
// add(obj) will add the object at the end of the list
myList->add(myObject);

// add(index, obj) method will insert the object at the specified index
myList->add(0, myObject); // Add at the beginning
myList->add(3, myObject); // Add at index 3
```

### Getting elements
```c++
// Get the first element
myObject = myList->get(0);

// Get the third element
myObject = myList->get(2);

// Get the last element
myObject = myList->get(myList->size() - 1);
```

### Replacing elements
```c++
// Replace the first element
myList->replace(0, myObject);

// Replace the third element
myList->replace(2, myObject);

// Replace the last element
myList->replace(myList->size() - 1, myObject);
```

### Removing elements
```c++
// Remove the first object
myList->remove(0);

// pop() will remove and return the last element
myDeletedObject = myList->pop();

// shift() will remove and return the first element
myDeletedObject = myList->shift();

// clear() will erase the entire list, leaving it with 0 elements
myList->clear();

// Please note that clear() wont free memory from pointers, you have to manually delete/free those!
// Example:
while(list->size() > 0){
    delete myList->get(0).somePointer;
    list->remove(0);
}
```

### Sorting list
```c++
myList->sort([](int &a, int &b) -> bool { 
    return a > b; 
});
```

### Searching for elements
```c++
// seach() returns the index of the element, not the element itself!
int indexOfSeven = list->search([](int &a) -> bool{ 
    return a == 7; 
});

int indexOftheFirstSelected = list->search([](MyClass &a) -> bool{ 
    return a.selected; 
});
MyClass firstSelected = list->get(indexOftheFirstSelected);

// searchNext is like search() but will start on the last used index instead of index 0
int indexOftheNextSelected = list->searchNext([](MyClass &a) -> bool{ 
    return a.selected; 
});

// When the list is sorted, you can also do a more efficient binary search
// here find the element 
int indexOfIntOne = list->binSearch([](int &a) -> int{ 
    if(a == 1) return 0; 
    if(a < 1) return 1; 
    if(a > 1) return -1;   
})); 
```

### Counting elements
```c++
int numberOfZeros = myList->count([](int &a)->bool{
    return a == 0;  
});

int selectedNum = myList->count([](MyClass &a)->bool{
    return a.selected;  
});
```

### Swapping elements
```c++
// swap(index-X, index-Y)
list->swap(0, list->size()-1);
```
