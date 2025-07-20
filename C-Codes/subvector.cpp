#include <iostream>
#include <string>
template <typename T>
class subvector{
    T* qv_;
    std::size_t top_;
    std::size_t capacity_;
public:
    subvector() : qv_(nullptr), top_(0), capacity_(0){}
    ~subvector(){
        delete[] qv_;
    }
    subvector(std::size_t _size, T& a) : qv_(nullptr), top_(_size), capacity_(_size){
        qv_ = new T[capacity_];
        for(std::size_t l = 0; l < top_; ++l){
            qv_[l] = a;
        }
    }
    subvector(const std::initializer_list<T> _list) : qv_(nullptr), top_(_list.size()), capacity_(_list.size()){
        qv_ = new T[capacity_];
        std::copy(_list.begin(), _list.end(), qv_);
    }
    subvector(const subvector& _o) : qv_(nullptr), top_(_o.top_), capacity_(_o.capacity_){
        qv_ = new T[capacity_];
        for(std::size_t l = 0; l < top_; ++l){
            qv_[l] = _o.qv_[l];
        }
    }
    subvector(subvector&& _o) noexcept : qv_(_o.qv_), top_(_o.top_), capacity_(_o.capacity_) {
        _o.qv_ = nullptr;
        _o.top_ = 0, _o.capacity_ = 0;
    }
    subvector& operator=(const subvector& _o) {
    if (this != &_o) {
        T* new_data = new T[_o.capacity_];
        for (std::size_t l = 0; l < _o.top_; ++l) {
            new_data[l] = _o.qv_[l];
        }
        delete[] qv_;
        qv_ = new_data;
        top_ = _o.top_;
        capacity_ = _o.capacity_;
    }
    return *this;
}
    subvector& operator=(subvector&& _o) noexcept {
        if(this != &_o){
            qv_ = _o.qv_;
            top_ = _o.top_, capacity_ = _o.capacity_;
            _o.top_ = 0, _o.capacity_ = 0;
        }
        return *this;
    }
    T operator[](std::size_t _index) const {
        if(_index > top_){throw std::invalid_argument("is out of range");}
        return qv_[_index];
    }
    T& operator[](std::size_t _index){
        if(_index > top_) {throw std::invalid_argument("is out of range");}
        return qv_[_index];
    }
    T* begin() {return qv_;}
    const T* begin() const {return qv_;}
    T* end() {return qv_ + top_;}
    const T* end() const {return qv_ + top_;}
    void push_back(T& _a){
        if(top_ >= capacity_){
            std::size_t __capacity = (capacity_ == 0) ? 1 : 2 * capacity_;
            T* res = new T[__capacity];
            for(std::size_t l = 0; l < top_; ++l){
                res[l] = qv_[l];
            }
            delete[] qv_;
            qv_ = res;
            capacity_ = __capacity;
        }
        qv_[top_++] = _a;
    }
    bool empty() const {
        return (top_ == 0);
    }
    bool operator==(const subvector& _o) const {
        static_assert(std::is_same_v<decltype(std::declval<T>() == std::declval<T>()), bool>, "Type T must support operator==");
        if(empty() && _o.empty()){
            return true;
        }
        if(top_ != _o.top_){
            return false;
        }
        for(std::size_t i = 0; i < top_; ++i){
            if(qv_[i] != _o.qv_[i]){return false;}
        }
        return true;
    }
    void pop_back(){
        if(top_ == 0){
            throw std::invalid_argument("vector is empty");
        }
        top_--;
    }
    void shrink_to_fit(){
        if(top_ == 0){
            delete[] qv_;
            qv_ = nullptr;
            capacity_ = 0;
        } else{
            T* res = new T[top_];
            for(std::size_t l = 0; l < top_; ++l){
                res[l] = qv_[l];
            }
            delete[] qv_;
            qv_ = res;
            capacity_ = top_;
        }
    }
    void erase(std::size_t _pos){
        if(_pos > top_){throw std::invalid_argument("index is out of range");}
        for(std::size_t i = _pos; i < top_; ++i){
            qv_[i] = qv_[i + 1];
        }
        top_--;
    }
    void clear(){
        delete[] qv_;
        qv_= nullptr;
        top_ = 0, capacity_ = 0;
    }
    void resize(std::size_t _other_size) {
        if (_other_size == top_) {return;}
        if (_other_size == 0) {clear();}
        T* res = new T[_other_size];
        std::size_t copy_size = std::min(top_, _other_size);
        for (std::size_t l = 0; l < copy_size; ++l) {
            res[l] = qv_[l];
        }
        if (_other_size > copy_size) {
            for (std::size_t l = copy_size; l < _other_size; ++l) {
                res[l] = T();
            }
        }
        delete[] qv_;
        qv_ = res;
        top_ = _other_size;
        capacity_ = _other_size;
    }
    void insert(std::size_t _pos, std::size_t _n, T& _a){
        if(_pos > top_){throw std::invalid_argument("index is out of range");}
        if(_n == 0){return;}
        std::size_t size = top_ + _n, capacity = std::max(size, 2 * capacity_);
        T* res = new T[capacity];
        for(std::size_t i = 0; i < _pos; ++i){
            res[i] = qv_[i];
        }
        for (std::size_t i = 0; i < _n; ++i) {
            res[_pos + i] = _a;
        }
        for(std::size_t l = _pos; l < top_; ++l){
            res[l + _n] = qv_[l];
        }
        delete[] qv_;
        qv_ = res;
        top_ = size, capacity_ = capacity;
    }
    void push_front(T& _a){
        if(top_ >= capacity_){
            std::size_t capacity = (capacity_ == 0) ? 1 : 2 * capacity_;
            T* res = new T[capacity];
            res[0] = _a;
            for(std::size_t l = 0; l < top_; ++l){
                res[l + 1] = qv_[l];
            }
            delete[] qv_;
            qv_ = res;
            capacity_ = capacity;
        }
        top_++;
    }
    void pop_front(){
        if(top_ == 0){
            throw std::invalid_argument("vector is empty");
        }
        for(std::size_t l = 0; l < top_ - 1; ++l){
            qv_[l] = qv_[l + 1];
        }
        top_--;
    }
};
template <typename T>
std::ostream& operator<<(std::ostream& _os, const subvector<T>& _data){
    for(const T& item : _data){
        _os << item << " ";
    }
    return _os;
}