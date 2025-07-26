#include <iostream>
#include <fstream>
#include <vector>
int main() {
    std::ifstream file("data.txt");
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    std::vector<double> x_values, y_values;
    double x, y;
    while (file >> x >> y) {
        x_values.push_back(x);
        y_values.push_back(y);
    }
    std::cout << "X\tY" << std::endl;
    for (size_t i = 0; i < x_values.size(); ++i) {
        std::cout << x_values[i] << "\t" << y_values[i] << std::endl;
    }

    return 0;
}