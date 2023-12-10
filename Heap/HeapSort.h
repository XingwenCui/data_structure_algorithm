#ifndef HEAPSORT_H
#define HEAPSORT_H

#include<iostream>
#include<algorithm>

template<typename T>
void __shiftDown(T arr[], int n, int k) {
    T e = arr[k];
    while (2*k+1 < n) {
        int j = 2*k+1;
        if (j+1 < n && arr[j+1]>arr[j])
            j+=1;
        if (e >= arr[j]) break;
        arr[k] = arr[j];
        k=j;
    }
    arr[k] = e;
}

template<typename T>
void heapSort(T arr[], int n) {
    // heap从0开始索引
    for (int i = (n-1-1)/2; i >= 0; i--)
        __shiftDown(arr, n, i);
    for (int i = n-1; i>0; i--) {
        std::swap(arr[0], arr[i]);
        __shiftDown(arr, i, 0);
    }
}

#endif  // HEAPSORT_H