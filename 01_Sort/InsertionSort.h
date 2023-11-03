#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

template<typename T>    // 他可以对任何数据类型的array排序
void insertionSort(T arr[], int n) {
    // 用模板定义的插入排序， 每次将一个待排序的元素插入到前面已经排好的list中
    // Best: O(n); Worst: O(n^2)
    // 从第二个元素开始遍历，默认第一个已经排好了
    for (int i = 1; i<n; i++) {
        T e = arr[i];           // 将待排序的元素存在e中
        int j;                  // 保存元素e应该插入的idx
        // 从i开始找e该插入的idx，可以看到
        // 只要前一个element大于e就往前移一位，并且提前更新第j位置的值
        for (j = i; j > 0 && arr[j-1] > e; j--) {
            arr[j] = arr[j-1];
        }
        // 停止时j位置的就是该插入的位置
        arr[j] = e;
    }

    return;
}

// 对arr[l...r]范围的数组进行插入排序
template<typename T>
void insertionSort(T arr[], int l, int r){

    for( int i = l+1 ; i <= r ; i ++ ) {

        T e = arr[i];
        int j;
        for (j = i; j > l && arr[j-1] > e; j--)
            arr[j] = arr[j-1];
        arr[j] = e;
    }

    return;
}


#endif // INSERTIONSORT_H