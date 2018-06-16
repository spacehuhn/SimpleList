
#ifndef SimpleList_h
#define SimpleList_h

#include <stddef.h>
#include <functional>

template<class T>
struct SimpleListNode {
    T                  data;
    SimpleListNode<T>* next;
};

template<typename T>
class SimpleList {
    public:
        SimpleList();
        virtual ~SimpleList();

        virtual void setCompare(int (*compare)(T & a, T & b));

        virtual int size();
        virtual void add(int index, T obj);
        virtual void add(T obj);
        virtual void insert(T obj);
        virtual void replace(int index, T obj);
        virtual void remove(int index);
        virtual bool has(T obj);
        virtual T shift();
        virtual T pop();
        virtual T get(int index);
        virtual int search(T obj);
        virtual int searchNext(T obj);
        virtual int binSearch(T obj);
        virtual int count(T obj);
        virtual void sort();
        virtual void swap(int x, int y);
        virtual void clear();
        virtual bool isSorted();

    protected:
        int (*compare)(T & a, T & b) = NULL;

        int listSize;
        SimpleListNode<T>* listBegin;
        SimpleListNode<T>* listEnd;

        // Helps get() method by saving last position
        SimpleListNode<T>* lastNodeGot;
        int lastIndexGot;
        bool isCached;

        bool sorted = true;

        virtual SimpleListNode<T>* getNode(int index);
        virtual int binSearch(T obj, int lowerEnd, int upperEnd);
};

template<typename T>
SimpleList<T>::SimpleList() {
    listBegin = NULL;
    listEnd   = NULL;
    listSize  = 0;

    lastNodeGot  = NULL;
    lastIndexGot = -1;
    isCached     = false;
}

// Clear Nodes and free Memory
template<typename T>
SimpleList<T>::~SimpleList() {
    clear();
    listBegin = NULL;
    listEnd   = NULL;
    listSize  = 0;

    lastNodeGot  = NULL;
    lastIndexGot = -1;
    isCached     = false;
}

template<typename T>
void SimpleList<T>::setCompare(int (*compare)(T & a, T & b)) {
    SimpleList<T>::compare = compare;
    sorted                 = false;
    sort();
}

template<typename T>
SimpleListNode<T>* SimpleList<T>::getNode(int index) {
    if ((index < 0) || (index >= listSize)) return NULL;

    SimpleListNode<T>* hNode = listBegin;
    int c                    = 0;

    if (isCached && (index >= lastIndexGot)) {
        c     = lastIndexGot;
        hNode = lastNodeGot;
    }

    while (hNode != NULL && c < index) {
        hNode = hNode->next;
        c++;
    }

    if (hNode) {
        isCached     = true;
        lastIndexGot = c;
        lastNodeGot  = hNode;
    }

    return hNode;
}

template<typename T>
int SimpleList<T>::size() {
    return listSize;
}

template<typename T>
void SimpleList<T>::add(T obj) {
    SimpleListNode<T>* node = new SimpleListNode<T>();
    node->data = obj;
    node->next = NULL;

    if (!listBegin) listBegin = node;

    if (listEnd) {
        listEnd->next = node;
        listEnd       = node;
    } else {
        listEnd = node;
    }

    listSize++;
    sorted = false;
}

template<typename T>
void SimpleList<T>::add(int index, T obj) {
    if ((index < 0) || (index >= listSize)) {
        add(obj);
        return;
    }

    SimpleListNode<T>* nodeNew = new SimpleListNode<T>();
    nodeNew->data = obj;
    nodeNew->next = NULL;

    if (index == 0) listBegin = nodeNew;
    else {
        SimpleListNode<T>* nodePrev = getNode(index - 1);
        nodeNew->next  = nodePrev->next;
        nodePrev->next = nodeNew;
    }

    listSize++;
    sorted = false;
}

template<typename T>
void SimpleList<T>::insert(T obj) {
    if ((compare == NULL) || !sorted) {
        add(obj);
        return;
    }

    // create new node
    SimpleListNode<T>* newNode = new SimpleListNode<T>();
    newNode->next = NULL;
    newNode->data = obj;

    if (listSize == 0) {
        // add at start (first node)
        listBegin = newNode;

        listEnd = newNode;
    } else {
        if (compare(obj, listEnd->data) >= 0) {
            // add at end
            listEnd->next = newNode;
            listEnd       = newNode;
        } else if (compare(obj, listBegin->data) <= 0) {
            // add at start
            newNode->next = listBegin;
            listBegin     = newNode;
        } else {
            // insertion sort
            SimpleListNode<T>* h = listBegin;
            SimpleListNode<T>* p = NULL;
            bool found           = false;

            // here a sequential search, because otherwise the previous node couldn't be accessed
            while (h != NULL && !found) {
                if (compare(h->data, obj) >= 0) {
                    found = true;
                } else {
                    p = h;
                    h = h->next;
                }
            }
            newNode->next = h;

            if (p) p->next = newNode;
        }
    }

    listSize++;
}

template<typename T>
void SimpleList<T>::replace(int index, T obj) {
    if ((index >= 0) && (index < listSize)) {
        getNode(index)->data = obj;
    }
}

template<typename T>
void SimpleList<T>::remove(int index) {
    if ((index < 0) || (index >= listSize)) return;

    SimpleListNode<T>* nodePrev     = getNode(index - 1);
    SimpleListNode<T>* nodeToDelete = getNode(index);

    if (index == 0) {
        listBegin = nodeToDelete->next;
    } else {
        nodePrev->next = nodeToDelete->next;

        if (!nodePrev->next) listEnd = nodePrev;
    }

    delete nodeToDelete;

    isCached = false;

    listSize--;
}

