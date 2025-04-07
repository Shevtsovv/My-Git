#include <iostream>
#include <string>
#include <vector>
using namespace std;

class student{
    public:
    int age;
    string name;
    int* greats;
    student(int age, string name): age(age), name(name){
        cout << "default" << endl;
        greats = new int[2];
        greats[0] = 0;
        greats[1] = 0;
    }
    student(const student& s){
        cout << "copy constructor" << endl;
        age = s.age;
        name = s.name;
        greats = new int[2];
        greats[0] = s.greats[0];
        greats[1] = s.greats[1];
    }
    student (student&& s) noexcept:  age(0), name(), greats(nullptr) {
        cout << "move constructor" << endl;
        swap(age, s.age);
        swap(name, s.name);
        swap(greats, s.greats);
    }
    student& operator=(const student& s) {
        cout << "copy operator" << endl;
        if (this != &s) {
            delete[] greats; //очищаем старое и добавляем новое
            age = s.age;
            name = s.name;
            greats = new int[2];
            greats[0] = s.greats[0];
            greats[1] = s.greats[1];
        }
        return *this;
    }
    student& operator=(student&& s) noexcept {
        cout << "move operator" << endl;
        if (this != &s) {
            delete[] greats;
            age = 0;
            name.clear();
            greats = nullptr;
            swap(age, s.age);
            swap(name, s.name);
            swap(greats, s.greats);
        }
        return *this;
    }
    ~student(){
        cout << "destructor" << endl;
        delete[] greats;
    }
};

//Демонтрация rvalue, lvalue
int get(){
    return 47;
}
void foo(int& x){ //ссылка на lvalue reference
    x = 47;
}
void foo1(int&& x){ //ссылка на rvalue reference
    x = 47;
}

int main(){
    //int j = get();//косяк с lvalue
    //j + 1 = 89;
    //int j = get();
    //foo(4);
    //foo1(move(j));
    //cout << j << endl;
    //student Misha(move(Vasya));
    //cout << Vasya.greats[0] << endl;
    student Vasya(13, "vasya");
    student Petya(Vasya); // копирование
    student Borya(23, "sdsd");
    Borya = Vasya; // копирующее присваивание
    student Misha(move(Vasya)); // перемещение

    // Опасное обращение к перемещённому объекту!
    // Vasya.greats теперь nullptr после перемещения
    if (Vasya.greats) { // Проверка на nullptr
        cout << Vasya.greats[0] << endl;
    } else {
        cout << "Vasya.greats is nullptr (was moved)" << endl;
    }

    return 0;
}
