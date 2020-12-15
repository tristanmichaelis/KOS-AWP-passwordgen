#ifndef GENERATOR_H
#define GENERATOR_H

#include <PasswordConstants.h>
#include <string>
#include <vector>
#include <tuple>

class generator
{
public:
    generator();
    std::string generateSinglePassword();
    std::vector<std::string> generateMultiplePasswords(int amount);
    void setCharSet(std::string charset);
    void addObligatoryChars(int minimum, std::string charset);
    void clearObligatoryChars();
    int setLength(int length);
    int getLength();
private:
    std::vector<std::tuple<int, std::string>> obligatoryCharset;
    std::string charset;
    int length;
};

#endif // GENERATOR_H
