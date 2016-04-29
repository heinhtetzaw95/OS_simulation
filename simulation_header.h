/*
*	File Name				:	simulation_header.h
*	Primary Author			:	Hein Htet Zaw
*	Contributing Author(s)	:
*	Date Created			:	26 April 2016
*	Date Last Modified		:	29 April 2016
*	
*	Description		:	This is the header file where all the global variables and data structures
*						are declared and defined.
*	
*/

#ifndef _SIMULATION_HEADER_H_
#define _SIMULATION_HEADER_H_

#include <string>
#include <array>

#define long_max 60
#define short_max 30
#define io_max 30

		//set up a structure for jobs
struct job {

				//include the following information in the job
	int num;					//job number
	int length;					//(CPU bursts + I/O bursts) time
	int arrival;				//arriaval time
	int io_burst;				//the length of time this job requires an I/O device
	int cpu_burst[25];				//the time this process requires the CPU
	int burst_count = 0;

				//create variables for the followings

	int time_in_cpu = 0;		//total time spent in the CPU
	int time_in_longQ = 0;		//total time spent in the Long Term Queue
	int time_in_shortQ = 0;		//total time spent in the Short Term Queue
	int time_in_ioQ = 0;		//total time spent in the I/O Queue
	int turnaround = 0;			//the turnaround time
	int response = 0;			//the response time
	int switching = 0;			//time spent in context switching

	job *left;
	job *right;
};

			//declare and define STORAGE *This is a binary tree*
class tree {
private:
	job *root;
	int jobCount = 0;

public:
	bool add(job *theJob);						//add the items in the tree, sorted by **JOB NUMBER**

	job* getJob(int JobNum);					//get the pointer of a certain job by its job number
	job* getRoot() { return root; };			//get the root of "this" tree

	int getJobCount() { return jobCount; };		//get the number of jobs in "this" tree

};

			//declare and instantiate global variables and arrays
			//create spaces for the followings

static job *processor = NULL;				//the (only) processor
static job *IO = NULL;						//the I/O device
static job * long_term[long_max];			//long-term queue
static job * short_term[short_max];		//short-term queue
static job * IO_q[io_max];					//I/O queue

			//declare variables for the followings
static int myClock = 0;						//clock to keep track of time
static int total_job_count = 0;			//place to keep track of how many jobs inputed
static int total_LTQ = 0;					//total long term queue wait time for all jobs
static int total_STQ = 0;					//total short term queue wait time for all jobs
static int total_ioQ = 0;					//total I/O Queue wait time for all jobs



static job temp;							//temporary space

						//*** more variables are to be added as needed ***//

#endif // !_SIMULATION_HEADER_H_
