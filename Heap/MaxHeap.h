#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cmath>
#include <cassert>

template<typename Item>
class MaxHeap {
private:
    Item *data;
    int count;
    int capacity;

    // 添加新元素，用shiftUp的方法
    void shiftUp(int k) {
        while (k>1 && data[k/2] < data[k]) {
            std::swap(data[k/2], data[k]);
            k /= 2;
        }
    }

    void shiftDown(int k) {
        while (2*k <= count) {
            int j = 2*k;    // data[k]和data[i]交换位置
            if (j+1 <= count && data[j+1] > data[j])
                j++;
            if (data[k] >= data[j]) break;
            std::swap(data[k], data[j]);
            k=j;
        }
    }

public:

    // constructor, 初始化Heap，设置容量
    MaxHeap(int capacity) {
        data = new Item[capacity+1];    
        count = 0;
    }
    // deconstuctor
    ~MaxHeap() {
        delete[] data;      // 对象array一定要用[]
    }

    // 返回元素个数
    int size() {return count;}
    
    // 堆是否为空
    bool isEmpty() {return count==0;}

    // 增：插入一个新元素
    void insert(Item item) {
        assert(count+1 <= capacity);
        // 先把item放入heap
        data[count+1] = item;
        count++;
        // 再调整位置
        shiftUp(count);
    }

    Item extractMax() {
        assert(count > 0);
        Item ret = data[1];

        std::swap(data[1], data[count]);
        count--;
        shiftDown(1);
        return ret;
    }

    int getMax() {
        assert(count>0);
        return data[1];
    }

    // 打印整个heap
    void testPrint() {
        // 我们只能打印100个元素以内的信息
        if (size() >= 100) {
            std::cout<<"Can only work for less than 100 int"<<std::endl;
            return;
        }
        // 只能处理整数信息
        if (typeid(Item) != typeid(int)) {
            std::cout<<"Can only work for int item"<<std::endl;
            return;
        }

        std::cout<<"The max heap size is: "<<size()<<std::endl;
        std::cout<<"Data in the max heap :";
        for (int i=1; i<=size(); i++) {
            assert(data[i]>=0 && data[i]<100);
            std::cout<<data[i]<<" ";
        }
        std::cout<<std::endl;
        std::cout<<std::endl;
    
        int n = size(), max_level = 0, number_per_level = 1;
        while (n>0) {
            max_level += 1;
            n -= number_per_level;
            number_per_level *= 2;  // 每层的node个数，由于是完全二叉，所以每层是2的次方数
        }

        int max_level_number = int(pow(2, max_level-1)); // 最深层的节点个数
        int cur_tree_max_level_number = max_level_number;
        int index = 1;
        for (int level = 0; level < max_level; level++) {
            std::string line1 = std::string(max_level_number*3-1, ' ');
            int cur_level_number = std::min(count - int(pow(2,level))+1, int(pow(2,level)));
            bool isLeft = true;
            for (int index_cur_level = 0; index_cur_level < cur_level_number; index++, index_cur_level++) {
                putNumberInLine( data[index] , line1 , index_cur_level , cur_tree_max_level_number*3-1 , isLeft );
                isLeft = !isLeft;
            }
            std::cout<<line1<<std::endl;

            if( level == max_level - 1 )
                break;

            std::string line2 = std::string(max_level_number*3-1, ' ');
            for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index_cur_level ++ )
                putBranchInLine( line2 , index_cur_level , cur_tree_max_level_number*3-1 );
            std::cout<<line2<<std::endl;

            cur_tree_max_level_number /= 2;
        }
    }

    void putNumberInLine( int num, std::string &line, int index_cur_level, int cur_tree_width, bool isLeft){

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int offset = index_cur_level * (cur_tree_width+1) + sub_tree_width;
        assert(offset + 1 < line.size());
        if( num >= 10 ) {
            line[offset + 0] = '0' + num / 10;
            line[offset + 1] = '0' + num % 10;
        }
        else{
            if( isLeft)
                line[offset + 0] = '0' + num;
            else
                line[offset + 1] = '0' + num;
        }
    }

    void putBranchInLine( std::string &line, int index_cur_level, int cur_tree_width){

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int sub_sub_tree_width = (sub_tree_width - 1) / 2;
        int offset_left = index_cur_level * (cur_tree_width+1) + sub_sub_tree_width;
        assert( offset_left + 1 < line.size() );
        int offset_right = index_cur_level * (cur_tree_width+1) + sub_tree_width + 1 + sub_sub_tree_width;
        assert( offset_right < line.size() );

        line[offset_left + 1] = '/';
        line[offset_right + 0] = '\\';
    }
        
};

#endif  // MAXHEAP_H