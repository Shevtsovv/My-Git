#include <iostream>
using namespace std;
int main()
{
    bool init(subvector * qv) 
    {
        qv->mas = NULL;
        qv->top = 0;
        qv->capacity = 0;
        return true;
    }
    int pop_back(subvector * qv)
    {
        if (qv->top == 0)
        {
            return 0;
        }
        else
        {
            qv->top--;
            return qv->mas[qv->top];
        }
    }
    bool resize(subvector * qv, unsigned int new_capacity)
        if (qv->capacity < new_capacity)
        {
            if (qv->capacity == 0)
            {
                delete[] qv->mas;
                qv->mas = new int[new_capacity];
            }
            else
            {
                int* mas_copy = new int[new_capacity];
                for (unsigned int i = 0; i < qv->top; i++)
                {
                    mas_copy[i] = qv->mas[i];
                }
                delete[] qv->mas;
                qv->mas = mas_copy;
            }
        }
        else
        {
            if (new_capacity == 0)
            {
                delete[] qv->mas;
                init(qv);
            }
            else
            {
                int* mas_copy = new int[new_capacity];
                for (unsigned int i = 0; i < qv->top; i++)
                {
                    mas_copy[i] = qv->mas[i];
                }
                delete[] qv->mas;
                qv->mas = mas_copy;
            }
        }
        qv->capacity = new_capacity;
        return true;
    
    bool push_back(subvector * qv, int d) 
    {
        if (qv->top + 1 > qv->capacity)
        {
            resize(qv, qv->top * 2 + 1);
        }
        qv->mas[qv->top] = d;
        qv->top += 1;
        return true;
    }
    void shrink_to_fit(subvector * qv)
    {
        int* mas_copy = new int[qv->top];
        for (unsigned int i = 0; i < qv->top; i++)
        {
            mas_copy[i] = qv->mas[i];
        }
        delete[] qv->mas;
        qv->mas = mas_copy;
        qv->capacity = qv->top;
    }
    void clear(subvector * qv) 
    {
        for (unsigned int i = 0; i < qv->top; i++)
        {
            qv->mas[i] = 0;
        }
        qv->top = 0;
    }
    void destructor(subvector * qv)	
    {
        delete[] qv->mas;
        init(qv);
    }
}
