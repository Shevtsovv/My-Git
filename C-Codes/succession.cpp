#include <iostream>
#include <string>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;

class M{
    private:
    double GM=398600.4415;
    double dt=10;
    double timer=100;

    public:
    void Coordinate(double var_init){
        double var=var_init;
        for(double i=0; i<timer; i+=dt){
            double r_var=sqrt(var*var);
            double a_var=-(GM)*var/(r_var*r_var*r_var);
            var+=a_var*dt*dt;
            std::cout<<var<<",";}}
    void Orbite_E(double x_init,double y_init,double z_init){
        double x=x_init,y=y_init,z=z_init;
        double vx{},vy{},vz{};
        double energy{};
        for(double i=0; i<timer; i+=dt){
            double r=sqrt(x*x+y*y+z*z);
            double ax=-(GM)*x/(r*r*r), ay=-(GM)*y/(r*r*r), az=-(GM)*z/(r*r*r);
            vx+=ax*dt;
            vy+=ay*dt;
            vz+=ay*dt;
            double v=vx*vx+vy*vy+vz*vz;
            double energy=((v*v))/2-((GM)/r);
            std::cout<<energy<<",";}}
};
class X:public M{};
class Y:public M{};
class Z:public M{};
class Energy:public M{};
int main(){
    X x;
    x.Coordinate(2);
    Y y;
    y.Coordinate(4);
    Z z;
    z.Coordinate(6);
    Energy energy;
    energy.Orbite_E(2,4,6);

}









