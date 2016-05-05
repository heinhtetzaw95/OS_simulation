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

        // old vars
    int myClock = 0; // The simulator clock to keep track of the total time of the simulation run
    int job_timer = 0; // Keeps track of the time between job arrivals
    bool job_flag          = false; // Signals the a job has arrived
    
        // Simulation devices
    longQueue longterm_queue;
    shortQueue shortterm_queue;
    ioQueue io_queue;
    IOdevice io_device;
    CPU cpu;
    
        // Initialize flags
    FlagContainer flags;
    flags.job_finished = false;
    flags.incoming_job = false;
    flags.interrupt = false;
    
         // initialize our job and jobs list
    job tempJob;
    job* currJob;
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
        manage_ltq(longterm_queue, currJob, flags);
        manage_stq(shortterm_queue, longterm_queue, &io_device, flags);
        manage_cpu(&cpu, currJob, shortterm_queue, flags);
        manage_ioq(io_queue, &cpu);
        manage_iodevice(&io_device, io_queue, currJob, flags);
        
        //remove finished jobs?
        //increment clock
        //check for incoming processes
    }
    
        // Process accumulated data
    
    return 0;
}
