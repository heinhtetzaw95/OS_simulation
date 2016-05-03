/*
 *	File Name				:	processing.cpp
 *	Primary Author			:
 *	Contributing Author(s)	:
 *	Date Created			:	26 April 2016
 *	Date Last Modified		:	26 April 2016
 *
 *	Description		:
 *
 *
 */

//libraries to include
#include <iostream>
#include <fstream>
#include <iomanip>

#include "simulation_header.h"

#define SUSPEND_TIME 3;

using namespace std;

    // prototypes
void manage_ltq(longQueue&, bool&, job*);
void manage_stq(shortQueue&, longQueue&, bool&, bool&, int&, bool&);
void manage_ioq(ioQueue&, bool&, job*, int&, bool&);
void manage_cpu(int&, int&, int&, bool&, int&, job*, bool&, bool&, int&, bool&, int&, shortQueue&);
void manage_iodevice(int&, int&, int&, bool&, job&, ioQueue&, bool&, bool&);

/* manage_ltq
 * Author: Katelyn Schaffer
 * Other contributors:
 * Last revised: April 29, 2016
 * 
 * Description: Manages the longterm queue
 */
void manage_ltq(longQueue& longterm_queue, bool& incoming_job, job* new_job) {
        // Handle any current jobs in longterm queue
    if (!longterm_queue.isEmpty()) {
            // Increment wait time for all processes in queue
        longterm_queue.incremement_wait();                                          // !! This function should be written
    }
        // Handle incoming job if the longtern queue is not full
    if (incoming_job && !longterm_queue.isFull()) {
            // Push incoming job to queue
        longterm_queue.add(new_job);
            // Remove incoming job flag
        incoming_job = false;
    }
    if (longterm_queue.isFull()) {
                                                                                    // !! Queue is full. What do?
    }
    
    return;
}

/* manage_stq
 * Author: Katelyn Schaffer
 * Other contributors:
 * Last revised: April 29, 2016
 *
 * Description: Manages the shortterm queue
 */
void manage_stq(shortQueue& shortterm_queue, longQueue& longterm_queue, bool& io_complete, bool& io_available, int& in_io, bool& job_finished) {
        // Handle any current jobs in shortterm queue
    if (!shortterm_queue.isEmpty()) {
        // Increment wait time for all processes in queue
        shortterm_queue.incremement_wait();                                         // !! This function should be written
    }
    
        // Handle any job that has just finished with the I/O device
    if (io_complete) {
            // Remove IO completion indicator
        io_complete = false;
            // Flag io device as available
        io_available = true;
            // Handle if the job is finished
        if (job_finished) {
                // (Decrement "more_jobs" / Remove job from the system)                 // ?? How do?
            
                // Remove jon finished flag
            job_finished = false;
            
                // (Collect the data)                                                   // ?? How do?
            
        }
            // If not finished, place back on shorttterm queue
        else {
                // Check for room in shortterm queue
            if (!shortterm_queue.isFull()) {
                    // Place the process in the shortterm queue                        // ?? What process?
            
                    // Reset IO device
                in_io = 0;
            }
            else {
                // Error
            }
        }
    } // End handling job finished with IO
    
        // Check for processes in longterm queue
    if (!shortterm_queue.isFull() && !longterm_queue.isEmpty() ) {
            // Move process from longterm queue to shortterm queue
        shortterm_queue.add(longterm_queue.getNext());                                  // !! Confirm we want to use "Next"
    }
    
    return;
}

/* manage_cpu
 * Author: Katelyn Schaffer
 * Other contributors:
 * Last revised: April 29, 2016
 *
 * Description: Manages the CPU
 */
