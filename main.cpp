#include <iostream>
#include <fstream>
#include <iomanip>

#include "simulation_header.h"

using namespace std;

void print(job*);
bool traverseTree(tree*, job*);

int main() {
	ifstream infile("SIM_DATA.txt", ios::in);
//	ofstream outfile("sample_output.txt", ios::out);
			
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
		print(theJob);	//print current job
		if (storage.add(theJob)) cout << "Input Success" << endl << endl;	//print message
		else cout << "Input Failed!" << endl << endl;
		//**********************************************************************//

	}

	//******* these are the tests to check if data is read correctly *******//
	cout << endl << "Total Job Count: " << storage.getJobCount() << endl;
	cout << "Job 100: "; print(storage.getJob(100)); cout << endl;
	cout << "Read Finish!" << endl;
	cout << endl << "The Storage Tree: " << endl;
	traverseTree(&storage, storage.getRoot());
	//**********************************************************************//

	cin.get();
	return 0;
}

void print(job* theJob) {
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

bool traverseTree(tree* storage, job* current) {

		// Receives – The storage tree and where to start
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