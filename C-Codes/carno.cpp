#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

const double r = 8.31;
struct state {
    double p_, v_, t_, molar_;
    state(double prs, double vlm, double tmp, double mlr) : p_(prs), v_(vlm), t_(tmp), molar_(mlr) {
        if (prs <= 0 || vlm <= 0 || tmp <= 0 || mlr <= 0) {
            throw std::invalid_argument("incorrect parametrs");
        }
    }
};
class Carno {
    state c_;
public:
    Carno(const state& c) : c_(c) {}
    const double& preasure() const {
        return c_.p_;
    }
    const double& volume() const {
        return c_.v_;
    }
    state isotermial(double vlm, const std::string& filename) const {
    const double dv = (vlm > c_.v_) ? 0.1 : -0.1;
    double cur_v = c_.v_;
    double p = c_.p_;
    std::ofstream data (filename);
        if (vlm > c_.v_) {
            for(; cur_v < vlm; cur_v += dv) {
                p = (c_.p_ * c_.v_) / (cur_v);
                data << cur_v << " " << p << std::endl;
            }
        }
        else{
            for (; cur_v > vlm; cur_v += dv){
                p = (c_.p_ * c_.v_) / (cur_v);
                data << cur_v << " " << p << std::endl;
            }
        }
        return state(p, vlm, c_.t_, c_.molar_);
    }
    state adiabatic(double vlm, double i, const std::string& filename) const {
        const double dv = (vlm > c_.v_) ? 0.1 : -0.1;
        double gamma = (i + 2) / (i);
        double t = c_.t_, p = c_.p_;
        double cur_v = c_.v_;
        std::ofstream data (filename);
        if (vlm > c_.v_) {
            for (; cur_v < vlm; cur_v += dv) {
                p = c_.p_ * std::pow(((c_.v_) / (cur_v)), gamma);
                t = c_.t_ * std::pow(((c_.v_) / (cur_v)), gamma - 1);
                data << cur_v << " " << p << std::endl;
            }
        } 
        else {
            for(; cur_v > vlm; cur_v += dv) {
                p = c_.p_ * std::pow(((c_.v_) / (cur_v)), gamma);
                t = c_.t_ * std::pow(((c_.v_) / (cur_v)), gamma - 1);
                data << cur_v << " " << p << std::endl;
            }
        }
        return state(p, vlm, t, c_.molar_);
    }
};
int main() {
    state gas(200, 10, 300, 28);
    Carno process(gas);
    process.isotermial(30, "iso.txt");
}