#ifndef GENERATOR_H
#define GENERATOR_H

#include <string>

class generator
{
public:
    generator();
    void helloWorld();
private:
    void setCharSet(std::string charset);
    std::string charset;
};

#endif // GENERATOR_H
