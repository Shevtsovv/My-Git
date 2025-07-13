#include <iostream>
#include <vector>
const double theta = 1e-5;
class subvector{
    double* qv_;
    std::size_t capacity_;
    std::size_t top_;
public:
    subvector() : capacity_(0), top_(0), qv_(nullptr){}
    subvector(const subvector& o) : capacity_(o.capacity_), top_(o.top_), qv_(nullptr){
        qv_ = new double[capacity_];
        for(std::size_t i = 0; i < top_; ++i){
            qv_[i] = o.qv_[i];
        }
    }
    subvector(std::size_t n_, double a) : top_(n_), capacity_(n_), qv_(new double[n_]){
        for(std::size_t i = 0; i < top_; ++i){
            qv_[i] = a;
        }
    }
    subvector(const std::initializer_list<double> list) : top_(list.size()), capacity_(2 * list.size()), qv_(nullptr){
        qv_ = new double[capacity_];
        std::size_t i = 0;
        for(const double& item : list){
            qv_[i++] = item;
        }
    }
    subvector(subvector&& o) : top_(o.top_), capacity_(o.capacity_), qv_(o.qv_){
        o.top_ = 0, o.capacity_ = 0;
        o.qv_ = nullptr;
    }
    ~subvector(){
        delete[] qv_;
    }
    subvector& operator=(const subvector& o){
        if(this != &o){
            delete[] qv_;
            qv_ = new double[o.capacity_];
            for(std::size_t i = 0; i < o.top_; ++i){
                qv_[i] = o.qv_[i];
            }
            top_ = std::min(o.top_, o.capacity_);
            capacity_ = o.capacity_;
        }
        return *this;
    }
    subvector& operator=(subvector&& o){
        if(this != &o){
            qv_ = o.qv_;
            top_ = o.top_, capacity_ = o.capacity_;
            o.qv_ = nullptr;
            o.top_ = 0, o.capacity_ = 0;
        }
        return *this;
    }
    const std::size_t& size() const {return top_;}
    const std::size_t& capacity() const {return capacity_;}
    double* begin(){return qv_;}
    const double* begin() const {return qv_;}
    double* end(){return qv_ + top_;}
    const double* end() const {return qv_ + top_;}
    bool operator==(const subvector& o) const {
        for(std::size_t i = 0; i < top_; ++i){
            if(std::abs(qv_[i] - o.qv_[i]) > theta){return false;}
        }
        return (top_ == o.top_ && capacity_ == o.capacity_);
    }
    double& operator[](std::size_t index) {
        if(index >= top_){throw std::out_of_range("is out os range vector!");}
        return qv_[index];
    }
    double operator[](std::size_t index) const {
        if(index >= top_){throw std::out_of_range("is out os range vector!");}
        return qv_[index];
    }
    void push_back(double a){
        if(top_ >= capacity_){
            std::size_t c = (capacity_ == 0) ? 1 : 2 * capacity_;
            double* o_qv_ = new double[c];
            for(std::size_t i = 0; i < top_; ++i){
                o_qv_[i] = qv_[i];
            }
            delete[] qv_;
            qv_ = o_qv_;
            capacity_ = c;
        }
        qv_[top_++] = a;
        return;
    }
    bool empty() const {
        return top_ == 0;
    }
    friend std::ostream& operator<<(std::ostream& os, const subvector& f){
        for(std::size_t i = 0; i < f.size(); ++i){
            os << f[i] << " ";
        }
        return os;
    }
};
class polynomial{
    subvector c_;
public:
    polynomial(const subvector& c) : c_(c){}
    polynomial(const std::initializer_list<double> list) : c_(list){}
    const subvector& data() const {return c_;}
    double operator[](std::size_t i) const {return c_[i];}
    double& operator[](std::size_t i){return c_[i];}
    bool operator==(const polynomial& o) const {return c_ == o.c_;}
    polynomial& operator=(const polynomial& o){
        c_ = o.c_;
        return *this;
    }
    double operator()(double m) const {
        double xx = 1;
        double res = 0;
        for(std::size_t i = 0; i < c_.size(); ++i){
            res += c_[i] * xx;
            xx *= m;
        }
        return res;
    }
    polynomial operator+(const polynomial& o) const {
        if(c_.size() != o.c_.size()){throw std::invalid_argument("vectors have different lenght");}
        subvector res = c_;
        for(std::size_t i = 0; i < c_.size(); ++i){
            res[i] += o.c_[i];
        }
        return {res};
    }
    polynomial operator-(const polynomial& o) const {
        if(c_.size() != o.c_.size()){throw std::invalid_argument("vectors have different lenght");}
        subvector res = c_;
        for(std::size_t i = 0; i < c_.size(); ++i){
            res[i] -= o.c_[i];
        }
        return {res};
    }
    polynomial operator*(const polynomial& o) const {
        std::size_t s = c_.size() + o.c_.size() - 1;
        if (s == 0) return polynomial{{}};
        subvector res(s, 0);
        for(std::size_t i = 0; i < c_.size(); ++i){
            for(std::size_t j = 0; j < o.c_.size(); ++j){
                res[i + j] += c_[i] * o.c_[j];
            }
        }
        return {res};
    }
    polynomial operator*(double m) const {
        subvector res = c_;
        for(std::size_t i = 0; i < res.size(); ++i){
            res[i] *= m;
        }
        return {res};
    }
    polynomial operator/(double m) const {
        if(m == 0){throw std::invalid_argument("divide by zero");}
        subvector res = c_;
        for(std::size_t i = 0; i < res.size(); ++i){
            res[i] /= m;
        }
        return {res};
    }
};
std::ostream& operator<<(std::ostream& os, const polynomial& f){
    for(const double& c : f.data()){
        os << c << " ";
    }
    return os;
}
int main(){
    polynomial a = {1, 1};
    polynomial b = {1, 1};
    std::cout << a * b;
}