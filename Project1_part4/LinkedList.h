#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
using namespace std;

template <typename T>
class LinkedList{
public:
    struct Node{
        T data; //data storing
        Node* next;  //pointer to next node
        Node* prev;  //pointer to previous node
    };

    //add information to the container
    void AddHead(const T& data);
    void AddTail(const T& data);
    void AddNodesHead(const T* data, unsigned int count);
    void AddNodesTail(const T* data, unsigned int count);

    //get some information about the container
    unsigned int NodeCount() const;

    //see the data in the container
    void PrintForward() const;
    void PrintReverse() const;

    //Getting the head and tail nodes
    Node* Head();
    const Node* Head() const;
    Node* Tail();
    const Node* Tail() const;

    //Getting a specific node based on an index
    const Node* GetNode(unsigned int index) const;
    Node* GetNode(unsigned int index);
    const T& operator[](unsigned int index) const;
    T& operator[](unsigned int index);

    //Finding the FIRST node based on a value
    const Node* Find(const T& data)const;
    Node* Find(const T& data);

    //Finding ALL nodes based on a value
    void FindAll(vector<Node*>& outData, const T& value) const;

    //Interation
    void InsertAfter(Node* node, const T& data);
    void InsertBefore(Node* node, const T& data);
    void InsertAt(const T& data, unsigned int index);

    //equality operator
    bool operator==(const LinkedList<T>& rhs) const;

    //remove
    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(const T& data);
    bool RemoveAt(unsigned int index);
    void Clear();

    //print recursive
    void PrintForwardRecursive(Node* node);
    void PrintReverseRecursive(Node* node);

    LinkedList();  //default constructor
    //BIG THREE
    LinkedList(const LinkedList<T>& list); //copy constructor
    LinkedList<T>& operator=(const LinkedList<T>& rhs); //assignment operator
    ~LinkedList();  //destructor


private:
    Node* head;  //node pointer to the head
    Node* tail;  //node pointer to the tail
    int nodeCounter;  //number of nodes
};


//---------PART 1-----------//

//default constructor
template <typename T>
LinkedList<T>::LinkedList(){
    head = nullptr;
    tail = nullptr;
    nodeCounter = 0;
}

//destructor
template <typename T>
LinkedList<T>::~LinkedList(){
    //References:
    //iterating while loop reference: TA Alexis Doughtery
    //steps for deleting each node:  Prof.Fox dynamic array lecture, Linked List lectures
    // Zybooks 11.1

    tail = nullptr;   //assign tail as null

    //loop through to delete all nodes in the list
    while(nodeCounter > 0){   //while current node (head) is not null (iterate through the list)

        //1. get pointer to the next node of the one to delete
        Node* currNode = head->next;   //assign new node to next node after head

        //2. delete node
        delete head;   //delete head

        //3. move head position
        head = currNode;    //assign head to current node

        nodeCounter--;   //decrement node counter
    }

}


//create a new Node at the front of the list to store the passed in parameter
template <typename T>
void LinkedList<T>::AddHead(const T& data){
    //Reference for AddHead function steps:
    //Prof. Fox Linked List Operations lecture
    //Zybooks: 10.5
    //T.A: Alexis Dougherty lab sessions & Blake office hours

    //1. Initializing a node
    Node* newNode = new Node;  //create new node;
    newNode->data = data;   //assign the data of new node to the parameter data
    newNode->next = nullptr;   //assign next of the new node to null

    if(nodeCounter > 0){   //if the list is not empty

        Node* headNode = head;   //create node pointer to the head

        //2. Set new node's next node to the current start of the list(i.e head)
        newNode->next = headNode;   //next node of the new node is the current head
        headNode->prev = newNode;   //the previous node of head is the new node (doubly-linked)

        //3. Set current head pointer to new node
        head = newNode;   //assign the current head to new node

        nodeCounter++;  //increment number of nodes
    }
    if(nodeCounter == 0){    //if list is empty and there is no head

        head = newNode;   //assign current head to the new node
        tail = newNode;   //assign current tail to the new node

        nodeCounter++;  //increment number of nodes
    }
}

