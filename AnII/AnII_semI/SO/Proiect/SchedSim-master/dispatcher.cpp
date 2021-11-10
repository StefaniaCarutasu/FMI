// ---------------------------------------------------------
/*
	File: dispatcher.cpp
	Package: SchedulerSim

	Author: John Pecarina
	Date: 17 July 2015

	Description: A simple dispatcher function for a computer.
	License/Copyright: None
*/
//---------------------------------------------------------
/*  INCLUDES					*/
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include <sys/types.h>
#include "dispatcher.h"
#include "scheduler.h"
#include "CPU.h"
#include "TCB.h"

//---------------------------------------------------------
/*  CLASS METHODS					*/
//---------------------------------------------------------

/**
 Description: Constructor
*/
Dispatcher::Dispatcher(CPU ** _cpu, Scheduler ** _sched){	

	//set the CPU
	set_CPU(_cpu);
	//set the scheduler
	set_sched(_sched);
	//set idle as current and next threads
	set_new_TCBnode(sched->get_idle_TCBnode());
	set_cur_TCBnode(sched->get_idle_TCBnode());
}

/**
	Description: Runs the thread currenty on the CPU
*/
bool Dispatcher::run_thread(){	
	
	//In an attempt to stop right on the scheduler period	
	//Normally an interrupt would stop
	//So check the time now and take the 
	//smaller of QUANTUM and what remains in SCHED_PERIOD
	long time_til_sched;
	time_til_sched = (SCHED_PERIOD - *cpu->get_time()) % SCHED_PERIOD;
	long run_time;	
	//comparison and assignment
	run_time = (time_til_sched < QUANTUM) ? time_til_sched : QUANTUM; 
	
	//run the thread until cpu hits a non-CPU burst	
	cpu->process_thread(run_time);
	
	// checks to see the return from the CPU
	if (*(cpu->get_result()) == EXIT_CODE)
		return false;  //This will shut it down
	return true; //Gets to the next iteration
}


/**
	Description: Calls sched to choose the next thread 
*/
void Dispatcher::choose_next_thread(){	

	//temporary assignment variable since we access cpu_time a lot
	unsigned long cpu_time;
	cpu_time = *cpu->get_time();
	if (cpu_time + CONTEXT_SWITCH_COST >= END_OF_DISPATCH){
		new_TCB_node = *sched->get_last_TCBnode();
		return;
	}

	//If this is a scheduled stop
	if ((cpu_time - sched->get_last_run()) >= SCHED_PERIOD){
		//go ahead and advance the clock
		cpu_time += SCHED_COST;
		sched->set_last_run(cpu_time);
		//Scheduling takes many thousand cycles
		cpu->set_time(&cpu_time);
		//checking again to see if we can execute after the scheduler
		if (cpu_time + CONTEXT_SWITCH_COST >= END_OF_DISPATCH){
			new_TCB_node = *sched->get_last_TCBnode();
			return;
		}
		//Then it is time to run the scheduler
		sched->run_scheduler();
	}

	//Take the front, it is in no queue after this and before th next save state
	TCBnode* node;
	node=sched->rq->dequeue();

	if (node != NULL){
		//Set it for the next TCB to be loaded
		new_TCB_node = node;
	}
	else// (new_TCB_node == NULL)
		new_TCB_node = *sched->get_idle_TCBnode();
}


/**
	Description: Saves the state of the CPU (cur_TCB_node)
*/
void Dispatcher::save_state_of_CPU(){	
	//skip all this for the IDLE thread
	if (*cpu->get_result() == IDLE_CODE){
		return;
	}

	cur_TCB_node->tcb.program_ctr = *cpu->get_pc();
	cur_TCB_node->tcb.register1 = *cpu->get_reg1() + 1;
	cur_TCB_node->tcb.register2 = *cpu->get_reg2() + 10;
	//cur_TCB_node->tcb.stack_pointer = cpu->get_stack_ptr();
	cur_TCB_node->tcb.result = *cpu->get_result();
	//Very important timing information
	if (!(cur_TCB_node->tcb.state_flags & PROC_FLAG)){
		cur_TCB_node->tcb.response_time = *cpu->get_time()-cur_TCB_node->tcb.arrive_time;
		//this was the first time, so set the PROC_FLAG
		cur_TCB_node->tcb.state_flags |= PROC_FLAG;
	}
	cur_TCB_node->tcb.state_flags = cur_TCB_node->tcb.result & WAIT_FLAG;
	cur_TCB_node->tcb.state_flags = cur_TCB_node->tcb.result & EXEC_FLAG;
	if (cur_TCB_node->tcb.result & TERM_FLAG){
		//this process is finished, so we set the finished time
		cur_TCB_node->tcb.state_flags |= TERM_FLAG;
		cur_TCB_node->tcb.turnaround_time = *cpu->get_time()-cur_TCB_node->tcb.arrive_time;
		//also, put it into the terminated queue
		sched->tq->enqueue(cur_TCB_node);
	}
	else if (cur_TCB_node->tcb.result == EXEC_CODE){
		sched->rq->enqueue(cur_TCB_node);
	}
	else if (cur_TCB_node->tcb.result & WAIT_FLAG){
		sched->wq->enqueue(cur_TCB_node);
	}
	else{
		printf("CRASH\n");
	}
}

/**-
	Description: Loads a new thread on the CPU
*/
void Dispatcher::load_state_of_CPU(){	

	cpu->set_pc(&new_TCB_node->tcb.program_ctr);
	cpu->set_reg1(&new_TCB_node->tcb.register1);
	cpu->set_reg2(&new_TCB_node->tcb.register2);

	//Very important timing information
	if (!(new_TCB_node->tcb.state_flags & PROC_FLAG)){
		new_TCB_node->tcb.wait_time = 
			*cpu->get_time()-new_TCB_node->tcb.arrive_time;
		//this was the first time, but the PROC_FLAG will be set after it comes off
	}

	//load initial values in the CPU, prep for jump to PC
	cpu->context_set();

	//done with the context switch, so swap the cur-new TCB
	cur_TCB_node = new_TCB_node;

	//count the time cost
	unsigned long cpu_time;
	cpu_time = *cpu->get_time();
	cpu_time += CONTEXT_SWITCH_COST;
	//Context switches takes many hundred cycles
	cpu->set_time(&cpu_time);
}


/**
	Description: Getters and Setters
**/
//getters and setters
TCBnode** Dispatcher::get_cur_TCBnode(){return &cur_TCB_node;}
void Dispatcher::set_cur_TCBnode(TCBnode ** _tcb){cur_TCB_node = *_tcb;}
TCBnode** Dispatcher::get_new_TCBnode(){return &new_TCB_node;}
void Dispatcher::set_new_TCBnode(TCBnode ** _tcb){new_TCB_node = *_tcb;}
CPU** Dispatcher::get_CPU(){return &cpu;}
void Dispatcher::set_CPU(CPU ** _cpu){cpu = *_cpu;}
Scheduler** Dispatcher::get_sched(){return &sched;}
void Dispatcher::set_sched(Scheduler ** _sched){sched = *_sched;}



