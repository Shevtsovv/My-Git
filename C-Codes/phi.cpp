#include <SFML/Graphics.hpp>
#include <vector>
#include <stdexcept>
#include <cmath>
class Color
{
    std::vector<unsigned int> color_;
    sf::Color c_;
public:
    Color(const std::vector<unsigned int>& color) : color_(color), c_(color[0], color[1], color[2]){}
    const std::vector<unsigned int>& data() const {return color_;}
    const sf::Color& sfc() const {return c_;}
};
class Heatmap
{
    sf::VertexArray vertice_;
    Color pixel_color_scheme(double value) const
    {
        const unsigned int mult = 5 * 255;
        if (value < 0.2)
        {
            unsigned int g = static_cast<unsigned int>(value * mult);
            return Color({0, g, 255});
        }
        else if (value < 0.4)
        {
            unsigned int b = static_cast<unsigned int>((0.4 - value) * mult);
            return Color({0, 255, b});
        } else if (value < 0.6)
        {
            unsigned int r = static_cast<unsigned int>((value - 0.4) * mult);
            return Color({r, 255, 0});
        }
        else if (value < 0.8)
        {
            unsigned int g = static_cast<unsigned int>((0.8 - value) * mult);
            return Color({255, g, 0});
        }
        else
        {
            unsigned int b = static_cast<unsigned int>((value - 0.8) * mult);
            return Color({255, 0, b});
        }
    }
public:
    std::size_t M_ = 500;
    std::size_t N_ = 500;
    Heatmap(const std::vector<std::vector<double>>& data) : vertice_(sf::Quads)
    {
        for(std::size_t i = 1; i < data.size(); ++i)
        {
            if(data[i - 1].size() != data[i].size())
            {
                throw std::invalid_argument("incorrect values!");
            }
        }
        if(data.size() != M_ || data[0].size() != N_)
        {
            throw std::invalid_argument("heatmap have incorrect sizes!");
        }
        vertice_.resize(M_ * N_ * 4);
        double min = 0;
        double max = 0;
        for(const auto& row : data)
        {
            for(const auto& crd : row)
            {
                if(crd < min) {min = crd;}
                if(crd > max){max = crd;}
            }
        }
        for(std::size_t y = 0; y < M_; ++y)
        {
            for(std::size_t x = 0; x < N_; ++x)
            {
                double normalize = (data[y][x] - min)/(max - min);
                Color coordinate_color = pixel_color_scheme(normalize);
                std::size_t  quad_index = (y * N_ + x) * 4;
                vertice_[quad_index].position = sf::Vector2f((x), (y));
                vertice_[quad_index + 1].position = sf::Vector2f((x + 1), (y));
                vertice_[quad_index + 2].position = sf::Vector2f((x + 1), (y + 1));
                vertice_[quad_index + 3].position = sf::Vector2f((x), (y + 1));
                for(std::size_t i = 0; i < 4; ++i)
                {
                    vertice_[quad_index + i].color = coordinate_color.sfc();
                }
            }
        }
    }
};
class Figure
{
    Heatmap obj_;
    std::string filename_;
public:
    Figure(const Heatmap& heatmap, std::size_t M, std::size_t N, const std::string& filename) : obj_(heatmap), filename_(filename){}
};
int main()
{
    std::size_t M = 500;
    std::vector<std::vector<double>> electricPotential(M, std::vector<double>(M));
    for(std::size_t i = 0; i < M; i++)
    {
        for(std::size_t j = 0; j < M; j++)
        {
            electricPotential[i][j] = (((i) - 0.5 * M) * ((j) - 0.5 * M));
        }
    }
    Heatmap map(electricPotential);
}
