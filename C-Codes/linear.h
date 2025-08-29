#pragma once
#include <iostream>
#include <vector>
template <typename T>
concept alg = std::is_floating_point_v<T> || std::is_integral_v<T>;
template <alg T> class matrix{
    std::vector<std::vector<T>> matrix_;
    std::size_t m_;
    std::size_t n_;
public:
    matrix(const std::vector<std::vector<T>>& matrix) : matrix_(matrix){
        if(matrix_.empty() || matrix_[0].empty()){
            throw std::invalid_argument("error 0");
        }
        m_ = matrix_.size();
        n_ = matrix_[0].size();
        for(const std::vector<T>& str : matrix_){
            if(str.size() != n_){
                throw std::invalid_argument("error 1");
            }
        }
    }
    matrix(const matrix&) = default;
    matrix(matrix&&) = default;
    matrix& operator=(const matrix&) = default;
    matrix& operator=(matrix&&) = default;
    const std::vector<std::vector<T>>& data() const {
        return matrix_;
    }
    const std::size_t& str() const {return m_;}
    const std::size_t& cols() const {return n_;}
    static matrix Vandermonde(const std::vector<T>& data, std::size_t vsize){
        std::vector<std::vector<T>> van(data.size(), std::vector<T>(vsize, 0));
        for(std::size_t i = 0; i < data.size(); ++i){
            T xx = 1;
            for(std::size_t j = 0; j < vsize; ++j){
                van[i][j] = xx;
                xx *= data[i];
            }
        }
        return van;
    }
    T& operator()(std::size_t index1, std::size_t index2){
        return matrix_[index1][index2];
    }
    const T operator()(std::size_t index1, std::size_t index2) const {
        return matrix_[index1][index2];
    }
};
template <alg T> matrix<T> operator+(const matrix<T>& mtx1, const matrix<T>& mtx2){
    if(mtx1.str() != mtx2.str() || mtx1.cols() != mtx2.cols()){
        throw std::invalid_argument("error 2");
    }
    std::vector<std::vector<T>> res = mtx1.data();
    for(std::size_t i = 0; i < mtx1.str(); ++i){
        for(std::size_t j = 0; j < mtx1.cols(); ++j){
            res[i][j] += mtx2.data()[i][j];
        }
    }
    return res;
};
template <alg T> matrix<T> operator-(const matrix<T>& mtx1, const matrix<T>& mtx2){
    if(mtx1.str() != mtx2.str() || mtx1.cols() != mtx2.cols()){
        throw std::invalid_argument("error 3");
    }
    std::vector<std::vector<T>> res = mtx1.data();
    for(std::size_t i = 0; i < mtx1.str(); ++i){
        for(std::size_t j = 0; j < mtx1.cols(); ++j){
            res[i][j] -= mtx2.data()[i][j];
        }
    }
    return res;
};
template <alg T> matrix<T> operator*(const matrix<T>& mtx1, const matrix<T>& mtx2){
    if(mtx1.cols() != mtx2.str()){
        throw std::invalid_argument("error 4");
    }
    std::vector<std::vector<T>> res(mtx1.str(), std::vector<T>(mtx2.cols(), 0));
    for(std::size_t i = 0; i < mtx1.str(); ++i){
        for(std::size_t j = 0; j < mtx2.cols(); ++j){
            T current = 0;
            for(std::size_t k = 0; k < mtx1.cols(); ++k){
                current += mtx1.data()[i][k] * mtx2.data()[k][j];
            }
            res[i][j] = current;
        }
    }
    return res;
}
template <alg T> matrix<T> operator*(const matrix<T>& mtx, const T& lambda){
    std::vector<std::vector<T>> res = mtx.data();
    for(std::size_t i = 0; i < mtx.str(); ++i){
        std::vector<T>& str = res[i];
        for(std::size_t j = 0; j < mtx.cols(); ++j){
            str[j] *= lambda;
        }
    }
    return res;
}
template <alg T> bool operator==(const matrix<T>& mtx1, const matrix<T>& mtx2){
    return (mtx1.data() == mtx2.data());
}
template <alg T> std::ostream& operator<<(std::ostream& os, const matrix<T>& mtx){
    const std::string whitespace = " ";
    for(std::size_t i = 0; i < mtx.str(); ++i){
        for(std::size_t j = 0; j < mtx.cols(); ++j){
            os << mtx.data()[i][j] << whitespace;
        }
        os << std::endl;
    }
    return os;
}
template <alg T> matrix<T> inverse(const matrix<T>& mtx){
    if(mtx.cols() != mtx.str()){
        throw std::invalid_argument("error 5");
    }
    std::size_t size = mtx.cols();
    std::vector<std::vector<T>> inv(size, std::vector<T>(size, 0));
    std::vector<std::vector<T>> data = mtx.data();
    for(std::size_t l = 0; l < size; ++l){
        inv[l][l] = 1;
    }
    for(std::size_t j = 0; j < size; ++j){
        T diag_elmnt = data[j][j];
        if(diag_elmnt == 0){
            bool is_singular_col = false;
            for(std::size_t i = j + 1; i < size; ++i){
                if(data[i][j] != 0){
                    std::swap(data[j], data[i]);
                    std::swap(inv[j], inv[i]);
                    is_singular_col = true;
                    break;
                }
            }
            if(!is_singular_col){throw std::invalid_argument("error 6");}
            diag_elmnt = data[j][j];
        }
        for(std::size_t k = 0; k < size; ++k){
            data[j][k] = data[j][k] / diag_elmnt;
            inv[j][k] = inv[j][k] / diag_elmnt;
        }
        for(std::size_t u = 0; u < size; ++u){
            if(u != j && data[u][j] != 0){
                T dmtx = data[u][j];
                for(std::size_t v = 0; v < size; ++v){
                    data[u][v] = data[u][v] - dmtx * data[j][u];
                    inv[u][v] = inv[u][v] - dmtx * inv[j][u];
                }
            }
        }
    }
    return inv;
}
template <alg T> matrix<T> transpose(const matrix<T>& mtx){
    std::vector<std::vector<T>> res(mtx.cols(), std::vector<T>(mtx.str(), 0));
    for(std::size_t i = 0; i < mtx.str(); ++i){
        for(std::size_t j = 0; j < mtx.cols(); ++j){
            res[j][i] = mtx.data()[i][j];
        }
    }
    return res;
}
template <alg T> std::pair<matrix<T>, matrix<T>> polyfit(const std::vector<T>& data1, const std::vector<T>& data2, std::size_t degree){
    if(data1.size() != data2.size() || data1.empty() || data2.empty()){
        throw std::invalid_argument("error 7");
    }
    matrix<T> V = matrix<T>::Vandermonde(data1, degree + 1);
    std::vector<std::vector<T>> y;
    for(const auto& item : data2){
        y.push_back({item});
    }
    matrix Y_REAL(y);
    matrix<T> A = transpose(V) * V;
    matrix<T> c = inverse(A) * transpose(V) * Y_REAL;
    matrix<T> Y_APPROBABLY = V * c;
    T varepsilon = 0;
    for(std::size_t i = 0; i < data2.size(); ++i){
        T eps_i = Y_REAL(i, 0) - Y_APPROBABLY(i, 0);
        varepsilon += eps_i * eps_i;
    }
    if(data1.size() <= degree + 1){
        throw std::invalid_argument("error 8");
    }
    T sigma = varepsilon / (data1.size() - degree - 1);
    matrix<T> Cov = inverse(A) * sigma;
    return {c, Cov};
}