//create a new Node at the end of the list to store the passed in parameter
template<typename T>
void LinkedList<T>::AddTail(const T& data) {
    //Reference for AddTail function steps:
    //Prof. Fox Linked List lectures
    //Zybooks: 10.5
    //T.A: Alexis Dougherty lab sessions & Blake office hours

    //1. Initializing a node
    Node* newNode = new Node;   //create new node
    newNode->data = data;   //assign data value of new node to data
    newNode->prev = nullptr;   //assign previous node of new node to null

    if(nodeCounter > 0){   //if list is full

        Node* endNode = tail; //create node pointer to the end of the node

        //2. Set new node's next node to the current end of the list(i.e tail)
        newNode->prev = endNode;    //previous node of new node is tail
        endNode->next = newNode;   //next node of tail is new node  (doubly-linked)

        //3. Set current tail pointer to new node
        tail = newNode;   //current tail is new node
        tail->next = nullptr;   //next node of new node is null   (doubly-linked)

        nodeCounter++;  //increment number of nodes
    }
    if(nodeCounter == 0){  //if list is empty and there is no tail

        tail = newNode;   //assign current tail to the new node
        head = newNode;   //assign current head to the new node

        nodeCounter++;  //increment number of nodes
    }
}

//Given an array of values, insert a node for each of those at the beginning of the list
template<typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {
    //Zybooks Reference for AddNodesHead function: 6.2 & 7.8
    //TA Reference: Alexis Doughtery, Blake

    unsigned int currNodes = count - 1;   //current index for number of nodes
    while(currNodes > 0){    //if current index of node is greater than 0 (not empty)
        AddHead(data[currNodes]);  //add to beginning of the list using AddHead function

        currNodes--;  //decrement current number of nodes
    }
    AddHead(data[0]);   //add node at index 0 to beginning of the list
}

//Given an array of values, insert a node for each of those at the end of the list
template<typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {
    //Zybooks Reference for AddNodesTail function: 6.2 & 7.8
    //TA Reference: Alexis Doughtery, Blake

    unsigned int currNodes = 0;   //current index for number of nodes
    while(currNodes < count){   //if current index of node is less than given count
        AddTail(data[currNodes]);   //add to end of the list using AddTail function
        currNodes++;    //increment current number of nodes
    }
}

//How many things are stored in this list?
template<typename T>
unsigned int LinkedList<T>::NodeCount() const {
    return nodeCounter;  //return number of current nodes
}

//Iterator through all of the nodes and print out their values, one a time
template<typename T>
void LinkedList<T>::PrintForward() const {
    //Reference for PrintForward function steps:
    //Prof. Fox Linked List lectures
    //T.A: Alexis Dougherty lab sessions
    //Zybooks: 10.5

    Node* currNode = head;   //assign current node to head
    T currData;   //create variable for current data

    //iterating while loop reference: TA Alexis Doughtery
    while(currNode != nullptr){   //current node is not null
        currData = currNode->data;   //assign current data to current node's data

        cout << currData << endl;  //print current data

        currNode = currNode->next;   //assign current node to current node's next node
    }
}

//Iterator through all of the nodes and print out their values, one a time in opposite way
template<typename T>
void LinkedList<T>::PrintReverse() const {
    //Reference for PrintReverse function steps:
    //T.A: Alexis Dougherty lab sessions
    //Zybooks: 10.5

    Node* currNode = tail;   //assign current node to tail
    T currData;   //create variable for current data

    //iterating while loop reference: TA Alexis Doughtery
    while(currNode != nullptr){  //current node is not null
        currData = currNode->data;   //assign current data to current node's data

        cout << currData << endl;  //print current data

        currNode = currNode->prev;   //assign current node to current node's previous node
    }
}


//---------PART 2------------//


//Returns the head pointer
template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
    return head;
}

//Returns the head pointer
template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
    return head;
}

//Returns the tail pointer
template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
    return tail;
}

//Returns the tail pointer
template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
    return tail;
}


//Given an index, return a pointer to the node at that index
template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
    //Reference for GetNode function:
    // steps given in project file
    // iterator loop: TA Alexis Doughtery

    Node* currNode = head;       //assign current node as head
    unsigned int currIndex = 0;  //initialize a current node index

    if(index >= nodeCounter || index < 0){   //index is greater than number of nodes or index is less than 0
        throw out_of_range("index is out of range");
    }

    while(currNode != nullptr){   //while the current node index is not equal to null
        if(currIndex == index){   //if current index is equal to index in parameter
            return currNode;  //return current node
        }
        currNode = currNode->next;    //assign current node to current node's next node
        currIndex++;   //increment current node index
    }

    return currNode;  //return pointer to current node
}



