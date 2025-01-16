#include <iostream>
using namespace std;
int main(){
    int *arr;
    int size;

    cout << "Выбранный размер массива: " << endl;
    cin >> size;

    arr = new int[size];
    cout << "Первоначально выбранный массив: "<< endl;
    for(int i = 0; i < size; i++){
        cout << "[" << i << "]" << endl;
        cin >> arr[i];
    }

    int temp;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size - i - 1; j++){
            if(arr[j] > arr[j+1]){
                temp = arr[i];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    cout << "Отсортированный массив: ";
    for(int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
    cout << endl;

}