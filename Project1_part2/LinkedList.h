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
    //Steps reference:
    // Prof.Fox dynamic array lecture, Linked List Operations lecture, TA Alexis Doughtery and Zybooks 11.1

    tail = nullptr;   //assign tail as null

    //loop through to delete all nodes in the list
    while(nodeCounter > 0){   //more the 0 nodes in the list

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
        currIndex++;   //increment current index
    }

    if(currData == data){    //if current node data is equal to the data in parameter
        return currNode;    //return pointer to current node
    }
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
        currIndex++;   //increment current index
    }

    if(currData == data){    //if current node data is equal to the data in parameter
        return currNode;    //return pointer to current node
    }
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
    while(currNode != nullptr){     //while current node is not null (iterate through the list)
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

        int currIndex = 0;
        tail = nullptr;  //assign tail to null
        while (currIndex < nodeCounter) {

            //1. get pointer to the next node of the one to delete
            Node* currNode = head->next;   //assign new node to next node after head

            //2. delete node
            delete head;   //delete head

            //3. move head position
            head = currNode;    //assign head to current node

            currIndex++;   //increment current index
        }
        nodeCounter = 0;


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


