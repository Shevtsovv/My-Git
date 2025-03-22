#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <map>

class compile{
    private:
    std::map <double, double> terms;

    public:
    void addterm(double degree, double coefficient = 1.0){
        terms[degree] += coefficient;
    }

    compile operator+(const compile& other) const{
        compile result = *this;
        for(const auto& term : other.terms){
            result.addterm(term.first, term.second);
        }
        return result;
    }

    compile operator*(const compile& other) const{
        compile result;
        for(const auto& sublime_term1 : this -> terms){
            for(const auto& sublime_term2 : other.terms){
                double new_power = sublime_term1.first + sublime_term2.first;
                double sublime_coefficients = sublime_term1.second * sublime_term2.second;
                result.addterm(new_power, sublime_coefficients);
            }
        }
        return result;
    }

    compile operator/(const compile& other) const{
        compile result;
        for(const auto& divide_term1 : this -> terms){
            for(const auto& divide_term2 : other.terms){
                double new_power = divide_term1.first - divide_term2.first;
                double divide_coefficients = divide_term1.second / divide_term2.second;
                result.addterm(new_power, divide_coefficients);
            }
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const compile& sx){
        bool potential = true;
        for(const auto& term : sx.terms){
            if(!potential){
                if(term.second >= 0){
                    os << "+";
                } else{
                    os << "-";
                }
            } else{
                if(term.second < 0){
                    os << "-";
                }
            }
            double abs_coefficient = std::abs(term.second);
            if(abs_coefficient == 1.0){
                os << "x^" << term.first;
            } else{
                os << abs_coefficient << "x^" << term.first;
            }
            potential = false;
        }
        return os;
    }

    static compile parse(const std::string& expr){
        compile result;
        std::stringstream ss(expr);
        std::string taylor_term;
        char oper = '+';
        compile current;

        while(ss >> taylor_term){
            if(taylor_term == "+" || taylor_term == "*" || taylor_term == "/"){
                oper = taylor_term[0];
                continue;
            }

            std::stringstream taylor_check(taylor_term);
            char x, sign;
            double degree;
            taylor_check >> x >> sign >> degree;

            if(x != 'x' || sign != '^'){
                throw std::invalid_argument("Incorrect form: " + taylor_term);
            }

            compile new_taylor_term;
            new_taylor_term.addterm(degree);

            switch (oper){
            case '+':
                result = result + new_taylor_term;
                break;
            case '*':
                current = current * new_taylor_term;
                break;
            case '/':
                current = current / new_taylor_term;
                break;
            
            default:
                throw std::invalid_argument("Incorrect operation form: " + std::string(1, oper));
                break;
            }
        }
        result = result + current;
        return result;
    }
};

int main(){
    try{
        std::string expr;
        std::getline(std::cin, expr);
        compile result = compile::parse(expr);
        std::cout << result << std::endl;

    } catch (const std::invalid_argument& e){
        std::cerr << "Invalid form: " << e.what() << std::endl;
    }
    return 0;
}