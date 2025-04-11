#pragma once
#include <iostream>
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
    //Поиск максимума из двух чисел, если аргументы некорректны, функция выдает ошибку
    int supremum(size_t a, size_t b)
    {
        if((a<0 && b<0) || (a<0 || b < 0)){
            throw std::invalid_argument("Invalid values for subvector's index");
        }
        return (a > b) ? a : b; 
    }
    //Поиск минимума из двух чисел, если аргументы некорректны, функция выдает ошибку
    int infinum(size_t a, size_t b)
    {
        if((a<0 && b<0) || (a<0 || b < 0)){
            throw std::invalid_argument("Invalid values for subvector's index");
        }
        return (a > b) ? b : a;
    }
    public:
    //Конструктор для subvector: вершина, емкость и указатель на ЛК по нулям
    subvector(): top(0), capacity(0), subvec(nullptr){}
    //Конструктор копирования, защита от двойного вызова деструктора при копировании
    subvector(const subvector& other): top(other.top), capacity(other.capacity), subvec(new T[other.capacity])
    {
        for(int i = 0; i < top; ++i)
        {
            subvec[i] = other.subvec[i];
        }
    }
    //Оператор присваивания, новые данные записываются в новый вектор
    subvector& operator=(const subvector& other)
    {
        if(this != &other){
            T* subvecx = new (std::nothrow) T[other.capacity];
            if(!subvecx)
            {
                throw std::bad_alloc();
            }
            for(unsigned int i = 0; i < other.top; ++i)
            {
                subvec[i] = other.subvec[i];
            }
            delete[] subvec;
            top = other.top;
            capacity = other.capacity;
            subvec = subvecx;
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
    //Добавление элемента в конец вектора с выделением памяти при необходимости
    bool sub_push_back(const T& value)
    {
        if(top >= capacity){
            size_t mod_capacity = (capacity == 0) ? 1 : 2 * capacity;
            T* extra = new (std::nothrow) T[mod_capacity];
            if(!extra)
            {
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
    void sub_insert(int pos, int amount, int value)
    {
        //Указатель по номер элемента вектора после вставки одного или нескольких значений 
        if((pos < 0) || (amount < 0) || (pos > top)){
            throw std::invalid_argument("Subvector's index in out of range!");
        }
        size_t sub_paste = pos + amount;
        if(sub_paste > capacity){
            //T* subvec1 = top;
            size_t mod_capacity = supremum(sub_paste, capacity * 2);
            T* subvec1 = new (std::nothrow) T[mod_capacity];
            if(!subvec1)
            {
                throw std::bad_alloc();
            }
            for(unsigned int i = 0; i < pos; ++i)
            {
                subvec1[i] = subvec[i];
            }
            for(unsigned int i = 0; i < amount; ++i)
            {
                subvec1[pos + i] = value;
            }
            for(unsigned int i = pos; i < top; ++i)
            {
                subvec1[i + amount] = subvec[i];
            }
            delete[] subvec;
            subvec = subvec1;
            capacity = mod_capacity;
        } else
        {
            for(unsigned int i = top; i >= pos; --i)
            {
                subvec[i + amount - 1] = subvec[i - 1];
            }
            for(unsigned int i = pos; i < sub_paste; ++i)
            {
                subvec[i] = value;
            }
        }
        top += amount;
    }
    //Удаление элемента из конца списка, функция вернет значение, если оно ненулевое
    T sub_pop_back(){
        if(top == 0){
            return 0;
        }
        top--;
        T value = subvec[top];
        return value;
    }
    //Удаление элемента из любого места вектора
    bool sub_erase(int pos){
        if(pos > top){
            throw std::out_of_range("Index of vector in out of range!");
            //sub_invalid();
        }
        for(unsigned int i = pos; i < top; ++i){
            subvec[i] = subvec[i + 1];
        }
        top--;
        return true;
    }
    //Увеличение ёмкости вектора при необходимости
    bool sub_resize(int mod_capacity) {
        if (mod_capacity == capacity) return true;
        
        if (mod_capacity == 0) {
            delete[] subvec;
            subvec = nullptr;
            top = capacity = 0;
            return true;
        }
        T* u = new T[mod_capacity];
        int elem = infinum(top, mod_capacity);
        for (unsigned int i = 0; i < elem; ++i) {
            u[i] = subvec[i];
        }
    
        delete[] subvec; 
        subvec = u;
        capacity = mod_capacity;
        top = elem;
        
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
            for(unsigned i = 0; i < top; ++i){
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
    int sub_size() const
    {
        if(top == 0){
            return 0;
        } else{
            return top;
        }
    }
    bool sub_empty() const
    {
        return top == 0;
    }
};
