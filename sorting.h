#ifndef SORTING_H
#define SORTING_H

using namespace std;

void bubbleSort(int[], int);
void heapSort(int[], int);
void insertionSort(int[], int);
void quickSort(int[], int);
int compare(const void *, const void *);
void mergeSort(int[], int);
void merge(int *, int, int);
void proxmapSort(int[], int);
void radixSort(int[], int);
void countSort(int[], int, int);
int getMax(int[], int);
void selectionSort(int[], int);
void shellSort(int[], int);
void treeSort(int[], int);

struct node {
    int key_value;
    node * left;
    node * right;
};

class btree {
    public:
        btree();
	    ~btree();

	    void insert(int key);
	    node * search(int key);
	    void destroy_tree();
	    void sortedArr();

    private:
        void destroy_tree(node * leaf);
	    void insert(int key, node * leaf);
	    node * search(int key, node * leaf);

	    node * root;
};

#endif
