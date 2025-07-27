#pragma once
#include <iostream>
#include <stack>
template<typename T>
struct node{
    T key_;
    node<T>* right_;
    node<T>* left_;
    node(const T& _data) : key_(_data), right_(nullptr), left_(nullptr){}
};
template <typename T>
class iterator{
    node<T>* c_;
    std::stack<node<T>*> stack_;
public:
    iterator(node<T>* _root) : c_(_root){
        while(!c_){
            stack_.push(c_);
            c_ = c_->left_;
        }
        if(!stack_.empty()){
            c_ = stack_.top();
            stack_.pop();
        }
    }
    T& operator*() { return c_->key_; }
    iterator& operator++() {
        c_ = c_->right_;
        while (c_ != nullptr) {
            stack.push(c_);
            c_ = c_->left_;
        }
        if (!stack.empty()) {
            c_ = stack.top();
            stack.pop();
        } else {
            c_ = nullptr;
        }
        return *this;
    }
    bool operator!=(const iterator& _o) const {
        return c_ != _o.c_;
    }
};
template <typename T>
class subset{
    node<T>* sn_;
public:
    subset() : sn_(nullptr){}
    ~subset(){
        clear(sn_);
    }
    subset(const subset& _o) : sn_(nullptr){
        if(_o.sn_){
            auto sn = [&](const node<T>* _node)->node<T>*{
                if(!_node){return nullptr;}
                node<T>* current_ = new node<T>(_node->key_);
                current_->left_ = sn(_node->left_);
                current_->right_ = sn(_node->right_);
                return current_;
            };
            sn_ = sn(_o.sn_);
        }
    }
    subset(subset&& _o) noexcept : sn_(_o.sn_) {
        _o.sn_ = nullptr;
    }
    subset& operator=(const subset& _o){
        if(this != &_o){
            clear(sn_);
            if(_o.sn_){
                auto sn = [&](const node<T>* _node)->node<T>*{
                    if(!_node){return nullptr;}
                    node<T>* current_ = new node<T>(_node->key_);
                    current_->left_ = sn(_node->left_);
                    current_->right_ = sn(_node->right_);
                    return current_;
                };
                sn_ = sn(_o.sn);
            }
        }
        return *this;
    }
    subset& operator=(subset&& _o) noexcept {
        if(this != &_o){
            clear(sn_);
            sn_ = _o.sn_;
            _o.sn_ = nullptr;
        }
        return *this;
    }
    void clear(node<T>* _sn){
        if(!_sn){
            return;
        }
        clear(_sn->left_);
        clear(_sn->right_);
        delete _sn;
    }
    bool insert(node<T>* _node, const T& _a){
        if(!_node){
            node<T>* current = new node<T>(_a);
            current->left_ = current->right_ = nullptr;
            _node = current;
            return true;
        }
        if(_node->key_ == _a){return false;}
        return(_node->key_ > _a) ? insert(_node->left_, _a) : insert(_node->right_, _a);
    }
    node<T>* find(node<T>* _node, const T& _a){
        if(!_node){
            return nullptr;
        }
        if(_node->key_ == _a){
            return _node;
        }
        if(_node->key_ > _a){
            return find(_node->left_, _a);
        } else {return find(_node->right_, _a);}
    }
    std::size_t size(node<T>* _node){
        std::size_t root = 1;
        if(!_node){return 0;}
        return size(_node->left_) + size(_node->right_) + root;
    }
    std::size_t height(node<T>* _node){
        if(!_node){return 0;}
        std::size_t h_r = height(_node->right_);
        std::size_t h_l = height(_node->left_);
        return (h_l > h_r) ? h_l : h_r;
    }
    bool remove(node<T>*& _node, const T& _a){
        if (!_node) {
            return false;
        }

        if (_a < _node->key_) {
            return remove(_node->left_, _a);
        } 
        else if (_a > _node->key_) {
            return remove(_node->right_, _a);
        } 
        else {
            if (!_node->left_) {
                node<T>* temp = _node;
                _node = _node->right_;
                delete temp;
            } 
            else if (!_node->right_) {
                node<T>* temp = _node;
                _node = _node->left_;
                delete temp;
            } 
            else {  // Есть оба поддерева → ищем минимальный в правом поддереве
                node<T>* minRight = _node->right_;
                while (minRight->left_) {
                    minRight = minRight->left_;
                }
                _node->key_ = minRight->key_;  // Копируем значение
                remove(_node->right_, minRight->key_);  // Рекурсивно удаляем дубликат
            }
            return true;
        }
    }
    iterator<T> begin(){
        return iterator<T>(sn_);
    }
    iterator<T> end(){
        return iterator<T>(nullptr);
    }
};