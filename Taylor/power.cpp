#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept> 

class x_power{
    private: 
    int power; 
    
    public:
    x_power(int n = 0) : power(n) {}
  
    x_power operator*(const x_power& second) const {
        return x_power(power + second.power);
    }

    friend std::ostream& operator<<(std::ostream& os, x_power& xn){
        os << "x^" << xn.power;
        return os;
    }

    static x_power parse(const std::string& degree){
        std::stringstream ss(degree);
        char x, construction;
        int order;
        ss >> x >> construction >> order;
        if(x != 'x' || construction != '^'){
            throw std::invalid_argument("Incorrect form");
        }
        return x_power(order);
    }

};

x_power expression_parse(const std::string& power){
    std::stringstream ss(power);
    std::string term1, term2;
    char sublime;
    ss >> term1 >> sublime >> term2;

    if(sublime != '*'){
        throw std::invalid_argument("Incorrect form");
    }

    x_power x1 = x_power::parse(term1);
    x_power x2 = x_power::parse(term2);
    return x1 * x2;
}

int main() {
    try {
        std::string ask;

        std::getline(std::cin, ask);
        x_power answer = expression_parse(ask);

        std::cout << answer << std::endl; 
    } catch (const std::invalid_argument& e) {
        std::cerr << " Syntax error" << e.what() << std::endl;
    }

    return 0;
}

//result:
//ask = x^2 * x^4
//answer: x^6;
