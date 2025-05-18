#include <iostream>
#include <vector>
#include <cmath>

template <typename Type>
class polynomial{
    std::vector<Type> c_;
public:
    polynomial<Type>(const std::vector<Type>& c) : c_{c} {}

    const std::vector<Type>& data() const {
        return c_;
    }

    Type operator[](std::size_t n) const {
        return c_[n];
    }

    Type& operator[](std::size_t n) {
        return c_[n];
    }
    
    Type operator()(Type m) const {
        Type res = 0;
        Type xx = 1;
        for (std::size_t i = 0; i < c_.size(); ++i){
            res += c_[i] * xx;
            xx *= m;
        }
        return res;
    }

    polynomial operator+(const polynomial& o) const {
        std::vector<Type> res = c_.size() < o.c_.size() ? o.c_ : c_;
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
        std::size_t ns = (c_.size() < d.c_.size()) ? d.c_.size() : c_.size();
        std::vector<Type> res(ns, 0);

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
        std::size_t ns = c_.size() + o.c_.size() - 1;
        std::vector<Type> res(ns, 0);

        for (std::size_t i = 0; i < c_.size(); ++i){
            for (std::size_t j = 0; j < o.c_.size(); ++j){
                res[i + j] += c_[i] * o.c_[j];
            }
        }
        return {res};
    }

    polynomial operator*(Type m) const {
        std::vector<Type> res = c_;
        for (std::size_t i = 0; i < c_.size(); ++i){
            res[i] = m * res[i];
        }
        return {res};
    }
    
    polynomial operator/(Type m) const {
        if (m == 0){
            throw std::invalid_argument("divide on zero");
        }
        std::vector<Type> res = c_;
        for (std::size_t i = 0; i < c_.size(); ++i){
            res[i] /= m;
        }
        return {res};
    }
};

template <typename Type>
std::ostream& operator<<(std::ostream& os, const polynomial<Type>& o){
    std::vector<Type> res = o.data();
    for (std::size_t i = 0; i < res.size(); ++i) {
        os << res[i] << " ";
    }
    return os;
}

template <typename Type>
polynomial<Type> sin(const polynomial<Type>& f, unsigned int r = 5){
    polynomial<Type> sin_({0});
    polynomial cf = f;
    const polynomial sqr = f * f;

    double fact = 1;
    for (unsigned int i = 1; i <= r; ++i){
        double p = (i % 2 != 0) ? 1 : -1;
        sin_ = sin_ + cf * (p / fact);
        cf = cf * sqr;
        fact *= (2 * i) * (2 * i + 1);
    }
    return {sin_};
}

template <typename Type>
polynomial<Type> cos(const polynomial<Type>& f, unsigned int r = 5){
    polynomial<Type> cos_({1});
    polynomial<Type> cf({1});
    const polynomial sqr = f * f;

    double fact = 1;
    for (unsigned int i = 1; i <= r; ++i){
        double p = (i % 2 == 0) ? 1 : -1;
        cf = cf * sqr;
        fact *= (2 * i - 1) * (2 * i);
        cos_ = cos_ + cf * (p / fact);
    }
    return {cos_};
}

template <typename Type>
polynomial<Type> sh(const polynomial<Type>& f, unsigned int r = 5){
    polynomial<Type> sh_({0});
    polynomial cf = f;
    const polynomial sqr = f * f;

    double fact = 1;
    for (unsigned int i = 1; i <= r; ++i){
        sh_ = sh_ + cf * (1 / fact);
        cf = cf * sqr;
        fact *= (2 * i) * (2 * i + 1);
    }
    return {sh_};
}

template <typename Type>
polynomial<Type> ch(const polynomial<Type>& f, unsigned int r = 5){
    polynomial<Type> ch_({1});
    const polynomial sqr = f * f;

    double fact = 1;
    polynomial<Type> cf ({1});
    for (unsigned int i = 1; i <= r; ++i){
        cf = cf * sqr;
        fact *= (2 * i - 1) * (2 * i);
        ch_ = ch_ + cf * (1 / fact);
    }
    return {ch_};
}

template <typename Type>
polynomial<Type> exp(const polynomial<Type>& f, unsigned int r = 5){
    polynomial<Type> exp_({1});
    const polynomial sqr = f;

    double fact = 1;
    polynomial<Type> cf ({1});
    for (unsigned int i = 1; i <= r; ++i){
        cf = cf * sqr;
        fact *= (i);
        exp_ = exp_ + cf * (1 / fact);
    }
    return {exp_};
}

