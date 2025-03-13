#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
using std::cout;
using std::endl;

//Parametrs (1)
double pi = 3.1415926;
double period = pi/2;

//Factorial (2) 
int factorial(int n){
    int result = 1;
    for(int i = 1; i <= n; ++i){
        result *= i;
    }
    return result;
}

//Euclid algoritm
int nod(int a, int b){
    while(b != 0){
        int step = b;
        b = a % b;
        a = step;
    }
    return a;
}
//transform decimals in frac
std::string frac(double decimal, int accuracy = 1.0e-6){
    int num = 1;
    int denum = 1;

    double frac = decimal;
    while(std::abs(frac - std::round(frac)) > accuracy){
        denum++;
        frac = denum*decimal;
    }
    num = std::round(frac);

    //simplify
    int common = nod(num, denum);
    num /= common;
    denum /= common; 

    //string form
    if(denum == 1){
        return std::to_string(num);
    } else{
        return std::to_string(num) + "/" + std::to_string(denum);
    }
}
//Derivatives, in sin and cos x transform in degrees!(3)
double dexp(double x, int df_order){
    return exp(x);
}
double dsin(double x, int df_order){
    double result = sin((x*180)/(pi) + period*df_order);
    return result;
}
double dcos(double x, int df_order){
    double result = cos((x*180)/(pi) + period*df_order);
    return result;
}
double dln(double x, int df_order){
    if(x > 0 && df_order - 1 > 0){
        double result = (pow(-1, df_order - 1)*factorial(df_order - 1))/(pow(x, df_order));
        return result;
    } 
    else{
        return x;
    }
}
//Taylor Polynom all functions
std::string exptaylor(int n){
    std::ostringstream exp;
    exp << "exp(x) = ";
    
    for(int l = 0; l <= n; ++l){
        double s = dexp(0, l)/factorial(l);
        std::string C = frac(s);
        if(s == 0) continue;

        if(l > 0 && s > 0) exp << " + ";
        exp << "[" << C << "]" <<"x";
        exp << "^" << l;
    }
    return exp.str();
}
std::string sintaylor(int n){
    std::ostringstream sin;
    sin << "f(x) = ";

    for(int l = 1; l <= n; l+=2){
        double s = dsin(0, l)/factorial(l);
        std::string C = frac(s);
        if(s == 0) continue;

        if(l > 0 && s > 0) sin << " + ";
        //else if(C < 0) sin << " - ";
        sin << "[" << C << "]"<<"x";
        sin << "^" << l;
    }
    return sin.str();
}
std::string costaylor(int n){
    std::ostringstream cos;
    cos << "f(x) = ";

    for(int l = 0; l <= n; l+=2){
        double s = dcos(0, l)/factorial(l);
        std::string C = frac(s);
        //if(s == 0) continue;

        if(l > 0 && s > 0) cos << " + ";
        else if(s < 0) cos << " + ";
        cos << " " <<"["<< C << "]"<< "x";
        cos << "^" << l;
    }
    return cos.str();
}
std::string lntaylor(int n){
    std::ostringstream ln;
    ln << "ln(1+x) = ";

    for(int l = 1; l <= n; ++l){
        double s = dln(1, l)/factorial(l);
        std::string C = frac(s);
        if(s == 0) continue;

        if(l > 1 && s > 0) ln << " + ";
        else if(s < 0) ln << " + ";
        ln <<" "<<"["<< C <<"]" <<"x";
        ln << "^" << l;
    }
    return ln.str();
}
int main(){
    std::string h = lntaylor(8);
    cout << h << endl;
}



