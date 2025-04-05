#pragma once
#include <iostream>
//Класс, отвечающий за операции с вектором
class subvector{
    public: 
    subvector(): top(0), capacity(0), arr(nullptr) {}
    ~subvector() {
        if(arr){delete[] arr;}
    }
    //Последний элемент вектора
    int top;
    //Ёмкость вектора
    int capacity;
    //Создание динамического массива через указатель
    int* arr;
    //Инициализация пустого недовектора
    bool sub_init(subvector* qv){
        qv -> top = 0;
        qv -> capacity = 0;
        qv -> arr = nullptr;
        return true;
    }
    //Добавление элемента в конец списка с выделением памяти при необходимости
    bool sub_push_back(subvector* qv, int memory){
        if(qv -> capacity == 0){
            int *main = new int[10];
            qv -> arr = main;
            qv -> capacity = 10;
        }
        if(qv -> top >= qv -> capacity){
            int *extra = new int[2 * qv -> top];
            for(unsigned int it = 0; it < qv -> top; ++it){
                extra[it] = qv -> arr[it];
            }
            delete[] qv -> arr;
            qv -> arr = extra;
            qv -> capacity *= 2;
        }
        qv -> arr[qv -> top] = memory;
        qv -> top++;
        return true;
    }
    //Вставка значения в любое место вектора
    void sub_insert(int pos, int move, int value){
        int paste_place = pos + move;
        if(pos > top){
            throw std::out_of_range("Index of vector in out of range!");
        }
        if(paste_place > capacity){
            unsigned int mod_capacity = std::max(paste_place, capacity * 2);
            int* u = new int[mod_capacity];
            for(unsigned int it = 0; it < pos; it++){
                u[it] = arr[it];
            }
            for(unsigned int it = 0; it < move; ++it){
                u[pos + it] = value;
            }
            for(unsigned int it = pos; it < top; ++it){
                u[it + move] = arr[it];
            }
            delete[] arr;
            arr = u;
            capacity = mod_capacity;
        } else{
        for(int it = top - 1; it >= pos; --it){
            arr[it + move] = arr[it];
        }
        for(int it = pos; it < pos + move; ++it){
            arr[it] = value;
        }
    }
    top += move;
    }
    //Удаление элемента из конца списка, функция вернет значение, если оно ненулевое
    int sub_pop_back(subvector* qv){
        if(qv -> top == 0){
            return 0;
        }
        qv -> top--;
        int r = qv -> arr[qv -> top];
        return r;
    }
    //Удаление элемента из любого места вектора
    bool sub_erase(int pos){
        if(pos > top){
            throw std::out_of_range("Index of vector in out of range!");
        }
        for(int it = pos; it < top; ++it){
            arr[it] = arr[it + 1];
        }
        top--;
        return true;
    }
    //Увеличение ёмкости вектора при необходимости
    bool sub_resize(subvector* qv, int mod_capacity) {
        if (mod_capacity == qv->capacity) return true;
        
        if (mod_capacity == 0) {
            delete[] qv->arr;
            qv->arr = nullptr;
            qv->top = qv->capacity = 0;
            return true;
        }
        int* u = new int[mod_capacity];
        unsigned int elements_to_copy = std::min(qv->top, mod_capacity);
        for (unsigned int it = 0; it < elements_to_copy; ++it) {
            u[it] = qv->arr[it];
        }
    
        delete[] qv->arr; 
        qv->arr = u;
        qv->capacity = mod_capacity;
        qv->top = elements_to_copy;
        
        return true;
    }
    //Очищение неиспользуемой памяти с уменьшением capacity до top
    void sub_shrink_to_fit(subvector* qv){
        if(qv -> top == 0){
            delete[] qv -> arr;
            sub_init(qv);
        }
        if(qv -> top > 0){
            int* temp = new int[qv -> top];
            for(unsigned it = 0; it < qv -> top; ++it){
                temp[it] = qv -> arr[it];
            }
            delete[] qv -> arr;
            qv -> arr = temp;
            qv -> capacity = qv -> top;
        }
    }
    //Очищение содержимого вектора, занимаемая память не меняется
    void sub_clear(subvector* qv){
        qv -> top = 0;
    }
    //Очищение всей неиспользуемой памяти, инициализация пустого вектора
    void sub_destructor(subvector* qv){
        delete[] qv -> arr;
        sub_init(qv);
    }
};
