#pragma once
#include <iostream>
#include <initializer_list>

template<typename T>
class subvector
{
    private:
    //Последний элемент вектора
    size_t top;
    //Емкость вектора
    size_t capacity;
    //Указатель на линейную комбинацию данных в векторе
    T* subvec;
    //Поиск максимума из двух чисел
    public:
    //Конструктор для subvector: вершина, емкость и указатель на ЛК по нулям
    subvector(): top(0), capacity(0), subvec(nullptr){}
    //Конструктор копирования, защита от двойного вызова деструктора при копировании
    subvector(const subvector& other): top(other.top), capacity(other.capacity), subvec(new T[other.capacity])
    {
        for(size_t i = 0; i < top; ++i)
        {
            subvec[i] = other.subvec[i];
        }
    }
    //Конструктор list для subvector
    subvector(const std::initializer_list<T> list_init): top(0), capacity(0), subvec(nullptr){
        for(const auto& item: list_init){
            sub_push_back(item);
        }
    }
    //Оператор [] для работы с вектором
    T& operator[](size_t index) const{
        if(index >= top){
            throw std::invalid_argument("Index is out of range!");
        }
        return subvec[index];
    }
    //Оператор присваивания, новые данные записываются в новый вектор
    subvector& operator=(const subvector& other)
    {
        if(this != &other){
            T* subvecx = new (std::nothrow) T[other.capacity];
            if(!subvecx){
                throw std::bad_alloc();
            }
            for(size_t i = 0; i < other.top; ++i){
                subvec[i] = other.subvec[i];
            }
            delete[] subvec;
            subvec = subvecx;
            top = other.top;
            capacity = other.capacity;
        }
        return *this;
    }
    ~subvector()
    {
        if(subvec){delete[] subvec;}
    }
    //Инициализация пустого вектора
    bool sub_init()
    {
        subvec = nullptr;
        top = 0;
        capacity = 0;
        return true;
    }
    //Поиск максимума из двух size_t чисел
    size_t supremum(size_t a, size_t b){
        return (a > b) ? a : b; 
    }
    //Поиск минимума из двух size_t чисел
    size_t infinum(size_t a, size_t b)
    {
        return (a > b) ? b : a;
    }
    //Добавление элемента в конец вектора с выделением памяти при необходимости
    bool sub_push_back(const T& value)
    {
        if(top >= capacity){
            size_t mod_capacity = (capacity == 0) ? 1 : 2 * capacity;
            T* extra = new (std::nothrow) T[mod_capacity];
            if(!extra){
                //throw std::bad_alloc();
                return false;
            }
            for(unsigned int i = 0; i < top; ++i){
                extra[i] = subvec[i];
            }
            delete[] subvec;
            subvec = extra;
            capacity = mod_capacity;
        }
        subvec[top++] = value;
        return true;
    }
    //Вставка одного или нескольких значений в вектор с выделением памяти при необходимости
    void sub_insert(size_t pos, size_t amount, double value)
    {
        //Указатель по номер элемента вектора после вставки одного или нескольких значений 
        if(pos > top){
            throw std::invalid_argument("Subvector's index in out of range!");
        }
        size_t sub_paste = pos + amount;
        if(sub_paste > capacity){
            //T* subvec1 = top;
            size_t mod_capacity = supremum(sub_paste, capacity * 2);
            T* subvec1 = new (std::nothrow) T[mod_capacity];
            if(!subvec1){
                throw std::bad_alloc();
            }
            for(size_t i = 0; i < pos; ++i){
                subvec1[i] = subvec[i];
            }
            for(size_t i = 0; i < amount; ++i){
                subvec1[pos + i] = value;
            }
            for(size_t i = pos; i < top; ++i){
                subvec1[i + amount] = subvec[i];
            }
            delete[] subvec;
            subvec = subvec1;
            capacity = mod_capacity;
        } else
        {
            for(size_t i = top; i >= pos; --i){
                subvec[i + amount - 1] = subvec[i - 1];
            }
            for(size_t i = pos; i < sub_paste; ++i){
                subvec[i] = value;
            }
        }
        top += amount;
    }
    //Удаление элемента из конца списка, функция вернет значение, если оно ненулевое
    T sub_pop_back(){
        if(top == 0){
            throw std::out_of_range("Subvector is empty!");
        }
        top--;
        T value = subvec[top];
        return value;
    }
    //Удаление элемента из любого места вектора
    bool sub_erase(size_t pos){
        if(pos > top){
            throw std::out_of_range("Index of vector in out of range!");
        }
        for(unsigned int i = pos; i < top; ++i){
            subvec[i] = subvec[i + 1];
        }
        top--;
        return true;
    }
    //Изменение ёмкости вектора при необходимости
    bool sub_resize(size_t mod_capacity) {
        if (mod_capacity == capacity) return true;

        if (mod_capacity == 0) {
            delete[] subvec;
            subvec = nullptr;
            top = capacity = 0;
            return true;
        }
        T* qv = new T[mod_capacity];
        size_t elements_to_copy = infinum(top, mod_capacity);
        //Копируем существующие элементы: в исходный вектор, если inf = top, и в "урезанный вектор", если inf = mod_capacity
        for(size_t i = 0; i < elements_to_copy; ++i) {
            qv[i] = subvec[i];
        }
        //Инициализируем новые элементы (если увеличиваем размер)
        if (mod_capacity > capacity) {
            for(size_t i = capacity; i < mod_capacity; ++i) {
                qv[i] = T();
            }
        }
        delete[] subvec;
        subvec = qv;
        capacity = mod_capacity;
        //Обновляем top, если новый размер меньше
        if (mod_capacity < top) {
            top = mod_capacity;
        }
        return true;
    }
    //Очищение неиспользуемой памяти с уменьшением capacity до top
    void sub_shrink_to_fit(){
        if(top == 0){
            delete[] subvec;
            sub_init();
        }
        if(top > 0){
            T* temp = new T[top];
            for(size_t i = 0; i < top; ++i){
                temp[i] = subvec[i];
            }
            delete[] subvec;
            subvec = temp;
            capacity = top;
        }
    }
    //Очищение содержимого вектора, занимаемая память не меняется
    void sub_clear(){
        top = 0;
    }
    //Размер вектора, функция вернет ноль, если он пустой
    size_t sub_size() const{
        if(top == 0){
            return 0;
        } else{
            return top;
        }
    }
    //Значение ёмкости вектора
    size_t sub_capacity() const{
        return capacity;
    }

    //Проверка векторы на пустоту, функция возращает top == 0;
    bool sub_empty() const{
        return top == 0;
    }
};