//Given an index, return a pointer to the node at that index
template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
    //Reference for GetNode function:
    // steps given in project file
    // iterator loop: TA Alexis Doughtery

    Node* currNode = head;       //assign current node as head
    unsigned int currIndex = 0;  //initialize a current node index

    if(index >= nodeCounter || index < 0){   //index is greater than number of nodes or index is less than 0
        throw out_of_range("index is out of range");
    }

    while(currNode != nullptr){   //while the current node index is not equal to null
        if(currIndex == index){   //if current index is equal to index in parameter
            return currNode;  //return current node
        }
        currNode = currNode->next;    //assign current node to current node's next node
        currIndex++;   //increment current node index
    }

    return currNode;  //return pointer to current node
}


// Takes an index, and returns data from the indexth node
template<typename T>
const T &LinkedList<T>::operator[](unsigned int index) const {
    //Reference:
    // steps given in project file

    if(index >= nodeCounter || index < 0){   //index is greater than number of nodes or index is less than 0
        throw out_of_range("index is out of range");
    }

    Node* currNode = GetNode(index);  //assign current node's pointer to the node returned from the GetNode fuction

    return currNode->data;  //return current node's data
}



// Takes an index, and returns data from the indexth node
template<typename T>
T &LinkedList<T>::operator[](unsigned int index) {
    //Reference:
    // steps given in project file

    if(index >= nodeCounter || index < 0){   //index is greater than number of nodes or index is less than 0
        throw out_of_range("index is out of range");
    }

    Node* currNode = GetNode(index);  //assign current node's pointer to the node returned from the GetNode fuction

    return currNode->data;  //return current node's data
}



//Find the first node with a data value matching the passed in parameter
template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {
//Reference for writing Find function: Prof. Fox linked list lectures
//steps given in project file

    Node* currNode = head;   //current node is head
    T currData = currNode->data;    //current data is the current node's data
    int currIndex = 1;   //current index

    while(currData != data){    //while current node's data is not equal to data in parameter
        if(currIndex == nodeCounter){    //if current index is at last node
            currNode = nullptr;     //assign current node to null
            return currNode;    //return nullptr
        }
        currNode = currNode->next;   //assign current node to current node's next node
        currData = currNode->data;    //current data is the current node's data
        currIndex++;   //increment current index
    }


    return currNode;    //return pointer to current node
}



//Find the first node with a data value matching the passed in parameter
template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {
//Reference for writing Find function: Prof. Fox linked list lectures
//steps given in project file

    Node* currNode = head;   //current node is head
    T currData = currNode->data;    //current data is the current node's data
    int currIndex = 1;   //current index

    while(currData != data){    //while current node's data is not equal to data in parameter
        if(currIndex == nodeCounter){  //if current index is at last node
            currNode = nullptr;    //assign current node to null
            return currNode;    //return nullptr
        }
        currNode = currNode->next;   //assign current node to current node's next node
        currData = currNode->data;    //current data is the current node's data
        currIndex++;   //increment current index
    }

    return currNode;    //return pointer to current node
}

//Find all nodes which match the passed in parameter value, and store a pointer to
//that node in the passed in vector
template<typename T>
void LinkedList<T>::FindAll(vector<LinkedList::Node*>& outData, const T& value) const {
//Reference for writing FindAll function: Prof. Fox linked list lectures
//steps given in project file

    Node* currNode = head;    //current node is head
    unsigned int currIndex = 0;    //assign current index to 0
    T currData;   //current data is current node's data

//Reference for while loop: TA Alexis Doughtery
    while(currNode != nullptr ){    //while current nodes is not null(iterate through the list)
        currData = currNode->data;  //assign current data to current node's data

        if(currData == value){    //if current node's data matches the value in parameter
            outData.push_back(currNode);   //store current node in the vector
            currNode = currNode->next;   //assign current node to current node's next node
        }
        if (currData != value){  //if current node's data is not equal to value in parameter
            currNode = currNode->next;   //assign current node to current node's next node
        }

        currIndex++;   //increment current index
    }
}


