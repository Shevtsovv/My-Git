#include <iostream>
using std::cin;
using std::cout;
using std::endl;

struct parametrs{
    int hour = 0;
    int minute = 0;
    int second = 0;
};

class clock{
    public:
    build(int hour, int minute, int second);
    int GetHour() const;
    int GetMinute() const;
    int GetSecond() const;

    private:
    int hour;
    int minute;
    int second;
};
clock::build(int hour, int minute, int second){
    if(hour<0 || hour>23){
        //Processing wrong hours
    }
    if(minute<0 || minute>59){
        //Processing wrong minutes
    }
    if(second<0 || second>59){
        //Processing wrong seconds 
    }
    hour = hour;
    minute = minute;
    second = second;
}
int clock::GetHour() const{
    return hour;
}
int clock::GetMinute() const{
    return minute;
}
int clock::GetSecond() const{
    return second;
}
int main(){
    clock t;
    std::cout << t.GetHour() << std::endl;
}