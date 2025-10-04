#include <string>
class Mathematical_Expression{
public:
    virtual ~Mathematical_Expression() = default;
    virtual double operator()(const double& value) const = 0;
};
class Constant : public Mathematical_Expression{
    double value_;
public:
    Constant(const double& value) : value_(value){}
    const double& data() const {return value_;}
    double operator()(const double& value) const override {return value_;}
};
class Variable : public Mathematical_Expression{
    std::string sign_;
public:
    Variable(const std::string& signature) : sign_(signature){}
    const std::string& signature() const {return sign_;}
    double operator()(const double& value) const override {return value;}
};
