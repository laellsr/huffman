#include "heap.h"

/* Estrutura da Heap */
/* A Fila foi construida de acordo com a frequência e o símbolo '*' */
struct heap
{
	int size;
	binary_tree* data[MAX_HEAP_SIZE];
};

/* Cria a Heap */
heap* create_heap()
{
	int i;
	heap* new_hp = (heap*)malloc(sizeof(heap));
	new_hp->size = 0;
	for (i = 0; i < MAX_HEAP_SIZE; ++i)
	{
		new_hp->data[i] = NULL;
	}
	return new_hp;
}

/* Adiciona um nó da árvore à Heap */
void enqueue(heap* hp, binary_tree* new_bt)
{
	if (hp->size < MAX_HEAP_SIZE)
	{
		int parent_index, current;
		binary_tree* aux;

		hp->data[++hp->size] = new_bt;
		current = hp->size;
		parent_index = get_parent_index(current);
		while(parent_index >= 1 && 
			(get_binary_tree_frequency(hp->data[current]) < get_binary_tree_frequency(hp->data[parent_index]) ||
				(get_binary_tree_frequency(hp->data[current]) <= get_binary_tree_frequency(hp->data[parent_index])
					&&(get_binary_tree_value(hp->data[current])=='*' && get_binary_tree_value(hp->data[parent_index])!='*'))
				))
		{
			/* Troca de nós */
			aux = hp->data[current];
			hp->data[current] = hp->data[parent_index];
			hp->data[parent_index] = aux;

			current = parent_index;
			parent_index = get_parent_index(current);
		}
	}

}

/* Retorna o pai do índice */
int get_parent_index(int i) {return i/2;}

/* Retorna o filho esquerdo do índice */
int get_left_index(int i) {return 2*i;}

/* Retorna o filho direito do índice */
int get_right_index(int i) {return 2*i + 1;}

/* Ordena a Heap em ordem decrescente */
void min_heapify(heap *heap, int index)
{
	int largest;
	int left = get_left_index(index);
	int right = get_right_index(index);

	if (left <= heap->size && (get_binary_tree_frequency(heap->data[left]) < get_binary_tree_frequency(heap->data[index]) ||
	(get_binary_tree_frequency(heap->data[left]) <= get_binary_tree_frequency(heap->data[index])
		&& get_binary_tree_value(heap->data[left])=='*' && get_binary_tree_value(heap->data[index])!='*' )))
	{
		largest = left;
	}
	else
	{
		largest = index;
	}
	if (right <= heap->size && (get_binary_tree_frequency(heap->data[right]) < get_binary_tree_frequency(heap->data[largest]) ||
		(get_binary_tree_frequency(heap->data[right]) <= get_binary_tree_frequency(heap->data[largest])
			&& get_binary_tree_value(heap->data[right])=='*' && get_binary_tree_value(heap->data[largest])!='*' )))
	{
		largest = right;
	}
	if (get_binary_tree_frequency(heap->data[index]) != get_binary_tree_frequency(heap->data[largest]) || 
			((get_binary_tree_frequency(heap->data[index]) == get_binary_tree_frequency(heap->data[largest]))
				&&  get_binary_tree_value(heap->data[index])!='*' && get_binary_tree_value(heap->data[largest])=='*' ))
	{
		binary_tree* aux;
		/* Troca de nós */
		aux = heap->data[index];
		heap->data[index] = heap->data[largest];
		heap->data[largest] = aux;

		min_heapify(heap, largest);
	}
}

/* Retorna o nó da árvore de menor frequência */
binary_tree* dequeue(heap *heap)
{
	if (heap->size)
	{
		binary_tree* aux;
		aux = heap->data[1];
		heap->data[1] = heap->data[heap->size];
		heap->size--;
	
		min_heapify(heap, 1);
		return aux;
	}
	else
	{
		return NULL;
	}
}

/* Retona o tamanho da Heap */
int get_heap_size(heap* heap)
{
	return heap->size;
}

/* Imprime a Heap */
void print_heap(heap* heap)
{
	int i;
	for (i = 1; i <= heap->size; ++i)
	{
		printf("[%c|", get_binary_tree_value(heap->data[i]));
		printf("%d] ", get_binary_tree_frequency(heap->data[i]));
	}
	printf("\n");
}

void build_minheap(heap *heap)
{
	int i;
	for (i = (heap->size)/2; i >=  1; --i)
	{
		min_heapify(heap, i);
	}
}