#include "linkedlist.h"
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <cfloat>
#include <valarray>

using namespace std;
using namespace s;

void quickSort(node * start, node * end);
node * partition (node * start, node * end);
float distVal (string * a);
list<string> find(linkedlist sl, string s);

map<char, float> qwerty = {{'q', 0.0F}, {'a', 0.33F}, {'z', 0.67F},
                           {'w', 1.0F}, {'s', 1.33F}, {'x', 1.67F},
                           {'e', 2.0F}, {'d', 2.33F}, {'c', 2.67F},
                           {'r', 3.0F}, {'f', 3.33F}, {'v', 3.67F},
                           {'t', 4.0F}, {'g', 4.20F}, {'b', 4.40F}, {'y', 4.60F}, {'h', 4.80F},
                           {'u', 5.0F}, {'j', 5.33F}, {'n', 5.67F},
                           {'i', 6.0F}, {'k', 6.33F}, {'m', 6.67F},
                           {'o', 7.0F}, {'l', 7.33F},
                           {'p', 8.0F}}; //grouped by keyboard closeness to account primarily for common typos

int main() {
    linkedlist sl;

    //FOR TEST
    sl.add(new string("hello"));
    sl.add(new string("wonderful"));
    sl.add(new string("world"));
    sl.add(new string("aardvarks"));
    sl.add(new string("admonish"));
    sl.add(new string("artistic"));
    sl.add(new string("zany"));
    sl.add(new string("ant"));
    sl.add(new string("or"));
    sl.add(new string("artichoke"));
    sl.add(new string("consumers"));
    sl.add(new string("however"));
    sl.add(new string("until"));
    sl.add(new string("dawn"));

    string searchWord;
    std::cout << "search for a word (file):" << endl;
    cin >> searchWord;
    list<string> res = find(sl, searchWord);

    //PRINT
    int i = 1;
    for (string str : res) {
        cout << i++ << ". " << str << endl;
    }
}

void quickSort(node * start, node * end) {
    if (start == end) return;
    struct node * pivot = partition(start, end);
    if (pivot != nullptr && pivot->next != nullptr) quickSort(pivot->next, end);
    if (pivot != nullptr && start != pivot) quickSort(start, pivot);
}

node * partition(node * start, node * end) {
    struct node* pivot = start;
    struct node* front = start;
    void * temp;
    while (front != nullptr && front != end) {
        if (distVal((string *)front->value) < distVal((string *)end->value)) {
            pivot = start;

            //swap start and front values
            temp = start->value;
            start->value = front->value;
            front->value = temp;

            start = start->next;
        }

        front = front->next;
    }

    //change last node value to current
    temp = start->value;
    start->value = end->value;
    end->value = temp;
    return pivot;
}

float distVal(string * a) {
    float val = 0.0F;
    float multiplier = 1000.0F;
    for (char c : *a) {
        val += ((c >= 97) ? qwerty.at(c) : qwerty.at((char)(c + 32))) * multiplier;
        multiplier /= 10; //different characters have different impact
    }
    return val;
}

list<string> find(linkedlist sl, string s) {
    list<string> result;

    quickSort(sl.retrieve(0), sl.retrieve(sl.size() - 1));

    for (int i = 0; i < sl.size(); i++) {
        auto * a = (string *)sl.get(i);
        float val = distVal(a);
        //cout << "distval " << *a << ": " << val << endl;
    }

    //cout << endl << "distval " << s << ": " << distVal(&s) << endl;

    //get index of closest
    int closestIndex = 0;

    float lastDiff = FLT_MAX;
    float toCompare = distVal(&s);
    for (int i = 0; i < sl.size(); i++) {
        auto * candidate = (string *)sl.get(i);
        float diff = abs(distVal(candidate) - toCompare);
        if (diff < lastDiff) {
            closestIndex = i;
            lastDiff = diff;
        }
    }

    //push closest and surrounding
    int i = 1;
    result.push_back(*(string *)sl.get(closestIndex));
    if (closestIndex != 0) { result.push_back(*(string *)sl.get(closestIndex - 1)); i++; }
    if (closestIndex != sl.size() - 1) { result.push_back(*(string *)sl.get(closestIndex + 1)); i++; }

    return result;
}
