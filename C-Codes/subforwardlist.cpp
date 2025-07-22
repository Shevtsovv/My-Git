#include <iostream>
template <typename T>
struct node{
    node<T>* next_;
    node<T>* prev_;
    T data_;
    node(const T& _data) : next_(nullptr), prev_(nullptr), data_(_data){}
};
template <typename T>
class list{
    node<T>* head_;
    node<T>* tail_;
    std::size_t size_;
public:
    list() : head_(nullptr), tail_(nullptr), size_(0){}
    ~list(){
        while(head_){
            node<T>* current_ = head_;
            head_ = head_->next_;
            delete current_;
        }
    }
    list(const list& _o) : head_(nullptr), tail_(nullptr), size_(_o.size_){
        node<T>* node = _o.head_;
        while(node){
            push_back(node->data_);
            node = node->next_;
        }
    }
    list(list&& _o) noexcept : head_(_o.head_), tail_(_o.tail_), size_(_o.size_){
        _o.head_ = _o.tail_ = nullptr;
        _o.size_ = 0;
    }
    list& operator=(const list& _o){
        if(this != &_o){
            while (head_) {
                node<T>* current_ = head_;
                head_ = head_->next_;
                delete current_;
            }
            tail_ = nullptr;
            size_ = 0;
            node<T>* node = _o.head_;
            while(node){
                push_back(node->data_);
                node = node->next_;
            }
            size_ = _o.size_;
        }
        return *this;
    }
    list& operator=(list&& _o) noexcept {
        if(this != &_o){
            while(head_){
                node<T>* current_ = head_;
                head_ = head_->next_;
                delete current_;
            }
            head_ = _o.head_;
            tail_ = _o.tail_;
            size_ = _o.size_;
            _o.head_ = _o.tail_ = nullptr;
            _o.size_ = 0;
        }
        return *this;
    }
    node<T>* begin(){return head_;}
    node<T>* end() {return nullptr;}
    const node<T>* begin() const {return head_;}
    const node<T>* end() const {return nullptr;}
    void push_back(const T& _a){
        node<T>* sqr = new node<T>(_a);
        if(!tail_){
            head_ = tail_ = sqr;
        } else{
            tail_->next_ = sqr;
            sqr->prev_ = tail_;
            tail_ = sqr;
        }
        size_++;
    }
    void push_front(const T& _a){
        node<T>* current_ = new node<T>(_a);
        if(!head_){
            head_ = tail_ = current_;
        } else{
            head_->prev_ = current_;
            current_->next_ = head_;
            head_ = current_;
        }
        size_++;
    }
    void pop_back(){
        if(!tail_) {throw std::runtime_error("list is empty!");}
        node<T>* current_ = tail_;
        tail_ = tail_->prev_;
        if(tail_){
            tail_->next_ = nullptr;
        } else {
            head_ = nullptr;
        }
        delete current_;
        size_--;
    }
    void pop_front(){
        if(!head_){throw std::runtime_error("list is empty");}
        node<T>* current_ = head_;
        head_ = head_->next_;
        if(head_){
            head_->prev_ = nullptr;
        } else{
            tail_ = nullptr;
        }
        delete current_;
        size_--;
    }
    node<T>* at(std::size_t _index){
        if(_index >= size_){throw std::invalid_argument("index is out of range");}
        node<T>* current_ = head_;
        for(std::size_t i = 0; i < _index; ++i){
            current_ = current_->next_;
        }
        return current_;
    }
    T& operator[](std::size_t _index){
        if(_index > size_){throw std::invalid_argument("index is out of range");}
        node<T>* current = head_;
        for(std::size_t i = 0; i < _index; ++i){
            current = current->next_;
        }
        return current->data_;
    }
    T operator[](std::size_t _index) const {
        if(_index > size_){throw std::invalid_argument("index is out of range");}
        const node<T>* current = head_;
        for(std::size_t i = 0; i < _index; ++i){
            current = current->next_;
        }
        return current->data_;
    }
    const std::size_t size() const {return size_;}
    void insert(std::size_t _index, const T& _a){
        if(_index > size_){throw std::invalid_argument("index is out of range");}
        if(_index == size_) {
            push_back(_a);
            return;
        }
        if(_index == 0) {
            push_front(_a);
            return;
        }
        node<T>* right = at(_index);
        node<T>* left = right->prev_;
        node<T>* current = new node<T>(_a);
        current->prev_ = left;
        current->next_ = right;
        left->next_ = current;
        right->prev_ = current;
        size_++;
    }
    void erase(std::size_t _index){
        if(size_ == 0){throw std::runtime_error("list is empty!");}
        if(_index == size_){
            pop_back();
            return;
        }
        if(_index == 0){
            pop_front();
            return;
        }
        node<T>* current = at(_index);
        node<T>* right = current->next_;
        node<T>* left = current->prev_;
        left->next_ = right;
        right->prev_ = left;
        delete current;
        size_--;
    }
};
template <typename T>
std::ostream& operator<<(std::ostream& _os, const list<T>& _data){
    const node<T>* scr = _data.begin();
    while(scr != _data.end()){
        _os << scr->data_ << " ";
        scr = scr->next_;
    }
    return _os;
}
int main(){
    double f = 9;
    list<double> h;
    h.insert(0, 8.9);
    std::cout << h;
}