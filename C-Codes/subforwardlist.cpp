#pragma once
#include <iostream>
//Класс, который отвечает за каждый элемент списка
class subforward_node{
    public:
    double data;
    subforward_node* next;
    subforward_node* previous;
    public:
    //Сохранение значения в элемент списка
    subforward_node(double data){
        this -> data = data;
        this -> previous = this -> next = nullptr;
    }
};

//Класс, реализующий методы работы списка
class subforwardlist{
    public:
    //Указатель на последний узел списка
    subforward_node* tail;
    //Указатель на последний узел списка
    subforward_node* head;
    public:
    subforwardlist(){
        tail = head = nullptr;
    }
    //Уничтожение элементов списка, очистка памяти
    ~subforwardlist(){
        while(head != nullptr){
            subforward_pop_front();
        }
    }
    //Инициализация пустого списка
    subforward_node* subforward_init(){
        head = tail = nullptr;
        return nullptr;
    }
    //Добавление элемента в начало списка
    subforward_node* subforward_push_front(double data){
        subforward_node* sfl = new subforward_node(data);
        sfl -> next = head;
        if(head != nullptr){
            head -> previous = sfl;
        }
        if(tail == nullptr){
            tail = sfl;
        }
        head = sfl;
        return sfl;
    }
    //Добавление элемента в конец списка
    subforward_node* subforward_push_back(double data){
        subforward_node* sfl = new subforward_node(data);
        sfl -> previous = tail;
        if(tail != nullptr){
            tail -> next = sfl;
        }
        if(head == nullptr){
            head = sfl;
        }
        tail = sfl;
        return sfl;
    }
    //Удаление элемента из начала списка
    void subforward_pop_front(){
        if(head == nullptr){
            return;
        }
        subforward_node* sfl = head -> next;
        if(sfl != nullptr){
            sfl -> previous = nullptr;
        } else{
            tail = nullptr;
        }
        delete head;
        head = sfl;
    }
    //Удаление элемента из конца списка
    void subforward_pop_back(){
        if(tail == nullptr){
            return;
        }
        subforward_node* sfl = tail -> previous;
        if(sfl != nullptr){
            sfl -> next = nullptr;
        } else{
            head = nullptr;
        }
        delete tail;
        tail = sfl;
    }
    //Получение значения любого элемента списка по индексу
    subforward_node* subforward_get(int index){
        subforward_node* sfl = head;
        int it = 0;
        while(it != index){
            if(sfl == nullptr){
                return 0;
            }
            sfl = sfl -> next;
            it++;
        }
        return sfl;
    }
    //Добавление произвольного элемента в любое место списка по индексу
    subforward_node* subforward_insert(int index, double value){
        subforward_node* right = subforward_get(index);
        if(right == nullptr){
            return subforward_push_back(value);
        }
        subforward_node* left = right -> previous;
        if(left == nullptr){
            return subforward_push_front(value);
        }
        subforward_node* sfl = new subforward_node(value);
        sfl -> previous = left;
        sfl -> next = right;
        left -> next = sfl;
        right -> previous = sfl;
        return sfl;
    }
    //Удаление произвольного элемента из любого места списка
    void subforward_erase(unsigned int index, double value){
        subforward_node* sfl = subforward_get(index);
        if(sfl -> previous == nullptr){
            subforward_pop_front();
            return;
        }
        if(sfl -> next == nullptr){
            subforward_pop_back();
            return;
        }
        subforward_node* left = sfl -> previous;
        subforward_node* right = sfl -> next;
        left -> next = right;
        left = right -> previous;
        delete sfl;
    }
    //Определение размера списка
    unsigned int subforward_size(){
        subforward_node* sfl = head;
        if(sfl == nullptr){
            return 0;
        }
        int it = 0;
        while(sfl -> next != NULL){
            sfl = sfl -> next;
            it++;
        }
        return it;
    }
};