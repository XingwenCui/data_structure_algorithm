#ifndef QUICKSORT_H
#define QUICKSORT_H

#include<iostream>
#include<algorithm>
#include"InsertionSort.h"

// 对arr[l..r]部分进行partition（分隔）操作
// 返回j使得 arr[l..j-1] < arr[j] < arr[j+1..r]
template<typename T>
int _partition(T arr[], int l, int r) {
    // 随机在arr[l..r]范围中选择一个数值作为pivot
    std::swap(arr[l], arr[rand()%(r-l+1)+l]);

    T v = arr[l];   // 取最左边的值
    int j = l;      // 取l为初始的idx
    for (int i = l+1; i<=r; i++) {
        if (arr[i] < v) {// 只要当前值比pivot小，就换到j的后一位 
            j++;
            std::swap(arr[j], arr[i]);
        }
    }
    std::swap(arr[l], arr[j]);
    return j;
}

// 对arr[l..r]部分进行快速排序
template<typename T>
void _quickSort(T arr[], int l, int r) {
    // 对于小规模数组，使用插入排序进行优化，提高性能
    if (r-l <= 15){
        insertionSort(arr, l, r);
        return;
    }

    int p = _partition(arr, l, r);
    _quickSort(arr, l, p-1);
    _quickSort(arr, p+1, r);
}

template<typename T>
void quickSort(T arr[], int n) {
    srand(time(NULL));  // 随机选pivot
    _quickSort(arr, 0, n-1);
}

#endif // QUICKSORT_H