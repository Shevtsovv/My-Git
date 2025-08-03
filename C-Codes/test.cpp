#include <GL/freeglut.h>
#include <iostream>
#include <memory>
#include <vector>
namespace chartify{
    struct Common{
        struct Constant{
            static constexpr int WIDTH = 480;
            static constexpr int HEIGHT = 240;
            static constexpr double INDENT = 0.1;
        };
        struct Color{
            static inline const std::vector<double> WHITE = {1.0, 1.0, 1.0};
            static inline const std::vector<double> BLACK = {0.0, 0.0, 0.0};
        };
        struct TypeError{
            static constexpr int CHARTIFY_OK = 0;
            static constexpr int CHARTIFY_INVALID = 1;
        };
    };
    class line{
        std::vector<double> color_;
        double alpha_;
    public:
        line() : color_(Common::Color::WHITE), alpha_(1.0){}
        line(const std::vector<double>& color, double& alpha) : color_(color), alpha_(alpha){
            if(color_.size() != std::size_t(3)){
                throw std::invalid_argument("Line color vector must have len = 3!");
            }
            if((alpha > 1.0) || (alpha < 0.0)){
                throw std::invalid_argument("Line transparency must be from 0 to 1!");
            }
            for(double c : color_){
                if(c > double(1) || c < double(0)){
                    throw std::invalid_argument("Color values must be 0-1!");
                }
            }
        }
        const std::vector<double>& color() const {return color_;}
        double alpha() const {return alpha_;}
        line& operator=(const line& o){
            if(this != &o){
                color_ = o.color_;
                alpha_ = o.alpha_;
            }
            return *this;
        }
    };
    class window{
        int width_, height_;
        std::vector<double> fone_, grid_, text_;
    public:
        window() : width_(Common::Constant::WIDTH), height_(Common::Constant::HEIGHT), fone_(Common::Color::BLACK), grid_({0.1, 0.1, 0.1}), text_(Common::Color::WHITE){}
        window(int width, int height, const std::vector<double>& fone_color, const std::vector<double>& grid_color, const std::vector<double>& text_color) : width_(width),
        height_(height), fone_(fone_color), grid_(grid_color), text_(text_color){
            if(width_ < 0 || height_ < 0){
                std::string msg = "Resolution parameter is negative : ";
                if(width_ < 0) {
                    msg += "width";
                }
                if(height_ < 0){
                    msg += "height";
                }
                throw std::invalid_argument(msg);
            }
            if((fone_.size() != std::size_t(3)) || (grid_.size() != std::size_t(3)) || (text_.size() != std::size_t(3))){
                throw std::invalid_argument("Color vector must have len = 3!");
            }
            auto lambda = [](const std::vector<double>& data)->bool{
                for(const double& item : data){
                    if(item > double(1) || item < double(0)){
                        return false;
                    }
                }
                return true;
            };
            if(!lambda(fone_) || !lambda(grid_) || !lambda(text_)){
                throw std::invalid_argument("Color vector must contain element for 0 to 1!");
            }
        }
        window(int width, int height) : width_(width), height_(height), fone_(Common::Color::BLACK), grid_({0.1, 0.1, 0.1}), text_(Common::Color::WHITE){
            if(width_ < 0 || height_ < 0){
                std::string msg = "Resolution parameter(s) is negative : ";
                if(width_ < 0) {
                    msg += "width";}
                if(height_ < 0){
                    msg += "height";
                }
                throw std::invalid_argument(msg);
            }
        }
        int Width() const {return width_;}
        int Height() const {return height_;}
        window& operator=(const window& o){
            if(this != &o){
                width_ = o.width_, height_ = o.height_;
                fone_ = o.fone_, grid_ = o.grid_, text_ = o.text_;
            }
            return *this;
        }
        struct PlotDisplaySettings{
            bool XLINE = false, YLINE = false;
            bool GRID = true;
            double GRID_PERIOD = Common::Constant::INDENT;
            void* FONT = GLUT_BITMAP_8_BY_13;
        };
    };
    class drawing{
        struct WindowSettings{
            static inline int WINDOW_X = 0, WINDOW_Y = 0, WINDOW_ID = 0;
            static inline double MAX_X = 0, MAX_Y = 0, MIN_X = 0, MIN_Y = 0;
            static inline bool WINDOW_INIT = false, RAW_DATA = false;
            window STYLE_;
            std::string NAME;
        };
        struct Data{
            std::vector<std::vector<double>> X, Y;
            std::vector<line> LINE_STYLE;
        };
        struct ImageSettings{
            std::unique_ptr<float[]> data, scale_data;
            std::size_t width = 0, height = 0;
        };
        struct PlotType{
            int CURVE = 0;
        };
        inline double x(double data){
            if(WindowSettings::MAX_X == WindowSettings::MIN_X){
                return 0.0;
            }
            double res = (data - WindowSettings::MIN_X) / (WindowSettings::MAX_X - WindowSettings::MIN_X) * double(2) - double(1);
            return res;
        }
        inline double y(double data){
            if(WindowSettings::MAX_Y == WindowSettings::MIN_Y){
                return 0.0;
            }
            double res = (data - WindowSettings::MIN_Y) / (WindowSettings::MAX_Y - WindowSettings::MIN_Y) * double(2) - double(1);
            return res;
        }
        void text(double x, double y, void* font, std::string txt){
            if(txt.empty()){
                throw std::invalid_argument("Text message is empty!");
            }
            const double indent = 1e-2;
            glRasterPos2d(x, y);
            for(std::size_t i = 0; i < txt.size(); ++i){
                glutBitmapCharacter(font, (int)txt[i]);
                x += glutBitmapWidth(font, (int)txt[i]) + indent;
            }
            return;
        }
    public:
        drawing(){}
        static drawing* qv_;
        struct ActualData{
            static inline int WINDOW_ID = -1, WIDTH = 0, HEIGHT = 0;
        };
        struct Mouse{
            static inline double X = double(0), Y = double(0);
            static inline bool IS_MOUSE = false;
        };
        void MousePosition(int x, int y){
            if(ActualData::WIDTH == 0 || ActualData::HEIGHT == 0){
                return;
            }
            auto lambda = [](int pixel, std::size_t amount)->double{
                const double max_l = double(2) + double(2) * Common::Constant::INDENT;
                double res = (double(pixel) / double(amount)) * max_l - (max_l / double(2));
                return res;
            };
            Mouse::X = lambda(x, ActualData::WIDTH);
            Mouse::Y = lambda(ActualData::HEIGHT - y, ActualData::HEIGHT);

        }
        void Close(){
            WindowSettings::WINDOW_INIT = false;
            WindowSettings::RAW_DATA = false;
            return;
        }
    };
};