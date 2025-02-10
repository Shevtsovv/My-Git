#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
struct ECC{
    std::vector<std::vector<int>>& arr;
    int key;
    ECC(std::vector<std::vector<int>>& array, int multiplier): arr(array), key(multiplier){}};
    
    int method (int m, const ECC &ecc){
        int K=ecc.key;
        int result=m;
        while (K>1){
            result = ecc.arr[m][result];
            K-=1;}
    return result;
    }
int main(){
    std::vector<std::vector<int>
    > arr = {{0,1,2,3,4,5,6},
           {1,4,0,2,6,3,5},
           {2,0,3,5,1,6,4},
           {3,2,5,6,0,4,1},
           {4,6,1,0,5,2,3},
           {5,3,6,4,2,1,0},
           {6,5,4,1,3,0,2}};       
    ECC A(arr, 3);
    ECC B(arr, 4);
    std::vector<int> final_result;
    for (int i = 0; i < 7; i++){
        int mA = method(arr[0][i], A);
        int mAB = method(mA, B);
        final_result.push_back(mAB);
    }
    
    for (int result:final_result){
        std::cout << result << " ";
    }
        std::cout<< std::endl;
}

