#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <memory>
#include <cmath>
struct Screen{
    static constexpr unsigned int Width = 1200;
    static constexpr unsigned int Height = 600;
};
struct Flag{
    static constexpr unsigned int Solid = 1;
    static constexpr unsigned int Dashed = 2;
    static constexpr unsigned int Dotted = 3;
};
class Color{
    uint8_t alpha_;
    sf::Color color_;
public:
    Color() = default;
    Color(const std::vector<uint8_t>& color, const uint8_t& alpha) : alpha_(alpha), color_(color[0], color[1], color[2], alpha_){}
    Color(const Color& o) : alpha_(o.alpha_), color_(o.color_){}
    Color& operator=(const Color&) = default;
    static Color White(){
        return Color({255, 255, 255}, 255);
    }
    static Color Black(){
        return Color({0, 0, 0}, 255);
    }
    const sf::Color& Data() const {return color_;}
    const uint8_t& Alpha() const {return alpha_;}
    ~Color() = default;
};
class RenderProfile{
    sf::String name_;
    sf::Vector2u sizes_;
    sf::RenderTexture texture_;
public:
    RenderProfile(unsigned int width, unsigned int height, const sf::String& name) : name_(name), sizes_(width, height){
        texture_.create(sizes_.x, sizes_.y);
    }
    const sf::Vector2u& Data() const {return sizes_;}
    sf::RenderTexture& Profile(){return texture_;}
    ~RenderProfile() = default;
};
template <typename T>
concept alg = std::is_integral_v<T> || std::is_floating_point_v<T>;
struct Cashed{
    static inline std::vector<std::vector<double>> data1_;
    static inline std::vector<std::vector<double>> data2_;
    static inline std::vector<unsigned int> linestyle_;
    static inline std::vector<Color> color_;
};
template <alg T> class Graph{
    std::unique_ptr<RenderProfile> profile_;
    Color fone_, grid_, axes_;
    bool Grid() const {
        const int space = 90;
        const unsigned int& a = profile_->Data().x;
        const unsigned int& b = profile_->Data().y;
        for(int v = space; v <= a - space; v += (a - 2 * space)/ 10){
            sf::Vertex vl[] = {sf::Vertex(sf::Vector2f(v, space), grid_.Data()), sf::Vertex(sf::Vector2f(v, (b - space)), grid_.Data())};
            profile_->Profile().draw(vl, 2, sf::LineStrip);
        }
        for(int h = space; h <= b - space; h += (b - 2 * space)/ 10){
            sf::Vertex hl[] = {sf::Vertex(sf::Vector2f(space, h), grid_.Data()), sf::Vertex(sf::Vector2f(a - space, h), grid_.Data())};
            profile_->Profile().draw(hl, 2, sf::LineStrip);
        }
        return true;
    }
    bool Solid(const std::vector<sf::Vertex>& c, const Color& color) const {
        const float space = 0.5f;
        const float R = 1.4f;
        for(std::size_t i = 1; i < c.size(); ++i){
            const sf::Vector2f& iu = c[i - 1].position;
            const sf::Vector2f& iv = c[i].position;
            sf::Vector2f div = iv - iu;
            float segment_len = std::sqrt(div.x * div.x + div.y * div.y);
            div /= segment_len;
            for(float s = 0.0f; s < segment_len; s += space){
                sf::Vector2f dx = iu + div * s;
                sf::CircleShape dot(R);
                dot.setPosition(dx);
                dot.setFillColor(color.Data());
                profile_->Profile().draw(dot);
            }
        }
        return true;
    }
    bool Plot() const {
        constexpr int space = 90;
        constexpr double r = space / 3;
        std::vector<std::vector<T>>& x = Cashed::data1_;
        std::vector<std::vector<T>>& y = Cashed::data2_;
        const unsigned int& a = profile_->Data().x;
        const unsigned int& b = profile_->Data().y;
        const unsigned int& solid = Flag::Solid;
        std::vector<Color>& color = Cashed::color_;
        std::vector<unsigned int>& linestyle = Cashed::linestyle_;
        std::vector<std::pair<std::vector<double>::const_iterator, std::vector<double>::const_iterator>> it_x;
        std::vector<std::pair<std::vector<double>::const_iterator, std::vector<double>::const_iterator>> it_y;
        profile_->Profile().clear(fone_.Data());
        for(std::size_t i = 0; i < x.size(); ++i){
            it_x.push_back(std::minmax_element(x[i].begin(), x[i].end()));
            it_y.push_back(std::minmax_element(y[i].begin(), y[i].end()));
            double u = *it_x[i].second - *it_x[i].first;
            double v = *it_y[i].second - *it_y[i].first;
            if(u == 0 || v == 0){
                u = 1;
                v = 1;
            }
            std::vector<sf::Vertex> c;
            for(std::size_t l = 0; l < x[i].size(); ++l){
                float scr_x = (space + r) + ((x[i][l] - *it_x[i].first) / (u)) * (a - 2 * (space + r));
                float scr_y = (space + r) + (b - 2 * (space + r)) * (1 - ((y[i][l] - *it_y[i].first) / (v)));
                c.emplace_back(sf::Vector2f(scr_x, scr_y), color[i].Data());
            }
            Solid(c, color[i]);
        }
        Grid();
        profile_->Profile().display();
        return true;
    }
public:
    Graph() : profile_(std::make_unique<RenderProfile>(Screen::Width, Screen::Height, sf::String("As Chartify!"))), fone_(Color::White()), grid_(Color({Color({180, 180, 180}, 200)})), axes_(Color::Black()){}
    bool ConfigurePlot(const std::vector<std::vector<double>>& data1, const std::vector<std::vector<double>>& data2, const std::vector<Color>& color, const std::vector<unsigned int>& linestyle){
        if(data1.size() != data2.size() || data1.size() != color.size() || data1.size() != linestyle.size() || data1.empty() || data2.empty()){
            throw std::invalid_argument("error 1");
        }
        Cashed::data1_.clear();
        Cashed::data2_.clear();
        for(std::size_t i = 0; i < data1.size(); ++i){
            if(data1[i].size() != data2[i].size() || data1[i].size() <= 2 || data2[i].size() <= 2){
                throw std::invalid_argument("error 2");
            }
            Cashed::data1_.push_back(data1[i]);
            Cashed::data2_.push_back(data2[i]);
        }
        Cashed::color_ = color;
        Cashed::linestyle_ = linestyle;
        return true;
    }
    bool Savefig(const std::string& filename) const {
        Plot();
        return profile_->Profile().getTexture().copyToImage().saveToFile(filename);
    }
    ~Graph() = default;
};