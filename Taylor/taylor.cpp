#include <iostream>
#include <vector>
#include <cmath>
class polynomial{
    std::vector<double> c_;
public:
    polynomial(){}
    polynomial(const std::vector<double>& __c) : c_(__c){}
    polynomial(const std::initializer_list<double> _list){
        for(const double& item : _list){
            c_.push_back(item);
        }
    }
    const std::vector<double>& data() const {return c_;}
    double operator[](std::size_t _index) const {return c_[_index];}
    double& operator[](std::size_t _index) {return c_[_index];}
    polynomial operator+(const polynomial& _o) const {
        std::vector<double> res = c_;
        if(c_.size() > _o.c_.size()){
            for(std::size_t i = 0; i < _o.c_.size(); ++i){
                res[i] += _o.c_[i];
            }
        } else{
            res.resize(_o.c_.size());
            for(std::size_t i = 0; i < c_.size(); ++i){
                res[i] += _o.c_[i];
            }
            for(std::size_t i = c_.size(); i < _o.c_.size(); ++i){
                res[i] = _o.c_[i];
            }
        }
        return res;
    }
    polynomial operator-(const polynomial& _o) const {
        std::vector<double> res = c_;
        if(c_.size() > _o.c_.size()){
            for(std::size_t i = 0; i < _o.c_.size(); ++i){
                res[i] -= _o.c_[i];
            }
        } else{
            res.resize(_o.c_.size());
            for(std::size_t i = 0; i < c_.size(); ++i){
                res[i] -= _o.c_[i];
            }
            for(std::size_t i = c_.size(); i < _o.c_.size(); ++i){
                res[i] = -_o.c_[i];
            }
        }
        return res;
    }
    polynomial operator*(const polynomial& _o) const {
        std::size_t size = c_.size() + _o.c_.size() - 1;
        std::vector<double> res(size, 0);
        for(std::size_t i = 0; i < c_.size(); ++i){
            for(std::size_t j = 0; j < _o.c_.size(); ++j){
                res[i + j] += c_[i] * _o.c_[j];
            }
        }
        return res;
    }
    polynomial operator*(double _m) const {
        std::vector<double> res = c_;
        for(std::size_t i = 0; i < res.size(); ++i){
            res[i] *= _m;
        }
        return res;
    }
    polynomial operator/(double _m) const {
        std::vector<double> res = c_;
        if(_m == 0) {throw std::invalid_argument("divide by zero");}
        for(std::size_t i = 0; i < res.size(); ++i){
            res[i] /= _m;
        }
        return res;
    }
    double operator()(double _m) const {
        double xx = 1, res = 0;
        for(std::size_t i = 0; i < c_.size(); ++i){
            res += c_[i] * xx;
            xx *= _m;
        }
        return res;
    }
    polynomial operator()(const polynomial& _round) const {
        polynomial res = {0}, xx = {1};
        for(std::size_t i = 0; i < c_.size(); ++i){
            res = res + xx * c_[i];
            xx = xx * _round;
        }
        return res;
    }
    const std::size_t degree() const {
        if(c_.empty()){return 0;}
        return c_.size() - 1;
    }
    const std::size_t size() const {return c_.size();}
};
std::ostream& operator<<(std::ostream& _os, const polynomial& _d){
    std::vector<double> f = _d.data();
    if(f.empty()){
        throw std::invalid_argument("polynomial is empty!");
    }
    for(const double& item : f){
        _os << item << " ";
    }
    return _os;
}
polynomial sin(const polynomial& _data, unsigned int r = 5){
    polynomial sin_({0});
    polynomial cf = _data;
    const polynomial sqr = _data * _data;
    double fact = 1;
    for (unsigned int i = 1; i <= r; ++i){
        double p = (i % 2 != 0) ? 1 : -1;
        sin_ = sin_ + cf * (p / fact);
        cf = cf * sqr;
        fact *= (2 * i) * (2 * i + 1);
    }
    return {sin_};
}
polynomial cos(const polynomial& _data, unsigned int r = 5){
    polynomial cos_({1});
    polynomial cf = polynomial({1});
    const polynomial sqr = _data * _data;
    double fact = 1;
    for (unsigned int i = 1; i <= r; ++i){
        double p = (i % 2 == 0) ? 1 : -1;
        cf = cf * sqr;
        fact *= (2 * i - 1) * (2 * i);
        cos_ = cos_ + cf * (p / fact);
    }
    return {cos_};
}
polynomial sh(const polynomial& _data, unsigned int r = 5){
    polynomial sin_({0});
    polynomial cf = _data;
    const polynomial sqr = _data * _data;
    double fact = 1;
    for (unsigned int i = 1; i <= r; ++i){
        sin_ = sin_ + cf * (1 / fact);
        cf = cf * sqr;
        fact *= (2 * i) * (2 * i + 1);
    }
    return {sin_};
}
polynomial ch(const polynomial& _data, unsigned int r = 5){
    polynomial ch_({1});
    polynomial cf = polynomial({1});
    const polynomial sqr = _data * _data;
    double fact = 1;
    for (unsigned int i = 1; i <= r; ++i){
        cf = cf * sqr;
        fact *= (2 * i - 1) * (2 * i);
        ch_ = ch_ + cf * (1 / fact);
    }
    return {ch_};
}
polynomial exp(const polynomial& _data, unsigned int r = 5){
    polynomial exp_({1});
    polynomial cf = polynomial({1});
    const polynomial sqr = _data;
    double fact = 1;
    for (unsigned int i = 1; i <= r; ++i){
        cf = cf * sqr;
        fact *= (i);
        exp_ = exp_ + cf * (1 / fact);
    }
    return {exp_};
}
polynomial ln(const polynomial& _data, unsigned int r = 5){
    polynomial cf = _data;
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
polynomial binomial(const polynomial& _data, double alpha, unsigned int r = 5){
    polynomial cf = _data;
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
polynomial frac(const polynomial& _data, unsigned int r = 5){
    polynomial cf = _data;
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
polynomial tan(const polynomial& _data){
    polynomial tan_ = sin(_data) * frac(cos(_data));
    return {tan_};
}
polynomial tanh(const polynomial& _data){
    polynomial th_ = sh(_data) * frac(ch(_data));
    return {th_};
}
polynomial arctan(const polynomial& _data, unsigned int r = 5){
    polynomial cf = _data;
    polynomial arctan_({0});
    const polynomial sqr = _data * _data;
    for (unsigned int i = 0; i < r; ++i){
        double p = (i % 2 == 0) ? 1 : -1;
        arctan_ = arctan_ + cf * (p / (2 * i + 1));
        cf = cf * sqr;
    }
    return {arctan_};
}
polynomial arcsin(const polynomial& _data, unsigned int r = 5){
    polynomial cf = _data;
    const polynomial sqr = _data * _data;
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
polynomial arccos(const polynomial& _data, unsigned int r = 5){
    const double pi = 3.1415926;
    polynomial arccos_ = polynomial({pi / 2}) - arcsin(_data);
    return {arccos_};
}