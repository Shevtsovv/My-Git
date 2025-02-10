#include <iostream>
using std::cin;
using std::cout;
using std::endl;
int main(){
int data[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
int state[4][4];
for (int i=0; i<4; i++){
    for (int j=0; j<4; j++){
        state[i][j] = data[j+4*i];
    }
}
for (int i=0; i<4; i++){
    for (int j=0; j<4; j++){
        std::cout<<data[i+4*j]<<" ";
    }
    std::cout << "\n";}
    std::cout << "final: " << std::endl;
int sbox_s[5][16] = {
{10, 14, 13, 5, 9, 7, 0, 6, 15, 4, 11, 8, 2, 12, 1, 3},
{0, 2, 11, 6, 8, 10, 5, 13, 15, 9, 12, 7, 1, 3, 14, 4},
{9, 3, 13, 5, 7, 11, 8, 6, 2, 4, 14, 15, 12, 0, 1, 10},
{7, 8, 5, 15, 11, 3, 9, 6, 2, 12, 1, 4, 14, 0, 10, 13},
{13, 12, 5, 15, 4, 0, 10, 9, 7, 8, 3, 2, 11, 6, 1, 14} };

int help_arr[64];
for (int i=0; i<5; i++){
    for (int j=0; j<16; j++){
        help_arr[j+16*i] = sbox_s[i][j];}}
for (int i=0; i<4; i++){
    for (int j=0; j<4; j++){
        int n = state[i][j];
        state[i][j] = help_arr[n];}}

for (int i=0; i<4; i++){
    for (int j=0; j<4; j++){
        std::cout << state[j][i] <<" ";
    }
    std::cout << "\n";}
std::cout<<"final: " << endl;

int state_rows[4][4];
for (int i=0; i<4; i++){
    for (int j=0; j<4; j++){
        if (i<=j){
            state_rows[i][j-i]=state[i][j];}
        if(i>j){
            state_rows[i][4+j-i]=state[i][j];}}}

for (int i=0; i<4; i++){
    for (int j=0; j<4; j++){
        std::cout<<state_rows[i][j]<<" ";
    }
    std::cout<<"\n";}
  return 0;
} 