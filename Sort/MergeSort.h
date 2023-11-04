#ifndef MERGESORT_H
#define MERGESORT_H

#include<iostream>
#include<algorithm>

// 将arr[l..mid]和arr[mid+1..r]合并，与算法第四版类似
template<typename T>
void __merge(T arr[], int l, int mid, int r) {
    T aux[r-l+1];   // 创建一个动态长度数组，也可以用new方法，但要记得delete
    // T *aux = new T[r-l+1];
    
    for (int i = l; i <= r; i++)    // 给辅助array aux赋值
        aux[i-l] = arr[i];

    // 初始化，i指向左半部分的l，j指向右半部分的mid+1
    int i = l, j = mid+1;
    for (int k = l; k <= r; k++) {
        if (i>mid) {            // 左半部分处理完
            arr[k] = aux[j-l];  
            j++;
        } else if (j>r) {       // 右半部分处理完
            arr[k] = aux[i-l];
            i++;
        } else if (aux[i-l] < aux[j-l]) {   // 左半部分元素<右半部分元素
            arr[k] = aux[i-l];
            i++;
        } else {    // 左半部分>=右半部分
            arr[k] = aux[j-l];
            j++;
        }      
    }
}

// 递归实现mergeSort对l..r范围排序
template<typename T>
void __mergeSort(T arr[], int l, int r) {
    if (l >= r)
        return;
    int mid = (r-l)/2 + l; // 避免overflow
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid+1, r);
    __merge(arr, l, mid, r);
}

// 归并排序算法
template<typename T>
void mergeSort(T arr[], int n) {
    __mergeSort(arr, 0, n-1);
}

#endif // MERGESORT_H