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
    int clock = 0; // The simulator clock to keep track of the total time of the simulation run
    int job_timer = 0; // Keeps track of the time between job arrivals
    
        // Simulation devices
    longQueue longterm_queue;
    shortQueue shortterm_queue;
    ioQueue io_queue;
    IOdevice io_device;
    CPU cpu;
    
        // Initialize flags
    FlagContainer flags;
    flags.jobs_in_system = 0;
    flags.incoming_job = false;
    flags.interrupt = false;
    
        // Initialize IO device
    io_device.available = true;
    io_device.complete = false;
    io_device.job_finished = false;
    io_device.timer = 0;
    //io_device.burst_length;
    
        // Initialize CPU
    cpu.ready = true;
    cpu.timer = 0;
    cpu.complete = false;
    cpu.processing_stopped = false;
    cpu.suspended = false;
    
         // initialize our job and jobs list
    job tempJob;
    job* current_job;
    job job_list[150];

         // initialize our
    ifstream infile("data.txt", ios::in);

         //initialize our reading flag and job count
    bool reading = true;
    int job_count = 0;

    //////////////////
    /// STEP 2 //////////////////////////////////////////////////////////////////
    //////////////////

         // Read and process data from our file
    while (reading) {
            // Create a new job
        tempJob = *new job();
            // Read in job information
        infile >> tempJob.num;
        infile >> tempJob.length;
        infile >> tempJob.arrival;
        infile >> tempJob.io_burst;

            // Next value to read could be burst or sentinel
        int temp_input;
        infile >> temp_input;

            // Continue to read until sentinel
        while (temp_input > 0){
                // Add CPU burst to temp job cpu burst array
            tempJob.cpu_burst[tempJob.burst_count]=temp_input;
            tempJob.burst_count++;
            infile >> temp_input;
        }

            // Add new job to job array
        job_list[job_count] = tempJob;
        job_count++;

            // Confirm we've reached the sentinel and finish reading
        if (temp_input == -1) {
            reading = false;
        }
    }


    //////////////////
    /// STEP 3 //////////////////////////////////////////////////////////////////
    //////////////////
    
    // Get first job into the system

    /// 3.1 //////////////////////////////////////////////////////////////////
        // Update job timer
    job_timer++;

    /// 3.2 //////////////////////////////////////////////////////////////////
        // When a job enters the system
    if (job_list[job_count].arrival == job_timer) {
            // Set job flag to true
        flags.incoming_job = true;
            // Get reference to job
        current_job = &job_list[job_count];
            // record time of arrival
        
            // reset job_timer to zero
        job_timer = 0;
            // increment count
        total_jobs_run++;
            // increment more_jobs
        flags.jobs_in_system++;
    }


    //////////////////
    /// STEP 4 //////////////////////////////////////////////////////////////////
    //////////////////

    /// 4.1 //////////////////////////////////////////////////////////////////
        //while there are jobs to process
    while(total_jobs_run <= job_count) {
        manage_ltq(longterm_queue, current_job, flags);
        manage_stq(shortterm_queue, longterm_queue, &io_device, flags);
        manage_cpu(&cpu, current_job, shortterm_queue, flags);
        manage_ioq(io_queue, &cpu);
        manage_iodevice(&io_device, io_queue, current_job, flags);
        
            // Remove finished jobs?
        
            // Increment clock
        clock++;
        
            // Check for incoming processes
        // GOTO 3.1 LOL
        
            // Update job timer
        job_timer++;
        
            // When a job enters the system
        if (job_list[job_count].arrival == job_timer) {
                // Set job flag to true
            flags.incoming_job = true;
                // Get reference to job
            current_job = &job_list[job_count];
                // record time of arrival
            
                // reset job_timer to zero
            job_timer = 0;
                // increment count
            total_jobs_run++;
                // increment more_jobs
            flags.jobs_in_system++;
        }
        
    }
    
        // Process accumulated data
    
    return 0;
}
