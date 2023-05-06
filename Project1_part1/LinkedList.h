#pragma once
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template <typename T>
class LinkedList{
public:
    struct Node{
        T data; //data storing
        Node* next;  //pointer to next node
        Node* previous;  //pointer to previous node
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

    LinkedList();  //default constructor
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
    //Steps reference: Prof.Fox dynamic array lecture, Linked List lectures and Zybooks 11.1

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
        headNode->previous = newNode;   //the previous node of head is the new node (doubly-linked)

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
    newNode->previous = nullptr;   //assign previous node of new node to null

    if(nodeCounter > 0){   //if list is full

        Node* endNode = tail; //create node pointer to the end of the node

        //2. Set new node's next node to the current end of the list(i.e tail)
        newNode->previous = endNode;    //previous node of new node is tail
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
    //TA: Alexis Doughtery, Blake

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
    //TA: Alexis Doughtery, Blake

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

        currNode = currNode->previous;   //assign current node to current node's previous node
    }
}
