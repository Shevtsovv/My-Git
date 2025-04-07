#pragma once
#include <iostream>
//Класс операций с матрицами
class submatrix{
    private:
    //Указатель для двумерного динамического массива (матрицы)
    double** matrix;
    //Количество строк матрицы
    int str;
    //Количество столбцов матрицы
    int cols;

    public:
    //Выделение памяти под двумерный массив, создание матрицы заданного размера
    submatrix(int m, int n): str(m), cols(n){
        if((m <= 0) && (n <= 0)){
            throw std::invalid_argument("The matrix's parameters is only positive numbers!");
        }
        matrix = new double*[m];
        for(int i = 0; i < m; ++i){
            matrix[i] = new double[n];
        }
    }
    //Освобождение неиспользуемой памяти, удаление матрицы заданного размера
    ~submatrix(){
        for(int it = 0; it < str; ++it){
            delete[] matrix[it];
        }
        delete[] matrix;
    }
    //Cложения двух матриц: если они разного размера, функция выдаёт ошибку
    submatrix& operator+=(const submatrix& other){
        if((str != other.str) && (cols != other.cols)){
            throw std::invalid_argument("err");
        }
        for(int i = 0; i < str; ++i){
            for(int j = 0; j < cols; ++j){
                matrix[i][j] += other.matrix[i][j];
            }
        }
        return *this;
    }
    //Вывод матрицы заданного размера на экран
    void submatrix_print(){
        for(int i = 0; i < str; ++i){
            for(int j = 0; j < cols; ++j){
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        } 
    }
    //Доступ к произвольному элементу матрицы: если вводится некорректный номер строки или столбца, функция выдаёт ошибку
    double& submatrix_element(int i, int j){
        return matrix[i][j];
    }
    //Произведение матриц, если их необходимые измерения не совпадают, то функция выдаёт ошибку
    submatrix operator*(const submatrix& other) const {
        if (cols != other.str) {
            throw std::invalid_argument("The matrixes's sizes have incorrect form");
        }
        submatrix result(str, other.cols);
        for (int i = 0; i < str; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                double sum = 0;
                for (int k = 0; k < cols; ++k) {
                    sum += matrix[i][k] * other.matrix[k][j];
                }
                result.matrix[i][j] = sum;
            }
        }
        return result;
    }
    //Транспонирование матрицы заданного размера
    submatrix submatrix_transpose() const{
        submatrix transpose(cols, str);
        for(int i = 0; i < str; ++i){
            for(int j = 0; j < cols; ++j){
                transpose.matrix[j][i] = matrix[i][j];
            }
        }
        return transpose;
    }
};

