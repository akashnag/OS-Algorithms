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

/* Implementation of the Round-Robin CPU Scheduling Algorithm */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int pid;
	int burst;
	int remaining_burst;
	int waiting;
	int turnaround;
} process;

void display(process**, int);

int main(void)
{
	int i, j, quantum, n, actual, completed;
	double avg_waiting, avg_turnaround;
	process** list;

	printf("Enter the no. of processes: ");
	scanf("%d", &n);

	printf("Enter the time quantum: ");
	scanf("%d", &quantum);

	list = (process**)malloc(n * sizeof(process*));

	for(i = 0; i < n; i++)
	{
		list[i] = (process*)malloc(sizeof(process));

		printf("Process P%d:", i+1);
		printf("\tEnter burst time: ");
		scanf("%d", &list[i]->burst);
		
		list[i]->remaining_burst = list[i]->burst;
		list[i]->pid = i+1;
		list[i]->waiting = 0;
		list[i]->turnaround = 0;
	}

	completed = 0;
	
	while(completed < n)
	{
		for(i=0; i<n; i++)
		{
			if(list[i]->remaining_burst == 0) continue;
			actual = (quantum <= list[i]->remaining_burst ? quantum : list[i]->remaining_burst);

			list[i]->remaining_burst -= actual;
			if(list[i]->remaining_burst == 0) completed++;

			for(j=0; j<n; j++)
			{
				if(i==j || list[j]->remaining_burst == 0) continue;
				list[j]->waiting += actual;
			}
		}
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
	printf("\nPID\tBurst\tWaiting\tTurnaround\n---\t-----\t-------\t----------\n");
	for(i = 0; i < n; i++)
	{
		printf("P%-2d\t%-5d\t%-7d\t%-10d\n", list[i]->pid, list[i]->burst, list[i]->waiting, list[i]->turnaround);
	}
}
