#include <iostream>
#include <vector>
#include <concepts>
#include <limits>
#include <cmath>
#include <SFML/Graphics.hpp>
template <typename T>
concept numeric = std::integral<T> || std::floating_point<T>;
template <numeric T>
class polynomial{
    std::vector<T> c_;
public:
    polynomial(const std::vector<T>& c) : c_(c){}
    polynomial(const std::initializer_list<T>& list){
        for(const T& item : list){
            c_.push_back(item);
        }
    }
    T& operator[](std::size_t index) {
        return c_[index];
    }
    const T operator[](std::size_t index) const {
        return c_[index];
    }
    const std::vector<T>& data() const {return c_;}
    polynomial operator+(const polynomial& o) const {
        std::vector<T> l = (c_.size() > o.c_.size()) ? c_ : o.c_;
        if(c_.size() > o.c_.size()){
            for(std::size_t i = 0; i < o.c_.size(); ++i){
                l[i] += o.c_[i];
            }
        } else {
            for(std::size_t i = 0; i < c_.size(); ++i){
                l[i] += c_[i];
            }
        }
        return l;
    }
    polynomial operator-(const polynomial& o) const {
        std::vector<T> l = (c_.size() > o.c_.size()) ? c_ : o.c_;
        if(c_.size() > o.c_.size()){
            for(std::size_t i = 0; i < o.c_.size(); ++i){
                l[i] -= o.c_[i];
            }
        } else {
            for(std::size_t i = 0; i < l.size(); ++i){
                l[i] *= static_cast<T>(-1);
            }
            for(std::size_t i = 0; i < c_.size(); ++i){
                l[i] += c_[i];
            }
        }
        return l;
    }
    polynomial operator*(const polynomial& o) const {
        std::size_t size = c_.size() + o.c_.size() - std::size_t(1);
        std::vector<T> l(size, 0);
        for(std::size_t i = 0; i < c_.size(); ++i){
            for(std::size_t j = 0; j < o.c_.size(); ++j){
                l[i + j] += c_[i] * o.c_[j];
            }
        }
        return l;
    }
    polynomial operator*(const T& a) const {
        std::vector<T> m = c_;
        for(std::size_t i = 0; i < m.size(); ++i){
            m[i] *= a;
        }
        return m;
    }
    polynomial operator/(const T& a) const {
        if(a == static_cast<T>(0)){
            throw std::invalid_argument("Divide by zero!");
        }
        std::vector<T> l = c_;
        for(std::size_t i = 0; i < l.size(); ++i){
            l[i] /= a;
        }
        return l;
    }
    T operator()(const T& a) const {
        T res = static_cast<T>(0), xx = static_cast<T>(1);
        for(std::size_t i = 0; i < c_.size(); ++i){
            res += xx * c_[i];
            xx *= a;
        }
        return res;
    }
    polynomial operator()(const polynomial& data) const {
        polynomial res = {0}, xx = polynomial({1});
        for(std::size_t i = 0; i < c_.size(); ++i){
            res = res + xx * c_[i];
            xx = xx * data;
        }
        return res;
    }
};
template <numeric T>
std::ostream& operator<<(std::ostream& os, const polynomial<T>& f){
    std::vector<T> poly = f.data();
    for(const T& item : poly){
        os << item << " ";
    }
    return os;
}
template <numeric T>
const T R(const polynomial<T>& data){
    if(data.data().size() < std::size_t(2)){
        throw std::invalid_argument("Impossible to fint radius of convergence!");
    }
    T max_r = static_cast<T>(0);
    for(std::size_t i = 0; i < data.data().size() - std::size_t(1); ++i){
        if(data[i] == static_cast<T>(0)){continue;}
        T l = std::abs((data[i + 1]) / data[i]);
        if(max_r < l){
            max_r = l;
        }
    }
    return (max_r == 0) ? std::numeric_limits<T>::infinity() : (double(1) / (max_r));
}
template <numeric T>
polynomial<T> sin(const polynomial<T>& data, const std::size_t order){
    polynomial<T> sin({0});
    polynomial<T> cf = data;
    const polynomial<T> xx = data * data;
    double fact = double(1);
    for (std::size_t i = 1; i <= order; ++i){
        double p = (i % 2 != 0) ? double(1) : double(-1);
        sin = sin + cf * (p / fact);
        cf = cf * xx;
        fact *= (2 * i) * (2 * i + 1);
    }
    return sin;
}
template <numeric T>
polynomial<T> cos(const polynomial<T>& data, const std::size_t order){
    polynomial<T> cos({1});
    polynomial<T> cf = polynomial<T>({1});
    const polynomial<T> xx = data * data;
    double fact = double(1);
    for (std::size_t i = 1; i <= order; ++i){
        double p = (i % 2 == 0) ? double(1) : double(-1);
        cf = cf * xx;
        fact *= (2 * i - 1) * (2 * i);
        cos = cos + cf * (p / fact);
    }
    return cos;
}
template <numeric T>
polynomial<T> sh(const polynomial<T>& data, const std::size_t order){
    polynomial<T> sh({0});
    polynomial<T> cf = data;
    const polynomial<T> xx = data * data;
    double fact = double(1);
    for (std::size_t i = 1; i <= order; ++i){
        sh = sh + cf * (1 / fact);
        cf = cf * xx;
        fact *= (2 * i) * (2 * i + 1);
    }
    return sh;
}
template <numeric T>
polynomial<T> ch(const polynomial<T>& data, const std::size_t order){
    polynomial<T> ch({1});
    polynomial<T> cf = polynomial<T>({1});
    const polynomial<T> xx = data * data;
    double fact = double(1);
    for (std::size_t i = 1; i <= order; ++i){
        cf = cf * xx;
        fact *= (2 * i - 1) * (2 * i);
        ch = ch + cf * (1 / fact);
    }
    return ch;
}
template <numeric T>
polynomial<T> exponent(const polynomial<T>& data, const std::size_t order){
    polynomial<T> exp({1});
    polynomial<T> cf = polynomial<T>({1});
    const polynomial<T> xx = data;
    double fact = 1;
    for (std::size_t i = 1; i <= order; ++i){
        cf = cf * xx;
        fact *= (i);
        exp = exp + cf * (1 / fact);
    }
    return exp;
}
template <numeric T>
polynomial<T> ln(const polynomial<T>& data, const std::size_t order){
    polynomial<T> cf = data;
    polynomial<T> ln({0});
    if (cf[0] == 0){
        throw std::invalid_argument("not taylor polynomial");
    } else {
        polynomial<T> tmp = (cf / cf[0]) - polynomial<T>({1});
        const polynomial<T> sqr = tmp;
        for (std::size_t l = 1; l <= order; ++l){
            double s = (l % 2 == 0) ? -1 : 1;
            ln = ln + tmp * (s / l);
            tmp = tmp * sqr;
        }
        double ucr = std::log(cf[0]);
        return ln + polynomial({ucr});
    }
}
template <numeric T>
polynomial<T> binomial(const polynomial<T>& data, double alpha, const std::size_t order){
    polynomial<T> cf = data;
    polynomial<T> b({1});
    if (cf[0] == 0){
        throw std::invalid_argument("not taylor polynomial");
    } else {
        polynomial<T> tmp = (cf / cf[0]) - polynomial({1});
        const polynomial<T> xx = tmp;
        double fact = double(1), u = double(1);
        for (std::size_t k = 1; k <= order; ++k){
            u *= alpha - k + 1;
            fact *= k;
            b = b + tmp * (u / fact);
            tmp = tmp * xx;
        }
        double ucr = std::pow(cf[0], alpha);
        return b * ucr;
    }
}
template <numeric T>
polynomial<T> tan(const polynomial<T>& data, const std::size_t order){
    auto lambda = [](const polynomial<T>& data, const std::size_t r)->polynomial<T>{
        polynomial<T> cf = data;
        polynomial<T> fr({1});
        if (cf[0] == 0){
            throw std::invalid_argument("is not taylor");
        } else {
            polynomial<T> tmp = (cf / cf[0]) - polynomial<T>({1});
            const polynomial<T> xx = tmp;
            for (std::size_t i = 0; i <= r; ++i){
                double a = (i % 2 == 0) ? double(1) : double(-1);
                fr = fr + tmp * a;
                tmp = tmp * xx;
            }
            double c = double(1) / cf[0];
            return fr * c;
        }
    };
    polynomial<T> tan = sin(data, order) * lambda(cos(data, order));
    return tan;
}
template <numeric T>
polynomial<T> tanh(const polynomial<T>& data, const std::size_t order){
    auto lambda = [](const polynomial<T>& data, const std::size_t r)->polynomial<T>{
        polynomial<T> cf = data;
        polynomial<T> fr({1});
        if (cf[0] == 0){
            throw std::invalid_argument("is not taylor");
        } else {
            polynomial<T> tmp = (cf / cf[0]) - polynomial<T>({1});
            const polynomial<T> xx = tmp;
            for (std::size_t i = 0; i <= r; ++i){
                double a = (i % 2 == 0) ? double(1) : double(-1);
                fr = fr + tmp * a;
                tmp = tmp * xx;
            }
            double c = double(1) / cf[0];
            return fr * c;
        }
    };
    polynomial<T> th = sh(data, order) * lambda(ch(data, order));
    return th;
}
template <numeric T>
polynomial<T> arctan(const polynomial<T>& data, const std::size_t order){
    polynomial<T> cf = data;
    polynomial<T> arctan({0});
    const polynomial<T> xx = data * data;
    for (std::size_t i = 0; i < order; ++i){
        double p = (i % 2 == 0) ? double(1) : double(-1);
        arctan = arctan + cf * (p / (2 * i + 1));
        cf = cf * xx;
    }
    return arctan;
}
template <numeric T>
polynomial<T> arcsin(const polynomial<T>& data, const std::size_t order){
    polynomial<T> cf = data;
    const polynomial<T> xx = data * data;
    polynomial<T> arcsin({0});
    for (std::size_t i = 0; i <= order; ++i) {
        double a = 1;
        double b = 1;
        for (std::size_t l = 1; l < 2 * i + 1; l += 2){
            a *= l;
        }
        for (std::size_t h = 2; h < 2 * i + 2; h += 2){
            b *= h;
        }
        arcsin = arcsin + cf * (a /(b * (2 * i + 1)));
        cf = cf * xx;
    }
    return arcsin;
}
template <numeric T>
polynomial<T> arccos(const polynomial<T>& data, const std::size_t order){
    const double pi = 3.1415926;
    polynomial<T> arccos = polynomial<T>({pi / 2}) - arcsin(data, order);
    return arccos;
}