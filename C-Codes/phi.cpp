#include <SFML/Graphics.hpp>
#include <vector>
#include <stdexcept>
#include <cmath>
class Color{
    std::vector<uint8_t> color_;
    sf::Color c_;
public:
    Color(const std::vector<u_int8_t>& color) : color_(color), c_(color[0], color[1], color[2]){}
    const std::vector<u_int8_t>& data() const {return color_;}
    const sf::Color& sfc() const {return c_;}
};
class Heatmap{
    sf::Image im_;
    const Color pixel_color(const double& value) const {
        if(value < 0.5){
            u_int8_t u = (value * 2) * 255;
            return Color({0, u, 255});
        } else{
            u_int8_t v = (value - 0.5) * 2 * 255;
            return Color({v, 255, 0});
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
        im_.create(data[0].size(), data.size());
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
    std::vector<std::vector<double>> electricPotential(1200, std::vector<double>(1500));
    for(std::size_t i = 0; i < 1200; i++){
        for(std::size_t j = 0; j < 1500; j++)
        electricPotential[i][j] = sqrt(i*i + j*j);
    }
    Heatmap map(electricPotential, "heat.png");
}