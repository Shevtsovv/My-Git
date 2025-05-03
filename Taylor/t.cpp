#include "raylib.h"
#include <iostream>
#include <vector>

const int scrw = 800, scrh = 800, h = 400;
const double dx = 0.1;
const int x_max = 5, x_min = -5;

double factorial(unsigned int a){
    unsigned int  res = 1;
    for (unsigned int i = 1; i <= a; ++i){
        res *= i;
    }
    return res;
}

class polynomial{
    std::vector<double> c_;
public:
    polynomial(const std::vector<double>& c) : c_{c} {}
    
    const std::vector<double>& data() const {
        return c_;
    }

    double operator[](std::size_t n) const {
        return c_[n];
    }

    double& operator[](std::size_t n) {
        return c_[n];
    }

    double operator()(double m) const {
        double res = 0;
        double xx = 1;
        for (std::size_t i = 0; i < c_.size(); ++i){
            res += c_[i] * xx;
            xx *= m;
        }
        return res;
    }
    
    polynomial operator+(const polynomial& o) const {
        std::vector<double> res = c_.size() < o.c_.size() ? o.c_ : c_;
        if (c_.size() < o.c_.size()){
            for (std::size_t i = 0; i < c_.size(); ++i){
                res[i] += c_[i];
            }
        } else {
            for (std::size_t i = 0; i < o.c_.size(); ++i){
                res[i] += o.c_[i];
            }
        }
        return {res};
    }

    polynomial operator-(const polynomial& d) const {
        std::size_t ns = (c_.size() < d.c_.size()) ? d.c_.size() : c_.size();
        std::vector<double> res(ns, 0);

        if (c_.size() < d.c_.size()){
            for (std::size_t i = 0; i < c_.size(); ++i){
                res[i] = c_[i] - d.c_[i];
                for (std::size_t l = 0; l < ns - c_.size(); ++l){
                    res[c_.size() + l] = 0 - d.c_[c_.size() + l];
                }
            }
        } else {
            for (std::size_t i = 0; i < d.c_.size(); ++i){
                res[i] = c_[i] - d.c_[i];
                for (std::size_t l = 0; l < ns - d.c_.size(); ++l){
                    res[d.c_.size() + l] = c_[d.c_.size() + l] - 0;
                }
            }
        }
        return {res};
    }

    polynomial operator*(const polynomial& o) const {
        std::size_t ns = c_.size() + o.c_.size() - 1;
        std::vector<double> res(ns, 0);

        for (std::size_t i = 0; i < c_.size(); ++i){
            for (std::size_t j = 0; j < o.c_.size(); ++j){
                res[i + j] += c_[i] * o.c_[j];
            }
        }
        return {res};
    }

    polynomial operator*(double m) const {
        std::vector<double> res = c_;
        for (std::size_t i = 0; i < c_.size(); ++i){
            res[i] = res[i] * m;
        }
        return {res};
    }
    
    polynomial operator/(double m) const {
        if (m == 0){
            throw std::invalid_argument("divide on zero");
        }
        std::vector<double> res = c_;
        for (std::size_t i = 0; i < c_.size(); ++i){
            res[i] /= m;
        }
        return {res};
    }
};

