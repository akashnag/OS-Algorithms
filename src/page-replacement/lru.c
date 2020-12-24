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

/* Implementation of the LRU (Least Recently Used) Page Replacement Algorithm */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
	int size;
	int capacity;
	int *frames;
} FrameBuffer;

FrameBuffer* init_new_buffer(int);
bool frame_exists(FrameBuffer*, int);
void add_new_frame(FrameBuffer*, int*, int);

int main(void)
{
	int fb_size, n, i, page_fault, j;
	int *ref_string;
	FrameBuffer *buffer;

	printf("Enter the frame buffer size: ");
	scanf("%d", &fb_size);
	printf("Enter the reference list size: ");
	scanf("%d", &n);

	ref_string = (int*)malloc(n * sizeof(int));
	buffer = init_new_buffer(fb_size);

	printf("Enter the frame reference list below:\n");
	for(i=0; i<n; i++)
	{
		printf("%d\t: ", i+1);
		scanf("%d", &ref_string[i]);
	}
	
	printf("\n#\tFrame\tFaults\tFrame Buffer\n---\t-----\t------\t------------");
	page_fault = 0;
	for(i=0; i<n; i++)
	{
		if(!frame_exists(buffer, ref_string[i]))
		{
			page_fault++;
			add_new_frame(buffer, ref_string, i);
		}

		printf("\n%-3d\t%-5d\t%-6d\t", i+1, ref_string[i], page_fault);
		printf("{ ");
		for(j=0; j<buffer->size-1; j++) printf("%d, ", buffer->frames[j]);
		printf("%d }", buffer->frames[buffer->size-1]);
	}

	printf("\n\nTotal no. of page faults: %d\n", page_fault);
	return EXIT_SUCCESS;
}

FrameBuffer* init_new_buffer(int size)
{
	FrameBuffer *buffer;

	buffer = (FrameBuffer*)malloc(sizeof(FrameBuffer));
	buffer->capacity = size;
	buffer->size = 0;
	buffer->frames = (int*)malloc(size * sizeof(int));
	
	return buffer;
}

bool frame_exists(FrameBuffer *buffer, int frame)
{
	int i;
	for(i=0; i<buffer->size; i++)
	{
		if(buffer->frames[i] == frame) return true;
	}
	return false;
}

void add_new_frame(FrameBuffer *buffer, int *ref_string, int pos)
{
	if(buffer->size < buffer->capacity)
	{
		buffer->frames[buffer->size++] = ref_string[pos];
	} else {
		int i, j, sel_frame, sel_pos, min_pos, min_sel_frame_pos;

		min_pos = -1;
		min_sel_frame_pos = -1;

		/* find farthest frame in the ref. string */
		for(i=0; i<buffer->capacity; i++)
		{
			sel_frame = buffer->frames[i];
			sel_pos = -1;

			for(j=pos-1; j>=0; j--)
			{
				if(ref_string[j] == sel_frame)
				{
					sel_pos = j;
					break;
				}
			}

			if(min_pos < 0 || sel_pos <= min_pos)
			{
				min_pos = sel_pos;
				min_sel_frame_pos = i;
			}
		}

		/* replace farthest frame with new frame */
		buffer->frames[min_sel_frame_pos] = ref_string[pos];
	}
}