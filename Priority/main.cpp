#include <stdio.h>
#include <stdlib.h>

struct P
{
	int processName;
	int arrivalTime;
	int burstTime;
	int priority;
	int startTime;
	int finishTime;
	int turnAroundTime;
	int waitTime;
};

typedef struct P Process;

void SortArrivalTime(Process ProcessList[], int NumberOfProcess);
void SortPriority(Process ProcessList[], int NumberOfProcess);

void main()
{
	int i;
	int numberOfProcess;

	printf("Enter the number of processes:");
	scanf("%d", &numberOfProcess);

	Process *processList = (Process*)malloc(numberOfProcess * sizeof(Process));

	for (i = 0; i<numberOfProcess; i++)
	{
		printf("Enter the Process Name, Arrival Time, BurstTime & Priority: ");
		scanf("%d%d%d%d", &processList[i].processName, &processList[i].arrivalTime, &processList[i].burstTime, &processList[i].priority);
	}

	SortArrivalTime(processList, numberOfProcess);

	int lastTimeStamp = 0;
	int timeStamp = processList[0].arrivalTime;

	Process *processQueue = (Process*)malloc(numberOfProcess * sizeof(Process));
	int index = 0;
	int queueSize = 0;
	do
	{
		for (i = 0; i < numberOfProcess; i++)
		{
			if (processList[i].arrivalTime <= timeStamp && processList[i].arrivalTime > lastTimeStamp)
			{
				processQueue[i] = processList[i];
				queueSize++;
			}
		}

		SortPriority(processQueue + index, queueSize - index);

		processQueue[index].startTime = timeStamp;
		processQueue[index].finishTime = processQueue[index].startTime + processQueue[index].burstTime;
		processQueue[index].waitTime = processQueue[index].startTime - processQueue[index].arrivalTime;
		processQueue[index].turnAroundTime = processQueue[index].finishTime - processQueue[index].arrivalTime;

		lastTimeStamp = timeStamp;
		timeStamp = processQueue[index].finishTime > processList[index + 1].arrivalTime ? processQueue[index].finishTime : processList[index + 1].arrivalTime;
		index++;
	} while (index < numberOfProcess);

	int totalWaitingTime = 0;
	int totalTurnaroundTime = 0;

	printf("\nPName Arrtime Burtime Start TAT Finish");
	printf("\n%s\t%6s\t\t%6s\t%6s\t%6s\t%6s", "PName", "Arrtime", "Burtime", "Start", "TAT", "Finish");
	for (i = 0; i< numberOfProcess; i++)
	{
		printf("\n%d\t%6d\t\t%6d\t%6d\t%6d\t%6d", processQueue[i].processName, processQueue[i].arrivalTime, processQueue[i].burstTime, processQueue[i].startTime, processQueue[i].turnAroundTime, processQueue[i].finishTime);
		totalWaitingTime += processQueue[i].waitTime;
		totalTurnaroundTime += processQueue[i].turnAroundTime;
	}

	printf("\n Average waiting time: %.2f", ((float)totalWaitingTime) / numberOfProcess);
	printf("\n Average turnaround time: %.2f", ((float)totalTurnaroundTime) / numberOfProcess);

	free(processList);
	free(processQueue);
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

void SortPriority(Process ProcessList[], int NumberOfProcess)
{
	int i, j;
	for (i = 0; i < NumberOfProcess - 1; i++)
	{
		for (j = i + 1; j < NumberOfProcess; j++)
		{
			if (ProcessList[i].priority > ProcessList[j].priority)
			{
				Process temp = ProcessList[i];
				ProcessList[i] = ProcessList[j];
				ProcessList[j] = temp;
			}
		}
	}
}