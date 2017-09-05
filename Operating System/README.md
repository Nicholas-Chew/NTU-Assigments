## Introduction
* Real operating systems are very complex
	* Difficult to see how OS concepts are realized
	* Too time intensive to be part of an OS course
	* Therefore not so suitable for educational purposes

* NachOS is an educational operating system
	* Developed at UC Berkeley in C++
	* Freely available: http://www.cs.washington.edu/homes/tom/nachos
	* Idea: use the simplest possible implementation for each subsystem
	* Simple but complete

* Advantages of NachOS
	* Easier to read and understand the code
	* Easier to understand OS concepts
	* Easier to make changes and experiment
	* “Hands on” learning

## About This Project
### Lab 1
* Objective
	* Understand how context switches work
	* Trace the execution flow of a thread
* Tasks
	* Make a complete copy of NachOS
	* Build it & Run it
	* Analyze the output and the source code
	* Figure out what is happening and why

### Lab 2
* Objective
	* Understand how to synchronize processes/threads. 
	* Understand interleavings and race conditions, and master some way of controlling them. 
	* Know how to use locks/semaphores to solve a critical section problem.
* Tasks
	* Implement the race condition scenario for inconsistent output
	* Implement the process synchronization scheme for consistent output 
