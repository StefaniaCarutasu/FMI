// ---------------------------------------------------------
/*
	File: CPU.h
	Package: SchedulerSim

	Author: John Pecarina
	Date: 17 Jul 15

	System: Linux Ubuntu 14.04
	Compiler: g++

	Description: Class header for the CPU.
	License/Copyright: None
*/
//---------------------------------------------------------
// Compilation wrapper to compile once 
#ifndef TCB_H
#define TCB_H

/*--------------------------------------------------------------------------*/
// INCLUDES 
/*--------------------------------------------------------------------------*/
#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
#include "SchedSim.h"
//---------------------------------------------------------
/*  DATA STRUCTURES				*/
//---------------------------------------------------------
typedef struct TCB TCB;

struct TCB{
	uint8_t 	pid;            //Process ID
	uint8_t 	result;			//Last result of the processor
	uint8_t		state_flags;    //Process State Flags
	char* stack_pointer;		//SP and PC are addresses
	char* program_ctr;
	unsigned int register1;		//could be uint16_t
	unsigned int register2;		//could be uint16_t
	struct TCB* parent;         //Parent pointer
	struct TCB* child_list;      //Pointer to list of children
	struct TCB* sibling_list;    //Pointer to list of siblings
	char* open_file_list;
	unsigned long create_time;	 //time this was put in the new queue
	unsigned long arrive_time;   //time this was put in the ready queue
	unsigned long wait_time;	 //time the processor was first obtained
	unsigned long response_time; //time of the first voluntary return off the processor
	unsigned long turnaround_time;  //time this was finished
	#ifdef REAL_TIME
	unsigned long deadline;		 //time this must finish by
	#endif
};

class TCBnode{
	public:
		TCB tcb;	//TCB struct to hold the TCB information
		TCBnode* next;	//Pointer to the next node in the queue
		TCBnode* prev;	//Pointer to the previous node in the queue
		TCBnode(uint8_t	pid,	//Constructor for the TCBNode
			char*	pc,
			unsigned int	r1,
			unsigned int	r2,
			struct TCB* parent,
			struct TCB* childList,
			struct TCB* siblingList,
			char*	openFilesList,
			unsigned long	createTime
			#ifdef REAL_TIME
			, unsigned long	deadline
			#endif
			)	//Constructor for the TCBNode
        	{
        		//Set all the variables of the TCB
			this->next=NULL;
			this->prev=NULL;
			this->tcb.pid=pid;
			this->tcb.result = 0;
			this->tcb.stack_pointer=0;	
			this->tcb.program_ctr=pc;
			this->tcb.register1=r1;
			this->tcb.register2=r2;
			this->tcb.parent=parent;
			this->tcb.child_list=childList;
			this->tcb.sibling_list=siblingList;	
			this->tcb.open_file_list=openFilesList;
			this->tcb.create_time=createTime;
			this->tcb.arrive_time=0;
			this->tcb.wait_time=ULONG_MAX;
			this->tcb.response_time=ULONG_MAX;
			this->tcb.turnaround_time=ULONG_MAX;
			#ifdef REAL_TIME
			this->tcb.deadline=deadline;
			#endif
		}

	};

#endif // TCB

