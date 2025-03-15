#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

class xdivide{
    private:
    int power;

    public:
    xdivide(int n = 0): power(n) {}

    xdivide operator/(const xdivide& second) const {
        return xdivide(power - second.power);
    }
    friend std::ostream& operator<<(std::ostream& os, xdivide& xn){
        os << "x^" << xn.power;
        return os;
    }

    static xdivide parse(std::string& degree){
        std::stringstream ss(degree);
        char x, construction;
        int order;
        ss >> x >> construction >> order;
        if(x != 'x' || construction != '^'){
            throw std::invalid_argument("Incorrect form");
        }
        return xdivide(order);
    }
};

xdivide divide_parse(const std::string& divide){
    std::stringstream ss(divide);
    std::string term1, term2;
    char multitude;
    ss >> term1 >> multitude >> term2;

    if(multitude != '/'){
        throw std::invalid_argument("Incorrect form");
    }
    xdivide x1 = xdivide::parse(term1);
    xdivide x2 = xdivide::parse(term2);
    return x1 / x2;
}

int main() {
    try {
        std::string ask;

        std::getline(std::cin, ask);
        xdivide answer = divide_parse(ask);

        std::cout << answer << std::endl; 
    } catch (const std::invalid_argument& e) {
        std::cerr << " Syntax error" << e.what() << std::endl;
    }

    return 0;
}
//ask: x^3 / x^2
//ans: x^1
