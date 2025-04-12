#pragma once
#include <iostream>
template <typename T>  
class subforwardlist{
private:
    struct subforward_node{ 
        T data;
        subforward_node* next;
        subforward_node* prev;
        subforward_node(const T& val) : data(val), next(nullptr), prev(nullptr) {}
    };
    subforward_node* head;
    subforward_node* tail;
    size_t size;

public:
    subforwardlist() : head(nullptr), tail(nullptr), size(0) {}
    ~subforwardlist() {
        while (head) {
            subforward_node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    //Конструктор копирования для двусвязного списка
    subforwardlist(const subforwardlist& other) : head(nullptr), tail(nullptr), size(0) {
        subforward_node* current = other.head;
        while (current) {
            subforward_push_back(current->data);
            current = current->next;
        }
    }
    //Оператор присваивания двусвязного списка
    subforwardlist& operator=(subforwardlist other) {
        swap(other);
        return *this;
    }
    //Обмен содержимым двух списков
    void swap(subforwardlist& other) noexcept{
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(size, other.size);
    }

    //Добавление элемента в конец двусвязного списка
    void subforward_push_back(const T& value){
        subforward_node* newNode = new subforward_node(value);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }
    //Удаление элемента с конца двусвязного списка
    bool subforward_pop_back() {
        if (!tail) return false;
        subforward_node* temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        size--;
        return true;
    }
    //Добавление элемента в начало двусвязного списка
    void subforward_push_front(const T& value) {
        subforward_node* newNode = new subforward_node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }
        size++;
    }
    //Удаление элемента из начала двусвчзного списка
    bool subforward_pop_front() {
        if (!head) return false;
        subforward_node* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        size--;
        return true;
    }
    //Получение элемента двусвязного списка по его индексу
    subforward_node* subforward_get(size_t index) const {
        if (index >= size) return nullptr;
        subforward_node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current;
    }
    //Вставка элемента в любое место двусвязного списка
    bool subforward_insert(size_t index, const T& value) {
        if (index > size) return false;
        if (index == 0) {
            subforward_push_front(value);
            return true;
        }
        if (index == size) {
            subforward_push_back(value);
            return true;
        }
        subforward_node* right = subforward_get(index);
        subforward_node* left = right->prev;
        subforward_node* newNode = new subforward_node(value);
        newNode->prev = left;
        newNode->next = right;
        left->next = newNode;
        right->prev = newNode;
        size++;
        return true;
    }
    //Удаление элемента из двусвязного списка по его индексу
    bool subforward_erase(size_t index) {
        if (index >= size) return false;
        if (index == 0) {
            return subforward_pop_front();
        }
        if (index == size - 1) {
            return subforward_pop_back();
        }
        subforward_node* node = subforward_get(index);
        subforward_node* left = node->prev;
        subforward_node* right = node->next;
        left->next = right;
        right->prev = left;
        delete node;
        size--;
        return true;
    }
    //Размер двусвязного списка
    size_t subforward_get_size() const {
        return size;
    }
};