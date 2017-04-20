#include <stdio.h>
#include <stdlib.h>

struct P
{
	int processName;
	int arrivalTime;
	int burstTime;
	int startTime;
	int finishTime;
	int turnAroundTime;
	int waitTime;
	int remainingTime;
};

typedef struct P Process;

void SortArrivalTime(Process ProcessList[], int NumberOfProcess);

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
		printf("Enter the Process Name, Arrival Time & BurstTime:");
		scanf("%d%d%d", &processList[i].processName, &processList[i].arrivalTime, &processList[i].burstTime);
		processList[i].remainingTime = processList[i].burstTime;

		totalBurstTime += processList[i].burstTime;
	}

	SortArrivalTime(processList, numberOfProcess);

	int lastTimeStamp = 0;
	int timeStamp = processList[0].arrivalTime;
	int finishTime = timeStamp + totalBurstTime;

	int listIndex = 0;
	int queueSize = 0;
	int queueIndex = 0;

	Process *processQueue = (Process*)malloc(numberOfProcess * sizeof(Process));

	while(timeStamp < finishTime)
	{
		if(listIndex < numberOfProcess)
		{
			if (processList[i].arrivalTime <= timeStamp && processList[i].arrivalTime > lastTimeStamp)
			{
				processQueue[i] = processList[i];
			}
		}
	}
}

void SortArrivalTime(Process ProcessList[], int NumberOfProcess)
{
	int i, j;
	for (i = 0; i < NumberOfProcess - 1; i++)
	{
		for (j = i + 1; j < NumberOfProcess; j++)
		{
			if (ProcessList[i].arrivalTime > ProcessList[j].arrivalTime)
			{
				Process temp = ProcessList[i];
				ProcessList[i] = ProcessList[j];
				ProcessList[j] = temp;
			}
		}
	}
}