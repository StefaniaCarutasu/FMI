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
#ifndef CPU_h
#define CPU_h
/*----------------------------------------------------------------------------------------
*
*		INCLUDES
*
---------------------------------------------------------------------------------------*/
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "SchedSim.h"

/*----------------------------------------------------------------------------------------
*
*		CLASS DEFINITION             
*
---------------------------------------------------------------------------------------*/
class CPU {
	
	private:
	
		unsigned long ticks;	// a notion of time in the system
		unsigned int register_1;// CPU has two general purpose registers
		unsigned int register_2;// holds unsigned int (16 bits)
		char * pc_register;	// holds program counter
		char inst_register; 	// holds instruction to be executed		
		uint8_t result;		// holds the result of the instruction
		
		void tick();		// increments the timer (ticks)
		void process_instruction();		
		void advance_instruction();
		
	public:
		CPU();		//Constructor
	
		void context_set();	//called after a context switch for ticks and jump
		void dump_proc();	//debugger to see instruction by instruction
		void process_thread(int _quantum); //runs threads, returns to dispatcher

		//Getters and Setters
		unsigned long * get_time();
		unsigned int * get_reg1();
		unsigned int * get_reg2();
		void set_time(unsigned long * _val);
		void set_reg1(unsigned int * _val);
		void set_reg2(unsigned int * _val);
		char ** get_pc();
		char * get_inst();
		uint8_t* get_result();
		void set_pc(char ** _val);
		void set_inst(char * _val);
		void set_result(uint8_t * _val);
};

#endif
