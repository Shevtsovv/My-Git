#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <cmath>
#include <cctype>
#include <stdexcept>
#include <cmath>
#include <memory>

class wolfram{
    private:
    std::map <double, double> terms;
    bool is_function = false;
    std::string trigonomic_func;
    std::shared_ptr <wolfram> func_arg;
    
    static wolfram parse_factor(std::stringstream& ss){
        skip_whitespace(ss);
        char sign;
        if(ss.peek() == '+' || ss.peek() == '-'){
            sign = ss.get();
        }

        wolfram result;
        if(ss.peek() == '('){
            ss.get();
            result.parse_expression(ss);
            if(ss.peek() != ')'){
                throw std::invalid_argument("Missing both parenthesis");
            }
        } else{
            result = parse_trigonomic_term(ss); 
        }
        if(sign = '-'){
            result = result * wolfram(-1.0);
        }
        return result;
        
    }

    static wolfram parse_term(std::stringstream& ss){
        wolfram result = parse_factor(ss);
        char operation;
        while(ss >> operation && (operation == '*' || operation == '/')){
            wolfram next = parse_factor(ss);
            if(operation == '*'){
                result = result * next;
            } else{
                result = result / next;
            }
        }
        if(ss){
            ss.putback(operation);
        }
        return result;
    }

    static wolfram parse_expression(std::stringstream& ss){
        wolfram current = parse_term(ss);
        char operation;
        while(ss >> operation && (operation == '+' || operation == '-')){
            wolfram next = parse_term(ss);
            if(operation == '+'){
                current = current + next;
            }else{
                current = current - next;
            }
        }
        if(ss){
            ss.putback(operation);
        } 
        return current;
    }
    
    public:
    wolfram(double coefficient = 0.0): is_function(false) {
        if(coefficient != 0.0){
            addterm(0.0, coefficient);
        }
    }

    wolfram(const std::string& trigonomic, const wolfram& arg): is_function(true), trigonomic_func(trigonomic), func_arg(std::make_unique <wolfram> (arg)) {}
    void addterm(double power, double coefficient = 1.0){
        terms[power] += coefficient;
        if(terms[power] == 0.0){
            terms.erase(power);
        }
    }

    wolfram operator+(wolfram other) {
        wolfram result = *this;
        for (const auto& term : other.terms) {
            result.addterm(term.first, term.second);
        }
        return result;
    }

    wolfram operator*(const wolfram& other){
        wolfram result;
        for(const auto& term1: this -> terms){
            for(const auto& term2 : other.terms){
                double new_power = term1.first + term2.first;
                double new_coefficient = term1.second * term2.second;
                result.addterm(new_power, new_coefficient);
            }
        }
        return result;
    }

    wolfram operator/(const wolfram& other){
        wolfram current;
        for(const auto& term1 : this -> terms){
            for(const auto& term2 : other.terms){
                double new_power = term1.first - term2.first;
                double new_coefficient = term1.second / term2.second;
            }
        }
        return current;
    }

    wolfram operator-(const wolfram& other){
        for(const auto& term : other.terms){
            this -> addterm(term.first, -term.second);
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const wolfram& sx){
        if(sx.is_function){
            os << sx.trigonomic_func << "(" << *sx.func_arg << ")";
            return os;
        } 

        if(sx.terms.empty()) return os << "0";

        bool first_term = true;
        for(auto it = sx.terms.rbegin(); it != sx.terms.rend(); ++it){
            const auto& term = *it;
            double power = term.first;
            double coefficient = term.second;

            if(!first_term){
                os << (coefficient >= 0 ? "+" : "-");
            } else if(coefficient < 0){
                os << "-";
            }

            double abs_coefficient = std::abs(coefficient);
            if(abs_coefficient != 1.0 || power == 0.0){
                os << abs_coefficient;
            }
            if(power != 0.0){
                os << "x";
                if(power != 1.0){
                    os << "^" << power;
                }
            }
            first_term = false;
        }
        return os;
    }

    static wolfram parse(std::stringstream& ss){
        wolfram result = parse_expression(ss);
        char remaining;
        if(ss >> remaining){
            throw std::invalid_argument("Unexpected singature: " + std::string(1, remaining));
        }
        return result;
    }

    static void skip_whitespace(std::stringstream& ss){
        while(ss.peek() == ' '){
            ss.get();
        }
    }

    static wolfram parse_trigonomic_term(std::stringstream& ss){
        skip_whitespace(ss);

        std::string func;
        while(std::isalpha(ss.peek())){
            func += static_cast <char> (ss.get());
        }
        if(func == "sin" || func == "cos" || func == "tan"){
            if(ss.get() != '(') throw std::invalid_argument("Expected '(' before: " + func);

            wolfram arg = parse_expression(ss);

            if(ss.get() != ')') throw std::invalid_argument("Expected ')' after: " + func);
            return wolfram(func, arg);
        }
        else if(!func.empty()) {
            for(int it = func.size() - 1; it >= 0; --it ){
                ss.putback(func[it]);
            }
        }

        double coefficient = 1.0;
        double power = 0.0;
        bool has_coefficient = false;

        if(std::isdigit(ss.peek()) || ss.peek() == '.'){
            ss >> coefficient;
            has_coefficient = true;
        }
        if(ss.peek() == 'x'){
            ss.get();
            power = 1.0;
            if(ss.peek() == '^'){
                ss.get();
                ss >> power;
            }
        } else if (!has_coefficient){
            coefficient = 1.0;
            power = 0.0;
        }
        wolfram term;
        term.addterm(power, coefficient);
        return term;
    }
};
int main(){
    while(true){
        std::string expr;
        std::getline(std::cin, expr);
        if(expr == "exit"){
            break;
        } 
        std::stringstream ss(expr);

        try{
            wolfram result = wolfram::parse(ss);
            std::cout << result << std::endl;
        } catch(std::invalid_argument& e){
            std::cerr << e.what() << std::endl;
        }
    }
}
