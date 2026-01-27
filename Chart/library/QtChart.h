#include <vector>
#include <stdint.h>
#include <SFML/Graphics.hpp>
#include <memory>
using vec = std::vector<double>;
class Qt
{
    std::shared_ptr<sf::RenderWindow> qt_;
    vec ScalePerform(const vec& u) const;
    std::vector<sf::VertexArray> CreateGrid(const vec& u, bool horizontal) const;
public:
    Qt(std::size_t a = 600, std::string name = "Qt Graph!") : qt_(nullptr)
    {
        qt_ = std::make_shared<sf::RenderWindow>(sf::VideoMode(a, a), name);
    }
    Qt(const Qt&) = delete;
    Qt& operator=(const Qt&) = delete;
    class Color
    {
        std::vector<uint8_t> c_;
    public:
        Color(const std::vector<uint8_t>& c) : c_(c){}
        uint8_t& operator[](std::size_t idx) {return c_[idx];}
        const uint8_t& operator[](std::size_t idx) const {return c_[idx];}
    };
    bool Visualize(const vec& u, double (*func)(double x), Color linecolor) const;
};