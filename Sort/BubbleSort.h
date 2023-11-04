#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <algorithm>

template<typename T>
void bubbleSort(T arr[], int n) {
    for (int i = 0; i<n-1; i++) {
        bool swapped = false;   // 如果一轮没换说明已经排好了
        // 降序操作，最小值先排到最后
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] < arr[j+1]){
                std::swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

#endif  // BUBBLESORT_H