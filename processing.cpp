/*
 *	File Name				:	processing.cpp
 *	Primary Author			:   Katie Schaffer
 *	Contributing Author(s)	:   Francesco Polizzi
 *	Date Created			:	26 April 2016
 *	Date Last Modified		:	6 May 2016
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

/* manage_ltq
 * Author: Katelyn Schaffer
 * Other contributors: Francesco Polizzi
 * Last revised: 6 May 2016
 *
 * Description: Manages the longterm queue
 */
void manage_ltq(longQueue& longterm_queue, job* new_job, FlagContainer& flags) {
    // Handle any current jobs in longterm queue
    if (!longterm_queue.isEmpty()) {
        // Increment wait time for all processes in queue
        longterm_queue.incrementAll();
        
        //* Track time in longterm queue?
    }
    // Handle incoming job if the longtern queue is not full
    if (flags.incoming_job && !longterm_queue.isFull()) {
        // Push incoming job to queue
        longterm_queue.add(new_job);
        // Remove incoming job flag
        flags.incoming_job = false;
    }

    return;
}

/* manage_stq
 * Author: Katelyn Schaffer
 * Other contributors: Francesco Polizzi
 * Last revised: 6 May 2016
 *
 * Description: Manages the shortterm queue
 */
void manage_stq(shortQueue& shortterm_queue, longQueue& longterm_queue, IOdevice* io_device, FlagContainer& flags) {
    // Handle any current jobs in shortterm queue
    if (!shortterm_queue.isEmpty()) {
        // Increment wait time for all processes in queue
        shortterm_queue.incrementAll();
        
        //* Track time in shortterm queue?
    }
    
    // Handle any job that has just finished with the I/O device
    if (io_device->complete) {
        // Remove IO completion indicator
        io_device->complete = false;
        // Flag io device as available
        io_device->available = true;
        // Handle if the job is finished
        if (io_device->job_finished) {
            // Collect data
            total_response_time += io_device->process->response;
            total_productive_time += io_device->process->length;
            total_turnaround_time += io_device->process->turnaround;
            total_stq_wait += io_device->process->time_in_shortQ;
            total_ltq_wait += io_device->process->time_in_longQ;
            total_ioq_wait += io_device->process->time_in_ioQ;
            
            io_device->process->time_in_system = sys_clock - io_device->process->arrival;
            io_device->process->turnaround = io_device->process->time_in_system;
            
            // Remove job from the system
            flags.jobs_in_system--;
            io_device->process = NULL;
            // Remove job finished flag
            io_device->job_finished = false;
        }
        // If not finished, place back on shorttterm queue
        else {
            // Check for room in shortterm queue
            if (!shortterm_queue.isFull()) {
                // Place the process in the shortterm queue
                shortterm_queue.add(io_device->process);
                // Reset IO device
                io_device->process = nullptr;
            }
            else {
                // Error
            }
        }
    } // End handling job finished with IO
    
    // Check for processes in longterm queue
    if (!shortterm_queue.isFull() && !longterm_queue.isEmpty() ) {
        // Move process from longterm queue to shortterm queue
        shortterm_queue.add(longterm_queue.getNext());
    }
    
    return;
}

/* manage_cpu
 * Author: Katelyn Schaffer
 * Other contributors: Francesco Polizzi
 * Last revised: 6 May 2016
 *
 * Description: Manages the CPU
 */
