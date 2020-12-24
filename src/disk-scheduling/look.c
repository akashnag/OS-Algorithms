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

/* Implementation of the LOOK Disk Scheduling Algorithm */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef enum {
	BACK = 0, FORWARD = 1
} Direction;

int get_shortest_seek_pos(int, Direction, int*, int);
void remove_from_queue(int*, int, int);

int main(void)
{
	int i, n, pos, current_pos, delta, sum, total;
	Direction dir;
	int *queue;

	printf("Enter current head position: ");
	scanf("%d", &current_pos);

	printf("Enter the total no. of cylinders: ");
	scanf("%d", &total);

	printf("Enter the size of the request queue: ");
	scanf("%d", &n);

	printf("Enter the direction of head movement (0:back, 1:forward): ");
	scanf("%d", &i);

	dir = i;
	queue = (int*)malloc(n * sizeof(int));

	printf("Enter the request queue below:\n");
	for(i=0; i<n; i++)
	{
		printf("%d\t: ", i+1);
		scanf("%d", &queue[i]);
	}

	sum = 0;
	i = 0;
	printf("\n#\tRequest\tMovement (cylinders)\n---\t-------\t--------------------");
	while(n > 0)
	{
		pos = get_shortest_seek_pos(current_pos, dir, queue, n);
		if(pos < 0)
		{
			dir = 1 - dir;
			pos = get_shortest_seek_pos(current_pos, dir, queue, n);
		}

		delta = abs(queue[pos] - current_pos);			
		printf("\n%-3d\t%-7d\t%d -> %d (%d)", i+1, queue[pos], current_pos, queue[pos], delta);
		current_pos = queue[pos];
		remove_from_queue(queue, pos, n);			
		n--;
		sum += delta;
		i++;
	}

	printf("\nTotal head movement: %d cylinders\n", sum);
	return EXIT_SUCCESS;
}

int get_shortest_seek_pos(int current_pos, Direction dir, int *queue, int n)
{
	int i, delta, min_delta, min_delta_pos;

	min_delta_pos = -1;
	for(i=0; i<n; i++)
	{
		if(dir == BACK && queue[i] > current_pos) continue;
		if(dir == FORWARD && queue[i] < current_pos) continue;

		delta = abs(queue[i] - current_pos);
		if(min_delta_pos < 0 || delta < min_delta)
		{
			min_delta = delta;
			min_delta_pos = i;
		}
	}

	return min_delta_pos;
}

void remove_from_queue(int *queue, int pos, int n)
{
	int i;
	for(i=pos; i<n-1; i++) queue[i] = queue[i+1];
}