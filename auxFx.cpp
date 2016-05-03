/*
 *	File Name				:	auxFx.cpp
 *	Primary Author			:
 *	Contributing Author(s)	:
 *	Date Created			:	26 April 2016
 *	Date Last Modified		:	26 April 2016
 *
 *	Description		:	This is the driver for our OS Simulation where all
 *						auxiliary functions are called
 *
 */

//libraries to include
#include <iostream>
#include <fstream>
#include <iomanip>
//#include "simulation_header.h"
using namespace std;

// write auxiliary functions for our driver
double avg_ltq(int, int);
double avg_stq(int,int);
double avg_ioq(int,int);
double avg_response_time(int,int);
double avg_turnaround_time(int, int);
double cpu_utilization(int,int);
void print_output(string, int, int, int, int, int, int, int, int, int, ofstream);
void print_header(ofstream);
void print_footer(ofstream);

double avg_ltq(int total_jobs, int total_in_ltq) {
    double average = total_in_ltq/total_jobs;
    
    return average;
}

double 	avg_stq(int total_jobs, int total_in_stq){
    double average = total_in_stq/total_jobs;
    
    return average;
}

double	avg_ioq(int total_jobs, int total_in_ioq){
    double average = total_in_ioq/total_jobs;
    
    return average;
}

double 	avg_response_time(int total_jobs, int total_response_time){
    double average = total_response_time/total_jobs;
    
    return average;
}

double 	avg_turnaround_time(int total_jobs, int total_turnaround_time){
    double average = total_turnaround_time/total_jobs;
    
    return average;
}

double cpu_utilization(int productive_time, int total_time){
    double average = productive_time/total_time;
    
    return average;
}

void print_output(string algorithmUsed, int timeToComplete, int contextSwitchTime,
                  int cpuUtilization, int avgResponse, int avgTurnaround, int systemThroughput,
                  int avgLTQ, int avgSTQ, int avgIOQ, ofstream Outfile){
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

void print_header(ofstream Outfile){
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

void print_footer(ofstream Outfile){
    Outfile << endl;
    Outfile << setw(35) << " --------------------------------- " << endl;
    Outfile << setw(35) << "|      END OF PROGRAM OUTPUT      |" << endl;
    Outfile << setw(35) << " --------------------------------- " << endl;
    Outfile << "" << endl;
    
}
