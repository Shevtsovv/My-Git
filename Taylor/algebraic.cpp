#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <stdexcept>
#include <cmath>
#include <cctype>
#include <vector>

class algebraic {
private:
    std::map<double, double> terms;

public:
    algebraic(double coefficient = 0.0) {
        if (coefficient != 0.0) {
            addterm(0.0, coefficient);
        }
    }

    void addterm(double power, double coefficient = 1.0) {
        terms[power] += coefficient;
        if (terms[power] == 0.0) {
            terms.erase(power); 
        }
    }

    algebraic operator+(const algebraic& other) const {
        algebraic result = *this;
        for (const auto& term : other.terms) {
            result.addterm(term.first, term.second);
        }
        return result;
    }

    algebraic operator-(const algebraic& other) const {
        algebraic result = *this;
        for (const auto& term : other.terms) {
            result.addterm(term.first, -term.second);
        }
        return result;
    }

    algebraic operator*(const algebraic& other) const {
        algebraic result;
        for (const auto& term1 : this->terms) {
            for (const auto& term2 : other.terms) {
                double new_power = term1.first + term2.first;
                double new_coefficients = term1.second * term2.second;
                result.addterm(new_power, new_coefficients);
            }
        }
        return result;
    }

    algebraic operator/(const algebraic& other) const {
        if (other.terms.size() != 1 || other.terms.begin()->first != 0.0) {
            throw std::invalid_argument("Division is only supported by constants");
        }
        double divisor = other.terms.begin()->second;
        algebraic result;
        for (const auto& term : this->terms) {
            result.addterm(term.first, term.second / divisor);
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const algebraic& sx) {
        if (sx.terms.empty()) {
            os << "0";
            return os;
        }

        bool firstTerm = true;
        for (auto it = sx.terms.rbegin(); it != sx.terms.rend(); ++it) {
            const auto& term = *it;
            double power = term.first;
            double coeff = term.second;

            if (!firstTerm) {
                os << (coeff >= 0 ? " + " : " - ");
            } else if (coeff < 0) {
                os << "-";
            }

            double abs_coeff = std::abs(coeff);
            if (abs_coeff != 1.0 || power == 0.0) {
                os << abs_coeff;
            }

            if (power != 0.0) {
                os << "x";
                if (power != 1.0) {
                    os << "^" << power;
                }
            }

            firstTerm = false;
        }
        return os;
    }

    static algebraic parse(const std::string& expr) {
        std::stringstream ss(expr);
        algebraic result = parse_expression(ss);
        
        char remaining;
        if (ss >> remaining) {
            throw std::invalid_argument("Unexpected character: " + std::string(1, remaining));
        }
        
        return result;
    }

private:
    static algebraic parse_expression(std::stringstream& ss) {
        algebraic result;
        algebraic current = parse_term(ss);
        char op;

        while (ss >> op && (op == '+' || op == '-')) {
            algebraic next = parse_term(ss);
            if (op == '+') {
                current = current + next;
            } else {
                current = current - next;
            }
        }

        if (ss) {
            ss.putback(op);
        }

        return current;
    }

    static algebraic parse_term(std::stringstream& ss) {
        algebraic result = parse_factor(ss);
        char op;

        while (ss >> op && (op == '*' || op == '/')) {
            algebraic next = parse_factor(ss);
            if (op == '*') {
                result = result * next;
            } else {
                result = result / next;
            }
        }
        if (ss) {
            ss.putback(op);
        }

        return result;
    }

    static algebraic parse_factor(std::stringstream& ss) {
        skip_whitespace(ss);
        char sign = '+';
        if (ss.peek() == '+' || ss.peek() == '-') {
            sign = ss.get();
        }

        algebraic result;
        if (ss.peek() == '(') {
            ss.get(); 
            result = parse_expression(ss);
            if (ss.get() != ')') {
                throw std::invalid_argument("Missing closing parenthesis");
            }
        } else {
            result = parse_simple_term(ss);
        }

        if (sign == '-') {
            result = result * algebraic(-1.0);
        }

        return result;
    }

    static algebraic parse_simple_term(std::stringstream& ss) {
        skip_whitespace(ss);
        double coefficient = 1.0;
        double power = 0.0;

        bool has_coefficient = false;
        if (std::isdigit(ss.peek())) {
            ss >> coefficient;
            has_coefficient = true;
        }

        if (ss.peek() == 'x') {
            ss.get(); 
            power = 1.0;
            if (ss.peek() == '^') {
                ss.get();
                ss >> power;
            }
        } else if (!has_coefficient) {
            coefficient = 1.0;
            power = 0.0;
        }

        algebraic term;
        term.addterm(power, coefficient);
        return term;
    }

    static void skip_whitespace(std::stringstream& ss) {
        while (ss.peek() == ' ') {
            ss.get();
        }
    }
};

int main() {
    try {
        std::string expr;
        std::getline(std::cin, expr);

        algebraic result = algebraic::parse(expr);
        std::cout << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
