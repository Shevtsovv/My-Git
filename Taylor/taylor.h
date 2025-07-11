#include <iostream>
#include <vector>
#include <cmath>

class polynomial{
    std::vector<double> c_;
public:
    polynomial(const std::vector<double>& c) : c_{c} {}
    polynomial(const std::initializer_list<double> list){
        for(const auto& item : list){
            c_.push_back(item);
        }
    }
    const std::vector<double>& data() const {
        return c_;
    }

    double operator[](std::size_t n) const {
        return c_[n];
    }

    double& operator[](std::size_t n) {
        return c_[n];
    }
    
    double operator()(double m) const {
        double res = 0;
        double xx = 1;
        for (std::size_t i = 0; i < c_.size(); ++i){
            res += c_[i] * xx;
            xx *= m;
        }
        return res;
    }

    polynomial operator+(const polynomial& o) const {
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
        const unsigned int r = 7;
        std::size_t ns = c_.size() + o.c_.size() - 1;
        std::vector<double> res(ns, 0);

        for (std::size_t i = 0; i < c_.size(); ++i){
            for (std::size_t j = 0; j < o.c_.size(); ++j){
                res[i + j] += c_[i] * o.c_[j];
            }
        }
        res.resize(r);
        return {res};
    }

    polynomial operator*(double m) const {
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
        std::vector<double> res = c_;
        for (std::size_t i = 0; i < c_.size(); ++i){
            res[i] /= m;
        }
        return {res};
    }
};

std::ostream& operator<<(std::ostream& os, const polynomial& o){
    std::vector<double> res = o.data();
    for (double c : res){
        os << c << " ";
    }
    return os;
}

class rational{
    polynomial nom_;
    polynomial denom_;
public:
    rational(const polynomial& m, const polynomial& n) : nom_(m), denom_(n) {
        if (n.data() == std::vector<double>(n.data().size(), 0)) {
            throw std::invalid_argument("divide by zero");
        }
    }

    const polynomial& nom() const {return nom_;}
    const polynomial& denom() const {return denom_;}

    double operator()(double m) const {
        double s = nom_(m);
        double q = denom_(m);
        return {s / q};
    }
    rational operator+(const rational& o) const {
        polynomial s = nom_ * o.denom_ + o.nom_ * denom_;
        polynomial q = denom_ * o.denom_;
        return {s, q};
    }

    rational operator-(const rational& o) const {
        polynomial s = nom_ * o.denom_ - o.nom_ * denom_;
        polynomial q = denom_ * o.denom_;
        return {s, q};
    }

    rational operator*(const rational& o) const {
        polynomial s = nom_ * o.nom_;
        polynomial q = denom_ * o.denom_;
        return {s, q};
    }

    rational operator*(double m) const {
        polynomial s = nom_ * m;
        polynomial q = denom_;
        return {s, q};
    }

    rational operator/(double m) const {
        polynomial s = nom_;
        polynomial q = denom_ * m;
        return {s, q};
    }
};
polynomial sin(const polynomial& f, unsigned int r = 5){
    polynomial sin_({0});
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

polynomial cos(const polynomial& f, unsigned int r = 5){
    polynomial cos_({1});
    polynomial cf = polynomial({1});
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

polynomial sh(const polynomial& f, unsigned int r = 5){
    polynomial sin_({0});
    polynomial cf = f;
    const polynomial sqr = f * f;

    double fact = 1;
    for (unsigned int i = 1; i <= r; ++i){
        sin_ = sin_ + cf * (1 / fact);
        cf = cf * sqr;
        fact *= (2 * i) * (2 * i + 1);
    }
    return {sin_};
}

polynomial ch(const polynomial& f, unsigned int r = 5){
    polynomial ch_({1});
    polynomial cf = polynomial({1});
    const polynomial sqr = f * f;

    double fact = 1;
    for (unsigned int i = 1; i <= r; ++i){
        cf = cf * sqr;
        fact *= (2 * i - 1) * (2 * i);
        ch_ = ch_ + cf * (1 / fact);
    }
    return {ch_};
}

polynomial exp(const polynomial& f, unsigned int r = 5){
    polynomial exp_({1});
    polynomial cf = polynomial({1});
    const polynomial sqr = f;

    double fact = 1;
    for (unsigned int i = 1; i <= r; ++i){
        cf = cf * sqr;
        fact *= (i);
        exp_ = exp_ + cf * (1 / fact);
    }
    return {exp_};
}

polynomial ln(const polynomial& f, unsigned int r = 5){
    polynomial cf = f;
    polynomial ln_({0});

    if (cf[0] == 0){
        throw std::invalid_argument("not taylor polynomial");
    } else {
        polynomial tmp = (cf / cf[0]) - polynomial({1});
        const polynomial sqr = tmp;
        for (unsigned int l = 1; l <= r; ++l){
            double s = (l % 2 == 0) ? -1 : 1;
            ln_ = ln_ + tmp * (s / l);
            tmp = tmp * sqr;
        }
        double ucr = std::log(cf[0]);
        return {ln_ + polynomial({ucr})};
    }
}

polynomial binomial(const polynomial& f, double alpha, unsigned int r = 5){
    polynomial cf = f;
    polynomial b_({1});

    if (cf[0] == 0){
        throw std::invalid_argument("not taylor polynomial");
    } else {
        polynomial tmp = (cf / cf[0]) - polynomial({1});
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
        return {b_ * ucr};
    }
}

polynomial frac(const polynomial& f, unsigned int r = 5){
    polynomial cf = f;
    polynomial fr_({1});
    if (cf[0] == 0){
        throw std::invalid_argument("is not taylor");
    } else {
        polynomial tmp = (cf / cf[0]) - polynomial({1});
        const polynomial sqr = tmp;
        for (unsigned int i = 0; i <= r; ++i){
            double a = (i % 2 == 0) ? -1 : 1;
            fr_ = fr_ + tmp * a;
            tmp = tmp * sqr;
        }
        double ucr = 1.0 / cf[0];
        return {fr_ * ucr};
    }
}

polynomial tan(const polynomial& f){
    polynomial tan_ = sin(f) * frac(cos(f));
    return {tan_};
}

polynomial tanh(const polynomial& f){
    polynomial th_ = sh(f) * frac(ch(f));
    return {th_};
}

polynomial arctan(const polynomial& f, unsigned int r = 5){
    polynomial cf = f;
    polynomial arctan_({0});
    const polynomial sqr = f * f;

    for (unsigned int i = 0; i < r; ++i){
        double p = (i % 2 == 0) ? 1 : -1;
        arctan_ = arctan_ + cf * (p / (2 * i + 1));
        cf = cf * sqr;
    }
    return {arctan_};
}

polynomial arcsin(const polynomial& f, unsigned int r = 5){
    polynomial cf = f;
    const polynomial sqr = f * f;
    polynomial arcsin_({0});

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

polynomial arccos(const polynomial& f, unsigned int r = 5){
    const double pi = 3.1415926;

    polynomial arccos_ = polynomial({pi / 2}) - arcsin(f);
    return {arccos_};
}
