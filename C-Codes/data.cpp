template<typename T>
T max(T a, T b){
    static_assert(std::is_arithmetic_v<T>, "T must be arifmetic");
    return (a >= b) ? a : b;
}
int main(){
    matrix A = unit(3), B = unit(5);
    std::cout << max(A, B);
}
