#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

class summary{
    private:
    int size;
    int *coefficients;
    void copycreate(int newSize){
        int *newCoefficients = new int[newSize]();
        for(int l = 0; l < size; ++l){
            newCoefficients[l] = coefficients[l];
        }
        delete[] coefficients;
        coefficients = newCoefficients;
        size = newSize;
    }

    public:
    summary(): coefficients(nullptr), size(0) {}

    ~summary(){
        delete[] coefficients;
    }
    void addterm(int power, int coefficient = 1){
        if(power < 0){
            throw std::invalid_argument("Incorrect degree form: " + std::to_string(power));
        };
        if(power >= size){
            copycreate(power + 1);
        }
        coefficients[power] += coefficient;
    }
    summary operator+(const summary& other) const{
        summary result = *this;
        for(int i = 0; i < other.size; ++i){
            if(other.coefficients[i] != 0){
                result.addterm(i, other.coefficients[i]);
            }
        }
        return result;
    }
    friend std::ostream& operator<<(std::ostream& os, const summary& sx){
        bool first = true;
        for(int j = 1; j < sx.size; ++j){
            if(sx.coefficients[j] != 0){
                if(!first){
                    os << " + ";
                }
                os << sx.coefficients[j] << "x^" << j;
                first = false;
            }
        }
        return os;
    }
    static summary parse(const std::string& expr){
        summary result;
        std::stringstream ss(expr);
        std::string term;

        while(ss >> term){
            if(term == "+") continue;
            std::stringstream term_stream(term);
            char x, sign;
            int power;
            term_stream >> x >> sign >> power;
            if(x != 'x' || sign != '^'){
                throw std::invalid_argument("Incorrect form: " + term);
            }
            result.addterm(power);
        }
        return result;

    }
};
int main() {
    try {
        std::string expr;

        std::getline(std::cin, expr);
        summary result = summary::parse(expr);

        std::cout << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

//ask: x^7 + x^7 + x^8
//res: 2x^7 + 1x^8