// ---------------------------------------------------------
/*
    File: scheduler.h
    Package: SchedulerSim

    System: Linux Ubuntu 14.04
    Compiler: g++
    External Files Required: N/A

    Description: Class header for the scheduler.

    License/Copyright: None
*/
//---------------------------------------------------------
// Compilation wrapper to compile once 
#ifndef TCB_QUEUE_H
#define TCB_QUEUE_H
/*--------------------------------------------------------------------------*/
// INCLUDES 
/*--------------------------------------------------------------------------*/
#include "TCB.h"
//---------------------------------------------------------
/*  CLASS DEFINITION					*/
//---------------------------------------------------------
class TCB_Queue
{
private:
    int max_size;               //Maximum max_size of the queue
    int size;              //The current number of nodes in the queue
    TCBnode* head;          //Pointer to the head of the queue
    TCBnode* tail;          //Pointer to the tail of the queue

public:
    TCB_Queue(int max_size);    //Constructor for the TCB_Queue class
    virtual ~TCB_Queue();   //Destructor for the TCB_Queue class

    //This function adds the new TCB node to the tail of the TCB_queue
    int enqueue(TCBnode* _tcbn);

    //This function will remove the TCB node from the head
    TCBnode* dequeue();

    //This function displays the queue
    void display();

    //Getters and Setters for private variables
    TCBnode* getTail();
    TCBnode* getHead();
    int get_max_size();
    int set_max_size(int _max_size);
    int get_size();
    int set_size(int _size);

    void dealloc();

    //This function creates a new TCB node
    TCBnode* createTCBnodePID(uint8_t pid, char* pc);

    //This function creates a new TCB node
    TCBnode* createTCBnode(uint8_t pid,
        char* pc,
        unsigned int r1,
        unsigned int r2,
        TCB* parent,
        TCB* childList,
        TCB* siblingList,
        char* openFilesList,
        unsigned long	createTime
#ifdef REAL_TIME
        , unsigned long	deadline
#endif
    );

};

#endif // TCB_QUEUE_H
