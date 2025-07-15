#include <iostream>
const double alpha = 1e-7;
class polynomial{
    double* qv_;
    std::size_t top_;
    std::size_t capacity_;
public:
    polynomial() : qv_(nullptr), top_(0), capacity_(0){}
    ~polynomial(){delete[] qv_;}
    polynomial(const polynomial& o) : qv_(nullptr), top_(o.top_), capacity_(o.capacity_){
        qv_ = new double[capacity_];
        for(std::size_t i = 0; i < top_; ++i){
            qv_[i] = o.qv_[i];
        }
    }
    polynomial(std::size_t size, double a) : qv_(nullptr), top_(size), capacity_(size){
        qv_ = new double[capacity_];
        std::fill(qv_, qv_ + top_, a);
    }
    polynomial(polynomial&& o) : qv_(o.qv_), top_(o.top_), capacity_(o.capacity_){
        o.qv_ = nullptr;
        o.top_ = 0;
        o.capacity_ = 0;
    }
    polynomial(const std::initializer_list<double> list) : qv_(nullptr), top_(list.size()), capacity_(list.size()){
        qv_ = new double[capacity_];
        std::copy(list.begin(), list.end(), qv_);
    }
    polynomial& operator=(const polynomial& o){
        if(this != &o){
            delete[] qv_;
            qv_ = new double[o.capacity_];
            for(std::size_t i = 0; i < o.top_; ++i){
                qv_[i] = o.qv_[i];
            }
            top_ = o.top_;
            capacity_ = o.capacity_;
        }
        return *this;
    }
    polynomial& operator=(polynomial&& o){
        if(this != &o){
            delete[] qv_;
            qv_ = o.qv_;
            top_ = o.top_;
            capacity_ = o.capacity_;
            o.qv_ = nullptr;
            o.top_ = 0;
            o.capacity_ = 0;
        }
        return *this;
    }
    double* begin() {return qv_;}
    const double* begin() const {return qv_;}
    double* end() {
        return qv_ + top_;
    }
    const double* end() const {
        return qv_ + top_;
    }
    double& operator[](std::size_t index){
        if(index >= top_){throw std::invalid_argument("is out of range");}
        return qv_[index];
    }
    double operator[](std::size_t index) const {
        if(index >= top_){throw std::invalid_argument("is out of range");}
        return qv_[index];
    }
    bool operator==(const polynomial& o) const {
        for(std::size_t i = 0; i < top_; ++i){
            if(std::abs(qv_[i] - o.qv_[i]) > alpha){return false;}
        }
        return (top_ == o.top_ && capacity_ == o.capacity_);
    }
    polynomial operator+(const polynomial& o) const {
        if(top_ != o.top_) {throw std::invalid_argument("polynoms have different lenght");}
        polynomial res(top_, 0);
        for(std::size_t i = 0; i < top_; ++i){
            res[i] = qv_[i] + o.qv_[i];
        }
        return res;
    }
    polynomial operator-(const polynomial& o) const {
        if(top_ != o.top_) {throw std::invalid_argument("polynoms have different lenght");}
        polynomial res(top_, 0);
        for(std::size_t i = 0; i < top_; ++i){
            res[i] = qv_[i] + o.qv_[i];
        }
        return res;
    }
    polynomial operator*(const polynomial& o){
        std::size_t s = top_ + o.top_ - 1;
        polynomial res(s, 0);
        for(std::size_t i = 0; i < top_; ++i){
            for(std::size_t j = 0; j < o.top_; ++j){
                res[i + j] += qv_[i] * o.qv_[j];
            }
        }
        return res;
    }
    polynomial operator*(double m) const {
        polynomial res(top_, 0);
        for(std::size_t i = 0; i < top_; ++i){
            res[i] = (this->qv_[i]) * m;
        }
        return res;
    }
    polynomial operator/(double m) const {
        if(std::abs(m) < alpha){throw std::invalid_argument("divide by zero");}
        polynomial res(top_, 0);
        for(std::size_t i = 0; i < top_; ++i){
            res[i] = (this->qv_[i]) / m;
        }
        return res;
    }
    const std::size_t& size() const {return top_;}
    const std::size_t& capacity() const {return capacity_;}
};
std::ostream& operator<<(std::ostream& os, const polynomial& o){
    if(o.size() == 0){os << "polynom is empty";}
    for(const double& item : o){
        os << item << " ";
    }
    return os;
}