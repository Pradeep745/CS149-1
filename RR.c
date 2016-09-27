#include <stdio.h>
#include <stdlib.h>
#include "process_producer.h"
#include "Sorter.h"

#define TRUE 1 //add header to store define variables

void RoundRobin(struct process* o_plist){ //original plist. Gonna use copy so the arrays can be modified in the funciton
	int counter_char_array = 0;
	int counter_process = 0;
	int queue[NUM_PROCESS] = {0};
	int available_service = 0;
	int quanta;
	char* rr_process_order = malloc(sizeof(char) * CHAR_ARRAYMAX);
//ADD TEST IF MAX_QUANTA LESS THAN NUM_PROCESS
	struct process* plist = malloc(sizeof(struct process) * NUM_PROCESS);
	memcpy(plist, o_plist, sizeof(struct process) * NUM_PROCESS);
	SortBy(&plist, 0); // in case not sorted by arrival time
	quanta = plist[0].arrival_time; //Set time to when first proces arrives
	

	while(counter_char_array < quanta){
		rr_process_order[counter_char_array] = ' ';
		counter_char_array++;
	}

	// NEED TO ACCOUNT FOR IDLE CPU - check for all 0's in array
	while(TRUE){ 
		if(quanta >= MAX_QUANTA) break;

		//Checks how many processes are currently in queued, if there is a 1 in the array slot, there is process that has both arrived and has positive service time
		for(int x = 0; x < NUM_PROCESS; x++){
			if(plist[x].service_time == 0) queue[x] = 0;
			else if(plist[x].service_time > 0 && plist[x].arrival_time <= quanta){
				queue[x] = 1;
				available_service = 1;
			}
			else queue[x] = 0;
		}

		if(available_service == 0){
			quanta += 1;
			//available_service = 0; not needed
			rr_process_order[counter_char_array] = ' ';
			counter_char_array++;
		}
		else if(queue[counter_process % NUM_PROCESS] == 1){
			if(plist[counter_process % NUM_PROCESS].service_time < 1) plist[counter_process % NUM_PROCESS].service_time = 0;
			else plist[counter_process % NUM_PROCESS].service_time -= 1;
			rr_process_order[counter_char_array] = plist[counter_process % NUM_PROCESS].name;
			counter_process++;
			counter_char_array++;
			quanta += 1;
		}
		else counter_process++;
	}

	// print all quanta slices
	for(int x = 0; x < MAX_QUANTA; x++){
		printf("%d ", x);
	}

	//print order of processes according to time
	printf("\n");

	for(int x = 0; x < CHAR_ARRAYMAX; x++){
		printf("%c ", rr_process_order[x]);
	}

	free(plist);
	free(rr_process_order);
	return;
}