//Copy constructor
//Sets "this" to a copy of the passed in LinkedList
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list){
    //References for copy constructor:
    //Alexis Dougherty lab sessions
    //Big three lecture
    //Zybooks: 11.2

    head = nullptr;   //set current head to null
    tail = nullptr;   //set current tail to null
    nodeCounter = 0;  //set current node counter to 0

    Node* currNode = list.tail;   //assign current node to parameter list's tail
    this->head = list.head;    //assign current head to parameter list's head
    this->nodeCounter = 0;    //assign current number of nodes to 0
    T currData;   //declare a variable for current node's data

    //Reference for writing this loop: TA Alexis Doughtery
    while (currNode != nullptr) {     //while current node is not null (iterate through the list)
        currData = currNode->data;   //current data is current node's data

        AddHead(currData);     //add to head of list the current data
        currNode = currNode->prev;   //assign current node to current node's next node

        nodeCounter++;   //increment number of nodes
    }

}

//copy assignment operator
template<typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T>& rhs) {
    //References for copy assignment operator:
    //Alexis Dougherty lab sessions
    //Big three lecture
    //1,2,3 steps reference: Zybooks: 11.3


    if(this != &rhs) {  //1.don't self assign

        //2. Delete old data

        int currIndex = 0;  //initialize current index
        while (currIndex < nodeCounter) {
            //1. get pointer to the next node of the one to delete
            Node* currNode = head->next;   //assign new node to next node after head

            //2. delete node
            delete head;   //delete head

            //3. move head position
            head = currNode;    //assign head to current node

            currIndex++;   //increment current index
        }
        tail = nullptr;  //tail is null
        nodeCounter = 0;   //number of nodes are 0


        //3. Copy rhs list to current list

        Node* currNode = rhs.tail;   //assign current node to parameter list's tail
        this->head = rhs.head;    //assign current head to parameter list's head
        this->nodeCounter = 0;    //assign current number of nodes to 0
        T currData;   //declare a variable for current node's data

        //Reference for writing this loop: TA Alexis Doughtery
        while (currNode != nullptr) {     //while current node is not null (iterate through the list)
            currData = currNode->data;   //current data is current node's data

            AddHead(currData);     //add to head of list the current data
            currNode = currNode->prev;   //assign current node to current node's next node

            nodeCounter++;   //increment number of nodes
        }
    }

    return *this;
}



//----------PART 3----------//

//Given a pointer to a node, create a new node to store the passed in value, before the indicated node
template<typename T>
void LinkedList<T>::InsertBefore(LinkedList::Node* node, const T& data) {
    //References for this function: Prof Fox Linked List lectures
    //iterating while loop reference: TA Alexis Doughtery
    //Zybooks: 10.5

    //Reference for writing the steps: T.A. Blake office hours

    //1. create new node
    Node* newNode = new Node;   //create new node
    newNode->data = data;    //assign given data value to new node's data value

    //2.find node before the node is the parameter
    Node* prevNode = head;  //assign new node to head
    while(prevNode->next != node){  //while current node's next node is not the node given in parameter
        prevNode = prevNode->next;   //assign current node as current nodes next node
    }

    //3. insert new node
    prevNode->next = newNode;  //assign previous node's next node is new node
    newNode->next = node;  //assign new node's next node is given node

    nodeCounter++;   //increment number of nodes
}

//Given a pointer to a node, create a new node to store the passed in value, after the indicated node
template<typename T>
void LinkedList<T>::InsertAfter(LinkedList::Node* node, const T& data) {
    //References for this function: Prof Fox Linked List lectures
    //iterating while loop reference: TA Alexis Doughtery
    //Zybooks: 10.5

    //Reference for writing the steps: T.A. Blake office hours

    //1. create new node
    Node* newNode = new Node;   //create new node
    newNode->data = data;    //assign given data value to new node's data value

    //2. find node after the node is the parameter
    Node* nextNode = head;  //assign new node to head
    while(nextNode != node){  //while current node's is not the node given in parameter
        nextNode = nextNode->next;   //assign current node as current nodes next node
    }
    nextNode = nextNode->next;   //assign current node as parameter's next node

    node->next = newNode;  //assign given node's next node is new node
    newNode->next = nextNode;     //assign new node's next node is the current node found

    nodeCounter++;  //increment number of nodes
}


