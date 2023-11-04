#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

#include<algorithm>

template<typename T> // 函数模板
void selectionSort(T arr[], int n) {
    // 选择排序
    for (int i = 0; i < n; i++) {
        int minIdx = i; // 最小值优先
        for (int j = i+1; j < n; j++){ 
            if (arr[j] < arr[minIdx]) {    // 找最小的
                minIdx = j;                // 找到小的就记录当前idx
            }
        }
        std::swap(arr[i], arr[minIdx]);
    }
}

#endif // SELECTIONSORT_H