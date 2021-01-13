// ---------------------------------------------------------
/* 
	File: CPU.cpp
	Package: SchedulerSim

	Author: John Pecarina
	Date: 15 July 2015
					
	Description: A 5 instruction CPU emulator.
	License/Copyright: None
*/
//---------------------------------------------------------
/*----------------------------------------------------------------------------------------
*
*	INCLUDES
*
---------------------------------------------------------------------------------------*/
#include "stdio.h"
#include "stdlib.h"
#include "CPU.h"
#include "unistd.h"
/*----------------------------------------------------------------------------------------
*
*  	CLASS METHODS          
*
---------------------------------------------------------------------------------------*/
	/* Constructor, just inserts random values and resets timer */	
	CPU::CPU(){
		unsigned char r = IDLE_CODE;
		result = r;
		inst_register = 'N';	
		pc_register = &inst_register;
		ticks = 0;
		register_1 = 0;
		register_2 = 0;			
	}	

	/* increments the timer (ticks), called by CPU */
	void CPU::tick(){				
		usleep(1000*CLOCK_DELAY);
		ticks++;
	}

	/* dispatcher calls this to load context and jump to PC */
	void CPU::context_set(){
		result = EXEC_CODE;
		inst_register = (char)*pc_register;
	}

	/* dispatcher calls this to run */
	void CPU::process_thread(int _quantum){

		int y = 0;
		int continue_processing = TRUE;		

		while ( continue_processing ){

			if (result & EXEC_FLAG) { //high bit set means continue processing
				process_instruction();
				if (DEBUG)
					dump_proc();
				advance_instruction();
			} else {
				continue_processing = FALSE;
			}
			y++;
			if ( y == _quantum ){
				continue_processing = FALSE;
			}
			//FIXME: How could we support preemption? We don't have interrupts yet.	
			//Scheduler could run as a separate thread and set an interrupt flag in simulated HW
			/*if (preempt_interrupt){
				continue_processing = FALSE;
			}*/
		}
	}

	/* Used by process_thread to process through instructions (CPU burst) */
	void CPU::process_instruction(){
		//first the CPU advances the timer
		tick();
		// then the CPU processes an instruction (parses and assigns a code)
		// this code is monitored from Scheduler to choose what to do
		switch(inst_register){
			case 'E':		//Keep Executing
				result = EXEC_CODE;
				break; 
			case 'N':		//Idle code
				result = IDLE_CODE;
				break; 
			case 'W':		//Wait
				result = WAIT_CODE;
				break; 
			case 'T':		//Terminate the thread
				result = TERM_CODE;
				break; 
			case 'X':		//Shutdown, Exit code
				result = EXIT_CODE;
				break;   
			default : /* ERROR - UNEXPECTED INPUT, */
				result = EROR_CODE;  //sets error flag
		}
		// nothings going to registers right now
		// lower result flags not used, reserved instruction set
	}
		
	/* Used by process_thread to process through instructions (CPU burst) */
	void CPU::advance_instruction(){
	//assume that the CPU is pipelined so this doesn't take an extra tick
		if (result == EXEC_CODE){
			pc_register++;
			inst_register = (char)*pc_register;
		}
	}

	/*
	* Prints a line for what's on the proc
	*/	
	void CPU::dump_proc(){
		printf("TM:%li\t", ticks);
		printf("R1:%x\t", register_1);
		printf("R2:%x\t", register_2);
		printf("RE:%x\t", result);
		printf("PC:%x\t", pc_register);
		printf("IN:%c\n", inst_register);
	}

	/**
	 * GETTERS AND SETTERS
	 */
	unsigned long * CPU::get_time(){return &ticks;	}
	unsigned int * CPU::get_reg1(){	return &register_1;}
	unsigned int * CPU::get_reg2(){	return &register_2;}
	void CPU::set_time(unsigned long * _val){ticks = *_val;	}
	void CPU::set_reg1(unsigned int * _val){register_1 = *_val;}
	void CPU::set_reg2(unsigned int * _val){register_2 = *_val;}
	char ** CPU::get_pc(){	return &pc_register;}
	char * CPU::get_inst(){	return &inst_register;	}
	uint8_t * CPU::get_result(){return &result;}
	void CPU::set_pc(char ** _val){	pc_register = *_val;	}
	void CPU::set_inst(char * _val){inst_register = *_val;	}
	void CPU::set_result(uint8_t * _val){result = *_val;}


