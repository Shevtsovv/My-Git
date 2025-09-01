#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <memory>
#include <cmath>
struct Screen{
    static constexpr unsigned int Width = 1400;
    static constexpr unsigned int Height = 700;
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
struct Cashed{
    static inline std::vector<std::vector<double>> data1_, data2_;
    static inline std::vector<Color> color_;
    static constexpr int space = 100;
};
struct Title{
    static inline sf::Font font_;
    static inline sf::Text title_;
    static inline sf::String ttl_;
    static constexpr int fontsize_ = 18;
    static inline bool TITLE_ENABLED_ = false;
};
template <typename T>
concept alg = std::is_integral_v<T> || std::is_floating_point_v<T>;
template <alg T> class Graph{
    std::unique_ptr<RenderProfile> profile_;
    Color fone_, grid_, axes_;
    const float dot_radius = 1.4f;
    bool Text(sf::Text& text, sf::Font& font, const sf::String& str, const unsigned int& fontsize, const T& x, const T& y) const {
        const std::string root = "../h/font/font.ttf";
        sf::RenderTexture& texture = profile_->Profile();
        const sf::Color& black = Color::Black().Data();
        if(!font.loadFromFile(root)){
            throw std::invalid_argument("error 0");
        }
        text.setFont(font);
        text.setFillColor(black);
        text.setCharacterSize(fontsize);
        text.setPosition(x, y);
        text.setString(str);
        texture.draw(text);
        return true;
    }
    bool Grid() const {
        const int& space = Cashed::space;
        const unsigned int& a = profile_->Data().x;
        const unsigned int& b = profile_->Data().y;
        sf::RenderTexture& texture = profile_->Profile();
        for(int v = space; v <= a - space; v += (a - 2 * space)/ 10){
            sf::Vertex vl[] = {sf::Vertex(sf::Vector2f(v, space), grid_.Data()), sf::Vertex(sf::Vector2f(v, (b - space)), grid_.Data())};
            texture.draw(vl, 2, sf::LineStrip);
        }
        for(int h = space; h <= b - space; h += (b - 2 * space)/ 10){
            sf::Vertex hl[] = {sf::Vertex(sf::Vector2f(space, h), grid_.Data()), sf::Vertex(sf::Vector2f(a - space, h), grid_.Data())};
            texture.draw(hl, 2, sf::LineStrip);
        }
        return true;
    }
    bool Solid(const std::vector<sf::Vertex>& c, const Color& color) const {
        sf::RenderTexture& texture = profile_->Profile();
        const float space = 0.5f;
        const float& R = dot_radius;
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
                texture.draw(dot);
            }
        }
        return true;
    }
    bool Plot() const {
        sf::RenderTexture& texture = profile_->Profile();
        const int& space = Cashed::space;
        const double r = space / 5;
        std::vector<std::vector<T>>& x = Cashed::data1_, y = Cashed::data2_;
        std::vector<Color>& color = Cashed::color_;
        const unsigned int& a = profile_->Data().x, b = profile_->Data().y;
        T global_min_x = std::numeric_limits<T>::max(),
                global_max_x = std::numeric_limits<T>::lowest();
        T global_min_y = std::numeric_limits<T>::max(),
                global_max_y = std::numeric_limits<T>::lowest();
        for(std::size_t i = 0; i < x.size(); ++i){
            for(const auto& val : x[i]){
                global_min_x = std::min(global_min_x, val);
                global_max_x = std::max(global_max_x, val);
            }
            for(const auto& val : y[i]){
                global_min_y = std::min(global_min_y, val);
                global_max_y = std::max(global_max_y, val);
            }
        }
        double u = global_max_x - global_min_x;
        double v = global_max_y - global_min_y;
        if(u == 0) u = 1;
        if(v == 0) v = 1;
        texture.clear(fone_.Data());
        for(std::size_t i = 0; i < x.size(); ++i){
            std::vector<sf::Vertex> c;
            for(std::size_t l = 0; l < x[i].size(); ++l){
                float scr_x = (space + r) + ((x[i][l] - global_min_x) / u) * (a - 2 * (space + r));
                float scr_y = (space + r) + (b - 2 * (space + r)) * (1 - ((y[i][l] - global_min_y) / v));
                c.emplace_back(sf::Vector2f(scr_x, scr_y), color[i].Data());
            }
            Solid(c, color[i]);
        }
        Grid();
        const bool& TITLE_EN = Title::TITLE_ENABLED_;
        const sf::String& ttl = Title::ttl_;
        if(TITLE_EN){Title(ttl);}
        texture.display();
        return true;
    }
public:
    Graph() : profile_(std::make_unique<RenderProfile>(Screen::Width, Screen::Height, sf::String("As Chartify!"))), fone_(Color::White()), grid_(Color({Color({180, 180, 180}, 200)})), axes_(Color::Black()){}
    bool ConfigurePlot(const std::vector<std::vector<double>>& data1, const std::vector<std::vector<double>>& data2, const std::vector<Color>& color){
        Cashed::data1_.clear();
        Cashed::data2_.clear();
        if(data1.size() != data2.size() || data1.size() != color.size() || data1.empty() || data2.empty()){
            throw std::invalid_argument("error 1");
        }
        for(std::size_t i = 0; i < data1.size(); ++i){
            if(data1[i].size() != data2[i].size() || data1[i].size() <= 2 || data2[i].size() <= 2){
                throw std::invalid_argument("error 2");
            }
            Cashed::data1_.push_back(data1[i]);
            Cashed::data2_.push_back(data2[i]);
        }
        Cashed::color_ = color;
        return true;
    }
    bool Title(const sf::String& title) const {
        sf::Text& text_ttl = Title::title_;
        sf::Font& font_ttl = Title::font_;
        const int& space = Cashed::space;
        const float& str_len = text_ttl.getGlobalBounds().getSize().x;
        const unsigned int& x = (profile_->Data().x - str_len) / 2, y = Cashed::space / 2, fsize = Title::fontsize_;
        Text(text_ttl, font_ttl, title, fsize, x, y);
        Title::ttl_ = title;
        Title::TITLE_ENABLED_ = true;
        return true;
    }
    bool Savefig(const std::string& filename) const {
        sf::RenderTexture& texture = profile_->Profile();
        Plot();
        return texture.getTexture().copyToImage().saveToFile(filename);
    }
    ~Graph() = default;
};