void manage_cpu(CPU* cpu, shortQueue& shortterm_queue, FlagContainer& flags) {
    // Handle if a process is suspended
    if (cpu->suspended) {
        
        //* Track wait time?
        
        // Decrement suspend timer
        cpu->suspend_timer--;
        // Check if interrupt is complete
        if (cpu->suspend_timer == 0) {
            flags.interrupt = false;
            cpu->suspended = false;
        }
        // Otherwise, check if process is in CPU when
        //  interrupt occured
        else if (cpu->susp_process != nullptr) {
            // Update CPU wait counter
            cpu->total_wait++;
            // Flag that processing has stopped
            cpu->processing_stopped = true;
        }
    } // End suspend handling
    
    // If processing has not been halted
    if (!cpu->processing_stopped) {
        
        // Handle interrupt if suspend timer is up
        if (flags.interrupt && cpu->suspend_timer == 0) {
            // Suspend any process that has the CPU currently
            if (cpu->process != nullptr) {
                // Suspend current process
                cpu->susp_process = cpu->process;
                // Now CPU is free of processes
                cpu->process = nullptr;
            }
            // Reset suspend timer
            cpu->suspend_timer = SUSPEND_TIME;
            // Flag suspension
            cpu->suspended = true;
        }
        // Handle if no interrupt
        else {
            // Handle any process that's in the CPU and check for completion
            if (cpu->process != nullptr) {
                // Update timer of current CPU burst
                cpu->process->cpu_burst[cpu->process->burst_num]--;
                
                //* Track process time in CPU
                
                cpu->process->time_in_cpu++;
                
                // Check for completion of burst
                if (cpu->timer == cpu->process->cpu_burst[cpu->process->burst_num]) {
                    // Flag completion
                    cpu->complete = true;
                    // Increment burst
                    cpu->process->burst_num++;
                    // Reset burst timer
                    cpu->timer = 0;
                }
            }
            // Handle any process with completed suspension or get next process
            else {
                // Unsuspend any process that's suspended
                if (cpu->suspended) {
                    // Give suspended process back to the CPU
                    cpu->process = cpu->susp_process;
                    // Increment cpu wait counter
                    cpu->total_wait++;                                                           // !! Again?!
                    // Process is no longer suspended
                    cpu->suspended = false;
                }
                // Get next job for the CPU if applicable
                else if (!shortterm_queue.isEmpty() && cpu->ready) {
                    // Give process to the CPU
                    cpu->process = shortterm_queue.getNext();
                    // Indicate CPU is not ready for more processes
                    cpu->ready = false;
                    // Initialize cpu process timer
                    cpu->timer = 0;
                }
            } // End handling process with completed suspension or next process
        }   // End handling no interrupt
    } // End handling if processing has not halted
    
    // Remove CPU stop flag
    cpu->processing_stopped = false;
    
    return;
}

/* manage_ioq
 * Author: Katelyn Schaffer
 * Other contributors: Francesco Polizzi, Jeremey Viner
 * Last revised: 6 May 2016
 *
 * Description: Manages the IO queue
 */
void manage_ioq(ioQueue& io_queue, CPU* cpu) {
    // Handle processes in IO queue
    if (!io_queue.isEmpty()) {
        // Increment wait times
        io_queue.incrementAll();
        
        //* Track time in IO queue?
    }
    
    // Handle any process that the CPU just finished processing
    if (cpu->complete && !io_queue.isFull()) {
        // Move process from CPU to IO queue
        io_queue.add(cpu->process);
        // Reset CPU process num
        cpu->process = nullptr;
        // Indicate CPU is ready for more processes
        cpu->ready = true;
        // Reset cpu_complete flag
        cpu->complete = false;
    }
    
    return;
}

/* manage_iodevice
 * Author: Katelyn Schaffer
 * Other contributors: Francesco Polizzi, Jeremey Viner
 * Last revised: 6 May 2016
 *
 * Description: Manages the IO device
 */
void manage_iodevice(IOdevice* io_device, ioQueue& io_queue, FlagContainer& flags) {
    // Handle if no current interrupt
    if (!flags.interrupt) {
        // Handle if process is in IO device
        if (io_device->process != nullptr) {
            // Update IO timer
            io_device->timer++;
            // If finished burst
            if (io_device->timer == io_device->burst_length) {
                // Indicate IO complete
                io_device->complete = true;
                // Interrupt if more CPU bursts to process
                if (io_device->process->cpu_burst[io_device->process->burst_num+1] <= 0)
                {
                    // Indicate interrupt
                    flags.interrupt = true;
                }
                // Finish up if all bursts are processed
                else {
                    io_device->job_finished = true;
                }
            } // End handling finished burst
        } // End handling process in device
        
        // If no processes in IO device, handle
        //  any processes in IO queue
        else {
            // Check for processes in IO queue and device availability
            if (!io_queue.isEmpty() && io_device->available) {
                // Give IO device to process
                io_device->process = io_queue.getNext();
                io_device->burst_length = io_device->process->io_burst;
                // Reset IO timer
                io_device->timer = 0;
                // Indicate IO device is busy
                io_device->available = false;
            }
        } // End handling IO queue
    }
    
    return;
}
