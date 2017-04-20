#include <stdio.h>
#include <stdlib.h>

struct P
{
	int processName;
	int burstTime;
	int startTime;
	int finishTime;
	int remainingTime;
};

typedef struct P Process;

void SortArrivalTime(Process ProcessList[], int NumberOfProcess);
void ContinueQueue(Process Queue[], int numberOfProcess);

void main()
{
	int i;
	int numberOfProcess;

	printf("Enter the number of processes: ");
	scanf("%d", &numberOfProcess);

	int quantumTime;
	printf("Enter quantum time: ");
	scanf("%d", &quantumTime);

	Process *processList = (Process*)malloc(numberOfProcess * sizeof(Process));

	int totalBurstTime = 0;

	for (i = 0; i<numberOfProcess; i++)
	{
		printf("Enter the Process Name & BurstTime:");
		scanf("%d%d", &processList[i].processName, &processList[i].burstTime);
		processList[i].remainingTime = processList[i].burstTime;
		processList[i].startTime = -1;

		totalBurstTime += processList[i].burstTime;
	}

	int timeStamp = 0;
	int finishTime = totalBurstTime;

	Process *processQueue = (Process*)malloc(numberOfProcess * sizeof(Process));

	for(i = 0; i < numberOfProcess; i++)
	{
		processQueue[i] = processList[i];
	}

	printf("\n%s%6s%6s", "Proc", "Start", "Stop");

	while(timeStamp < finishTime)
	{
		if(processQueue[0].remainingTime > 0)
		{
			printf("\n%d%6d", processQueue[0].processName, timeStamp);

			if(processQueue[0].startTime == -1)
			{
				processQueue[0].startTime = timeStamp;
			}

			timeStamp += (processQueue[0].remainingTime > quantumTime ? quantumTime : processQueue[0].remainingTime);

			processQueue[0].remainingTime -= quantumTime;

			if(processQueue[0].remainingTime <= 0)
			{
				processQueue[0].finishTime = timeStamp;
			}

			printf("%6d", timeStamp);
		}

		ContinueQueue(processQueue, numberOfProcess);
	}

	int totalWaitingTime = 0;
	int totalTurnaroundTime = 0;

	for(i = 0; i < numberOfProcess; i++)
	{
		totalWaitingTime += processQueue[i].startTime;
		totalTurnaroundTime += processQueue[i].finishTime;
	}

	printf("\n Average waiting time: %.2f", ((float)totalWaitingTime) / numberOfProcess);
	printf("\n Average turnaround time: %.2f", ((float)totalTurnaroundTime) / numberOfProcess);

	free(processList);
	free(processQueue);
}

void ContinueQueue(Process Queue[], int numberOfProcess)
{
	Process temp = Queue[0];
	int i;

	for(i = 0; i < numberOfProcess - 1; i++)
	{
		Queue[i] = Queue[i + 1];
	}
	Queue[numberOfProcess - 1] = temp;
}