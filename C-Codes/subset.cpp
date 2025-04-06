#pragma once
#include <iostream>
struct subset_node{
    //Ключ, значение, которое будет в дереве
    double key;
    //Указатель на правое поддерево
    subset_node* right;
    //Указатель на левое поддерево
    subset_node* left;
};
class subset{
    public:
    //Инициализация пустого дерева
    bool subset_init(subset_node** sn){
        *sn = nullptr;
        return true;
    }
    //Вставка ключа в любое место дерева, если в дереве уже есть элемент, который необходимо вставить, функция выдаст ошибку
    bool subset_insert(subset_node** sn, double k){
        if(*sn == nullptr){
            subset_node* tmp = new subset_node();
            tmp -> key = k;
            tmp -> left = tmp -> right = nullptr;
            *sn = tmp;
            return true;
        }
        if((*sn) -> key == k){
            return false;
        }
        return(k > (*sn) -> key)
            ? subset_insert(&(*sn) -> right, k)
            : subset_insert(&(*sn) -> left, k);
        
        return true;
    }
    //Рекурсивный поиск ключа в любом месте дерева, если оно пустое, функция возвращает нулевой указатель
    subset_node* subset_find(subset_node* sn, double k){
        if(sn == nullptr){
            return nullptr;
        }
        if(sn -> key == k){
            return sn;
        }
        if(k > sn -> key){
            return subset_find(sn -> right, k);
        } else{
            return subset_find(sn -> left, k);
        }
    }
    //Определение размера дерева, если оно пустое,возвращаемое значение равно нулю
    unsigned int subset_size(subset_node* sn){
        if(sn == nullptr){
            return 0;
        } else{
            return subset_size((sn) -> left) + subset_size((sn) -> right) + 1;
        }
    }
    //Определение высоты дерева, если оно пустое, то возвращаемое значение равно нулю
    unsigned int subset_height(subset_node* sn){
        if(sn == nullptr){
            return 0;
        }
        int h_left = subset_height((sn) -> left);
        int h_right = subset_height((sn) -> right);
        return std::max(h_left, h_right) + 1;
    }
    //Очищение дерева, если оно пустое, функция ничего не возвращает
    void subset_clear(subset_node* sn){
        if(sn == nullptr){
            return;
        }
        subset_clear((sn) -> left);
        subset_clear((sn) -> right);
        delete sn;
    }
    //Удаление элемента из дерева, если оно пустое, функция вернет ноль
    bool subset_remove(subset_node** sn, double k){
        if(*sn == nullptr){
            return false;
        }
        if(k < (*sn) -> key){
            return subset_remove(&(*sn) -> left, k);
        } else if(k > (*sn) -> key){
            return subset_remove(&(*sn) -> right, k);
        } else{
            subset_node* sn_delete = *sn;
            if(!(*sn) -> left){
                *sn = (*sn) -> right;
                delete sn_delete;
            } else if(!(*sn) -> right){
                *sn = (*sn) -> left;
                delete sn_delete;
            } else{
                subset_node** sn_min_node = &(*sn) -> right;
                while((*sn_min_node) -> left){
                    sn_min_node = &(*sn_min_node) -> left; 
                }
                (*sn) -> key = (*sn_min_node) -> key;
                subset_node* tmp = *sn_min_node;
                *sn_min_node = (*sn_min_node) -> right;
                delete tmp;
            }
            return true;
        }
    }
};
