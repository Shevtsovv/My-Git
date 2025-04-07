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
    //Создание матрицы заданного размера, если введены некорректные размеры, функция выдает ошибку
    submatrix(int m, int n): str(m), cols(n){
        if((m <= 0) && (n <= 0)){
            throw std::invalid_argument("The matrix's parameters is only positive numbers!");
        }
        matrix = new double*[m];
        for(int i = 0; i < m; ++i){
            matrix[i] = new double[n];
        }
    }
    //Освобождение неиспользуемой памяти, удаление матрицы заданного размера, вызывается автоматически после завершения программы
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
    void subprint(){
        for(int i = 0; i < str; ++i){
            for(int j = 0; j < cols; ++j){
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        } 
    }
    //Доступ и чтение к произвольному элементу матрицы
    double& subqv(int i, int j){
        return matrix[i][j];
    }
    //Доступ и чтение любого элемента из заданной матрицы 
    double& operator()(int i, int j) const {
        return matrix[i][j];
    }
    //Произведение матриц, если их необходимые измерения не совпадают, то функция выдаёт ошибку
    submatrix operator*(const submatrix& other) const {
        if (cols != other.str) {
            throw std::invalid_argument("The matrixes's sizes have incorrect form!");
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
    submatrix subtranspose() const{
        submatrix transpose(cols, str);
        for(int i = 0; i < str; ++i){
            for(int j = 0; j < cols; ++j){
                transpose.matrix[j][i] = matrix[i][j];
            }
        }
        return transpose;
    }
    
    //Создание дополнительного минора без заданной строки и столбца 
    submatrix subminor(int row, int col) const {
        if(str != cols) {
            throw std::invalid_argument("Matrix isn't square!");
        }
        submatrix minor(str - 1, cols - 1);
        int minor_i = 0;
        for (int i = 0; i < str; ++i) {
            if (i == row) continue;
            int minor_j = 0;
            for (int j = 0; j < cols; ++j) {
                if (j == col) continue;
                minor(minor_i, minor_j) = matrix[i][j];
                minor_j++;
            }
            minor_i++;
        }
        return minor;
    }

    //Вычисление определителя квадратной матрицы
    int subdeterminant() const {
        if (str != cols) {
            throw std::invalid_argument("Matrix isn't square!");
        }
        if (str == 1) {
            return matrix[0][0];
        }
        if (str == 2) {
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        }
        int det = 0;
        for (int j = 0; j < cols; ++j) {
            submatrix minor = subminor(0, j);
            int sign = (j % 2 == 0) ? 1 : -1;
            det += sign * matrix[0][j] * minor.subdeterminant();
        }
        return det;
    }
};

