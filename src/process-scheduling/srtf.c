/*
  Copyright (C) 2020 Akash Nag

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
	
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
	
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* Implementation of the preemptive SJF / SRTF (Shortest Remaining Time First) CPU Scheduling Algorithm */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int pid;
	int arrival;
	int burst;
	int remaining_burst;
	int waiting;
	int turnaround;
} process;

void display(process**, int);
int get_first_arrival_time(process**, int);
int get_shortest_process(process**, int, int);

int main(void)
{
	int i, k, n, time, completed;
	double avg_waiting, avg_turnaround;
	process** list;

	printf("Enter the no. of processes: ");
	scanf("%d", &n);

	list = (process**)malloc(n * sizeof(process*));

	for(i = 0; i < n; i++)
	{
		list[i] = (process*)malloc(sizeof(process));

		printf("Process P%d:", i+1);
		printf("\n\tEnter arrival time: ");
		scanf("%d", &list[i]->arrival);
		printf("\tEnter burst time: ");
		scanf("%d", &list[i]->burst);
		
		list[i]->remaining_burst = list[i]->burst;
		list[i]->pid = i+1;
		list[i]->waiting = 0;
		list[i]->turnaround = 0;
	}

	completed = 0;
	time = get_first_arrival_time(list, n);
	while(completed < n)
	{
		k = get_shortest_process(list, n, time);

		for(i=0; i<n; i++)
		{
			if(i != k && list[i]->arrival <= time && list[i]->remaining_burst > 0) list[i]->waiting++;
		}

		list[k]->remaining_burst--;
		if(list[k]->remaining_burst == 0) completed++;
		time++;
	}

	avg_turnaround = 0;
	avg_waiting = 0;
	for(i=0; i<n; i++)
	{
		list[i]->turnaround = list[i]->burst + list[i]->waiting;
		avg_waiting += list[i]->waiting;
		avg_turnaround += list[i]->turnaround;
	}

	display(list, n);

	avg_waiting /= n;
	avg_turnaround /= n;
	printf("\nAverage waiting time: %lf\nAverage turnaround time: %lf\n", avg_waiting, avg_turnaround);

	return EXIT_SUCCESS;
}

void display(process** list, int n)
{
	int i;
	printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\n---\t-------\t-----\t-------\t----------\n");
	for(i = 0; i < n; i++)
	{
		printf("P%-2d\t%-7d\t%-5d\t%-7d\t%-10d\n", list[i]->pid, list[i]->arrival, list[i]->burst, list[i]->waiting, list[i]->turnaround);
	}
}

int get_first_arrival_time(process** list, int n)
{
	int i, pos;
	pos = -1;

	for(i=0; i<n; i++)
	{
		if(pos == -1 || list[i]->arrival < list[pos]->arrival)
			pos = i;
	}

	return list[pos]->arrival;
}

int get_shortest_process(process** list, int n, int time)
{
	int i, pos;

	pos = -1;
	for(i = 0; i<n; i++)
	{
		if(list[i]->arrival <= time && list[i]->remaining_burst > 0)
		{
			if(pos == -1 || list[i]->remaining_burst < list[pos]->remaining_burst)
				pos = i;
			else if(list[i]->remaining_burst == list[pos]->remaining_burst && list[i]->arrival < list[pos]->arrival)
				pos = i;
		}
	}

	return pos;
}