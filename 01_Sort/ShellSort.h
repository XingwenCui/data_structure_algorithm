#ifndef SHELLSORT_H
#define SHELLSORT_H

template<typename T>
void shellSort(T arr[], int n) {

    // Compute increment sequence: 3*h + 1
    int h = 1;
    while (h < n/3)
        h = 3*h + 1;

    while (h >= 1) {
        for (int i = h; i<n; i++) {
            // 对arr[i], arr[i-h], arr[i-2*h]使用插入排序
            T e = arr[i];
            int j;
            for (j = i; j>=h && e<arr[j-h]; j-=h)
                arr[j] = arr[j-h];
            arr[j] = e;
        }
        h /= 3;
    }
}

#endif // SHELLSORT_H