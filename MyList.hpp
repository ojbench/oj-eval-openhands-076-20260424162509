
#ifndef MYLIST_HPP
#define MYLIST_HPP

#include <stdexcept>

template<typename ValueType>
class MyList {
private:
    struct Node {
        ValueType data;
        Node* prev;
        Node* next;
        
        Node(const ValueType& value) : data(value), prev(nullptr), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int listSize;
    
    Node* getNodeAt(int index) const {
        if (index < 0 || index >= listSize) {
            throw std::out_of_range("Index out of range");
        }
        
        Node* current;
        if (index < listSize / 2) {
            current = head;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
        } else {
            current = tail;
            for (int i = listSize - 1; i > index; --i) {
                current = current->prev;
            }
        }
        return current;
    }

public:
    MyList() : head(nullptr), tail(nullptr), listSize(0) {}
    
    MyList(MyList&& obj) noexcept : head(obj.head), tail(obj.tail), listSize(obj.listSize) {
        obj.head = nullptr;
        obj.tail = nullptr;
        obj.listSize = 0;
    }
    
    MyList(const MyList& obj) : head(nullptr), tail(nullptr), listSize(0) {
        Node* current = obj.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }
    
    ~MyList() {
        clear();
    }

    void push_back(const ValueType& value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        listSize++;
    }
    
    void pop_back() {
        if (tail == nullptr) return;
        
        Node* toDelete = tail;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete toDelete;
        listSize--;
    }
    
    void push_front(const ValueType& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }
        listSize++;
    }
    
    void pop_front() {
        if (head == nullptr) return;
        
        Node* toDelete = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete toDelete;
        listSize--;
    }
    
    ValueType& front() const {
        if (head == nullptr) {
            throw std::runtime_error("List is empty");
        }
        return head->data;
    }
    
    ValueType& back() const {
        if (tail == nullptr) {
            throw std::runtime_error("List is empty");
        }
        return tail->data;
    }
    
    void insert(int index, const ValueType& value) {
        if (index < 0 || index > listSize) {
            throw std::out_of_range("Index out of range");
        }
        
        if (index == 0) {
            push_front(value);
        } else if (index == listSize) {
            push_back(value);
        } else {
            Node* current = getNodeAt(index);
            Node* newNode = new Node(value);
            newNode->prev = current->prev;
            newNode->next = current;
            current->prev->next = newNode;
            current->prev = newNode;
            listSize++;
        }
    }
    
    void erase(int index) {
        if (index < 0 || index >= listSize) {
            throw std::out_of_range("Index out of range");
        }
        
        if (index == 0) {
            pop_front();
        } else if (index == listSize - 1) {
            pop_back();
        } else {
            Node* toDelete = getNodeAt(index);
            toDelete->prev->next = toDelete->next;
            toDelete->next->prev = toDelete->prev;
            delete toDelete;
            listSize--;
        }
    }
    
    int size() const {
        return listSize;
    }
    
    bool empty() const {
        return listSize == 0;
    }
    
    void clear() {
        while (head != nullptr) {
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
        }
        head = tail = nullptr;
        listSize = 0;
    }

    void link(const MyList& obj) {
        Node* current = obj.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }
    
    MyList cut(int index) {
        if (index < 0 || index > listSize) {
            throw std::out_of_range("Index out of range");
        }
        
        MyList result;
        
        if (index == 0) {
            result.head = head;
            result.tail = tail;
            result.listSize = listSize;
            head = tail = nullptr;
            listSize = 0;
        } else if (index == listSize) {
            return result;
        } else {
            Node* cutPoint = getNodeAt(index);
            result.head = cutPoint;
            result.tail = tail;
            result.listSize = listSize - index;
            
            tail = cutPoint->prev;
            tail->next = nullptr;
            cutPoint->prev = nullptr;
            listSize = index;
        }
        
        return result;
    }
};

#endif
