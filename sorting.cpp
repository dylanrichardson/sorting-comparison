#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "sorting.h"
#include <math.h>
#include <conio.h>
#include <stdio.h>

using namespace std;

void bubbleSort(int array[], int length) {
    int i, j, tmp;
    for (i = 0; i < length - 1; ++i) {
        for (j = 0; j < length - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
}

void heapSort(int array[], int length) {
    vector < int > v(array, array + length);
    make_heap(v.begin(), v.end());
    pop_heap(v.begin(), v.end());
    v.pop_back();
    v.push_back(99);
    std::push_heap(v.begin(), v.end());
    sort_heap(v.begin(), v.end());
    copy(v.begin(), v.end(), array);
}

void insertionSort(int array[], int length) {
    int i, j, tmp;
    for (i = 1; i < length; i++) {
        j = i;
        while (j > 0 && array[j - 1] > array[j]) {
            tmp = array[j];
            array[j] = array[j - 1];
            array[j - 1] = tmp;
            j--;
        }
    }
}

void quickSort(int array[], int length) {
    qsort(array, length, sizeof(int), compare);
}

int compare(const void * a,
    const void * b) {
    return ( * (int * ) a - * (int * ) b);
}

void mergeSort(int arr[], int size) {
    if (size == 1)
        return;

    int size1 = size / 2, size2 = size - size1;
    mergeSort(arr, size1);
    mergeSort(arr + size1, size2);
    merge(arr, size1, size2);
}

void merge(int * arr, int size1, int size2) {
    int temp[size1 + size2];
    int ptr1 = 0, ptr2 = 0;

    while (ptr1 + ptr2 < size1 + size2) {
        if (ptr1 < size1 && arr[ptr1] <= arr[size1 + ptr2] || ptr1 < size1 && ptr2 >= size2)
            temp[ptr1 + ptr2] = arr[ptr1++];

        if (ptr2 < size2 && arr[size1 + ptr2] < arr[ptr1] || ptr2 < size2 && ptr1 >= size1)
            temp[ptr1 + ptr2] = arr[size1 + ptr2++];
    }

    for (int i = 0; i < size1 + size2; i++)
        arr[i] = temp[i];
}

void proxmapSort(int array[], int length) {
    // TODO
}

void radixSort(int array[], int length) {
    int max = getMax(array, length);
    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(array, length, exp);
}

void countSort(int arr[], int n, int exp) {
    int output[n];
    int i, count[10] = {
        0
    };
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

int getMax(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void selectionSort(int array[], int length) {
    int pos_min, temp;
    for (int i = 0; i < length - 1; i++) {
        pos_min = i;
        for (int j = i + 1; j < length; j++) {
            if (array[j] < array[pos_min])
                pos_min = j;
        }
        if (pos_min != i) {
            temp = array[i];
            array[i] = array[pos_min];
            array[pos_min] = temp;
        }
    }
}

void shellSort(int array[], int length) {
    int i, temp, flag = 1;
    int d = length;
    while (flag || (d > 1)) {
        flag = 0;
        d = (d + 1) / 2;
        for (i = 0; i < (length - d); i++) {
            if (array[i + d] < array[i]) {
                temp = array[i];
                array[i] = array[i + d];
                array[i + d] = temp;
                flag = 1;
            }
        }
    }
}

void treeSort(int array[], int length) {
    btree tree;
    for (int i = 0; i < length; i++)
        tree.insert(array[i]);
    tree.sortedArr();
}

btree::btree() {
    root = NULL;
}

btree::~btree() {
    destroy_tree();
}

void btree::destroy_tree(node * leaf) {
    if (leaf != NULL) {
        destroy_tree(leaf - > left);
        destroy_tree(leaf - > right);
        delete leaf;
    }
}

void btree::insert(int key, node * leaf) {
    if (key < leaf - > key_value) {
        if (leaf - > left != NULL)
            insert(key, leaf - > left);
        else {
            leaf - > left = new node;
            leaf - > left - > key_value = key;
            leaf - > left - > left = NULL; //Sets the left child of the child node to null
            leaf - > left - > right = NULL; //Sets the right child of the child node to null
        }
    } else if (key >= leaf - > key_value) {
        if (leaf - > right != NULL)
            insert(key, leaf - > right);
        else {
            leaf - > right = new node;
            leaf - > right - > key_value = key;
            leaf - > right - > left = NULL; //Sets the left child of the child node to null
            leaf - > right - > right = NULL; //Sets the right child of the child node to null
        }
    }
}

node * btree::search(int key, node * leaf) {
    if (leaf != NULL) {
        if (key == leaf - > key_value)
            return leaf;
        if (key < leaf - > key_value)
            return search(key, leaf - > left);
        else
            return search(key, leaf - > right);
    } else
        return NULL;
}

void btree::insert(int key) {
    if (root != NULL)
        insert(key, root);
    else {
        root = new node;
        root - > key_value = key;
        root - > left = NULL;
        root - > right = NULL;
    }
}

node * btree::search(int key) {
    return search(key, root);
}

void btree::destroy_tree() {
    destroy_tree(root);
}

void btree::sortedArr() {
    int count = 0;
    cout << root - > key_value;
}
