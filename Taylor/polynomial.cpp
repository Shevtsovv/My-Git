#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
double factorial(int a){
    if (a < 0){
        throw std::invalid_argument("factorial");
    }
    double res = 1;
    for (int i = 1; i <= a; ++i){
        res *= i;
    }
    return res;
}

class polynomial{
    std::vector<double> c_;
public:
    polynomial(const std::vector<double>& c) : c_{c} {}
    
    const std::vector<double>& get_poly() const {
        if (c_.empty()){
            throw std::invalid_argument("incorrect");
        } else {return c_;}
    }

    const double& operator[](std::size_t n) const {
        if (c_.empty()){
            throw std::invalid_argument("incorrect");
        } else {
            return c_.at(n);
        }
    }

    const double operator()(double m) const {
        if(c_.empty()){
            throw std::invalid_argument("incorrect");
        }
        double res = 0;
        for (std::size_t i = 0; i < c_.size(); ++i){
            res += c_[i] * std::pow(m, i);
        }
        return res;
    }
    
    polynomial operator+(const polynomial& o) const {
        if (c_.empty() || o.c_.empty()){
            throw std::invalid_argument("incorrect");
        }
        std::vector<double> res = c_.size() < o.c_.size() ? o.c_ : c_;
        if (c_.size() < o.c_.size()){
            for (std::size_t i = 0; i < c_.size(); ++i){
                res[i] += c_[i];
            }
        } else {
            for (std::size_t i = 0; i < o.c_.size(); ++i){
                res[i] += o.c_[i];
            }
        }
        return {res};
    }

    polynomial operator-(const polynomial& d) const {
        if (c_.empty() || d.c_.empty()){
            throw std::invalid_argument("incorrect");
        }
        std::size_t ns = (c_.size() < d.c_.size()) ? d.c_.size() : c_.size();
        std::vector<double> res(ns, 0);

        if (c_.size() < d.c_.size()){
            for (std::size_t i = 0; i < c_.size(); ++i){
                res[i] = c_[i] - d.c_[i];
                for (std::size_t l = 0; l < ns - c_.size(); ++l){
                    res[c_.size() + l] = 0 - d.c_[c_.size() + l];
                }
            }
        } else {
            for (std::size_t i = 0; i < d.c_.size(); ++i){
                res[i] = c_[i] - d.c_[i];
                for (std::size_t l = 0; l < ns - d.c_.size(); ++l){
                    res[d.c_.size() + l] = c_[d.c_.size() + l] - 0;
                }
            }
        }
        return {res};
    }

    polynomial operator*(const polynomial& o) const {
        if (c_.empty() || o.c_.empty()){
            throw std::invalid_argument("incorrect");
        }
        std::size_t ns = c_.size() + o.c_.size() - 1;
        std::vector<double> res(ns, 0);

        for (std::size_t i = 0; i < c_.size(); ++i){
            for (std::size_t j = 0; j < o.c_.size(); ++j){
                res[i + j] += c_[i] * o.c_[j];
            }
        }
        return {res};
    }

    polynomial operator*(double m) const {
        if (c_.empty()){
            throw std::invalid_argument("incorrect");
        }
        std::vector<double> res = c_;
        for (std::size_t i = 0; i < c_.size(); ++i){
            res[i] = m * res[i];
        }
        return {res};
    }
    
    polynomial operator/(double m) const {
        if (m == 0){
            throw std::invalid_argument("divide on zero");
        }
        if (c_.empty()){
            throw std::invalid_argument("incorrect");
        }
        std::vector<double> res = c_;
        for (std::size_t i = 0; i < c_.size(); ++i){
            res[i] /= m;
        }
        return {res};
    }
};
std::ostream& operator<<(std::ostream& os, const polynomial& o){
    std::vector<double> res = o.get_poly();
    for (double c : res){
        os << c << " ";
    }
    return os;
}

