#include <vector>
#include <stdexcept>
#include <ostream>
#include <iostream>
class Polynomial
{
    std::vector<double> c_;
public:
    Polynomial(std::vector<double>& c) : c_(c)
    {
        if(c.empty()){throw std::invalid_argument("Polynomial is empty!");}
    }
    const std::vector<double>& data() const {return c_;}
    double& operator[](std::size_t index){return c_[index];}
    const double& operator[](std::size_t index) const {return c_[index];}
    Polynomial operator+(const Polynomial& other) const
    {
        std::vector<double> sum = (c_.size() > other.c_.size()) ? c_ : other.c_;
        if(c_.size() > other.c_.size())
        {
            for(std::size_t i = 0; i < other.c_.size(); ++i)
            {
                sum[i] += other.c_[i];
            }
        }
        else
        {
            for(std::size_t i = 0; i < c_.size(); ++i)
            {
                sum[i] += c_[i];
            }
        }
        return Polynomial(sum);
    }
};
std::ostream& operator<<(std::ostream& os, const Polynomial& P)
{
    for(auto& item : P.data())
    {
        os << item << " ";
    }
    return os;
}
int main(){
    std::vector<double> j = {4}, f = {3, 4, 5, 5, 6};
    Polynomial poly1(j), poly2(f);
    std::cout << poly1 + poly2 << " " << poly2 + poly1;
}






