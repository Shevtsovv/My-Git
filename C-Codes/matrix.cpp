#include <iostream>
#include <cmath>
#include <vector>
class matrix;
matrix unit(std::size_t n);
const double theta = 1e-5;
class matrix{
    std::vector<std::vector<double>> matrix_;
    std::size_t m_, n_;
public:
    matrix(const std::vector<std::vector<double>>& matrix) : matrix_(matrix){
        if(matrix_.empty() || matrix_[0].empty()){throw std::invalid_argument("matrix is empty!");}
        m_ = matrix_.size();
        n_ = matrix_[0].size();
        for(const std::vector<double>& row : matrix_){
            if(row.size() != n_){throw std::invalid_argument("rows have different lendth");}
        }
    }
    const double operator()(std::size_t i, std::size_t j){return matrix_[i][j];}
    const std::vector<std::vector<double>>& data() const {return matrix_;}
    const std::size_t& rows() const {return m_;}
    const std::size_t& columns() const {return n_;}
    matrix& operator=(const matrix& o){
        if(m_ != o.m_ || n_ != o.n_){
            throw std::invalid_argument("invalid size");
        }
        for(std::size_t i = 0; i < m_; ++i){
            for(std::size_t j = 0; j < n_; ++j){
                matrix_[i][j] = o.matrix_[i][j];
            }
        }
        return *this;
    }
    bool operator==(const matrix& o) const {
        if(m_ != o.m_ || n_ != o.n_){return false;}
        for(std::size_t i = 0; i < m_; ++i){
            for(std::size_t j = 0; j < n_; ++j){
                if(std::abs(matrix_[i][j] - o.matrix_[i][j]) > theta){return false;}
            }
        }
        return true;
    }
    matrix operator+(const matrix& o) const {
        std::vector<std::vector<double>> ss = matrix_;
        if(m_ != o.m_ || n_ != o.n_){throw std::invalid_argument("not equal");}
        for(std::size_t i = 0; i < m_; ++i){
            for(std::size_t j = 0; j < n_; ++j){
                ss[i][j] += o.matrix_[i][j];
            }
        }
        return {ss};
    }
    matrix operator-(const matrix& o) const {
        std::vector<std::vector<double>> ss = matrix_;
        if(m_ != o.m_ || n_ != o.n_){throw std::invalid_argument("not equal");}
        for(std::size_t i = 0; i < m_; ++i){
            for(std::size_t j = 0; j < n_; ++j){
                ss[i][j] -= o.matrix_[i][j];
            }
        }
        return {ss};
    }
    matrix operator*(const matrix& o) const {
        if(n_ != o.m_){throw std::invalid_argument("impossible to mult matrixes");}
        std::vector<std::vector<double>> ll(m_, std::vector<double>(o.n_, 0));
        for(std::size_t i = 0; i < m_; ++i){
            for(std::size_t j = 0; j < o.n_; ++j){
                double ss = 0;
                for(std::size_t l = 0; l < n_; ++l){
                    ss += matrix_[i][l] * o.matrix_[l][j];
                }
                ll[i][j] = ss;
            }
        }
        return {ll};
    }
    matrix& operator*(double lambda){
        for(std::size_t i = 0 ; i < m_; ++i){
            for(std::size_t j = 0; j < n_; ++j){
                matrix_[i][j] *= lambda;
            }
        }
        return *this;
    }
    matrix T() const {
        std::vector<std::vector<double>> ss(n_, std::vector<double>(m_, 0));
        for(std::size_t i = 0; i < m_; ++i){
            for(std::size_t j = 0; j < n_; ++j){
                ss[j][i] = matrix_[i][j];
            }
        }
        return {ss};
    }
    bool zero() const {
        for(std::size_t i = 0; i < m_; ++i){
            for(std::size_t j = 0; j < n_; ++j){
                if(std::abs(matrix_[i][j]) > theta){return false;} 
            }
        }
        return true;
    }
    std::size_t rank(double eps = 1e-10) const {
        if(matrix_.empty()){return 0;}
        if(*this == unit(m_)){return m_;}
        std::size_t r = 0;
        std::vector<std::vector<double>> R = matrix_;
        for(std::size_t cur_row = 0, cur_col = 0; cur_col < n_ && cur_row < m_; ++cur_col){
            std::size_t m = cur_row;
            for(std::size_t l = cur_row + 1; l < m_; ++l){
                if(std::abs(R[l][cur_col] - R[m][cur_col]) > theta){
                    m = l;
                }
            }
            if(std::abs(R[m][cur_col]) < theta){continue;}
            if(m != cur_row){
                std::swap(R[cur_row], R[m]);
            }
            for(std::size_t l = cur_row + 1; l < m_; ++l){
                double f = R[l][cur_col] / R[cur_row][cur_col];
                for(std::size_t k = cur_col; k < n_; ++k){
                    R[l][k] -= f * R[cur_row][k];
                }
            }
            ++r;
            ++cur_row;
        }
        return r;
    }
    double det() const {
        if(m_ != n_){throw std::runtime_error("matrix is not square");}
        if(zero()){return 0;}
        std::vector<std::vector<double>> l(n_, std::vector<double>(n_, 0)), u(n_, std::vector<double>(n_, 0));
        for(std::size_t i = 0; i < m_; ++i){
            l[i][i] = 1;
        }
        for(std::size_t i = 0; i < n_; ++i){
            for(std::size_t j = 0; j < n_ ; ++j){
                if(i <= j){
                    double s = 0;
                    for(std::size_t k = 0; k < i; ++k){
                        s += l[i][k] * u[k][j];
                    }
                    u[i][j] = matrix_[i][j] - s;
                } else {
                    double q = 0;
                    for(std::size_t k = 0; k < j; ++k){
                        q += l[i][k] * u[k][j];
                    }
                    if(std::abs(u[j][j]) < theta){throw std::runtime_error("main element is zero");}
                    l[i][j] = (matrix_[i][j] - q) / (u[j][j]);
                }
            }
        }
        double det = 1;
        for(std::size_t i = 0; i < n_; ++i){
            det *= u[i][i];
        }
        return det;
    }
    matrix inverse() const {
        if(m_ != n_){throw std::runtime_error("matrix is not square");}
        if(zero() || std::abs(det()) < theta){throw std::runtime_error("matrix is singular");}
        std::vector<std::vector<double>> inv(n_, std::vector<double>(n_, 0));
        std::vector<std::vector<double>> u = matrix_;
        for(std::size_t i = 0; i < n_; ++i){
            inv[i][i] = 1;
        }
        for(std::size_t j = 0; j < n_; ++j){
            double m = u[j][j];
            if(std::abs(m) < theta){
                bool f = false;
                for(std::size_t i = j + 1; i < n_; ++i){
                    if(std::abs(u[i][j]) > theta){
                        std::swap(u[j], u[i]);
                        std::swap(inv[j], inv[i]);
                        f = true;
                        break;
                    }
                }
                if(!f){throw std::runtime_error("matrix is singular!");}
                m = u[j][j];
            }
            for(std::size_t l = 0; l < n_; ++l){
                u[j][l] /= m;
                inv[j][l] /= m;
            }
            for(std::size_t p = 0; p < n_; ++p){
                if(p != j && std::abs(u[p][j]) > theta){
                    double h = u[p][j];
                    for(std::size_t q = 0; q < n_ ; ++q){
                        u[p][q] -= u[j][q] * h;
                        inv[p][q] -= inv[j][q] * h;
                    }
                }
            }
        }
        return {inv};
    }
    double tr() const {
        if(n_ != m_){throw std::runtime_error("matrix isn't square");}
        double sum = 0;
        for(std::size_t i = 0; i < n_; ++i){
            sum += matrix_[i][i];
        }
        return sum;
    }
    double frobenius() const {
        std::vector<std::vector<double>> trs(n_, std::vector<double>(m_, 0));
        for(std::size_t i = 0; i < m_; ++i){
            for(std::size_t j = 0; j < n_; ++j){
                trs[j][i] = matrix_[i][j];
            }
        }
        matrix aa = matrix(trs) * matrix(matrix_);
        double s = 0;
        for(std::size_t i = 0; i < m_; ++i){
            s += aa.matrix_[i][i];
        }
        return std::sqrt(s);
    }
};
matrix unit(std::size_t n){
    std::vector<std::vector<double>> unit(n, std::vector<double>(n, 0));
    for(std::size_t i = 0; i < n; ++i){
        unit[i][i] = 1;
    }
    return matrix(unit);
}
std::ostream& operator<<(std::ostream& os, const matrix& f){
    for(std::size_t i = 0; i < f.rows(); ++i){
        for(std::size_t j = 0; j < f.columns(); ++j){
            os << f.data()[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
};