void manage_cpu(int& cpu_wait, int& cpu_process, int& cpu_timer, bool& cpu_complete, int& cpu_ready,
                job* entering_process, bool& processing_stopped, bool& suspended, int& suspend_timer, bool& interrupt, int& susp_process, shortQueue& shortterm_queue) {
        // Handle if a process is suspended
    if (suspended) {
            // Decrement suspend timer
        suspend_timer--;
            // Check if interrupt is complete
        if (suspend_timer == 0) {
            interrupt = false;
            suspended = false;
        }
            // Otherwise, check if process is in CPU when
            //  interrupt occured
        else if (susp_process == entering_process->num) {
                // Update CPU wait counter
            cpu_wait++;
                // Flag that processing has stopped
            processing_stopped = true;
        }
    } // End suspend handling
    
        // If processing has not been halted
    if (!processing_stopped) {
        
            // Handle interrupt if suspend timer is up
        if (interrupt && suspend_timer == 0) {
                // Suspend any process that has the CPU currently
            if (cpu_process > 0) {
                susp_process = cpu_process; // Suspend current process
                cpu_process = 0;            // Now CPU is free of processes
            }
                // Reset suspend timer
            suspend_timer = SUSPEND_TIME;
                // Flag suspension
            suspended = true;
        }
            // Handle if no interrupt
        else {
                // Handle any process that's in the CPU and check for completion
            if (entering_process->num == cpu_process) {                                         // Process ID ?
                    // Update timer of current CPU burst
                cpu_timer++;
                    // Check completion
                if (entering_process->time_in_cpu == entering_process->cpu_burst_length) {      // !! cpu_burst_length ?
                        // Flag completion
                    cpu_complete = true;
                        // Reset burst timer
                    cpu_timer = 0;
                }
            }
                // Handle any process with completed suspension or get next process
            else {
                    // Unsuspend any process that's suspended
                if (entering_process->num == suspended) {
                        // Give entering process the CPU
                    cpu_process = entering_process->num;
                        // Increment cpu wait counter
                    cpu_wait++;
                        // Process is no longer suspended
                    suspended = 0;
                }
                    // Get next job for the CPU if applicable
                else if (!shortterm_queue.isEmpty() && cpu_ready) {
                        // Get process from the shortterm queue
                    entering_process = shortterm_queue.getNext();
                        // Give process to the CPU
                    cpu_process = entering_process->num;
                        // Update queue
                                                                            // !! not necessary if getNext() already deletes job from queue

                        // Indicate CPU is not ready for more processes
                    cpu_ready = false;
                        // Initialize cpu process timer
                    cpu_timer = 0;
                }
            } // End handling process with completed suspension or next process
        }   // End handling no interrupt
    } // End handling if processing has not halted
    
        // Flag CPU as unstopped
    processing_stopped = false;
    
    return;
}

/* manage_ioq
 * Author: Katelyn Schaffer
 * Other contributors:
 * Last revised: April 29, 2016
 *
 * Description: Manages the IO queue
 */
void manage_ioq(ioQueue& io_queue, bool& cpu_complete, job* cpu_process, int& cpu_process_num, bool& cpu_ready) {
        // Handle processes in IO queue
    if (!io_queue.isEmpty()) {
            // Increment wait times
        io_queue.increment_wait();                                            // !! Need function to increment all wait times
    }
    
        // Handle any process that the CPU just finished processing
    if (cpu_complete && !io_queue.isFull()) {
            // Move process from CPU to IO queue
        io_queue.add(cpu_process);
            // Reset CPU process num
        cpu_process_num = 0;
            // Indicate CPU is ready for more processes
        cpu_ready = true;
            // Reset cpu_complete flag
        cpu_complete = false;
    }
    
    return;
}

/* manage_iodevice
 * Author: Katelyn Schaffer
 * Other contributors:
 * Last revised: April 29, 2016
 *
 * Description: Manages the IO device
 */
void manage_iodevice(int& in_device, int& io_timer, int& io_burst_length, bool& io_complete, bool& io_available,
                     job* entering_io, ioQueue& io_queue, bool& interrupt, bool& job_finished) {
        // Handle if no current interrupt
    if (interrupt) {
            // Handle if process is in IO device
        if (entering_io->num == in_device) {
                // Update IO timer
            io_timer++;
                // If finished burst
            if (io_timer == io_burst_length) {
                    // Indicate IO complete
                io_complete = true;
                    // Reset IO device
                in_device = 0;
                    // Interrupt if more CPU bursts to process
                if (NEXT_CPU_BURST_LENGTH != 0) {                               // !!!! need way to check this
                        // Indicate interrupt
                    interrupt = true;
                }
                    // Finish up if all bursts are processed
                else {
                    job_finished = true;                                       // !! job finished flag
                }
            } // End handling finished burst
        } // End handling process in device

            // If no processes in IO device, handle
            //  any processes in IO queue
        else {
                // Check for processes in IO queue and device availability
            if (!io_queue.isEmpty() && io_available) {
                    // Get process from queue
                entering_io = io_queue.getNext();                               // !! get number or job?
                    // Give IO device to process
                in_device = entering_io->num;
                    // (Delete job from IO queue)
                
                    // Reset IO timer
                io_timer = 0;
                    // Indicate IO device is busy
                io_available = false;
            }
        } // End handling IO queue
    }
    
    return;
}
