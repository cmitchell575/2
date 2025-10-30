#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

template <typename T>
class LinkedList
{
private:
   struct Node {
    T data;
        Node* next;
        Node(T d, Node* n) : data(d), next(n) {}
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
    void pushFront(T value) {
        Node* newNode = new Node(value, head_);
        head_ = newNode;
    }
    void pushBack(T value) {
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
    T popFront() {
        Node* old = head_;
        T value = old->data;
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