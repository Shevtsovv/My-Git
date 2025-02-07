#include <iostream>
using std::cout;
using std::cin;
using std::istream;

//average summary for one variable
float average()
{
    int quantity;
    float x_var;
    float sum = 0;
    std::cin >> quantity;
    for (int i = 1; i <= quantity; i++){
        std::cin >> x_var;
        sum += x_var;
    }
    //std::cout << sum << std::endl;
    return 0;
}

//average summary for two variable. The first x is compiled, after y is compiled. The sequence is important!
float duo_average(int size){
    std::cin >> size;
    float sum = 0;
    for(int i = 1; i <= size; i++){
        float x;
        float y;
        std::cin >> x >> y;
        float pow = x*y;
        sum += pow;
    }
    std:: cout << sum << std::endl;
    return 0;
}
int main()
{
    int n;
    duo_average(n);
    average();
}
