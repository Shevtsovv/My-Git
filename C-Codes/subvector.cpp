#include <iostream>
#include <vector>
const double alpha = 1e-7;
class subvector{
    double* qv_;
    std::size_t top_;
    std::size_t capacity_;
public:
    subvector() : qv_(nullptr), top_(0), capacity_(0){}
    ~subvector(){
        delete[] qv_;
    }
    subvector(const std::initializer_list<double> list) : qv_(nullptr), top_(list.size()), capacity_(2 * list.size()){
        std::size_t i = 0;
        qv_ = new double[capacity_];
        std::copy(list.begin(), list.end(), qv_);
    }
    subvector(const subvector& o) : qv_(nullptr), top_(o.top_), capacity_(o.capacity_){
        qv_ = new double[o.capacity_];
        for(std::size_t i = 0; i < o.top_; ++i){
            qv_[i] = o.qv_[i];
        }
    }
    subvector(subvector&& o) : qv_(o.qv_), top_(o.top_), capacity_(o.capacity_){
        o.qv_ = nullptr;
        o.top_ = 0;
        o.capacity_ = 0;
    }
    subvector& operator=(const subvector& o){
        if(this != &o){
            delete[] qv_;
            qv_ = new double[o.capacity_];
            for(std::size_t i = 0; i < o.top_; ++i){
                qv_[i] = o.qv_[i];
            }
            capacity_ = o.capacity_;
            top_ = o.top_;
        }
        return *this;
    }
    subvector& operator=(subvector&& o){
        if(this != &o){
            qv_ = o.qv_;
            top_ = o.top_;
            capacity_ = o.capacity_;
            o.qv_ = nullptr;
            o.top_ = 0;
            o.capacity_ = 0;
        }
        return *this;
    }
    double* begin(){return qv_;}
    const double* begin() const {return qv_;}
    double* end(){return qv_ + top_;}
    const double* end() const {return qv_ + top_;}
    double& operator[](std::size_t n){
        if(n >= top_){throw std::invalid_argument("index is out of range");}
        return qv_[n];
    }
    double operator[](std::size_t n) const {
        if(n >= top_){throw std::invalid_argument("index is out of range");}
        return qv_[n];
    }
    bool operator==(const subvector& o) const {
        for(std::size_t i = 0; i < top_; ++i){
            if(std::abs(qv_[i] - o.qv_[i]) > alpha){return false;}
        }
        return (top_ == o.top_);
    }
    bool empty() const {return top_ == 0;}
    const std::size_t& size() const {return top_;}
    const std::size_t& capacity() const {return capacity_;}
    void clear() {top_ = 0;}
    void push_back(double a){
        if(top_ >= capacity_){
            std::size_t o_capacity_ = (capacity_ == 0) ? 1 : 2 * capacity_;
            double* o_qv_ = new double[o_capacity_];
            std::copy(qv_, qv_ + top_, o_qv_);
            delete[] qv_;
            qv_ = o_qv_;
            capacity_ = o_capacity_;
        }
        qv_[top_++] = a;
        return;
    }
    void pop_back(){
        if(empty()){throw std::invalid_argument("vector is empty");}
        top_--;
        return;
    }
    void insert(std::size_t position, std::size_t amount, double a){
        if(position > top_){throw std::invalid_argument("index is out of range");}
        std::size_t s = top_ + amount;
        if(s >= capacity_){
            std::size_t o_capacity_ = std::max(s, 2 * capacity_);
            double* o_qv_ = new double[o_capacity_];
            std::copy(qv_, qv_ + position, o_qv_);
            std::fill(o_qv_ + position, o_qv_ + position + amount, a);
            std::copy(qv_ + position, qv_ + top_, o_qv_ + position + amount);
            delete[] qv_;
            qv_ = o_qv_;
            capacity_ = o_capacity_;
        } else{
            std::copy_backward(qv_ + position, qv_ + top_, qv_ + top_ + amount);
            std::fill(qv_ + position, qv_ + position + amount, a);
        }
        top_ = s;
        return;
    }
    void shrink_to_fit(){
        if(top_ == 0){
            delete[] qv_;
            qv_ = nullptr;
            capacity_ = 0;
        } else{
            double* o_qv_ = new double[top_];
            std::copy(qv_, qv_ + top_, o_qv_);
            delete[] qv_;
            qv_ = o_qv_;
            capacity_ = top_;
        }
        return;
    }
    void erase(std::size_t position){
        if(position > top_){throw std::invalid_argument("index is out of range");}
        for(std::size_t i = position; i < top_; ++i){
            qv_[i] = qv_[i + 1];
        }
        top_--;
        return;
    }
    void resize(std::size_t o_top_){
        if(o_top_ == top_){return;}
        if(o_top_ == 0){
            delete[] qv_;
            qv_ = nullptr;
            top_ = 0;
            capacity_ = 0;
        }
        if(o_top_ > top_){
            std::size_t s = std::max(o_top_, 2 * capacity_);
            double* o_qv_ = new double[s];
            std::copy(qv_, qv_ + top_, o_qv_);
            std::fill(o_qv_ + top_, o_qv_ + o_top_, 0);
            delete[] qv_;
            qv_ = o_qv_;
            capacity_ = s;
            top_ = o_top_;
        } else{
            std::size_t g = std::max(2 * o_top_, capacity_);
            capacity_ = g;
            top_ = o_top_;
        }
        return;
    }
};
std::ostream& operator<<(std::ostream& os, const subvector& f){
    std::size_t i = 0;
    for(const double& c : f){
        os << c << " ";
    }
    return os;
}
int main() {
    subvector v = {1, 2, 3};
    v.resize(2);
}