/*
*	File Name				:	treeNqueue_functions.cpp
*	Primary Author			:	Hein Htet Zaw
*	Contributing Author(s)	:
*	Date Created			:	29 April 2016
*	Date Last Modified		:	29 April 2016
*
*	Description		:	This file defines all the functions needed for the storage tree and queues
*                       required to make this project work.
*
*/

#include <iostream>
#include "simulation_header.h"

using namespace std;

bool tree::add(job *theJob) {

		// Receives – The job to insert
		// Task - Insert the job into the tree
		// Returns - Whether or not success

			//reserve vrequired variables
	bool inserted = false;
	job *currentPointer;

				//set left and right pointers to NULL for new node
		theJob->left = NULL;
		theJob->right = NULL;

				//the first ever node is root
		currentPointer = root;

				//loop if not inserted yet
		while (inserted == false) {

					//put the node in root if the root is empty
			if (currentPointer == NULL) {
				root = theJob;
				inserted = true;
			}

					//reject the job if the same job information is already in the tree
			else if (theJob->num == currentPointer->num) return false;

					//branch to left if the new node is less than current node
			else if (theJob->num < currentPointer->num) {
						
						//extend branch from the free side
				if (currentPointer->left != NULL) currentPointer = currentPointer->left;
				else {
					currentPointer->left = theJob;
					inserted = true;
				}
			}

					//branch to right side if the new node is higher than current one
			else {

						//extend the branch from the free side
				if (currentPointer->right != NULL) currentPointer = currentPointer->right;
				else {
					currentPointer->right = theJob;
					inserted = true;
				}
			}
		}
		jobCount++;

	return true;
}

//*****************************************************************************************************
job * tree::getJob(int jobNum) {

		// Receives - The job number
		// Task - Find the job in the tree
		// Returns - The pointer of the job if found, NULL pointer if not found

			//begin at root
	job *current = root;
	
			//go through the whole tree
	while (current != NULL) {

				//return the node if found
		if (jobNum == current->num) return current;

				//keep searching till found or the end
		else {
			if (jobNum < current->num) current = current->left;
			else current = current->right;
		}
	}

			//return NULL pointer if not found
	return NULL;
}

//*****************************************************************************************************