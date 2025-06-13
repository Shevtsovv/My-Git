#include <iostream>
#include <fstream>
#include <cmath>

const double R = 8.31;
struct state {
    double p_, v_, t_, n_;
    double A_, Q_, S_;
    state(double p, double v, double t, double n = 1, double A = 0, double Q = 0, double S = 0) :
    p_(p), v_(v), t_(t), n_(n), A_(A), Q_(Q), S_(S) {}
};
class isoprocess {
    state iso_;
public:
    isoprocess(const state& iso) : iso_(iso) {}
    state isotermial(double vlm, std::ofstream& data) const {
        double step = std::abs((vlm - iso_.v_) / 10);
        double dv = (vlm > iso_.v_) ? step : -step;

        double cur_v = iso_.v_;
        double p = 0;
        double S = 0;
        if (vlm > iso_.v_) {
            for (; cur_v <= vlm; cur_v += dv) {
                p = (iso_.p_ * iso_.v_) / (cur_v);
                S = iso_.S_ + iso_.n_ * R * std::log(cur_v / iso_.v_);
                data << cur_v << " " << p << " "<< iso_.t_<< " " << S << std::endl;
            }
        } else {
            for(; cur_v >= vlm; cur_v += dv) {
                p = (iso_.p_ * iso_.v_) / (cur_v);
                S = iso_.S_ + iso_.n_ * R * std::log(cur_v / iso_.v_);
                data << cur_v << " " << p << " "<< iso_.t_<< " " << S << std::endl;
            }
        }
        double A = iso_.n_ * R * iso_.t_ * std::log((vlm) / (iso_.v_));
        double Q = A;
        return state(p, vlm, iso_.t_, iso_.n_, A, Q, S);
    }
    state adiabatic(double vlm, double i, std::ofstream& data) const {
        double step = std::abs((vlm - iso_.v_) / 10);
        double dv = (vlm > iso_.v_) ? step : -step;
        const double c_v = (i / 2) * R;

        double cur_v = iso_.v_;
        double p, t = 0;

        const double xx = (2 + i) / (i);
        if(vlm > iso_.v_) {
            for(; cur_v <= vlm; cur_v += dv) {
                double vv = ((iso_.v_) / (cur_v));
                p = iso_.p_ * std::pow(vv, xx);
                t = iso_.t_ * std::pow(vv, xx - 1);
                data << cur_v << " " << p << " "<< t << " " << iso_.S_ << std::endl;
            }
        } else {
            for(; cur_v >= vlm; cur_v += dv) {
                double vv = ((iso_.v_) / (cur_v));
                p = iso_.p_ * std::pow(vv, xx);
                t = iso_.t_ * std::pow(vv, xx - 1);
                data << cur_v << " " << p << " "<< t << " " << iso_.S_ << std::endl;
            }
        }
        double A = (i / 2.0) * iso_.n_ * R * (iso_.t_ - t);
        return state(p, vlm, t, iso_.n_, A, iso_.Q_, iso_.S_);
    }
};

int main() {
    std::ofstream p12("12.txt"), p23("23.txt"), p34("34.txt"), p41("41.txt");

    const double T_heat = 312;

    state s1(1e5, 5.0, T_heat, 1, 0, 0, 0);
    isoprocess isoterm_1(s1);
    state s2 = isoterm_1.isotermial(10.0, p12);

    isoprocess adiabat_2(s2);
    state s3 = adiabat_2.adiabatic(15.0, 3, p23);

    state s3_iso(s3.p_, s3.v_, s3.t_, s3.n_, 0, 0, s3.S_);
    isoprocess p3(s3_iso);
    state s4 = p3.isotermial(7.5, p34);

    isoprocess p4(s4);
    state s1_final = p4.adiabatic(s1.v_, 3, p41);

    std::ofstream data("cua.txt");
    double theta = 1 - (std::abs(s4.Q_) / s2.Q_);
    double A_cycle = s2.Q_ + s4.Q_;
    data << theta << " " << A_cycle << " " << s2.Q_ << " " << std::abs(s4.Q_) << " " << T_heat << " " << s3.t_ << std::endl;
}
