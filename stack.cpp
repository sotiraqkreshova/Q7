#include "stack.h"

Stack::Stack()
{
    size = 0;
}


bool Stack::isFull() {
    return size == MAX_SIZE;
}
bool Stack::isEmpty() {
    return size == 0;
}

bool Stack::push(char data) {
    if (isFull()) return false;
    this->data[size] = data;
    size++;
}
char Stack::pop() {
    if (isEmpty()) return '~';
    size--;
    return this->data[size];
}
int  Stack::getSize() {
    return size;
}

void Stack::printAll() {
    if (isEmpty()) {
        cout << "No data to print" << endl;
        return;
    }
    for (int i = 0; i < size; i++)
    {
        cout << "element in pos : (" << i + 1 << ") :" << data[i] << endl;
    }
}

bool Stack::update(int pos, char data)
{
    if (pos > size) return false;
    this->data[pos - 1] = data;
    return true;
}