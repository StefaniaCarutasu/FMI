#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <sys/types.h>
#include <string>
#include <unistd.h>
using namespace std;

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

// ---------------------------------------------------------
// ---------------------------------------------------------

/*----------------------------------------------------------------------------------------
*
*		CLASS DEFINITION
*
---------------------------------------------------------------------------------------*/
class CPU {

private:

	unsigned long ticks;	// timpul sistemului
	unsigned int register_1;
	unsigned int register_2;
	char* pc_register;	// holds program counter
	char inst_register; 	// pastreaza instructiunea curenta	
	uint8_t result;		// rezultatul instructiunii

	void tick();		// incrementeaza contorul temporal
	void process_instruction();
	void advance_instruction();

public:
	CPU();		//Constructor

	void context_set();	//apelat dupa context switch 
	void dump_proc();	//debugger pentru a vedea instructiunile pe rand
	void process_thread(int _quantum); //runs threads, returns to dispatcher

	//Getters and Setters
	unsigned long* get_time();
	unsigned int* get_reg1();
	unsigned int* get_reg2();
	void set_time(unsigned long* _val);
	void set_reg1(unsigned int* _val);
	void set_reg2(unsigned int* _val);
	char** get_pc();
	char* get_inst();
	uint8_t* get_result();
	void set_pc(char** _val);
	void set_inst(char* _val);
	void set_result(uint8_t* _val);
};



/*----------------------------------------------------------------------------------------
*
*  	CLASS METHODS
*
---------------------------------------------------------------------------------------*/
/* Constructor, insereaza valori random si reseteaza timpul */
CPU::CPU() {
	unsigned char r = IDLE_CODE;
	result = r;
	inst_register = 'N';
	pc_register = &inst_register;
	ticks = 0;
	register_1 = 0;
	register_2 = 0;
}

/* incrementeaza timer-ul (ticks) */
void CPU::tick() {
	usleep(1000 * CLOCK_DELAY); // suspenda executia pentru un anumit timp
	ticks++;
}

/* dispatcher calls this to load context and jump to PC */
void CPU::context_set() {
	result = EXEC_CODE;
	inst_register = (char)*pc_register;
}

