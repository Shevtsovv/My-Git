#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
using namespace std;
atomic<int> atomic_count(0);
chrono::time_point<chrono::steady_clock> t1, t2;

auto time(){
    return chrono::steady_clock::now();
}

void make_rand_array(int *arr, int size_arr){
    for(int i=0; i<size_arr; i++){
        arr[i]=rand();
    }
}

void print_array(int *arr, int size_arr){
    cout<<"arr: ";
    for(int i=0; i<size_arr; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

void copy_array(int *source, int *destination, int size) {
    for(int i=0; i<size; i++) {
        destination[i]=source[i];
    }
}

void bubble_sort(int *arr, int size_arr) {
    for(int i=0; i<size_arr-1; i++) {
        for(int j=0; j<size_arr-i-1; j++) {
            if(arr[j]>arr[j+1]) {
                //Swap elements
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
                //swapcount1 ++;
                atomic_count ++;
            }
        }
    }
}

int main() {
    const int size_arr=10000; 
    int arr[size_arr];
    make_rand_array(arr, size_arr);
    int arrc[size_arr];
    int swapcount1=0;

    copy_array(arr, arrc, size_arr);

    int *arr1=arrc;
    int *arr2=arrc+(size_arr/2);
    print_array(arr,3); 

    t1=time();
    bubble_sort(arr,size_arr/2); 
    bubble_sort(arr+(size_arr/2),size_arr/2);
    //end
    t2=time();
    cout<<"Time all: "<<chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()<<" ms.\n";
    
    cout<<swapcount1<<endl;
    swapcount1=0;

    t1=time();
    thread th1(bubble_sort, arr1, size_arr/2); 
    thread th2(bubble_sort, arr2, size_arr/2); 
    th1.join(); 
    th2.join();
    t2=time();
    cout<<"Time 1-2: "<<chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()<<" ms.\n";


    print_array(arr,3);
    print_array(arrc,3);
    int count=0;
    for (int i=0; i<size_arr; i++)
    {
    if (arr[i]=arrc[i]) count ++;
    }
    if (count=size_arr) std::cout<<"Ok"<<endl;
    cout << swapcount1 <<endl;
}
