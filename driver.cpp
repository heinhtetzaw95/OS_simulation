    //libraries to include
#include <iostream>
#include <fstream>
#include <iomanip>

#include "simulation_header.h"

using namespace std;

double total_stq_wait;
int total_jobs_run;
double total_response_time;
double total_productive_time;
double total_turnaround_time;
double total_ltq_wait;
double total_ioq_wait;
int sys_clock;

int main() {
    //////////////////
    /// STEP 1 ///////////////////////////////////////////////////////
    //////////////////

        // old vars
    int job_timer = 0; // Keeps track of the time between job arrivals
    total_stq_wait = 0;
    total_jobs_run = 0;
    total_response_time = 0;
    total_productive_time = 0;
    total_turnaround_time = 0;
    total_stq_wait = 0;
    total_ltq_wait = 0;
    total_ioq_wait = 0;
    sys_clock = 0;
    
    int jobs_admitted = 0;
    
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
    ifstream infile("SIM_DATA.txt", ios::in);
    ofstream outfile("Output.txt", ios::out);

         //initialize our reading flag and job count
    bool reading = true;
    int job_count = 0;
    int jobs_entering_system=0;
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
        infile >> tempJob.inter_arrival;
        infile >> tempJob.io_burst;
        
            // Initialize other job variables
        tempJob.burst_num = 0;
        
            // Initialize burst list to all -1
        for (int burst_num = 0; burst_num < cpu_burst_max; burst_num++) {
            tempJob.cpu_burst[burst_num] = -1;
        }

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
    if (job_list[jobs_admitted].inter_arrival == job_timer) {
            // Set job flag to true
        flags.incoming_job = true;
            // Get reference to job
        current_job = &job_list[total_jobs_run];
            // record time of arrival
        current_job->arrival = sys_clock;
            // reset job_timer to zero
        job_timer = 0;
        
        jobs_admitted++;
        
            // increment more_jobs
        jobs_entering_system++;
        flags.jobs_in_system++;
        
        
    }
    
   
    //////////////////
    /// STEP 4 //////////////////////////////////////////////////////////////////
    //////////////////

    /// 4.1 //////////////////////////////////////////////////////////////////
        //while there are jobs to process
    while(total_jobs_run < job_count) {
        manage_ltq(longterm_queue, current_job, flags);
        manage_stq(shortterm_queue, longterm_queue, &io_device, flags);
        manage_cpu(&cpu, shortterm_queue, flags);
        manage_ioq(io_queue, &cpu);
        manage_iodevice(&io_device, io_queue, flags);
        
            // Increment clock
        sys_clock++;
        
            // Check for incoming processes
        // GOTO 3.1 LOL
        
            // When a job enters the system
        if (job_list[jobs_admitted].inter_arrival == job_timer) {
                // Set job flag to true
            flags.incoming_job = true;
                // Get reference to job
            current_job = &job_list[jobs_entering_system];
                // record time of arrival
            current_job->arrival = sys_clock;
                // reset job_timer to zero
            job_timer = 0;
                //increment admitted job count
            jobs_admitted++;
                // increment more_jobs
            jobs_entering_system++;
            flags.jobs_in_system++;
        }
        
        // Update job timer
        job_timer++;
        
    }
    
        // Process accumulated data
    double avgLTQ = avg_ltq(total_jobs_run, total_ltq_wait);
    double avgSTQ = avg_stq(total_jobs_run, total_stq_wait);
    double avgIOQ = avg_ioq(total_jobs_run, total_ioq_wait);
    double avgResponse = avg_response_time(total_jobs_run, total_response_time);
    double avgTurnaround = avg_turnaround_time(total_jobs_run, total_turnaround_time);
    double total_time = 0;
    double cpuUtilization = 0;
    double contextSwitchTime = 0;
    double systemThroughput = 0;
    //double cpuUtilization = cpu_utilization(total_productive_time, total_time);
    
    print_header(outfile);
    print_output("First in First Out", total_time, contextSwitchTime,
                 cpuUtilization, avgResponse, avgTurnaround, systemThroughput, avgLTQ, avgSTQ, avgIOQ, outfile);
    
    
    
    return 0;
}
