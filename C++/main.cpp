/* 
* main.cpp
*
* author:  Jack Fletcher
* date:    10/23/2016
*
* CSE 2383 Data Structures
* Honors Assignment
*
* This is a test file for SkipList, LinkedList, and BinarySearchTree data structures.
*
*/


#include <fstream>
#include <iostream>
#include <random>
#include <chrono>
#include "SkipList.h"
#include "BinarySearchTree.h"
#include "LinkedList.h"

using namespace std;


void print_skiplist();
void test_timing(ofstream& time_csv, bool test_linked_list);
void test_delete();

void write_to_csv(ofstream& file, long n, long long time, string structure, string operation) {
    float tpo = (float) time / n;
    file << n << ',' << time << ',' << tpo << ',' << structure << ',' << operation << ',' << endl;
}


int main() {
    ofstream time_csv("timing_results.csv", std::ios::app | std::ios::out);
    time_csv << "n, time, tpo, structure, operation" << endl;

    bool loop = true;
    while (loop) {
        int choice;
        cout << "Pick:" << endl;
        cout << "(1) print example skip list" << endl;
        cout << "(2) test timing (skip list, binary tree, and linked list)" << endl;
        cout << "(3) test timing (skip list and binary tree)" << endl;
        cout << "(4) test deletion" << endl;
        cout << "(9) exit" << endl;
        cin >> choice;

        switch (choice) {
        case 1: 
            print_skiplist();
            break;
        case 2:
            test_timing(time_csv, true);
            break;
        case 3:
            test_timing(time_csv, false);
            break;
        case 4: 
            test_delete();
            break;
        case 9: 
            loop = false;
            break;
        default: break;
        }

        cout << endl;

    }
    return 0;
}


void print_skiplist() {
    ofstream SLoutFile("SL.txt");
    SkipList<int> *SLprint = new SkipList<int>(0, 9999);

    random_device print_rand_dev;
    mt19937 print_generator(print_rand_dev());
    uniform_int_distribution<int> print_distr(1, 9998);

    int example_points[100];
    for (int i = 0; i < 100; ++i)
        example_points[i] = print_distr(print_generator);

    for (int i = 0; i < 100; i++)
        SLprint->insert(example_points[i]);

    SLprint->print_list(SLoutFile);

    SLoutFile.close();
    delete SLprint;
}


void test_timing(ofstream& time_csv, bool test_linked_list) {
    string structure;
    string operation;
    long size_n;

    const long int min_key = 0;
    const long int max_key = LONG_MAX;

    // prompt for n
    cout << "Enter size of input: ";
    cin >> size_n;

    // create random number generator and generate values
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<long> distr(min_key + 1, max_key - 1);

    long *dist = new long[size_n];
    for (long i = 0; i < size_n; ++i)
        dist[i] = distr(generator);


    // Skip List
    structure = "skip list";
    cout << "----Skip List----" << endl;
    SkipList<long> *skiplist = new SkipList<long>(min_key, max_key);

    // insert
    operation = "insert";
    chrono::steady_clock::time_point t0 = chrono::steady_clock::now();
    for (long i = 0; i < size_n; i++)
        skiplist->insert(dist[i]);
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
    cout << "insert: " << duration << endl;

    write_to_csv(time_csv, size_n, duration, structure, operation);

    // search
    operation = "search";
    t0 = chrono::steady_clock::now();
    for (long i = 0; i < size_n; i++)
        skiplist->search(dist[i]);
    t1 = chrono::steady_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
    cout << "search: " << duration << endl;
    write_to_csv(time_csv, size_n, duration, structure, operation);

    // delete
    operation = "delete";
    t0 = chrono::steady_clock::now();
    for (long i = 0; i < size_n; i++)
        skiplist->remove(dist[i]);
    t1 = chrono::steady_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
    cout << "delete: " << duration << endl << endl;
    write_to_csv(time_csv, size_n, duration, structure, operation);

    delete skiplist;


    // Binary Tree
    structure = "binary tree";
    cout << "----Binary Tree---" << endl;
    BSTree *binarytree = new BSTree();

    // insert
    operation = "insert";
    t0 = chrono::steady_clock::now();
    for (long i = 0; i < size_n; i++)
        binarytree->insert(dist[i]);
    t1 = chrono::steady_clock::now();

    duration = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
    cout << "insert: " << duration << endl;
    write_to_csv(time_csv, size_n, duration, structure, operation);

    // search
    operation = "search";
    t0 = chrono::steady_clock::now();
    for (long i = 0; i < size_n; i++)
        binarytree->search(dist[i]);
    t1 = chrono::steady_clock::now();

    duration = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
    cout << "search: " << duration << endl;
    write_to_csv(time_csv, size_n, duration, structure, operation);

    // delete
    operation = "delete";
    t0 = chrono::steady_clock::now();
    for (long i = 0; i < size_n; i++)
        binarytree->remove(dist[i]);
    t1 = chrono::steady_clock::now();

    duration = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
    cout << "delete: " << duration << endl << endl;
    write_to_csv(time_csv, size_n, duration, structure, operation);
    
    delete binarytree;

    if (test_linked_list) {
        // Linked List
        structure = "linked list";
        cout << "----Linked List----" << endl;

        LinkedList<long> *linkedlist = new LinkedList<long>();

        // insert
        operation = "insert";
        t0 = chrono::steady_clock::now();
        for (long i = 0; i < size_n; i++)
            linkedlist->insert(dist[i]);
        t1 = chrono::steady_clock::now();

        duration = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
        cout << "insert: " << duration << endl;
        write_to_csv(time_csv, size_n, duration, structure, operation);

        // search
        operation = "search";
        t0 = chrono::steady_clock::now();
        for (long i = 0; i < size_n; i++)
            linkedlist->search(dist[i]);
        t1 = chrono::steady_clock::now();

        duration = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
        cout << "search: " << duration << endl;
        write_to_csv(time_csv, size_n, duration, structure, operation);

        // delete
        operation = "delete";
        t0 = chrono::steady_clock::now();
        for (long i = 0; i < size_n; i++)
            linkedlist->remove(dist[i]);
        t1 = chrono::steady_clock::now();

        duration = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
        cout << "delete: " << duration << endl << endl;
        write_to_csv(time_csv, size_n, duration, structure, operation);

        delete linkedlist;
    }

    delete[] dist;
}


void test_delete() {
    ofstream SL_delete("SL_delete.txt");
    ofstream SL_delete15("SL_delete15.txt");

    SkipList<int> *skiplist_delete = new SkipList<int>(0, 50);
    int arr[5] = { 10, 15, 20, 30, 40 };

    // insert
    skiplist_delete->insert(arr[0]);
    skiplist_delete->insert(arr[1]);
    skiplist_delete->insert(arr[2]);
    skiplist_delete->insert(arr[3]);
    skiplist_delete->insert(arr[4]);

    skiplist_delete->print_list(SL_delete);

    skiplist_delete->remove(15);

    skiplist_delete->print_list(SL_delete15);

    SL_delete.close();
    SL_delete15.close();

    delete skiplist_delete;
}