void Taylor_Sin(int* m, unsigned int l, const polynomial& f, Color color){
    polynomial sin_({0});
    polynomial cf = f.data();

    for (unsigned int i = 0; i < l; ++i){
        double p = (i % 2 == 0) ? 1 : -1;
        sin_ = sin_ + cf * (p/(factorial(2 * i + 1)));
        cf = cf * f.data() * f.data();
    }

    for (double i = x_min; i < x_max; i += dx){
        double y = sin_(i);
        int xs = i * (*m) + scrw / 2;
        int ys = - y * (*m) + scrh / 2;
        DrawCircle(xs, ys, 3, color);
    }
}
void Taylor_Sh(int* m, unsigned int l, const polynomial& f, Color color){
    polynomial sh_({0});
    polynomial cf = f.data();

    for (unsigned int i = 0; i < l; ++i){
        sh_ = sh_ + cf * (1/(factorial(2 * i + 1)));
        cf = cf * f.data() * f.data();
    }
    
    for (double i = x_min; i < x_max; i += dx){
        double y = sh_(i);
        int xs = i * (*m) + scrw / 2;
        int ys = - y * (*m) + scrh / 2;
        DrawCircle(xs, ys, 3, color);
    }
}
void Taylor_Cos(int* m, unsigned int l, const polynomial& f, Color color){
    polynomial cos_({0});
    polynomial cf = polynomial({1});

    for (unsigned int i = 0; i < l; ++i){
        double p = (i % 2 == 0) ? 1 : -1;
        cos_ = cos_ + cf * (p/(factorial(2 * i)));
        cf = cf * f.data() * f.data();
    }

    for (double i = x_min; i < x_max; i += dx){
        double y = cos_(i);
        int xs = i * (*m) + scrw / 2;
        int ys = - y * (*m) + scrh / 2;
        DrawCircle(xs, ys, 3, color);
    }
}
void Taylor_Ch(int* m, unsigned int l, const polynomial& f, Color color){
    polynomial ch_({0});
    polynomial cf = polynomial({1});

    for (unsigned int i = 0; i < l; ++i){
        ch_ = ch_ + cf * (1/(factorial(2 * i)));
        cf = cf * f.data() * f.data();
    }

    for (double i = x_min; i < x_max; i += dx){
        double y = ch_(i);
        int xs = i * (*m) + scrw / 2;
        int ys = - y * (*m) + scrh / 2;
        DrawCircle(xs, ys, 3, color);
    }
}
void Taylor_Exp(int* m, unsigned int l, const polynomial& f, Color color){
    polynomial exp_({0});
    polynomial cf = polynomial({1});
    for (unsigned int i = 0; i < l; ++i){
        exp_ = exp_ + cf * (1/factorial(i));
        cf = cf * f.data();
    }
    for (double i = x_min; i < x_max; i += dx){
        double y = exp_(i);
        int xs = i * (*m) + scrw / 2;
        int ys = - y * (*m) + scrh / 2;
        DrawCircle(xs, ys, 3, color);
    }
}
void Draw_Axes(int* m){
    Vector2 x_ = {0, scrh / 2};
    Vector2 x1_ = {scrw, scrh / 2};
    Vector2 y_ = {scrw / 2, 0};
    Vector2 y1_ = {scrw / 2, scrh};

    DrawLineEx(x_, x1_, 2, GRAY);
    DrawLineEx(y_, y1_, 2, GRAY);

    for(int x = scrw / 2; x < scrw; x += (1*(*m))){
        DrawLine(x, scrh / 2 - h, x, scrh / 2 + h, DARKGRAY);
    }

    for(int x = scrw / 2; x > 0; x -= (1*(*m))){
        DrawLine(x, scrh / 2 - h, x, scrh / 2 + h, DARKGRAY);
    }

    for(int y = scrh / 2; y < scrh; y += (1*(*m))){
        DrawLine(scrw / 2 - h, y, scrw / 2 + h, y, DARKGRAY);
    }

    for(int y = scrh / 2; y > 0; y -= (1*(*m))){
        DrawLine(scrw / 2 - h, y, scrw / 2 + h, y, DARKGRAY);
    }
}

int main() {
    int mult = 500, dm = 20;
    
    InitWindow(scrw, scrh, "Raylib Taylor Graph");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);
        Taylor_Sin(&mult, 7, polynomial({0, 1}), BLUE);
        Taylor_Sin(&mult, 3, polynomial({0, 1}), YELLOW);
        Taylor_Sin(&mult, 1, polynomial({0, 1}), ORANGE);
        Draw_Axes(&mult);
        if (GetMouseWheelMove() > 0){
            mult += dm;
            if (mult >= 310){mult = 310;}
        }
        if (GetMouseWheelMove() < 0) 
        {
            mult -= dm;
            if (mult <= 50) {mult = 50;}
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
