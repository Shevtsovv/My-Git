#include <iostream>
#include <chrono>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;

void bubble_sort(int size){
    int *arr;
    arr=new int[size];
    for(int i=0; i<size; ++i){
        std::cout<<"["<<i<<"]";
        std::cin>>arr[i];
    }
    int arrs;
    auto start=std::chrono::steady_clock::now();
    for(int i=0; i<size; ++i){
        for(int j=0; j<size-i-1; j++){
            if(arr[j]>arr[j+1]){
                arrs=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=arrs;
            }
        }
    }
    auto end=std::chrono::steady_clock::now();
    std::chrono::duration<double> time_sort=end-start;
    std::cout<<"Time,sec: "<<time_sort.count()<<"\n";
    std::cout<<"Sort: "<<"\n";
    for(int i=0; i<size; ++i){
        std::cout<<arr[i]<<" ";
    }
}

int main(){
    bubble_sort(10);
    std::cout<<"\n";
}
