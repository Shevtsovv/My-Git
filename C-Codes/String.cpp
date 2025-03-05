#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

class ProjectPlaytime{
    protected:
    std::string object;
    std::string name;
    double exp_num;
    public:
    ProjectPlaytime(std::string object, std::string name, double exp_num): object{object}, name{name}, exp_num{exp_num} {}
    void PlaytimePrint(){
        std::cout<<"Subject: "<<object<<std::endl;
        std::cout<<"Name: "<<name<<std::endl;
        std::cout<<"Experiment #: "<<exp_num<<std::endl;
        std::cout<<"Subject was created"<<std::endl;
    }
};
int main(){
    ProjectPlaytime M{"Mommy Long Legs", "Mary Pain", 1222};
    M.PlaytimePrint();
    ProjectPlaytime H{"Huggy-Wuggy", "Unstated", 1170};
    H.PlaytimePrint();
    ProjectPlaytime C{"Catnap", "Theodor", 1100};
    C.PlaytimePrint();

}
