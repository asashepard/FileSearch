#include "linkedlist.h"
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;
using namespace s;

node::node() {
    next = nullptr;
    value = nullptr;
}

node::node(void *data) {
    next = nullptr;
    value = data;
}

linkedlist::linkedlist() = default;

void linkedlist::add(void *value) {
    node *n = new node(value);

    if (head == nullptr) {
        head = n;
        length = 1;
        return;
    }

    // traverse linked list
    node *current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    // Insert at the last.
    current->next = n;

    length++;
}

void linkedlist::clear() {
    while (head != nullptr) {
        remove(0);
    }
}

bool linkedlist::equals(linkedlist s) {
    // traverse both linked lists
    node *current = head;
    node *c = s.head;
    while (current != nullptr && c != nullptr) {
        if (current->value != c->value) {
            return false;
        }
    }
    return true;
}

void *linkedlist::get(int index) {
    int c;
    node *i;

    i = head;
    for (c = 0; c < index; c++) {
        i = i->next;
    }
    return i->value;
}

node *linkedlist::retrieve(int index) {
    int c;
    node *i;

    i = head;
    for (c = 0; c < index; c++) {
        i = i->next;
    }
    return i;
}

void linkedlist::insert(int index, void *value) {
    // create new node
    node *n = new node();
    n->value = value;

    // traverse linked list
    int i = 0;
    node *current = head;
    node *previous;
    while (current != nullptr && i++ != index) {
        previous = current;
        current = current->next;
    }
    // add new node
    if (current == head) {
        n->next = head;
        head = current->next;
    } else {
        previous->next = n;
        n->next = current;
    }

    length++;
}

void linkedlist::exchg(int index1, int index2) {
    node * i1pointer;
    node * i2pointer;
    // traverse linked list
    int i = 0;
    node * current = head;
    while (current != nullptr) {
        if (i == index1) {
            i1pointer = current;
        }
        if (i == index2) {
            i2pointer = current;
        }
        i++;
        current = current->next;
    }
    // swap payload data (pointers)
    void * temp;
    temp = i1pointer->value;
    i1pointer->value = i2pointer->value;
    i2pointer->value = temp;
}

void linkedlist::swap(int index1, int index2) {
    cout << "swapping" << endl;
    cout << index1 << " " << index2 << endl;
    if (index1 == index2)
        return;

    // traverse linked list
    node *prevY;
    node *currY = head;
    node *prevX;
    node *currX = head;
    for (int i = 0; i < index1; i++) {
        prevX = currX;
        currX = currX->next;
    }
    for (int i = 0; i < index2; i++) {
        prevY = currY;
        currY = currY->next;
    }

    if(currX == nullptr || currY == nullptr) return;

    if (prevX != nullptr) // x not head
        prevX->next = currY;
    else
        head = currY;

    if (prevY != nullptr) // y not head
        prevY->next = currX;
    else
        head = currX;

    node * temp = currY->next;
    currY->next = currX->next;
    currX->next = temp;
}

bool linkedlist::isEmpty() {
    return length == 0;
}

void linkedlist::remove(int index) {
    node *temp1 = head, *temp2 = nullptr;

    if (length < index) {
        cout << "Index out of range" << endl;
        return;
    }

    temp1 = head;

    if (index == 1) { // delete, update head
        head = head->next;
        delete temp1;
        return;
    }

    // traverse
    while (index-- > 1) {
        temp2 = temp1;
        temp1 = temp1->next;
    }

    temp2->next = temp1->next;

    delete temp1;
}

void linkedlist::set(int index, void *value) {
    remove(index);
    insert(index, value);
}

int linkedlist::size() {
    return length;
}

linkedlist linkedlist::subList(int start, int subListLength) {
    linkedlist result;

    // traverse
    int i = 0;
    int d = 0;
    node *current = head;
    while (current != nullptr) {
        if (i++ > start && d < subListLength) {
            result.add(current->value);
            d++;
        }
        current = current->next;
    }
    return result;
}
