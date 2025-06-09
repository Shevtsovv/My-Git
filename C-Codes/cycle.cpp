#include <iostream>
#include <cmath>
#include <fstream>

const double R = 8.31;
struct state {
    double p_, v_, t_, n_;
    double A_, Q_;
    state(double p, double v, double t, double n = 1, double A = 0, double Q = 0) : p_(p), v_(v), t_(t), n_(n), A_(A), Q_(Q) {}
};
class isoprocess {
    state iso_;
public:
    isoprocess(const state& iso) : iso_(iso) {}
    state isotermial(double vlm, const std::string& filename) const {
        double step = std::abs((vlm - iso_.v_) / 100);
        double dv = (vlm > iso_.v_) ? step : -step;

        double cur_v = iso_.v_;
        double p = 0;
        std::ofstream data(filename);
        if (vlm > iso_.v_) {
            for (; cur_v <= vlm; cur_v += dv) {
                p = (iso_.p_ * iso_.v_) / (cur_v);
                data << cur_v << " " << p << std::endl;
            }
        } else {
            for(; cur_v >= vlm; cur_v += dv) {
                p = (iso_.p_ * iso_.v_) / (cur_v);
                data << cur_v << " " << p << std::endl;
            }
        }
        double A = iso_.n_ * R * iso_.t_ * std::log((vlm) / (iso_.v_));
        double Q = A;
        return state(p, vlm, iso_.t_, iso_.n_, A, Q);
    }
    state adiabatic(double vlm, double i, const std::string& filename) const {
        double step = std::abs((vlm - iso_.v_) / 100);
        double dv = (vlm > iso_.v_) ? step : -step;

        double cur_v = iso_.v_;
        double p, t = 0;

        const double gamma = (2 + i) / (i);

        std::ofstream data(filename);
        if(vlm > iso_.v_) {
            for(; cur_v <= vlm; cur_v += dv) {
                p = iso_.p_ * std::pow(((iso_.v_) / (cur_v)), gamma);
                t = iso_.t_ * std::pow(((iso_.v_) / (cur_v)), gamma - 1);
                data << cur_v << " " << p << std::endl;
            }
        } else {
            for(; cur_v >= vlm; cur_v += dv) {
                p = iso_.p_ * std::pow(((iso_.v_) / (cur_v)), gamma);
                t = iso_.t_ * std::pow(((iso_.v_) / (cur_v)), gamma - 1);
                data << cur_v << " " << p << std::endl;
            }
        }
        double A = (i / 2.0) * iso_.n_ * R * (iso_.t_ - t);
        return state(p, vlm, t, iso_.n_, A);
    }
    state isohorical(double tmp, double i, const std::string& filename) const {
        double step = std::abs(tmp - iso_.t_) / 100;
        double dt = (tmp > iso_.t_) ? step : -step;

        double cur_t = iso_.t_;
        double p = 0;

        std::ofstream data(filename);
        if(tmp > iso_.t_) {
            for(; cur_t <= tmp; cur_t += dt) {
                p = (cur_t / iso_.t_) * iso_.p_;
                data << cur_t << " " << p << std::endl;
            }
        } else {
            for(; cur_t >= tmp; cur_t += dt) {
                p = (cur_t / iso_.t_) * iso_.p_;
                data << cur_t << " " << p << std::endl;
            }
        }
        double Q = (i / 2) * iso_.n_ * R * (tmp - iso_.t_);
        return state(p, iso_.v_, tmp, iso_.n_, iso_.A_, Q);
    }
    state isobarical(double tmp, double i, const std::string& filename) const {
        double step = std::abs(tmp - iso_.t_) / 100;
        double dt = (tmp > iso_.t_) ? step : -step;

        double cur_t = iso_.t_;
        double v = 0;

        std::ofstream data(filename);
        if(tmp > iso_.t_){
            for(; cur_t <= tmp; cur_t += dt) {
                v = iso_.v_ * (cur_t) / (iso_.v_);
                data << cur_t << " " << v << std::endl;
            }
        } else {
            for(; cur_t >= tmp; cur_t += dt) {
                v = iso_.v_ * (cur_t / iso_.v_);
                data << cur_t << " " << v << std::endl;
            }
        }
        double A = iso_.p_ * (v - iso_.v_);
        double Q = ((2 + i) / 2) * iso_.p_ * (v - iso_.v_);
        return state(iso_.p_, v, tmp, iso_.n_, A, Q);
    }
};
int main() {
    const double T_hot = 380;
    const double T_cold = 286;

    state s1(1e5, 5, T_hot, 1);
    isoprocess p1(s1);
    state s2 = p1.isotermial(10, "12.txt");
    
    isoprocess p2(s2);
    state s3 = p2.adiabatic(15, 3, "23.txt");

    state s3_iso(s3.p_, s3.v_, T_cold, s3.n_);
    isoprocess p3(s3_iso);
    state s4 = p3.isotermial(7.5, "34.txt");

    isoprocess p4(s4);
    state s1_final = p4.adiabatic(5, 3, "41.txt");

    std::ofstream data("cua.txt");
    double theta = 1 - (std::abs(s4.Q_) / (s2.Q_));
    double A = theta * s2.Q_;
    data << theta << " " << A << " " << s2.Q_ << " " << std::abs(s4.Q_) << std::endl;
}