/* dispatcher calls this to run */
void CPU::process_thread(int _quantum) {

	int y = 0;
	int continue_processing = TRUE;

	while (continue_processing) {

		if (result & EXEC_FLAG) { //high bit set means continue processing
			process_instruction();
			if (DEBUG)
				dump_proc();
			advance_instruction();
		}
		else {
			continue_processing = FALSE;
		}
		y++;
		if (y == _quantum) {
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
void CPU::process_instruction() {
	//first the CPU advances the timer
	tick();
	// then the CPU processes an instruction (parses and assigns a code)
	// this code is monitored from Scheduler to choose what to do
	switch (inst_register) {
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
	default: /* ERROR - UNEXPECTED INPUT, */
		result = EROR_CODE;  //sets error flag
	}
	// nothings going to registers right now
	// lower result flags not used, reserved instruction set
}

/* Used by process_thread to process through instructions (CPU burst) */
void CPU::advance_instruction() {
	//assume that the CPU is pipelined so this doesn't take an extra tick
	if (result == EXEC_CODE) {
		pc_register++;
		inst_register = (char)*pc_register;
	}
}

/*
* Prints a line for what's on the proc
*/
void CPU::dump_proc() {
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
unsigned long* CPU::get_time() { return &ticks; }
unsigned int* CPU::get_reg1() { return &register_1; }
unsigned int* CPU::get_reg2() { return &register_2; }
void CPU::set_time(unsigned long* _val) { ticks = *_val; }
void CPU::set_reg1(unsigned int* _val) { register_1 = *_val; }
void CPU::set_reg2(unsigned int* _val) { register_2 = *_val; }
char** CPU::get_pc() { return &pc_register; }
char* CPU::get_inst() { return &inst_register; }
uint8_t* CPU::get_result() { return &result; }
void CPU::set_pc(char** _val) { pc_register = *_val; }
void CPU::set_inst(char* _val) { inst_register = *_val; }
void CPU::set_result(uint8_t* _val) { result = *_val; }


//---------------------------------------------------------
/*  DATA STRUCTURES				*/
//---------------------------------------------------------
typedef struct TCB TCB;

struct TCB {
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

class TCBnode {
public:
	TCB tcb;	//TCB struct to hold the TCB information
	TCBnode* next;	//Pointer to the next node in the queue
	TCBnode* prev;	//Pointer to the previous node in the queue
	TCBnode(uint8_t	pid,	//Constructor for the TCBNode
		char* pc,
		unsigned int	r1,
		unsigned int	r2,
		struct TCB* parent,
		struct TCB* childList,
		struct TCB* siblingList,
		char* openFilesList,
		unsigned long	createTime
#ifdef REAL_TIME
		, unsigned long	deadline
#endif
	)	//Constructor for the TCBNode
	{
		//Set all the variables of the TCB
		this->next = NULL;
		this->prev = NULL;
		this->tcb.pid = pid;
		this->tcb.result = 0;
		this->tcb.stack_pointer = 0;
		this->tcb.program_ctr = pc;
		this->tcb.register1 = r1;
		this->tcb.register2 = r2;
		this->tcb.parent = parent;
		this->tcb.child_list = childList;
		this->tcb.sibling_list = siblingList;
		this->tcb.open_file_list = openFilesList;
		this->tcb.create_time = createTime;
		this->tcb.arrive_time = 0;
		this->tcb.wait_time = ULONG_MAX;
		this->tcb.response_time = ULONG_MAX;
		this->tcb.turnaround_time = ULONG_MAX;
#ifdef REAL_TIME
		this->tcb.deadline = deadline;
#endif
	}

};

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



//---------------------------------------------------------
/*  CLASS METHODS					*/
//---------------------------------------------------------

//Constructor for TCB_Queue class
TCB_Queue::TCB_Queue(int max_size)
{
    this->max_size = max_size;        //Initialize max_size of the queue
    this->size = 0;          //Initialize size
    this->head = NULL;        //Initialize head
    this->tail = NULL;        //Initialize tail
}

//Destructor for TCB_Queue Class
TCB_Queue::~TCB_Queue()
{
    TCBnode* temp;          //Temp node
    int i = 0, size = this->size;

    //Loop through the queue
    for (i = 0; i < size; i++)
    {
        temp = dequeue();     //Dequeue
        delete temp;        //Delete the node
    }
}

//This function enqueues a node
//Return values:
//      0 - The queue is full, node was not enqueued
//      1 - The node was successfully enqueued
int TCB_Queue::enqueue(TCBnode* _tcbn)
{
    //If the queue is full,
    if (this->size >= this->max_size)
    {
        printf("The queue is full.");
        return 0;   //Return 0
    }
    //Else if the queue is not empty,
    else if (this->tail != NULL)
    {
        //Point the current tails pointer to the new node
        this->tail->next = _tcbn;
        //Point the previous pointer on the new node to the current tail
        _tcbn->prev = this->tail;
        //Update the tail pointer to the new node
        this->tail = _tcbn;
    }
    //Else the queue is empty
    else
    {
        //Update the head and tail pointers to the new node
        this->head = _tcbn;
        this->tail = _tcbn;
    }

    //Increment the node size and return the new size
    return ++this->size;
}

//This function dequeues a node
//Return Value:
//      NULL - The queue was empty
//      Not NULL - Pointer to the dequeue node
TCBnode* TCB_Queue::dequeue()
{
    //Initialize the nodeDQ pointer to the head of the queue
    TCBnode* nodeDQ = this->head;

    //Print debug information if needed
#ifdef DEBUG
    printf("\nDequeue from a queue with %d nodes.\n", this->size);
#endif // DEBUG

    //If the queue is empty
    if (this->head == NULL)
    {
        printf("The queue is empty.\n\n");
        return NULL;
    }
    //Else if the queue contains one node
    else if (this->size == 1)
    {
        //Update the head and tail pointers to NULL
        this->head = NULL;
        this->tail = NULL;
    }
    //Else the queue has at least two nodes
    else
    {
        //Update the head pointer to the original second node
        this->head = this->head->next;
        //Update the new head previous pointer to NULL
        this->head->prev = NULL;
    }

    //To prevent a circularly linked list in case the dequeued node is enqueued later on
    //set the next pointer on the dequeued node to NULL
    nodeDQ->next = NULL;

    //Decrement the node size
    this->size--;

    //Return a pointer to the node to be dequeued
    return nodeDQ;
}

//This function displays the pid of each node in the queue
//Return vlaues:
//      N/A
void TCB_Queue::display()
{
    //Create a pointer to the head of the queue
    TCBnode* node = this->head;
    int counter = 0;  //Initialize sizeer

    //Display the number of nodes in the queue
    printf("\n\nTCB size: %d.\n", this->size);

    //Loop through the queue
    while (node != NULL)
    {
        //Print the PID of the current node
        printf("%d: PID: %d\n", ++counter, node->tcb.pid);
        node = node->next;    //Move the node pointer to the next node
    }
}

//Getters and Setters for private variables
int TCB_Queue::get_max_size() { return max_size; }
int TCB_Queue::set_max_size(int _max_size) { max_size = _max_size; }
int TCB_Queue::get_size() { return size; }
int TCB_Queue::set_size(int _size) { size = _size; }

//This function returns a pointer to the tail of the queue
//Return values:
//      NULL - The queue is empty
//      Not NULL - Pointer to the tail of the queue
TCBnode* TCB_Queue::getTail()
{
    //Return the tail pointer of the queue
    return this->tail;
}

//This function returns a pointer to the head of the queue
//Return values:
//      NULL - The queue is empty
//      Not NULL - Pointer to the head of the queue
TCBnode* TCB_Queue::getHead()
{
    //Return the head pointer of the queue
    return this->head;
}

//This function creates a new node to be placed in the queue
//Returns a pointer to a new TCB node
TCBnode* TCB_Queue::createTCBnode(uint8_t pid,
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
)
{
    //Call the TCBnode constructor to create a new node
    TCBnode* newNode = new TCBnode(pid,
        pc,
        r1,
        r2,
        parent,
        childList,
        siblingList,
        openFilesList,
        createTime
#ifdef REAL_TIME
        , deadline
#endif // REAL_TIME
    );

    //Return the pointer to the new node
    return newNode;
}

//This function creates a new node when only given the pid
//Return a pointer to the newly created node
TCBnode* TCB_Queue::createTCBnodePID(uint8_t pid, char* pc)
{
    //Return a pointer created using the createTCBnode function
    return this->createTCBnode(pid, pc,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00000000
#ifdef REAL_TIME
        , 0x00000000
#endif // REAL_TIME
    );
}

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
	void set_idle_TCBnode(TCBnode** _tcb_node);
	void set_last_run(long l);
	long get_last_run();

};



/*--------------------------------------------------------------------------*/
/* CLASS METHODS */
/*--------------------------------------------------------------------------*/

Scheduler::Scheduler() {
	//Intialize the new, ready, wait and terminated queues
	nq = new TCB_Queue(MAX_QUEUE_SIZE); //new_queue;
	rq = new TCB_Queue(MAX_QUEUE_SIZE); //ready_queue;
	wq = new TCB_Queue(MAX_QUEUE_SIZE); //wait_queue;
	tq = new TCB_Queue(MAX_QUEUE_SIZE); //terminated_queue;
	last_run = 0;

	//build an idle TCB node
	string c = "N";
	char* nop = new char[c.size() + 1];
	copy(c.begin(), c.end(), nop);
	nop[c.size()] = '\0';
	idle = tq->createTCBnodePID(0, nop);
}

void Scheduler::load_new_job(uint8_t pid, char* program) {
	//Fill the new queue with jobs
	TCBnode* node;
	node = nq->createTCBnodePID(pid, program);
	nq->enqueue(node);
	//nq->display();
}

void Scheduler::load_last_job(uint8_t pid, char* program) {
	//Set the last TCB (which will exit when needed)
	last = nq->createTCBnodePID(pid, program);
}

void Scheduler::run_scheduler() {
	printf("In SCHEDULER::RunScheduler\n");
	//One way you could do this...
	//resume_threads();	//moves threads from wait if signals rec'd
	//add_new_threads();	//moves threads from new to ready		
	//sort_ready_queue();	//sort the ready queue from the dispatcher
	/* sort_ready_queue() can be implemented in several ways depending on the Algorithm requested */
	;
}

TCBnode** Scheduler::get_last_TCBnode() { return &last; }
TCBnode** Scheduler::get_idle_TCBnode() { return &idle; }
void Scheduler::set_idle_TCBnode(TCBnode** _node) { idle = *_node; }
void Scheduler::set_last_run(long l) { last_run = l; }
long Scheduler::get_last_run() { return last_run; }

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
	Dispatcher(CPU** _cpu, Scheduler** _sched);

	//main functions
	bool run_thread();  //runs the current thread
	void choose_next_thread(); //gets the next one
	void save_state_of_CPU(); //saves the old
	void load_state_of_CPU(); //loads the new

	//getters and setters
	TCBnode** get_cur_TCBnode();
	void set_cur_TCBnode(TCBnode** _tcb_node);
	TCBnode** get_new_TCBnode();
	void set_new_TCBnode(TCBnode** _tcb_node);
	CPU** get_CPU();
	void set_CPU(CPU** _cpu);
	Scheduler** get_sched();
	void set_sched(Scheduler** _sched);


};

//---------------------------------------------------------
/*  CLASS METHODS					*/
//---------------------------------------------------------

/**
 Description: Constructor
*/
Dispatcher::Dispatcher(CPU** _cpu, Scheduler** _sched) {

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
bool Dispatcher::run_thread() {

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
void Dispatcher::choose_next_thread() {

	//temporary assignment variable since we access cpu_time a lot
	unsigned long cpu_time;
	cpu_time = *cpu->get_time();
	if (cpu_time + CONTEXT_SWITCH_COST >= END_OF_DISPATCH) {
		new_TCB_node = *sched->get_last_TCBnode();
		return;
	}

	//If this is a scheduled stop
	if ((cpu_time - sched->get_last_run()) >= SCHED_PERIOD) {
		//go ahead and advance the clock
		cpu_time += SCHED_COST;
		sched->set_last_run(cpu_time);
		//Scheduling takes many thousand cycles
		cpu->set_time(&cpu_time);
		//checking again to see if we can execute after the scheduler
		if (cpu_time + CONTEXT_SWITCH_COST >= END_OF_DISPATCH) {
			new_TCB_node = *sched->get_last_TCBnode();
			return;
		}
		//Then it is time to run the scheduler
		sched->run_scheduler();
	}

	//Take the front, it is in no queue after this and before th next save state
	TCBnode* node;
	node = sched->rq->dequeue();

	if (node != NULL) {
		//Set it for the next TCB to be loaded
		new_TCB_node = node;
	}
	else// (new_TCB_node == NULL)
		new_TCB_node = *sched->get_idle_TCBnode();
}


/*
	Description: Saves the state of the CPU (cur_TCB_node)
*/
void Dispatcher::save_state_of_CPU() {
	//skip all this for the IDLE thread
	if (*cpu->get_result() == IDLE_CODE) {
		return;
	}

	cur_TCB_node->tcb.program_ctr = *cpu->get_pc();
	cur_TCB_node->tcb.register1 = *cpu->get_reg1() + 1;
	cur_TCB_node->tcb.register2 = *cpu->get_reg2() + 10;
	//cur_TCB_node->tcb.stack_pointer = cpu->get_stack_ptr();
	cur_TCB_node->tcb.result = *cpu->get_result();
	//Very important timing information
	if (!(cur_TCB_node->tcb.state_flags & PROC_FLAG)) {
		cur_TCB_node->tcb.response_time = *cpu->get_time() - cur_TCB_node->tcb.arrive_time;
		//this was the first time, so set the PROC_FLAG
		cur_TCB_node->tcb.state_flags |= PROC_FLAG;
	}
	cur_TCB_node->tcb.state_flags = cur_TCB_node->tcb.result & WAIT_FLAG;
	cur_TCB_node->tcb.state_flags = cur_TCB_node->tcb.result & EXEC_FLAG;
	if (cur_TCB_node->tcb.result & TERM_FLAG) {
		//this process is finished, so we set the finished time
		cur_TCB_node->tcb.state_flags |= TERM_FLAG;
		cur_TCB_node->tcb.turnaround_time = *cpu->get_time() - cur_TCB_node->tcb.arrive_time;
		//also, put it into the terminated queue
		sched->tq->enqueue(cur_TCB_node);
	}
	else if (cur_TCB_node->tcb.result == EXEC_CODE) {
		sched->rq->enqueue(cur_TCB_node);
	}
	else if (cur_TCB_node->tcb.result & WAIT_FLAG) {
		sched->wq->enqueue(cur_TCB_node);
	}
	else {
		printf("CRASH\n");
	}
}

/**-
	Description: Loads a new thread on the CPU
*/
void Dispatcher::load_state_of_CPU() {

	cpu->set_pc(&new_TCB_node->tcb.program_ctr);
	cpu->set_reg1(&new_TCB_node->tcb.register1);
	cpu->set_reg2(&new_TCB_node->tcb.register2);

	//Very important timing information
	if (!(new_TCB_node->tcb.state_flags & PROC_FLAG)) {
		new_TCB_node->tcb.wait_time =
			*cpu->get_time() - new_TCB_node->tcb.arrive_time;
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
TCBnode** Dispatcher::get_cur_TCBnode() { return &cur_TCB_node; }
void Dispatcher::set_cur_TCBnode(TCBnode** _tcb) { cur_TCB_node = *_tcb; }
TCBnode** Dispatcher::get_new_TCBnode() { return &new_TCB_node; }
void Dispatcher::set_new_TCBnode(TCBnode** _tcb) { new_TCB_node = *_tcb; }
CPU** Dispatcher::get_CPU() { return &cpu; }
void Dispatcher::set_CPU(CPU** _cpu) { cpu = *_cpu; }
Scheduler** Dispatcher::get_sched() { return &sched; }
void Dispatcher::set_sched(Scheduler** _sched) { sched = *_sched; }
/*--------------------------------------------------------------------------*/
/* Global Variables */
/*--------------------------------------------------------------------------*/

/* -- CPU pointer */
CPU* cpu;

/* -- The system scheduler */
Scheduler* sched;

/* -- The dispatcher */
Dispatcher* ds;

/*-----------------------------------------------------------------
   RANDOM THREAD SIMULATOR  -----------------------------------------------------------------*/

void init() {

	srand(time(NULL)); //Seed
	int r_burst_length, w_bursts;// Random Variables
	int i, j, k, str_idx;
	//thread 0 was idle, so start PID at 1 and goto INIT_PROGRAMS+1
	for (i = 1; i < INIT_PROGRAMS + 1; i++)
	{
		w_bursts = 1 + rand() % MAX_CPU_BURSTS;
		char* thread_str = (char*)malloc(w_bursts * MAX_CPU_BURST_LENGTH);
		if (thread_str) {
			str_idx = 0;
			for (j = 0; j < w_bursts; j++)
			{
				r_burst_length = 1 + rand() % MAX_CPU_BURST_LENGTH;
				for (k = 0; k < r_burst_length; k++)
				{
					thread_str[str_idx] = 'E';
					str_idx++;
				}
				if (j == w_bursts - 1)
					thread_str[str_idx] = 'T';
				else
					thread_str[str_idx] = 'W';
				str_idx++;
			}
			thread_str[str_idx] = '\0';
			//printf("%s\n", thread_str);
			sched->load_new_job(i, thread_str);
		}
	}

	//Add the shutdown process last
	string c = "X";
	char* end = new char[c.size() + 1];
	copy(c.begin(), c.end(), end);
	end[c.size()] = '\0';

	sched->load_last_job(INIT_PROGRAMS + 1, end);
	//this is for the scheduler to exit when the scheduler chooses

	//runs the scheduler the first time
	ds->choose_next_thread();
	//load the first process on the CPU
	ds->load_state_of_CPU();
}

/*--------------------------------------------------------------------------*/
/* MAIN ENTRY INTO THE OS */
/*--------------------------------------------------------------------------*/

int main() {

	//Provision a CPU
	cpu = new CPU;

	//Provision a Scheduler for the CPU
	sched = new Scheduler;

	//Provision the dispatcher
	ds = new Dispatcher(&cpu, &sched);

	//A welcome banner	
	printf("Dispatcher on...Calling init()");

	//Call init to load user programs into NEW queue
	init();

	//All is setup, Entering the main loop
	printf("Entering main dispatch loop...\n");
	//A constant loop until the shutdown instruction: 'X'
	while (ds->run_thread()) { // Runs a thread that is currently on the CPU
	//Gets the next thread from the ready queue
		ds->choose_next_thread();
		// save the state of the process
		ds->save_state_of_CPU();
		//Loads state from new TCB onto the CPU
		ds->load_state_of_CPU();

	}
	//a hanging prompt that waits for the user to exit
	printf("System shutting down\n");
	printf("New Queue size = %d\n", sched->nq->get_size());
	printf("Ready Queue size = %d\n", sched->rq->get_size());
	printf("Wait Queue size = %d\n", sched->wq->get_size());
	printf("Terminated Queue size = %d\n", sched->tq->get_size());
	//one might output other statistics here...
	printf("Press enter to exit:");
	scanf("Enter");


	return 1;
}