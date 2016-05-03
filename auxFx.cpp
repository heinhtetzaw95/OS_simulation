/*
 *	File Name				:	auxFx.cpp
 *	Primary Author			:   Francesco Polizzi
 *	Contributing Author(s)	:
 *	Date Created			:	26 April 2016
 *	Date Last Modified		:	3 May 2016
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

    // function declarations for auxillary functions
double avg_ltq(int, int);
double avg_stq(int,int);
double avg_ioq(int,int);
double avg_response_time(int,int);
double avg_turnaround_time(int, int);
double cpu_utilization(int,int);
void print_output(string, int, int, int, int, int, int, int, int, int, ofstream&);
void print_header(ofstream&);
void print_footer(ofstream&);


/* AVG_LTQ
 * Author: Francesco Polizzi
 * Other contributors:
 * Last revised: May 3, 2015
 * Description: Calculating the % of jobs in the LTQ
 */
double avg_ltq(int total_jobs, int total_in_ltq) {
        // calculate average
    double average = total_in_ltq/total_jobs;
    
        // return average
    return average;
}

/* AVG_STQ
 * Author: Francesco Polizzi
 * Other contributors:
 * Last revised: May 3, 2015
 * Description: Calculating the % of jobs in the STQ
 */
double 	avg_stq(int total_jobs, int total_in_stq){
        // calculate average
    double average = total_in_stq/total_jobs;
    
        // return average
    return average;
}

/* AVG_IOQ
 * Author: Francesco Polizzi
 * Other contributors:
 * Last revised: May 3, 2015
 * Description: Calculating the % of jobs in the IOQ
 */
double	avg_ioq(int total_jobs, int total_in_ioq){
        // calculate average
    double average = total_in_ioq/total_jobs;
    
        // return average
    return average;
}

/* AVG_RESPONSE_TIME
 * Author: Francesco Polizzi
 * Other contributors:
 * Last revised: May 3, 2015
 * Description: Calculating the average response time on all jobs
 */
double 	avg_response_time(int total_jobs, int total_response_time){
        // calculate average
    double average = total_response_time/total_jobs;
    
        // return average
    return average;
}

/* AVG_TURNAROUND_TIME
 * Author: Francesco Polizzi
 * Other contributors:
 * Last revised: May 3, 2015
 * Description: Calculating the average turnaround time on all jobs
 */
double 	avg_turnaround_time(int total_jobs, int total_turnaround_time){
        // calculate average
    double average = total_turnaround_time/total_jobs;
    
        // return average
    return average;
}

/* CPU_UTILIZATION
 * Author: Francesco Polizzi
 * Other contributors:
 * Last revised: May 3, 2015
 * Description: Calculating the CPU Utilization for jobs
 */
double cpu_utilization(int productive_time, int total_time){
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
                  int cpuUtilization, int avgResponse, int avgTurnaround, int systemThroughput,
                  int avgLTQ, int avgSTQ, int avgIOQ, ofstream& Outfile){
        // print our output
    Outfile << "Developed using " << algorithmUsed << " algorithm." << endl;
    Outfile << "Total Simulation Time: " << timeToComplete << endl;
    Outfile << "Total Context Switch Time: " << contextSwitchTime << endl;
    Outfile << "CPU Utilization Rate: " << cpuUtilization << endl;
    Outfile << "Average Response Time: " << avgResponse << endl;
    Outfile << "Average Turnaround Time: " << avgTurnaround << endl;
    Outfile << "System Throughput: " << systemThroughput << endl;
    Outfile << "Average LTQ Wait Time: " << avgLTQ << endl;
    Outfile << "Average STQ Wait Time: " << avgSTQ << endl;
    Outfile << "Average IOQ Wait Time: " << avgIOQ << endl;
}

/* PRINT_HEADER
 * Author: Francesco Polizzi
 * Other contributors:
 * Last revised: May 3, 2015
 * Description: Printing our header to the user
 */
void print_header(ofstream& Outfile){
        // print our output header
    Outfile << setw(30) << "Francesco Polizzi,";
    Outfile << setw(30) << "Katie Schaffer,";
    Outfile << setw(30) << "Jeremy Viner,";
    Outfile << setw(30) << "& Hein Htet Zaw";
    Outfile << setw(17) << "CSC 40600";
    Outfile << setw(15) << "Section 11" << endl;
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
