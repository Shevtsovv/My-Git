#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

class sublimation{
    private:
    double degree;

    public:
    sublimation(int n = 0): degree(n) {}
    sublimation operator*(const sublimation& l_degree) const {
        return sublimation(degree + l_degree.degree);
    }
    friend std::ostream& operator<<(std::ostream& os, const sublimation& xn){
        os << "x^" << xn.degree;
        return os;
    }
    static sublimation parse(const std::string str){
        std::stringstream ss(str);
        char x, sign;
        double power;
        ss >> x >> sign >> power;
        if(x != 'x' || sign != '^'){
            throw std::invalid_argument("Incorrect: " + str);
        }
        return sublimation(power);
    }
};

std::istream& operator>>(std::istream& is, sublimation& result){
    std::string expr;
    std::getline(is, expr);
    
    std::stringstream ss(expr);
    std::string term;
    result = sublimation(0);

    while(ss >> term){
        if(term == "*") continue;
        
        sublimation xp = sublimation::parse(term);
        result = result * xp;
    }
    return is;

}
//enter any number of "x"
//x^7 * x^7 * x^7
//result = x^21