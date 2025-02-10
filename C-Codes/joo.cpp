#include <iostream>
using std::cin;
using std::cout;
using std::endl;
int main(){
    //Introduce data array
    int n, m;
    std::cin>>m>>n;
    int **state=new int*[m];
    for (int i = 0; i < m; i++){
        state[i] = new int[n];
    }
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            std::cin>>state[i][j];} //*(*(m+i)+j) = i*n+j;
        } 
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            std::cout << state[j][i] <<" ";}
            std::cout<<std::endl;
        }
        for (int i = 0; i < n; i++){
            delete[] state[i];
        }
    delete[] state;
}