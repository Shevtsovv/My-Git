#include <vector>
#include <ostream>
class Polynomial
{
    std::vector<double> c_;
public:
    Polynomial(const std::vector<double>& c) : c_(c){}
    Polynomial(const std::initializer_list<double>& list){
        for(const double& item : list){
            c_.push_back(item);
        }
    }
    Polynomial operator+(const Polynomial& other) const {
        std::vector<double> sum = (c_.size() > other.c_.size()) ? c_ : other.c_;
        if(c_.size() > other.c_.size()){
            for(std::size_t i = 0; i < other.c_.size(); ++i){
                sum[i] = sum[i] + other.c_[i];
            }
        } else{
            for(std::size_t i = 0; i < c_.size(); ++i){
                sum[i] = sum[i] + c_[i];
            }
        }
        return Polynomial(sum);
    }
    Polynomial operator-(const Polynomial& other) const {
        std::vector<double> dif = (c_.size() > other.c_.size()) ? c_ : other.c_;
        if(c_.size() > other.c_.size()){
            for(std::size_t i = 0; i < other.c_.size(); ++i){
                dif[i] = dif[i] - other.c_[i];
            }
        } else{
            for(std::size_t i = 0; i < other.c_.size(); ++i){
                dif[i] = dif[i] * (-1);
            }
            for(std::size_t i = 0; i < c_.size(); ++i){
                dif[i] = dif[i] + c_[i];
            }
        }
        return Polynomial(dif);
    }
    Polynomial operator*(const Polynomial& other) const {
        std::vector<double> fg(c_.size() + other.c_.size() - 1, 0);
        for(std::size_t i = 0; i < c_.size(); ++i){
            for(std::size_t j = 0; j < other.c_.size(); ++j){
                fg[i + j] += c_[i] * other.c_[j];
            }
        }
        return Polynomial(fg);
    }
    Polynomial operator*(double value) const {
        std::vector<double> mult_v = c_;
        for(std::size_t i = 0; i < c_.size(); ++i){
            mult_v[i] = mult_v[i] * (-1);
        }
        return Polynomial(mult_v);
    }
    Polynomial operator/(double value) const{
        if(value == 0){throw std::invalid_argument("incorrect value");}
        std::vector<double> del = c_;
        for(std::size_t i = 0; i < c_.size(); ++i){
            del[i] /= value;
        }
        return Polynomial(del);
    }
    double operator()(double value) const {
        double xx = 1;
        double fx = 0;
        for(std::size_t i = 0; i < c_.size(); ++i){
            fx += c_[i] * xx;
            xx *= value;
        }
        return fx;
    }
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& object){
        for(const auto& item : object.c_){
            os << item << " ";
        }
        return os;
    }
};
