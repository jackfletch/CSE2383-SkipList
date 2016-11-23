/*
* main.cpp
*
* author:  Jack Fletcher
* date:    10/23/2016
*
* CSE 2383 Data Structures
* Honors Assignment
*
* This is a Skip List implementation using SkipListNode.
*
* This class is a friend class of SkipNode and therefore can access the private
* data members of SkipNode directly.
*
*/

#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <iostream>
#include <sstream>
#include "SkipNode.h"

using namespace std;


template <typename T>
class SkipList {
    public:
        SkipList<T>(T min_key, T max_key);
        ~SkipList();

        void insert(T key);
        bool remove(T key);
        SkipNode<T> *search(T key);
        
        void print_list(ofstream& outFile);

        int heightGen();
        
        SkipNode<T> *head;
        SkipNode<T> *tail;
        float prob = 0.5;
        static const int max_height = 16;
        int max_curr_height;
};

#endif
