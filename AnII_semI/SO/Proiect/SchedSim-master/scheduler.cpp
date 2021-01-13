// ---------------------------------------------------------
/*
	File: scheduler.cpp
	Package: SchedulerSim

	Author: John Pecarina
	Date: 17 July 2015

	Description: A simple dispatcher function for a computer.
	License/Copyright: None
*/
//---------------------------------------------------------
/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"
#include "TCB.h"
#include "TCB_Queue.h"
//Use the standard namespace
using namespace std;

/*--------------------------------------------------------------------------*/
/* CLASS METHODS */
/*--------------------------------------------------------------------------*/
   
	Scheduler::Scheduler(){
		//Intialize the new, ready, wait and terminated queues
		nq = new TCB_Queue(MAX_QUEUE_SIZE); //new_queue;
		rq = new TCB_Queue(MAX_QUEUE_SIZE); //ready_queue;
		wq = new TCB_Queue(MAX_QUEUE_SIZE); //wait_queue;
		tq = new TCB_Queue(MAX_QUEUE_SIZE); //terminated_queue;
		last_run = 0;

		//build an idle TCB node
		char *nop = "N";	
		idle = tq->createTCBnodePID(0, nop);
	}

	void Scheduler::load_new_job(uint8_t pid, char* program){
		//Fill the new queue with jobs
		TCBnode* node;
		node=nq->createTCBnodePID(pid, program);
		nq->enqueue(node);
		//nq->display();
	}

	void Scheduler::load_last_job(uint8_t pid, char* program){
		//Set the last TCB (which will exit when needed)
		last=nq->createTCBnodePID(pid, program);
	}

	void Scheduler::run_scheduler(){
		printf("In SCHEDULER::RunScheduler\n");
		//One way you could do this...
		//resume_threads();	//moves threads from wait if signals rec'd
		//add_new_threads();	//moves threads from new to ready		
		//sort_ready_queue();	//sort the ready queue from the dispatcher
		/* sort_ready_queue() can be implemented in several ways depending on the Algorithm requested */
		;
	}

	TCBnode** Scheduler::get_last_TCBnode(){return &last;}
	TCBnode** Scheduler::get_idle_TCBnode(){return &idle;}
	void Scheduler::set_idle_TCBnode(TCBnode ** _node){idle = *_node;}
	void Scheduler::set_last_run(long l){last_run = l;}
	long Scheduler::get_last_run(){	return last_run;}



