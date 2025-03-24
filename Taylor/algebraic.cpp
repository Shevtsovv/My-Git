#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <stdexcept>
#include <cmath>
#include <cctype>

class algebraic{
    private:
    std::map <double, double> terms;

    public:

    algebraic(double coefficient = 0.0){
        if(coefficient != 0.0){
            addterm(0.0, coefficient);
        }
    }
    void addterm(double power, double coefficient = 1.0){
        terms[power] += coefficient;
    }

    algebraic operator+(const algebraic& other) const{
        algebraic result = *this;
        for(const auto& term : other.terms){
            result.addterm(term.first, term.second);
        }
        return result;
    }

    algebraic operator*(const algebraic& other) const{
        algebraic result;
        for(const auto& term1 : this -> terms){
            for(const auto& term2 : other.terms){
                double new_power = term1.first + term2.first;
                double new_coefficients = term1.second * term2.second;
                result.addterm(new_power, new_coefficients);
            }
        }
        return result;
    }

    algebraic operator/(const algebraic& other){
        algebraic result;
        for(const auto& term1 : this -> terms){
            for(const auto& term2 : other.terms){
                double new_power = term1.first - term2.first;
                double new_coefficients = term1.second / term2.second;
                result.addterm(new_power, new_coefficients);
            }
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const algebraic& sx){
        bool value = true;
        for(const auto& term : sx.terms){
            if(!value){
                if(term.second >= 0){
                    os << " + ";
                } else{
                    os << " - ";
                }
            } else{
                if(term.second < 0){
                    os << " - ";
                }
            }
            double abs_coefficients = std::abs(term.second);
            if(abs_coefficients == 1.0 && term.first != 0.0){
                os << "x^" << term.first;
            } else if(term.first == 0.0){
                os << abs_coefficients;
            } else {
                os << abs_coefficients << "x^" << term.first;
            }
            value = false;
        }
        return os;
    }

    static algebraic parse(const std::string& expr){
        std::stringstream ss(expr);
        return parse_expression(ss);
    }

    private:
    static algebraic parse_expression(std::stringstream& ss){
        algebraic result;
        char operation = '+';
        algebraic current;

        while(ss){
            char ch = ss.peek();
            if(ch == ' '){
                ss.get();
                continue;
            }

            if(ch == '('){
                ss.get();
                algebraic sub_expr = parse_expression(ss);
                current = apply_operation(current, sub_expr, operation);
                
            } else if(ch == ')'){
                ss.get();
                break;

            } 
            else if (std::isalpha(ch) || std::isdigit(ch) || ch == '+' || ch == '-' || ch == '^'){
                algebraic term = parse_term(ss);
                current = apply_operation(current, term, operation);
            } 
            else if(ch == '*' || ch == '/'){
                operation = ss.get();
            } else{
                throw std::invalid_argument("Incorrect symbol: " + std::string(1, ch));
            }
        }
        result = result + current;
        return result;
    }

    static algebraic parse_term(std::stringstream& ss){
        double coefficient = 1.0;
        double power = 1.0;

        if(std::isdigit(ss.peek()) || ss.peek() == '+' || ss.peek() == '-'){
            ss >> coefficient;
        }

        if(ss.peek() == 'x'){
            ss.get();
            if(ss.peek() == '^'){
                ss.get();
                ss >> power;

            } else{
                power = 1.0;
            }
        } else if(coefficient != 1.0 || ss.peek() == '+' || ss.peek() == '-'){
            power = 0.0;
        }
        algebraic term;
        term.addterm(power, coefficient);
        return term;
    }

    static algebraic apply_operation(algebraic current, const algebraic& term, char operation){
        switch(operation){
            case '+':
            return current + term;

            case '-':
            return current + term * algebraic(-1.0);

            case '*':
            return current * term;

            case '/':
            return current / term;

            default:
            throw std::invalid_argument("Incorrect operation form: " + std::string(1, operation));
        }
    }
};
int main(){
    try{
        std::string expr;
        std::getline(std::cin, expr);

        algebraic result = algebraic::parse(expr);
        std::cout << result << std::endl;
    } catch (const std::invalid_argument& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}