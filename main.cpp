/*
 *	File Name				:	main.cpp
 *	Primary Author			:	Hein Htet Zaw
 *	Contributing Author(s)	:
 *	Date Created			:	29 April 2016
 *	Date Last Modified		:	7 May 2016
 *
 *	Description		:	This file contains the main function of the program and some small functions
 *                       required by the main function.
 *
 *				**This file is mainly for testing for the binary tree and the three queues**
 *
 */

#include <iostream>
#include <fstream>
#include <iomanip>

#include "simulation_header.h"

using namespace std;

void print(job *);
bool traverseTree(tree *, job *);

int main_() {
    ifstream infile("SIM_DATA.txt", ios::in);
    
    //create a storage
    tree storage;
    
    //set a boolean to know if the data input if done or not yet
    bool read = true;
    
    //read the given data file and store all jobs in the storage
    while (read == true) {
        job *theJob = new job;
        //make a temporary space to read UNKNOWN number of cpu_bursts
        int temp_cpu_burst;
        
        //actual read in the data
        infile >> theJob->num;					//read job number
        infile >> theJob->length;				//read job length
        infile >> theJob->arrival;				//read job arrival time
        infile >> theJob->io_burst;				//read job's I/O burst length
        infile >> temp_cpu_burst;				//read job's first cpu burst
        //read the length cpu bursts
        while (temp_cpu_burst != 0 && read == true) {
            
            //store the current cpu burst
            theJob->cpu_burst[theJob->burst_count] = temp_cpu_burst;
            infile >> temp_cpu_burst;			//read job's next cpu burst
            
            //detect sentinel and stop reading
            if (temp_cpu_burst == -1) read = false;
            
            //increment cpu burst count
            theJob->burst_count++;
        }
        
        //******* these are the tests to check if data is read correctly *******//
        //print(theJob);	//print current job
        if (storage.add(theJob));// cout << "Input Success!" << endl << endl;	//print message
        else cout << "Input Failed!" << endl << endl;
        //**********************************************************************//
        
    }
    
    //******* these are the tests to check if data is read correctly *******
    cout << endl << "Total Job Count: " << storage.getJobCount() << endl;
    cout << "Job 100: "; print(storage.getJob(100)); cout << endl;
    cout << "Read Finish!" << endl;
    cout << endl << "The Storage Tree: " << endl;
    traverseTree(&storage, storage.getRoot());
    //**********************************************************************/
    
    //******* these are the tests to check if long term queue is working correctly *******
    longQueue *Qlong = new longQueue();
    for (int i = 1;!Qlong->isFull(); i++) {
        Qlong->add(storage.getJob(i));
        cout << "Added at Slot " << Qlong->getRear() << endl;
    }
    //cout << "------------------------------------------" << endl;
    for (int i = 1; i <= 10; i++) {
        job *temp = new job();
        temp = Qlong->getNext();
        cout << temp->time_in_cpu << " " << temp->time_in_longQ << " "
        << temp->time_in_shortQ << " " << temp->time_in_ioQ << " " << temp->num << endl;
    }
    if (Qlong->incrementAll()) cout << "Incrementing Success!" << endl;
    for (int i = 1; i <= 10; i++) {
        job *temp = new job();
        temp = Qlong->getNext();
        cout << temp->time_in_cpu << " " << temp->time_in_longQ << " "
        << temp->time_in_shortQ << " " << temp->time_in_ioQ << " " << temp->num << endl;
    }
    for (int i = 61; i <= 70; i++) {
        Qlong->add(storage.getJob(i));
        cout << "Added at Slot " << Qlong->getRear() << endl;
    }
    if (Qlong->incrementAll()) cout << "Incrementing Success!" << endl;
    for (int i = 1; i<=10; i++) {
        job *temp = new job();
        temp = Qlong->getNext();
        cout << temp->time_in_cpu << " " << temp->time_in_longQ << " "
        << temp->time_in_shortQ << " " << temp->time_in_ioQ << " " << temp->num << endl;
    }
    cout << "-----------------------------" << endl;
    //if (Qlong->incrementAll()) cout << "Incrementing Success!" << endl;
    for (int i = 1; i <= 10; i++) {
        job *temp = new job();
        temp = Qlong->getNext();
        cout << temp->time_in_cpu << " " << temp->time_in_longQ << " "
        << temp->time_in_shortQ << " " << temp->time_in_ioQ << " " << temp->num << endl;
    }
    for (int i = 71; i <= 80; i++) {
        Qlong->add(storage.getJob(i));
        cout << "Added at Slot " << Qlong->getRear() << endl;
    }
    if (Qlong->incrementAll()) cout << "Incrementing Success!" << endl;
    for (int i = 1; i<=10; i++) {
        job *temp = new job();
        temp = Qlong->getNext();
        cout << temp->time_in_cpu << " " << temp->time_in_longQ << " "
        << temp->time_in_shortQ << " " << temp->time_in_ioQ << " " << temp->num << endl;
    }
    if (Qlong->incrementAll()) cout << "Incrementing Success!" << endl;
    for (int i = 1; !Qlong->isEmpty(); i++) {
        job *temp = new job();
        temp = Qlong->getNext();
        cout << temp->time_in_cpu << " " << temp->time_in_longQ << " "
        << temp->time_in_shortQ << " " << temp->time_in_ioQ << " " << temp->num << endl;
    }
    /*
     for (int i = 1; i <= 20; i++) {
     cout << "Front " << Qlong->getFront() << endl;
     cout << "Rear " << Qlong->getRear() << endl;
     cout << "Size " << Qlong->getSize() << endl;
     print(Qlong->getNext());
     }
     cout << "------------------------------------------" << endl;
     for (int i = 61; !Qlong->isFull(); i++) {
     Qlong->add(storage.getJob(i));
     cout << "Front " << Qlong->getFront() << endl;
     cout << "Rear " << Qlong->getRear() << endl;
     cout << "Size " << Qlong->getSize() << endl;
     }
     cout << "------------------------------------------" << endl;
     while (!Qlong->isEmpty()) {
     cout << "Front " << Qlong->getFront() << endl;
     cout << "Rear " << Qlong->getRear() << endl;
     cout << "Size " << Qlong->getSize() << endl;
     print (Qlong->getNext());
     }
     //************************************************************************************/
    
    /******* these are the tests to check if short term queue is working correctly *******
     shortQueue *Qshort = new shortQueue();
     for (int i = 1;!Qshort->isFull(); i++) {
     Qshort->add(storage.getJob(i));
     cout << Qshort->getSize() << endl;
     }
     cout << "------------------------------------------" << endl;
     for (int i = 1; i <= 20; i++) {
     cout << "Front " << Qshort->getFront() << endl;
     cout << "Rear " << Qshort->getRear() << endl;
     cout << "Size " << Qshort->getSize() << endl;
     print(Qshort->getNext());
     }
     cout << "------------------------------------------" << endl;
     for (int i = 61; !Qshort->isFull(); i++) {
     Qshort->add(storage.getJob(i));
     cout << "Front " << Qshort->getFront() << endl;
     cout << "Rear " << Qshort->getRear() << endl;
     cout << "Size " << Qshort->getSize() << endl;
     }
     cout << "------------------------------------------" << endl;
     while (!Qshort->isEmpty()) {
     cout << "Front " << Qshort->getFront() << endl;
     cout << "Rear " << Qshort->getRear() << endl;
     cout << "Size " << Qshort->getSize() << endl;
     print(Qshort->getNext());
     }
     //************************************************************************************/
    
    /******* these are the tests to check if I/0 queue is working correctly *******
     ioQueue *Qio = new ioQueue();
     for (int i = 1;!Qio->isFull(); i++) {
     Qio->add(storage.getJob(i));
     cout << Qio->getSize() << endl;
     }
     cout << "------------------------------------------" << endl;
     for (int i = 1; i <= 20; i++) {
     cout << "Front " << Qio->getFront() << endl;
     cout << "Rear " << Qio->getRear() << endl;
     cout << "Size " << Qio->getSize() << endl;
     print(Qio->getNext());
     }
     cout << "------------------------------------------" << endl;
     for (int i = 61; !Qio->isFull(); i++) {
     Qio->add(storage.getJob(i));
     cout << "Front " << Qio->getFront() << endl;
     cout << "Rear " << Qio->getRear() << endl;
     cout << "Size " << Qio->getSize() << endl;
     }
     cout << "------------------------------------------" << endl;
     while (!Qio->isEmpty()) {
     cout << "Front " << Qio->getFront() << endl;
     cout << "Rear " << Qio->getRear() << endl;
     cout << "Size " << Qio->getSize() << endl;
     print(Qio->getNext());
     }
     //************************************************************************************/
    
    cin.get();
    return 0;
}

void print(job* theJob) {
    
    // Receives ñ The pointer of a job
    // Task - Print the job information about the given job
    // Returns - Nothing
    
    cout << setw(5) << theJob->num << " "
    << setw(5) << theJob->length << " "
    << setw(5) << theJob->arrival << " "
    << setw(5) << theJob->io_burst << "     ";
    
    int temp_count = 0;
    while (temp_count < theJob->burst_count) {
        cout << theJob->cpu_burst[temp_count] << " ";
        
        temp_count++;
    }
    
    cout << endl;
    cout << "CPU Burst Count: " << theJob->burst_count << endl;
}

//*****************************************************************************************************
bool traverseTree(tree *storage, job *current) {
    
    // Receives ñ The storage tree and where to start
    // Task - Considering the recieved node is root and print every node below it
    // Returns - Whether or not the received node is valid
    
    if (current != NULL) {
        traverseTree(storage, current->left);
        cout << current->num << endl;
        traverseTree(storage, current->right);
    }
    else return false;
    
    return true;
}

//*****************************************************************************************************
