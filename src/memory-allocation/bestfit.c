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

/* Implementation of the Best-Fit Memory Allocation Algorithm */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int start_address;
	int end_address;
} hole;

int main(void)
{
	int i, n, process_size, hole_size, pos, min_hole_size;
	hole **list;

	printf("Enter the no. of holes: ");
	scanf("%d", &n);
	list = (hole**)malloc(n * sizeof(hole*));

	for(i=0; i<n; i++)
	{
		list[i] = (hole*)malloc(sizeof(hole));
		printf("Hole #%d:\n", i+1);
		printf("\tEnter starting address: ");
		scanf("%d", &list[i]->start_address);
		printf("\tEnter ending address: ");
		scanf("%d", &list[i]->end_address);
	}

	printf("\nEnter the size of the process (in bytes): ");
	scanf("%d", &process_size);

	pos = -1;
	min_hole_size = -1;
	for(i=0; i<n; i++)
	{
		hole_size = list[i]->end_address - list[i]->start_address + 1;
		if(hole_size >= process_size)
		{
			if(pos == -1 || hole_size < min_hole_size)
			{
				pos = i;
				min_hole_size = hole_size;
			}
		}
	}

	if(pos < 0)
		printf("Not enough space in memory to allocate for the process!");
	else {
		printf("\nProcess will be stored at hole #%d starting from address: %d", pos+1, list[pos]->start_address);
		printf("\nOriginal hole size: %d, new hole size: %d\n", min_hole_size, min_hole_size - process_size);
	}

	return EXIT_SUCCESS;
}