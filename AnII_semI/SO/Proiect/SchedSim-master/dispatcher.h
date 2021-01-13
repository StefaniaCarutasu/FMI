// ---------------------------------------------------------
/*
	File: dispatcher.h
	Package: SchedulerSim

	Author: John Pecarina
	Date: 17 Jul 15

	System: Linux Ubuntu 14.04
	Compiler: g++
	External Files Required: N/A

	Description: Class header for the dispatcher.

	License/Copyright: None
*/
//---------------------------------------------------------
// Compilation wrapper to compile once 
#ifndef _DISPATCHER_H
#define _DISPATCHER_H

/*--------------------------------------------------------------------------*/
// INCLUDES 
/*--------------------------------------------------------------------------*/
#include "stdio.h"
#include "stdlib.h"
#include "SchedSim.h"
#include "TCB.h"
#include "CPU.h"
#include "scheduler.h"
//---------------------------------------------------------
/*  CLASS DEFINITION					*/
//---------------------------------------------------------
class Dispatcher
{
	private:
		CPU* cpu;
		Scheduler* sched;
		TCBnode* cur_TCB_node;
		TCBnode* new_TCB_node;

	public:
		// constructor
		Dispatcher(CPU ** _cpu, Scheduler ** _sched);

		//main functions
		bool run_thread();  //runs the current thread
		void choose_next_thread(); //gets the next one
		void save_state_of_CPU(); //saves the old
		void load_state_of_CPU(); //loads the new

		//getters and setters
		TCBnode** get_cur_TCBnode();
		void set_cur_TCBnode(TCBnode ** _tcb_node);
		TCBnode** get_new_TCBnode();
		void set_new_TCBnode(TCBnode ** _tcb_node);
		CPU** get_CPU();
		void set_CPU(CPU ** _cpu);
		Scheduler** get_sched();
		void set_sched(Scheduler ** _sched);


};

#endif

