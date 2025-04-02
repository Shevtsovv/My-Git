#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class matrix{
    public:
    double data;

    void print_arr(int string, int column){
        if(string <= 0 || column <= 0){
            throw std::invalid_argument("The matrix's parameters is only positive numbers!");
            std::cout << std::endl;
        }
        int **arr = new int*[string];
        for(int it = 0; it < string; ++it){
            arr[it] = new int[column];
        }
        for(int i = 0; i < string; ++i){
            for(int j = 0; j < column; ++j){
                std::cin >> arr[i][j];
            }
        }
        for(int i = 0; i < string; ++i){
            for(int j = 0; j < column; ++j){
                std::cout << arr[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void summary(const int m, const int n){
        int arr[m][n];
        int brr[m][n];
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                std::cin >> arr[i][j];}}
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                std::cin >> brr[i][j];}}
        int c[m][n];
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                c[i][j] = arr[i][j] + brr[i][j];}}
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                std::cout << c[i][j] << " ";
            }
            std::cout << std::endl;
        }
    } 
    void matrix_multiply(const int m1, const int m2, const int n){
        int arr[m1][n];
        int brr[n][m2];
        for(int i = 0; i < m1; ++i){
            for(int j = 0; j < n; ++j){
                std::cin >> arr[i][j];
            }
        }
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m2; ++j){
                std::cin >> brr[i][j];
            }
        }

        int c[m1][m2] = {0};
        for(int i = 0; i < m1; ++i){
            for(int j = 0; j < m2; ++j){
                c[i][j] = 0;
                for(int k = 0; k < n; ++k){
                    c[i][j] += arr[i][k] * brr[k][j];
                }
                std::cout << c[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    void transpose_matrix(int string, int column){
        int **arr = new int*[string];
        for(int it = 0; it < string; ++it){
            arr[it] = new int[column];
        }
        for(int i = 0; i < string; ++i){
            for(int j = 0; j < column; ++j){
                std::cin >> arr[i][j];
            }
        }
        int transpose[column][string];
        for(int i = 0; i < string; ++i){
            for(int j = 0; j < column; ++j){
                transpose[j][i] = arr[i][j];
            }
        }
        for(int i = 0; i < column; ++i){
            for(int j = 0; j < string; ++j){
                std::cout << transpose[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};
int main(){
    matrix mat;
    mat.print_arr(2, 2);
    mat.summary(2, 2);
    mat.matrix_multiply(2, 2, 2);
    mat.transpose_matrix(3, 3);


}
