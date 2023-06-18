#ifndef MINHEAP
#define MINHEAP

typedef struct MinHeapNode{
    int  v;
    int dist;
}MinHeapNode;

typedef struct MinHeap
{
    int size;    
    int capacity; 
    int *pos;   
    struct MinHeapNode **array;
}MinHeap;

MinHeap* criarMinHeap(int capacity);
MinHeapNode * novoMinHeapNo(int v, int dist);
bool estaNoHeap( MinHeap *minHeap, int v);
void atualizarHeap( MinHeap* minHeap,int v, int dist);
MinHeapNode* mininoElemento( MinHeap*minHeap);
int vazio( MinHeap* minHeap);
void minHeapify( MinHeap* minHeap,int idx);
void trocarMinHeapNo( MinHeapNode** a, MinHeapNode** b);

#endif