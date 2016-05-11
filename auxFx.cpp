/*
 *	File Name				:	auxFx.cpp
 *	Primary Author			:   Francesco Polizzi
 *	Contributing Author(s)	:
 *	Date Created			:	26 April 2016
 *	Date Last Modified		:	11 May 2016
 *
 *	Description		:	This is the file for our OS Simulation driver where all
 *						auxiliary functions are called
 *
 */

    // libraries to include
#include <iostream>
#include <fstream>
#include <iomanip>
#include "simulation_header.h"
using namespace std;


/* AVG_LTQ
 * Author: Francesco Polizzi
 * Other contributors:
 * Last revised: May 3, 2015
 * Description: Calculating the the LTQ avg wait time
 */
double avg_ltq(int total_jobs, double ltq_wait) {
        // calculate average
    double average = ltq_wait/total_jobs;
    
        // return average
    return average;
}

/* AVG_STQ
 * Author: Francesco Polizzi
 * Other contributors:
 * Last revised: May 3, 2015
 * Description: Calculating the the STQ avg wait time
 */
double 	avg_stq(int total_jobs, double stq_wait){
        // calculate average
    double average = stq_wait/total_jobs;
        
        // return average
    return average;
}

/* AVG_IOQ
 * Author: Francesco Polizzi
 * Other contributors:
 * Last revised: May 3, 2015
 * Description: Calculating the the IOQ avg wait time
 */
double	avg_ioq(int total_jobs, double ioq_wait){
        // calculate average
    double average = ioq_wait/total_jobs;
    
        // return average
    return average;
}

/* AVG_RESPONSE_TIME
 * Author: Francesco Polizzi
 * Other contributors:
 * Last revised: May 3, 2015
 * Description: Calculating the average response time on all jobs
 */
double 	avg_response_time(int total_jobs, double response_time){
        // calculate average
    double average = response_time/total_jobs;
    
        // return average
    return average;
}

/* AVG_TURNAROUND_TIME
 * Author: Francesco Polizzi
 * Other contributors:
 * Last revised: May 3, 2015
 * Description: Calculating the average turnaround time on all jobs
 */
double 	avg_turnaround_time(int total_jobs, double turnaround_time){
        // calculate average
    double average = turnaround_time/total_jobs;
    
        // return average
    return average;
}

/* CPU_UTILIZATION
 * Author: Francesco Polizzi
 * Other contributors:
 * Last revised: May 3, 2015
 * Description: Calculating the CPU Utilization for jobs
 */
double cpu_utilization(int productive_time, double total_time){
        // calculate CPU utilization
    double cpuUtilization = productive_time/total_time;
    
        // return CPU utilization
    return cpuUtilization;
}

/* PRINT_OUTPUT
 * Author: Francesco Polizzi
 * Other contributors:
 * Last revised: May 3, 2015
 * Description: Printing our information output to the user
 */
void print_output(string algorithmUsed, int timeToComplete, int contextSwitchTime,
                  double cpuUtilization, int avgResponse, int avgTurnaround, double systemThroughput,
                  double avgLTQ, double avgSTQ, double avgIOQ, ofstream& Outfile){
        // print our output
    
    Outfile << fixed << setprecision(2);
    Outfile << "Developed using \"" << algorithmUsed << "\" algorithm." << endl << endl;
    Outfile << "Total Simulation Time      :" << setw(8) << timeToComplete << endl;
    Outfile << "Total Context Switch Time  :" << setw(8) << contextSwitchTime << endl;
    Outfile << "CPU Utilization Rate       :" << setw(8) << cpuUtilization << "%" << endl;
    Outfile << "Average Response Time      :" << setw(8) << avgResponse << endl;
    Outfile << "Average Turnaround Time    :" << setw(8) << avgTurnaround << endl;
    Outfile << fixed << setprecision(4);
    Outfile << "System Throughput          :" << setw(8) << systemThroughput << endl;
    Outfile << fixed << setprecision(2);
    Outfile << "Average LTQ Wait Time      :" << setw(8) << avgLTQ << endl;
    Outfile << "Average STQ Wait Time      :" << setw(8) << avgSTQ << endl;
    Outfile << "Average IOQ Wait Time      :" << setw(8) << avgIOQ << endl;
}

/* PRINT_HEADER
 * Author: Francesco Polizzi
 * Other contributors:
 * Last revised: May 3, 2015
 * Description: Printing our header to the user
 */
void print_header(ofstream& Outfile){
        // print our output header
    Outfile << setw(22) << "Francesco Polizzi, ";
    Outfile << "Katie Schaffer, ";
    Outfile << "Jeremy Viner, ";
    Outfile << "& Hein Htet Zaw" << endl;
    Outfile << setw(30) << "CSC 40600";
    Outfile << setw(17) << "Section 11" << endl;
    Outfile << setw(30) << "Spring 2016";
    Outfile << setw(20) << "Assignment #2" << endl;
    Outfile << setw(35) << "-----------------------------------";
    Outfile << setw(35) << "-----------------------------------\n\n";
}

/* PRINT_HEADER
 * Author: Francesco Polizzi
 * Other contributors:
 * Last revised: May 3, 2015
 * Description: Printing our footer to the user
 */
void print_footer(ofstream& Outfile){
        // print our output footer
    Outfile << endl;
    Outfile << setw(35) << " --------------------------------- " << endl;
    Outfile << setw(35) << "|      END OF PROGRAM OUTPUT      |" << endl;
    Outfile << setw(35) << " --------------------------------- " << endl;
    Outfile << "" << endl;
    
}