//Inserts a new Node to store the first parameter, at the index-th location
template<typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {
    //References for this function: Prof Fox Linked List lectures
    //iterating while loop reference: TA Alexis Doughtery
    //Zybooks: 10.5


    if(index > (unsigned int) nodeCounter || index < 0){   //index is greater than number of nodes or index is less than 0
        throw out_of_range("index is out of range");
    }
    if(index == 0){   //if index is 0
        AddHead(data);     //use AddHead function to add to the front of the list
    }
    if(index > 0){

        //Reference for writing the steps: T.A. Blake office hours
        //1.create new node
        Node* newNode = new Node;   //create new node
        newNode->data = data;    //assign given data value to new node's data value

        //2.find node before the node at the index
        Node* prevNode = head;  //previous node before new node
        unsigned int currIndex = 0;  //initialize a current node index
        while(currIndex != (index-1)){   //while the current node index is not equal to parameter index
            prevNode = prevNode->next;    //assign current node to current node's next node
            currIndex++;   //increment current node index
        }

        //3.find node at the index
        Node* currNode = head;       //assign current node as head
        currIndex = 0;
        while(currIndex != index){   //while the current node index is not equal to parameter index
            currNode = currNode->next;    //assign current node to current node's next node
            currIndex++;   //increment current node index
        }

        newNode->next = currNode;   //assign new node's next node as the node at the index
        prevNode->next = newNode;   //assign previous node's next node as new node

        nodeCounter++;  //increment number of nodes
    }
}

//Overloaded equality operator
template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
    //References for this function: Prof Fox operator overloading lectures
    //iterating while loop reference: TA Alexis Doughtery
    //Zybooks: 9.13

    bool match = true;  //assign bool variable to true

    if(nodeCounter != rhs.nodeCounter){  //if number of nodes in current list don't match the number of nodes is rhs
        match = false;
        return match;   //return false
    }

    Node* currNode = head;   //assign current node to head
    T currentData = currNode->data;  //assign current data to data of current node

    Node* listNode = rhs.head;    //assign new node to rhs list head
    T listData = listNode->data;   //assign current list data to data of current rhs node data

    while(currNode != nullptr){    //current node is not null
        if(currentData == listData){     //if current node data is equal to list node data
            match = true;    //assign variable as true
        }
        if(currentData != listData){    //if current node data is NOT equal to list node data
            match = false;    //assign variable as false
            return match;    //return false
        }
        currNode = currNode->next;    //assign current node as current node's next node
        listNode = listNode->next;    //assign current list node as current list node's next node
    }

    return match; //return variable
}




//------------PART 4-------------//

//Deletes the first Node in the list
template<typename T>
bool LinkedList<T>::RemoveHead() {
    //Reference for steps: Prof.Fox linked list operations lecture

    bool remove = true;

    if(head != nullptr) {
        //1. Create a pointer to node after the head
        Node* newNode = head;
        newNode = newNode->next;

        //2. Delete head node
        delete head;

        //3. set the head node to the newNode pointer
        head = newNode;

        nodeCounter--;  //decrement number of nodes

        remove = true;
    }
    else {
        remove = false;
    }

    return remove;   //return true
}

//Deletes the last Node in the list
template<typename T>
bool LinkedList<T>::RemoveTail() {
    //Reference for steps: Prof.Fox linked list operations lecture

    bool remove = true;


    if(tail != nullptr) {
        //1. Create a pointer to node before the tail
        Node* newNode = tail;
        newNode = newNode->prev;

        //2. Delete tail node
        delete tail;

        //3. set the tail node to the newNode pointer
        tail = newNode;
        nodeCounter--;  //decrement number of nodes

        if(tail == nullptr){   //if tail is null
            return remove;    //return to bool variable
        }
        if(tail != nullptr){    //else
            newNode->next = nullptr;    //next node is null
            return remove;    //return to bool variable
        }

    }
    else{
        remove = false;    //return false
    }


    return remove;   //return bool variable
}