template <typename Type>
polynomial<Type> ln(const polynomial<Type>& f, unsigned int r = 5){
    polynomial cf = f;
    polynomial<Type> ln_({0});

    if (cf[0] == 0){
        return cf;
    } else {
        polynomial<Type> ss({1});
        polynomial<Type> tmp = (cf / cf[0]) - ss;
        const polynomial sqr = tmp;
        for (unsigned int l = 1; l <= r; ++l){
            double s = (l % 2 == 0) ? -1 : 1;
            ln_ = ln_ + tmp * (s / l);
            tmp = tmp * sqr;
        }
        double ucr = std::log(cf[0]);
        polynomial<Type> mm ({ucr});
        return {ln_ + mm};
    }
}

template <typename Type>
polynomial<Type> binomial(const polynomial<Type>& f, double alpha, unsigned int r = 5){
    polynomial cf = f;
    polynomial<Type> b_({1});

    if (cf[0] == 0){
        return cf;
    } else {
        polynomial<Type> ss({1});
        polynomial<Type> tmp = (cf / cf[0]) - ss;
        const polynomial sqr = tmp;
        double fact = 1;
        double u = 1;
        for (unsigned int k = 1; k <= r; ++k){
            u *= alpha - k + 1;
            fact *= k;
            b_ = b_ + tmp * (u / fact);
            tmp = tmp * sqr;
        }
        double ucr = std::pow(cf[0], alpha);
        polynomial<Type> pp ({ucr});
        return {b_ * pp};
    }
}

template <typename Type>
polynomial<Type> tan(const polynomial<Type>& f){
    polynomial tan_ = sin(f) * binomial(cos(f), -1);
    return {tan_};
}

template <typename Type>
polynomial<Type> tanh(const polynomial<Type>& f){
    polynomial th_ = sh(f) * binomial(ch(f), -1);
    return {th_};
}

template <typename Type>
polynomial<Type> arctan(const polynomial<Type>& f, unsigned int r = 5){
    polynomial cf = f;
    polynomial<Type> arctan_({0});
    const polynomial sqr = f * f;

    for (unsigned int i = 0; i < r; ++i){
        double p = (i % 2 == 0) ? 1 : -1;
        arctan_ = arctan_ + cf * (p / (2 * i + 1));
        cf = cf * sqr;
    }
    return {arctan_};
}

template <typename Type>
polynomial<Type> arcsin(const polynomial<Type>& f, unsigned int r = 5){
    polynomial cf = f;
    const polynomial sqr = f * f;
    polynomial<Type> arcsin_({0});

    for (unsigned int i = 0; i <= r; ++i) {
        double a = 1;
        double b = 1;
        for (unsigned int l = 1; l < 2 * i + 1; l += 2){
            a *= l;
        }
        for (unsigned int h = 2; h < 2 * i + 2; h += 2){
            b *= h;
        }
        arcsin_ = arcsin_ + cf * (a /(b * (2 * i + 1)));
        cf = cf * sqr;
    }
    return {arcsin_};
}

template <typename Type>
polynomial<Type> arccos(const polynomial<Type>& f, unsigned int r = 5){
    const double pi = 3.1415926;
    const polynomial<Type> ss ({pi / 2});

    polynomial arccos_ = ss - arcsin(f);
    return {arccos_};
}

template <typename Type>
class rational{
    polynomial<Type> nom_;
    polynomial<Type> denom_;
public:
    rational(const polynomial<Type>& m, const polynomial<Type>& n) : nom_(m), denom_(n) {}

    const polynomial<Type>& nom() const {return nom_;}
    const polynomial<Type>& denom() const {return denom_;}

    Type operator()(Type m) const {
        Type s = nom_(m);
        Type q = denom_(m);
        return {s / q};
    }
    rational operator+(const rational& o) const {
        polynomial<Type> s = nom_ * o.denom_ + o.nom_ * denom_;
        polynomial<Type> q = denom_ * o.denom_;
        return {s, q};
    }

    rational operator-(const rational& o) const {
        polynomial<Type> s = nom_ * o.denom_ - o.nom_ * denom_;
        polynomial<Type> q = denom_ * o.denom_;
        return {s, q};
    }

    rational operator*(const rational& o) const {
        polynomial<Type> s = nom_ * o.nom_;
        polynomial<Type> q = denom_ * o.denom_;
        return {s, q};
    }

    rational operator*(Type m) const {
        polynomial<Type> s = nom_ * m;
        polynomial<Type> q = denom_;
        return {s, q};
    }

    rational operator/(Type m) const {
        polynomial<Type> s = nom_;
        polynomial<Type> q = denom_ * m;
        return {s, q};
    }

};

template <typename Type>
std::ostream& operator<<(std::ostream& os, const rational<Type>& f) {
    polynomial<Type> t = f.nom();
    polynomial<Type> k = f.denom();
    os << t << " / " << k;
    return os;
}

int main() {
    polynomial<double> v = sin(polynomial<double>({0, 1}));
    polynomial<double> s({0, 1});
    rational<double> f(v,s);
    std::cout << f(M_PI / 2 - 1e-10);
}