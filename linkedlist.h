#ifndef FILESEARCH_SLIST_H

#include <string>

namespace s {

    class node {
    public:
        node * next;
        void * value;
        node();
        node(void * data);
    };

    class linkedlist {
    public:
        node * head{};
        int length{};

        linkedlist();
        void add(void * value);
        void clear();
        bool equals(linkedlist s);
        void * get(int index);
        node * retrieve(int index);
        void insert(int index, void * value);
        void exchg(int index1, int index2);
        void swap(int index1, int index2);
        bool isEmpty();
        void remove(int index);
        void set(int index, void * value);
        int size();
        linkedlist subList(int start, int length);
    };

}

#endif