template<typename T>
bool SimpleList<T>::has(T obj) {
    if ((compare != NULL) && sorted) return binSearch(obj) >= 0;
    else return search(obj) >= 0;
}

template<typename T>
T SimpleList<T>::get(int index) {
    SimpleListNode<T>* hNode = getNode(index);
    return hNode ? hNode->data : T();
}

template<typename T>
int SimpleList<T>::search(T obj) {
    if (compare == NULL) return -1;

    int i = 0;

    SimpleListNode<T>* hNode = getNode(i);
    bool found               = compare(obj, hNode->data) == 0;

    while (!found && i < listSize) {
        i++;
        hNode = getNode(i);
        found = compare(obj, hNode->data) == 0;
    }

    return found ? i : -1;
}

template<typename T>
int SimpleList<T>::searchNext(T obj) {
    if (compare == NULL) return -1;

    int i = lastIndexGot;

    SimpleListNode<T>* hNode = lastNodeGot;
    bool found               = compare(obj, hNode->data) == 0;

    while (!found && i < listSize) {
        i++;
        hNode = getNode(i);
        found = compare(obj, hNode->data) == 0;
    }

    return found ? i : -1;
}

template<typename T>
int SimpleList<T>::binSearch(T obj, int lowerEnd, int upperEnd) {
    if ((compare == NULL) || !sorted) return -1;

    int res;
    int mid = (lowerEnd + upperEnd) / 2;

    SimpleListNode<T>* hNode = listBegin;
    int hIndex               = 0;

    while (lowerEnd <= upperEnd) {
        hNode  = lastNodeGot;
        hIndex = lastIndexGot;
        res    = compare(obj, getNode(mid)->data);

        if (res == 0) {
            return mid;
        } else if (res < 0) {
            // when going left, set cached node back to previous cached node
            lastNodeGot  = hNode;
            lastIndexGot = hIndex;
            isCached     = true;

            upperEnd = mid - 1;
            mid      = (lowerEnd + upperEnd) / 2;
        } else if (res > 0) {
            lowerEnd = mid + 1;
            mid      = (lowerEnd + upperEnd) / 2;
        }
    }

    return -1;
}

template<typename T>
int SimpleList<T>::binSearch(T obj) {
    return binSearch(obj, 0, listSize - 1);
}

template<typename T>
int SimpleList<T>::count(T obj) {
    if (compare == NULL) return -1;

    int c = 0;

    for (int i = 0; i < listSize; i++) {
        if (compare(obj, getNode(i)->data) == 0) c++;
    }

    return c;
}

template<typename T>
T SimpleList<T>::pop() {
    if (listSize <= 0) return T();

    T data = listEnd->data;
    remove(listSize - 1);
    return data;
}

template<typename T>
T SimpleList<T>::shift() {
    if (listSize <= 0) return T();

    T data = listBegin->data;
    remove(0);
    return data;
}

template<typename T>
void SimpleList<T>::clear() {
    while (listSize > 0) remove(0);
}

template<typename T>
void SimpleList<T>::swap(int x, int y) {
    // only continue when the index numbers are unequal and at least 0
    if ((x != y) && (x >= 0) && (y >= 0)) {
        if (x > y) { // the first index should be smaller than the second. If not, swap them!
            int h = x;
            x = y;
            y = h;
        }

        // When data is small, copy it
        if (sizeof(T) < 24) {
            SimpleListNode<T>* nodeA = getNode(x);
            SimpleListNode<T>* nodeB = getNode(y);
            T h                      = nodeA->data;
            nodeA->data = nodeB->data;
            nodeB->data = h;
        }

        // otherwise change the pointers
        else {
            // Example: a -> b -> c -> ... -> g -> h -> i
            //          we want to swap b with h
            SimpleListNode<T>* nodeA = getNode(x - 1);                      // x.prev
            SimpleListNode<T>* nodeB = getNode(x);                          // x
            SimpleListNode<T>* nodeC = getNode(x + 1);                      // x.next
            SimpleListNode<T>* nodeG = y - 1 == x ? nodeB : getNode(y - 1); // y.prev
            SimpleListNode<T>* nodeH = getNode(y);                          // y
            SimpleListNode<T>* nodeI = getNode(y + 1);                      // y.next

            // a -> h -> i      b -> c -> ... -> g -> h -> i
            if (nodeA) nodeA->next = nodeH;
            else listBegin = nodeH;

            // a -> h -> c -> ... -> g -> h -> i    b -> i
            if (nodeH != nodeC) // when nodes between b and h exist
                nodeH->next = nodeC;
            else nodeH->next = nodeB;

            // a -> h -> i      b -> i
            nodeB->next = nodeI;

            if (!nodeI) listEnd = nodeB;

            // a -> h -> c -> ... -> g -> b -> i
            if (nodeG != nodeB) // when more than 1 nodes between b and h exist
                nodeG->next = nodeB;
        }
    }
}

template<typename T>
void SimpleList<T>::sort() {
    if ((compare == NULL) || sorted) return;

    // selection sort

    int indexH;                 // index of node i
    int indexMin;               // index of next minimum node

    SimpleListNode<T>* nodeMin; // next minimum node
    SimpleListNode<T>* nodeH;   // helper node at index j

    for (int i = 0; i < listSize - 1; i++) {
        nodeMin  = getNode(i);
        indexH   = i;
        indexMin = i;

        for (int j = i + 1; j < listSize; j++) {
            nodeH = getNode(j);

            if (compare(nodeMin->data, nodeH->data) > 0) {
                nodeMin  = nodeH;
                indexMin = j;
            }
        }
        swap(indexH, indexMin);
    }

    sorted = true;
}

template<typename T>
bool SimpleList<T>::isSorted() {
    return sorted;
}

#endif // ifndef SimpleList_h