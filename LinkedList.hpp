#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <cstddef>
using namespace std;

class LinkedList
{
private:
    struct Node {
        Node* next;
        string data;
        Node(string d, Node* n) : data(d), next(n) {}
    };
    Node* head_;
public:
    LinkedList() {
        head_ = nullptr;
    }
    ~LinkedList() {
        clear();
    }
    bool empty() {
        return (head_ == nullptr);
    }
    int size() {
        int count = 0;
        Node* p = head_;
        while (p != nullptr) {
            ++count;
            p = p->next;
        }
        return count;
    }
    void pushFront(string value) {
        Node* newNode = new Node(value, head_);
        head_ = newNode;
    }
    void pushBack(string value) {
        Node* newNode = new Node(value, nullptr);
        if (head_ == nullptr) {
            head_ = newNode;
            return;
        }
        Node* p = head_;
        while (p->next != nullptr) {
            p = p->next;
        }
        p->next = newNode;
    }
    string popFront() {
        Node* old = head_;
        string value = old->data;
        head_ = old->next;
        delete old;
        return value;
    }
    void clear() {
        Node* p = head_;
        while (p != nullptr) {
            Node* nxt = p->next;
            delete p;
            p = nxt;
        }
        head_ = nullptr;
    }
};

#endif