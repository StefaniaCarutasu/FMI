OBJS = CPU.o TCB_Queue.o scheduler.o dispatcher.o kernel.o
CPP = g++
DEBUG = -g
CFLAGS = -c -w $(DEBUG)
C  = gcc
LFLAGS = $(DEBUG)


SchedSim : $(OBJS)
	$(CPP) $(LFLAGS) $(OBJS) -o SchedSim

# ==== CPU =====

CPU.o: CPU.cpp CPU.h SchedSim.h
	$(CPP) $(CFLAGS) CPU.cpp

TCB_Queue.o: TCB_Queue.cpp TCB_Queue.h TCB.h SchedSim.h
	$(CPP) $(CFLAGS) TCB_Queue.cpp

# ==== KERNEL FUNCTIONS =====

scheduler.o: scheduler.cpp scheduler.h TCB.h TCB_Queue.h SchedSim.h
	$(CPP) $(CFLAGS) scheduler.cpp

dispatcher.o: dispatcher.cpp dispatcher.h TCB.h CPU.h SchedSim.h
	$(CPP) $(CFLAGS) dispatcher.cpp

# ==== MAIN =====

kernel.o: kernel.cpp scheduler.h dispatcher.h CPU.h SchedSim.h
	$(CPP) $(CFLAGS) kernel.cpp

clean:
	\rm *.o *~ SchedSim
	
	
