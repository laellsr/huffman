#ifndef HEAP_H
#define HEAP_H

#include "../@functions/default.h"
#include "../@data_structures/binary_tree.h"

#define MAX_HEAP_SIZE 257

typedef struct heap heap;

heap* create_heap();

void enqueue(heap* hp, int frequency);

binary_tree* dequeue(heap *heap);

int get_parent_index(int i);

int get_left_index(int i);

int get_right_index(int i);

void min_heapify(heap *heap, int index);

#endif
