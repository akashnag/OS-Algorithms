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

/* Implementation of the FCFS (First-Come First-Served) CPU Scheduling Algorithm */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int pid;
	int arrival;
	int burst;
	int waiting;
	int turnaround;
} process;

void sort(process**, int);
void swap(process**, int, int);
void display(process**, int);

int main(void)
{
	int i, n, time;
	double avg_waiting, avg_turnaround;
	process** list;

	printf("Enter the no. of processes: ");
	scanf("%d", &n);

	list = (process**)malloc(n * sizeof(process*));

	for(i = 0; i < n; i++)
	{
		int arrival, burst;

		printf("Process P%d:", i+1);
		printf("\n\tEnter arrival time: ");
		scanf("%d", &arrival);
		printf("\tEnter burst time: ");
		scanf("%d", &burst);

		list[i] = (process*)malloc(sizeof(process));
		list[i]->pid = i+1;
		list[i]->arrival = arrival;
		list[i]->burst = burst;
		list[i]->waiting = 0;
		list[i]->turnaround = 0;
	}

	sort(list, n);

	time = list[0]->arrival;
	avg_waiting = 0;
	avg_turnaround = 0;

	for(i = 0; i < n; i++)
	{
		if(time < list[i]->arrival) time = list[i]->arrival;

		list[i]->waiting = time - list[i]->arrival;
		list[i]->turnaround = list[i]->burst + list[i]->waiting;

		time += list[i]->burst;

		avg_waiting += list[i]->waiting;
		avg_turnaround += list[i]->turnaround;
	}

	display(list, n);

	avg_waiting /= n;
	avg_turnaround /= n;
	printf("\nAverage waiting time: %lf\nAverage turnaround time: %lf\n", avg_waiting, avg_turnaround);

	return EXIT_SUCCESS;
}

void sort(process** list, int n)
{
	int i, j;
	for(i = 0; i < n - 1; i++)
	{
		for(j = 0; j < n - i - 1; j++)
		{
			if(list[j]->arrival > list[j+1]->arrival) swap(list, j, j+1);
		}
	}
}

void swap(process** list, int p1, int p2)
{
	int temp;

	temp = list[p1]->pid;
	list[p1]->pid = list[p2]->pid;
	list[p2]->pid = temp;

	temp = list[p1]->arrival;
	list[p1]->arrival = list[p2]->arrival;
	list[p2]->arrival = temp;

	temp = list[p1]->burst;
	list[p1]->burst = list[p2]->burst;
	list[p2]->burst = temp;
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