//Remove ALL Nodes containing values matching that of the passed-in parameter
template<typename T>
unsigned int LinkedList<T>::Remove(const T& data) {
    //Reference to write this function:
    //Prof. Fox linked list operations lecture

    int nodesDeleted = 0;   //initialize number of nodes to be deleted

    Node* currNode = head;   //assign current node to head
    T currData;  //declare variable for current node's data

    while(currNode != nullptr){     //while current node is not null

        currData = currNode->data;   //assign current data to current node's data

        if(currData == data){   //if current node's data matches the data in the parameter

            //1. Get a pointer to the node before AND after of the node to delete

            Node* newNode = currNode;    //assign new node to current node
            Node* prevNode = currNode;   //assign new node to current node

            //2. Assign values to previous and next node of the node to be delete

            prevNode = currNode->prev;   //assign previous node to current node's previous node
            newNode = currNode->next;    //assign new node to current node's next node

            //3. delete current node
            delete currNode;

            //4. assign current node to new node (i.e the next node)
            currNode = newNode;
            prevNode->next = currNode;    //assign next node of previous node to current node

            nodesDeleted++;   //increment number of nodes deleted
            nodeCounter--;   //decrement number of nodes
        }

        currNode = currNode->next;     //assign current node to current node's next node
    }

    return nodesDeleted;    //return number of nodes delete
}



//Deletes the index-th Node from the list
template<typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
//Reference to write this function:
    //Prof. Fox linked list operations lecture

    bool remove = true;    //set variable as true
    unsigned int currIndex = 0;     //initialize current index

    if(index > (unsigned int)nodeCounter || index < 0){    //if index is out of range
        remove = false;
        return remove;    //return false
    }
    else {

        Node* currNode = head;  //assign current node to head

        while (currIndex < (unsigned int)nodeCounter) {    //while current index is less than number of nodes

            if (currIndex == (index - 1)) {
                //1. Get a pointer to the node before AND after the node to delete

                Node* prevNode = currNode;   //assign new node to current node
                Node* nextNode = currNode->next->next;   //assign new node to current node's next next node


                //2. Assign value of previous node to the next node of the node to be deleted
                currNode = currNode->next;    //current node is current node's next node(index)
                prevNode->next = nextNode;    //assign previous node's next node is the current node's next node

                //3. delete current node
                delete currNode;

                nodeCounter--;   //decrement number of nodes

                return remove;   //return true
            }
            currNode = currNode->next;     //assign current node to current node's next node
            currIndex++;    //increment current index
        }
    }

    return remove;   //return bool variable
}

//Deletes all Nodes
template<typename T>
void LinkedList<T>::Clear() {
    //References:
    //iterating while loop reference: TA Alexis Doughtery
    //steps for deleting each node:  Prof.Fox dynamic array lecture, Linked List lectures
    // Zybooks 11.1

    tail = nullptr;   //assign tail as null

    //loop through to delete all nodes in the list
    while(nodeCounter > 0){   //while current node (head) is not null (iterate through the list)

        //1. get pointer to the next node of the one to delete
        Node* currNode = head->next;   //assign new node to next node after head

        //2. delete node
        delete head;   //delete head

        //3. move head position
        head = currNode;    //assign head to current node

        nodeCounter--;   //decrement node counter
    }
}


//prints data forward recursivley
template<typename T>
void LinkedList<T>::PrintForwardRecursive(LinkedList::Node* node) {
    //Reference: Zybooks 14.2, 14.5
    //1. Base case
    if(node->next == nullptr){    //if node is at tail
        cout << tail->data << endl;     //print data at tail
    }
        //2. recursive
    else{
        cout << node->data << endl;    //print data of node
        PrintForwardRecursive(node->next);   //go to next node
    }

}

//prints data backward recursivley
template<typename T>
void LinkedList<T>::PrintReverseRecursive(LinkedList::Node* node) {
    //Reference: Zybooks 14.2, 14.5
    //1. Base case
    if(node->prev == nullptr){      //if node is at head
        cout << head->data << endl;    //print data at head
    }
        //2. Recursive
    else{
        cout << node->data << endl;    //print data of node
        PrintReverseRecursive(node->prev);     //go to prev node
    }
}

