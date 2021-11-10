/* 
    File: SchedSim.h
	Package: SchedulerSim

    Author: John Pecarina
    Date  : 08/01/15

		System: Linux Ubuntu 14.04
		Compiler: g++
		External Files Required: N/A

    This file has all the defines and options for the program in 
	one spot to make experimentation easier.

    MAIN HEADER FILE FOR CSCE 489 SCHEDULER LAB
		License/Copyright: None
*/
//---------------------------------------------------------
/*--------------------------------------------------------------------------*/
// DEFINES - General
/*--------------------------------------------------------------------------*/
#define ULONG_MAX 4294967295 //Use this value for infinity
#define TRUE 1
#define FALSE 0
#define DEBUG TRUE
/*--------------------------------------------------------------------------*/
/* DEFINES - USEFUL SIMULATION VARIABLES 				*/
/*--------------------------------------------------------------------------*/
//#define _REAL_TIME_
	//Activates Real time scheduling which will use the deadlines
	//There is currently no data in the deadline field at init()
#define INIT_PROGRAMS 10	//Number of programs to test with
	//1 is always added at the end for shutting down the CPU
	//The maximum is bound by the size of the NEW queue
#define MAX_CPU_BURSTS 1	//Number of CPU bursts, 
	//1 means no wait instructions or queues
	//The maximum is high enough to not worry about (tried 100)
#define MAX_CPU_BURST_LENGTH 10 //Maximum number of instructions in a burst
	//The number of E's can be 0 up to at least 100 
	//W, T or X is always added to the end of any sequence
#define QUANTUM ULONG_MAX //time limit on the procesor for a RR Queue Mgr
	// Setting at ULONG_MAX makes the scheduler use FCFS scheduling
#define SCHED_PERIOD 10000 //time between when scheduler is run
	//NOTE: It cannot equal the CONTEXT_SWITCH_COST
#define END_OF_DISPATCH ULONG_MAX //sets the time the simulation finishes dispatch
	//END_OF_DISPATCH must be greater than CONTEXT_SWITCH_COST 
	//   otherwise the simulation ends right away
	//   The end of the sim will not be exactly at the time, since the shutdown 
	//   instruction must be assigned on or after the time + CONTEXT_SWITCH_COST
	//   The dispatcher returns at QUANTUM or at the WAIT 'W' instruction

//These costs are somewhat related to real CPUs though the relative size of
//the programs and CPU bursts in this simulation make this hard to realize 
//in an authoritative or generalizable way. Nevertheless, it should be possible
//to evaluate algorithms. If that is all we care about, then both costs can be 
//brought to 0.
#define CONTEXT_SWITCH_COST 100	//context switch takes more ticks than instructions
#define SCHED_COST 10000 //scheduling costs more ticks than a context switch
//In real computers, a 1-2 Ghz processor may run one instruction per nanosecond
//and make a context switch of 1-10 microseconds. Scheduling takes 1-10 milliseconds
//Thus, 1 tick for instructions, 1000 for context switch and 1000000 for scheduler
//would make since if the programs were long enough and numerous enough to use
//all this space.
/*--------------------------------------------------------------------------*/
// QUEUE AND DATA STRUCTURE DEFINES 
/*--------------------------------------------------------------------------*/
#define MAX_QUEUE_SIZE 100	//governs all TCB Queue data structure max size
//#define MAX_NEW_QUEUE_SIZE 100	//we don't use any of these
//#define MAX_READY_QUEUE_SIZE 100	//but we could if Sched changes
//#define MAX_TERM_QUEUE_SIZE 100	//(in constructor)
//#define MAX_WAIT_QUEUE_SIZE 100
/*--------------------------------------------------------------------------*/
// TCB STATE FLAG DEFINES - state flags hold state, result holds OPCODE
/*--------------------------------------------------------------------------*/
#define EXEC_FLAG 0x80
#define WAIT_FLAG 0x40
#define TERM_FLAG 0x20
#define PROC_FLAG 0x10	//this indicates thread has been on the processor once
//note that 4 flags not yet used in state_flags field
/*--------------------------------------------------------------------------*/
// CPU and TCB RESULT FLAG DEFINES  - these flags check masks in result field
/*--------------------------------------------------------------------------*/
//#define EXEC_FLAG 0x80	//FLAGS already defined elsewhere
//#define WAIT_FLAG 0x40	//kept here in case something diverges
//#define TERM_FLAG 0x20	//between state flags and result, such as...
#define EROR_FLAG 0x10		//invalid instruction
//note that 4 flags not yet used in result field
/*--------------------------------------------------------------------------*/
// CPU and TCB RESULT OPCODE DEFINES  - state flags hold state, result holds OPCODE
/*--------------------------------------------------------------------------*/
#define EXEC_CODE 0x80	//OPCODES
#define IDLE_CODE 0xA0
#define WAIT_CODE 0x40
#define TERM_CODE 0x20
#define EXIT_CODE 0x60
#define EROR_CODE 0x10
/*--------------------------------------------------------------------------*/
// CPU CLOCK DEFINES 
/*--------------------------------------------------------------------------*/
#define CLOCK_RATE 100		//clock has 100 cycles per second (100 Hz)
#define CLOCK_DELAY 1000/CLOCK_RATE	//clock delay is the time between ticks

