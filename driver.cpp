    //libraries to include
#include <iostream>
#include <fstream>
#include <iomanip>

#include "simulation_header.h"

using namespace std;

int main() {
    //////////////////
    /// STEP 1 ///////////////////////////////////////////////////////
    //////////////////

    int myClock = 0; // The simulator clock to keep track of the total time of the simulation run
    int io_timer = 0; // Indicates the current I/O burst
    int job_timer = 0; // Keeps track of the time between job arrivals
    int more_jobs = 0; // Keeps track of the # of jobs in system
    int process_timer = 0; // Keeps track of the current CPU burst/
    int suspend_timer = 0; // Keeps track of current interrupt time
    bool cpu_ready_flag    = true; // Signals that the CPU is available
    bool cpu_complete_flag = false; // Signals the completion of a CPU burst
    bool finished_flag     = false; // Signals that a JOB is finished
    bool interrupt_flag    = false; // Signals that an interrupt is in progress
    bool io_complete_flag  = false; // Signals the completion of an I/O burst
    bool io_device_flag    = true; // Signals that the I/O device is available
    bool job_flag          = false; // Signals the a job has arrived
    bool stop_flag         = false; // Signals to stop CPU job processing
    bool suspend_flag      = false; // Signals context switch to handle interrupt

    //int cpu = 0;  // integer to indicate which job has the CPU.
    int count = 0; // keeps track of the number of processes ran
    int devise = 0; // integer to signal which process is in the I/O device
    int process = -1;  // integer to indicate the process entering the CPU
    int ioprocess =-1; // integer to indicate the process entering the I/O device
    int temp = 0;  // integer to indicate which process is suspended
    bool ioq_full = false; // Signals that the I/O Queue is full
    bool ioq_empty = true; // Signals that the I/O Queue is empty
    bool ltq_empty = true; // Signals that the Long Term Queue is empty
    bool ltq_full = false; // Signals that the Long Term Queue is full
    bool stq_empty = true; // Signals that the Short Term Queue is empty
    bool stq_full = false; // Signals that the Short term Queue is full
    
    
    ////////////////
    // NEW VARIABLES
    ////////////////
    
    struct IOdevice {
        bool    available;
        bool    complete;
        int     device;
        int     timer;
        int     burst_length;
        job*    process;
    };
    
    struct CPU {
        int     wait;
        int     process;
        int     timer;
        bool    complete;
        bool    ready;
        bool    processing_stopped;
        bool    suspended;
        int     suspend_timer;
        int     susp_process;
    };
    
    IOdevice io_device;
    CPU cpu;

         // initialize our job and jobs list
    job tempJob;
    job job_list[];

         // initialize our
    ifstream infile("data.txt", ios::in);

         //initialize our reading flag and job count
    bool reading = true;
    int job_count = 0;


    //////////////////
    /// STEP 2 //////////////////////////////////////////////////////////////////
    //////////////////

         //read and process data from our file
    while (reading) {
        //create a new job
        tempJob = new job();
        //read in job information
        infile >> tempJob.num;
        infile >> tempJob.length;
        infile >> tempJob.arrival;
        infile >> tempJob.io_burst;

        int temp_input;
        infile >> temp_input;

        while (temp_input > 0){
            //add CPU burst to temp job cpu burst array
            tempJob.cpu_burst[tempJob.burst_count]=temp_input;
            tempJob.burst_count++;
            infile >> temp_input;
        }

        // Add new job to job array
        job_list[job_count] = tempJob;
        job_count++;

        if (temp_input == -1) {
            reading = false;
        }
    }


    //////////////////
    /// STEP 3 //////////////////////////////////////////////////////////////////
    //////////////////

    /// 3.1 //////////////////////////////////////////////////////////////////
    job_timer++;

    /// 3.2 //////////////////////////////////////////////////////////////////
    if (job_list[job_count].arrival == job_timer) {
            // Set job flag to true
        job_flag = true;
            // record time of arrival

            // reset job_timer to zero
        job_timer = 0;
            // increment count
        job_count++;
            // increment more_jobs
    }


    //////////////////
    /// STEP 4 //////////////////////////////////////////////////////////////////
    //////////////////

    /// 4.1 //////////////////////////////////////////////////////////////////
        //while there are jobs to process
    while(JOBS_TO_PROCESS) {
        //manage_ltq()
        //manage_stq()
        //manage_cpu()
        //manage_ioq()
        //manage_iodevice()
        
        //remove finished jobs?
        //increment clock
        //check for incoming processes
    }
    
        // Process accumulated data
    
    return 0;
}
