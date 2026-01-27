#include <QtChart.h>
#include <iostream>
#include <cmath>
double foo(double x){
    return x * sin(x);
}
int main()
{
    try
    {
        vec u;
        for(float i = 0; i < 30; i += 0.1)
        {
            u.push_back(i);
        }
        Qt s;
        Qt::Color linec({255, 0, 0});
        s.Visualize(u, foo, linec);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what()  << '\n';
    }
}