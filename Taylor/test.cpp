#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
double factorial(int a){
    if (a < 0){
        throw std::invalid_argument("factorial");
    }
    double res = 1;
    for (std::size_t i = 1; i <= a; ++i){
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

    bool operator==(const polynomial& o) const {
        return c_ == o.c_;
    }

    bool operator!=(const polynomial& o) const {
        return c_ != o.c_;
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

polynomial operator*(double m, const polynomial& s){
    return s * m;
}
std::ostream& operator<<(std::ostream& os, const polynomial& o){
    std::vector<double> res = o.get_poly();
    for (double c : res){
        os << c << " ";
    }
    return os;
}

polynomial sin(int m, const polynomial& g) {
    if (m < 0){throw std::invalid_argument("m must be more than 0");}

    std::vector<double> arg_ = g.get_poly();
    polynomial res({0});
    polynomial cf_ = arg_;
    for (std::size_t i = 0; i < m; ++i){
        double p = (i % 2 == 0) ? 1 : -1;
        double q = factorial(2 * i + 1);

        res = res + cf_ * polynomial({p/q});
        cf_ = cf_ * arg_ * arg_;
    }
    return {res};
}

polynomial cos(int m, const polynomial& g){
    if (m < 0){throw std::invalid_argument("m must be more than 0");}

    std::vector<double> arg_ = g.get_poly();
    polynomial res({0});
    polynomial cf_ = polynomial({1});
    for (std::size_t i = 0; i < m; ++i){
        double p = (i % 2 == 0) ? 1 : -1;
        double q = factorial(2 * i);

        res = res + cf_ * polynomial({p/q});
        cf_ = cf_ * arg_ * arg_;
    }
    return {res};

}
polynomial exponenta(int m, const polynomial& g){
    if (m < 0){throw std::invalid_argument("m must have positive form");}

    std::vector<double> arg_ = g.get_poly();
    polynomial res({0});
    polynomial cf_ = polynomial({1});
    for (std::size_t i = 0; i < m; ++i){
        double q = factorial(i);
        res = res + cf_ * polynomial({1/q});
        cf_ = cf_ * arg_;
    }
    return {res};
}
polynomial sh(int m, const polynomial& g){
    if (m < 0){throw std::invalid_argument("m must have positive form");}

    std::vector<double> arg_ = g.get_poly();
    polynomial res({0});
    polynomial cf_ = arg_;
    for (std::size_t i = 0; i < m; ++i){
        double q = factorial(2 * i + 1);
        res = res + cf_ * polynomial({1/q});
        cf_ = cf_ * arg_ * arg_;
    }
    return {res};
}
polynomial ch(int m, const polynomial& g){
    if (m < 0){throw std::invalid_argument("m must have positive form");}

    std::vector<double> arg_ = g.get_poly();
    polynomial res({0});
    polynomial cf_ = polynomial({1});
    for (std::size_t i = 0; i < m; ++i){
        double q = factorial(2 * i);
        res = res + cf_ * polynomial({1/q});
        cf_ = cf_ * arg_ * arg_;
    }
    return {res};
}
polynomial arctg(int m, const polynomial& g){
    if (m < 0) {throw std::invalid_argument("m must have positive form");}

    std::vector<double> arg_ = g.get_poly();
    polynomial res({0});
    polynomial cf_ = arg_;
    for (std::size_t i = 0; i < m; ++i){
        double p = (i % 2 == 0) ? 1 : -1;
        double q = 2 * i + 1;
        res = res + cf_ * polynomial({p/q});
        cf_ = cf_ * arg_ * arg_;
    }
    return {res};
}
int main(){
    polynomial arg_({0, 1});
    cout << arctg(7, arg_)(0.34);
} 
