// ---------------------------------------------------------
/*
	File: scheduler.h
	Package: SchedulerSim

	Author: John Pecarina
	Date: 17 Jul 15

	System: Linux Ubuntu 14.04
	Compiler: g++
	External Files Required: N/A

	Description: Class header for the scheduler.

	License/Copyright: None
*/
//---------------------------------------------------------
// Compilation wrapper to compile once 
#ifndef SCHEDULER_H
#define SCHEDULER_H

/*--------------------------------------------------------------------------*/
// INCLUDES 
/*--------------------------------------------------------------------------*/
#include <stdint.h>
#include <sys/types.h>
#include "SchedSim.h"
#include "TCB.h"
#include "TCB_Queue.h"

/*--------------------------------------------------------------------------*/
// SCHEDULER
/*--------------------------------------------------------------------------*/

class Scheduler {


private:

	long last_run;
	TCBnode* idle;
	TCBnode* last;

public:

	Scheduler();	
	void run_scheduler();
	void load_new_job(uint8_t pid, char* program);
	void load_last_job(uint8_t pid, char* end);
	//Declare the new, ready, wait and terminated queues
	TCB_Queue* nq; //new_queue;
	TCB_Queue* rq; //ready_queue;
	TCB_Queue* wq; //wait_queue;
	TCB_Queue* tq; //terminated_queue;
	
	TCBnode** get_idle_TCBnode();
	TCBnode** get_last_TCBnode();
	void set_idle_TCBnode(TCBnode ** _tcb_node);
	void set_last_run(long l);
	long get_last_run();

};
	

#endif
