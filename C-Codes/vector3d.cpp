#include <iostream>
#include <vector>
#include <cmath>

class vector3d {
    std::vector<double> c_;
public:
    vector3d (const std::vector<double>& c) : c_(c) {
        if (c_.size() != 3) {throw std::invalid_argument("expect 2d");}
    }
    const std::vector<double>& data() const {return c_;}

    double& operator[](std::size_t index) {
        return c_[index];
    }
    double operator[](std::size_t index) const {
        return c_[index];
    }
    bool operator==(const vector3d& o) const {
        return c_ == o.c_;
    }
    vector3d operator+(const vector3d& o) const {
        std::vector<double> res = c_;
        for (unsigned int i = 0; i < res.size(); ++i) {
            res[i] += o.c_[i];
        }
        return {res};
    }
    vector3d operator-(const vector3d& o) const {
        std::vector<double> res = c_;
        for (unsigned int i = 0; i < res.size(); ++i) {
            res[i] -= o.c_[i];
        }
        return {res};
    }
    vector3d operator*(double m) const {
        std::vector<double> res = c_;
        for (unsigned int i = 0; i < res.size(); ++i) {
            res[i] *= m;
        }
        return {res};
    }
    vector3d operator/(double m) const {
        if (m == 0) {throw std::invalid_argument("divide by zero");}
        std::vector<double> res = c_;
        for (unsigned int i = 0; i < res.size(); ++i) {
            res[i] /= m;
        }
        return {res};
    }
    double operator*(const vector3d& o) const {
        double scalar = 0;
        for (unsigned int i = 0; i < c_.size(); ++i) {
            scalar += c_[i] * o.c_[i];
        }
        return scalar;
    }
    bool zero() const {
        double delta = 1e-19;
        for (unsigned int i = 0; i < c_.size(); ++i) {
            if (c_[i] >= delta) {return false;}
        }
        return true;
    }
    vector3d norm() const {
        if (c_ == std::vector<double>(c_.size(), 0)) {throw std::invalid_argument("impos to norm zero vec");}
        std::vector<double> tmp = c_;
        double len = length(c_);
        for (unsigned int i = 0; i < c_.size(); ++i) {
            tmp[i] /= len;
        }
        return {tmp};
    }
};
double length(const vector3d& vec) {
    if (vec.zero()) {return 0;}
    double len = std::sqrt (vec * vec);
    return len;
}
