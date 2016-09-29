#include <stdio.h>
#include <stdlib.h>
#include "process_producer.h"
#include "Calculation.h"
#include "ShortestJobFirst.h"
#include <string.h>




void shortestJobFirst(struct process* o_plist) //process list is an array with all the processes 
//with info about arrival time and service time. 

{
	int currentQuanta; //keep track of the quanta during odering.

	struct process* newArrivalArray = malloc(sizeof(struct process) * NUM_PROCESS); //initialize arrays with size of NUM_PROCESS

	struct process* temp; //this is a single empty process called temp that I use for swapping.
    
	memcpy(newArrivalArray, o_plist, (sizeof(struct process) * NUM_PROCESS)); //copy processes into newArrivalArray
	
	SortBy(&newArrivalArray, 0); //Sort processes in array by arrival times only.
	
	//Since the first process will always be started.
	currentQuanta = newArrivalArray[0].arrival_time + newArrivalArray[0].service_time; 

//HERE IS START OF SJF ordering. Return array of processes with correct order of SJF execution. 
for(int i = 1; i< NUM_PROCESS; i++)
{
	for(int j=1; j<NUM_PROCESS; j++) //we start at 1 because the first process (0 index) will start first always
	{
		
		
			//swap around indexes within serviceArray
			if(newArrivalArray[j].service_time <= newArrivalArray[j+1].service_time)
			{
				if(newArrivalArray[j].arrival_time <= currentQuanta)
				{
				temp = newArrivalArray[j];
				newArrivalArray[j] = newArrivalArray[j+1];
				newArrivalArray[j+1] = temp;
				currentQuanta = currentQuanta + temp.service_time;
			    }

			    else{
				currentQuanta++;
			           }
		    
		}
		else //(newArrivalArray[j].service_time > newArrivalArray[j+1].service_time)
		{
			if(newArrivalArray[j+1].arrival_time <= currentQuanta)
			{
				temp = newArrivalArray[j+1];
				newArrivalArray[j+1] = newArrivalArray[j];
				newArrivalArray[j] = temp;
				currentQuanta = currentQuanta + temp.service_time;
			}
			else
			{
				currentQuanta++;
			}
		}
            
		

		}
	}
	//Displaying the order of each process with its name, arrival time, and service time.
	printf("\nThe Order of Processes for ShortestJobFirst\n");
	printf("\nProcess Name,   Arrival Time,    Service Time\n");
for(int i = 0; i < NUM_PROCESS; i++)
{
 printf("%s", &newArrivalArray[i].name);
}

		
		


//printshortestjobfirst(newArrivalArray);
return;
}
