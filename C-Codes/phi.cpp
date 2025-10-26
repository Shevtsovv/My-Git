#include <SFML/Graphics.hpp>
#include <vector>
#include <stdexcept>
#include <cmath>
class Color{
    std::vector<unsigned int> color_;
    sf::Color c_;
public:
    Color(const std::vector<unsigned int>& color) : color_(color), c_(color[0], color[1], color[2]){}
    const std::vector<unsigned int>& data() const {return color_;}
    const sf::Color& sfc() const {return c_;}
};
class Heatmap{
    sf::Image im_;
    Color pixel_color(double value) const {
        const unsigned int mult = 5 * 255;
        if (value < 0.2){
            unsigned int g = static_cast<unsigned int>(value * mult);
            return Color({0, g, 255});
        }
        else if (value < 0.4) {
            unsigned int b = static_cast<unsigned int>((0.4 - value) * mult);
            return Color({0, 255, b});
        }
        else if (value < 0.6) {
            unsigned int r = static_cast<unsigned int>((value - 0.4) * mult);
            return Color({r, 255, 0});
        }
        else if (value < 0.8) {
            unsigned int g = static_cast<unsigned int>((0.8 - value) * mult);
            return Color({255, g, 0});
        }
        else {
            unsigned int b = static_cast<unsigned int>((value - 0.8) * mult);
            return Color({255, 0, b});
        }
    }
public:
    Heatmap(const std::vector<std::vector<double>>& data, const std::string& filename){
        for(std::size_t i = 1; i < data.size(); ++i){
            if(data[i - 1].size() != data[i].size()){
                throw std::invalid_argument("incorrect values!");
            }
        }
        std::size_t index = 0;
        im_.create(data[index].size(), data.size());
        double min = 0, max = 0;
        for(const auto& row : data){
            for(const auto& crd : row){
                if(crd < min) {min = crd;}
                if(crd > max){max = crd;}
            }
        }
        for(std::size_t y = 0; y < data.size(); ++y){
            for(std::size_t x = 0; x < data[y].size(); ++x){
                double normalize = (data[y][x] - min)/(max - min);
                Color pxl_crd_clr = pixel_color(normalize);
                im_.setPixel(x, y, pxl_crd_clr.sfc());
            }
        }
        im_.saveToFile(filename);
    }
};
int main(){
    std::size_t M = 900, N = 900;
    std::vector<std::vector<double>> electricPotential(M, std::vector<double>(M));
    for(std::size_t i = 0; i < M; i++){
        for(std::size_t j = 0; j < M; j++)
        electricPotential[i][j] = (i * j);
    }
    Heatmap map(electricPotential, "heat.png");
}
