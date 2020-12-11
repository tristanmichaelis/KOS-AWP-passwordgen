#include "generator.h"
#include <iostream>


using namespace std;

string upperCase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string lowerCase = "abcdefghijklmnopqrstuvwxyz";
string numbers = "0123456789";
string special = " !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

string charset = "";

generator::generator()
{
    this->setCharSet(this->charset.append(upperCase));
    this->setCharSet(this->charset.append(lowerCase));
    this->setCharSet(this->charset.append(numbers));
}

void generator::setCharSet(string charset)
{
    this->charset = charset;
}

void generator::helloWorld()
{
    for (int i = 0; i < 5 ; i++ ) {
        char randChar = this->charset[rand() % this->charset.size()];
        cout << randChar << " ";
    }
    cout << endl;

    cout << upperCase << endl;
}
