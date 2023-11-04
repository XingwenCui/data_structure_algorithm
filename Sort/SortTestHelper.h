#ifndef SORTTESTHELPER_H
#define SORTTESTHELPER_H

#include<iostream>
#include<algorithm>
#include<string>
#include<ctime>
#include<cassert>
#include<string>

namespace SortTestHelper {

    // 生成有n个元素的随机数组，每个元素的随机范围为[rangeL, rangeR]
    int *generateRandomArray(int n, int range_l, int range_r) {
        int *arr = new int[n]; // 这里用new在heap上分配了内存，使外部可以访问
        std::srand(std::time(NULL));    // 以时间的long数据设置随机数种子
        for (int i = 0; i < n; i++) {   
            // 生成n个随机数
            arr[i] = std::rand() % (range_r - range_l + 1) + range_l;
        }
        return arr;
    }   

    // 生成一个近乎有序的数组, Swaptimes是交换次数
    int *generateNearlyOrderedArray(int n, int swapTimes) {
        int *arr = new int[n];
        for (int i = 0; i<n; i++) {
            arr[i] = i;         // 简单的有序array
        }
        std::srand(std::time(NULL));
        for (int i = 0; i < swapTimes; i++) {
            int posx = rand()%n;// 生成n内的随机int作为index
            int posy = rand()%n;
            std::swap(arr[posx], arr[posy]);
        }
        return arr;
    }

    // copy一个int数组，并返回新数组
    int *copyIntArray(int a[], int n) {
        int *arr = new int[n];
        std::copy(a, a+n, arr);
        return arr;
    }

    // print数组中的内容
    template<typename T>
    void printArray(T arr[], int n) {
        for (int i = 0; i < n; i++) 
            std::cout<< arr[i] <<" ";
        std::cout<<std::endl;
    }

    // 判断array是否为倒序
    template<typename T>
    bool isSortedAsc(T arr[], int n) {
        for (int i = 0; i<n-1; i++){
            if (arr[i] > arr[i+1])
                return false;
        }
        return true;
    }

    template<typename T>
    bool isSortedDes(T arr[], int n) {
        for (int i = 0; i<n-1; i++){
            if (arr[i] < arr[i+1])
                return false;
        }
        return true;
    }

    template<typename T>
    bool isSorted(T arr[], int n) {
        return isSortedAsc(arr, n) || isSortedDes(arr, n);
    }


    // 测试sort算法结果正确性以及运行时间
    template<typename T>
    void testSort(const std::string &sortName, void (*sort)(T[], int), T arr[], int n) {
        
        std::clock_t startTime = clock();
        sort(arr, n);
        std::clock_t endTime = clock();
        assert(isSorted(arr, n));
        std::cout<<sortName<<":"<<double(endTime-startTime)/CLOCKS_PER_SEC<<" s"<<std::endl;
    }
};

#endif // SORTTESTHELPER_H