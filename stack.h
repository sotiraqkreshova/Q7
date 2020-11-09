#include <iostream>
#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#define MAX_SIZE 500

using namespace std;

class Stack {
private: char data[MAX_SIZE];
       int size;
public: Stack();
      bool isFull();
      bool isEmpty();
      bool push(char data);
      char pop();
      int  getSize();
      void printAll();
      bool update(int pos, char data);
};

#endif // STACK_H_INCLUDED#pragma once
