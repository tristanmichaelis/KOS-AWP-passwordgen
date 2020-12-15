#include "generator.h"
#include <time.h>
#include <algorithm>

using namespace std;
using namespace PasswordConstants;

string charset;
vector<tuple<int, string>> obligatoryCharset;
int length;

generator::generator()
{
    srand(time(NULL));
}

int generator::setLength(int length)
{
    this->length = length;
    return length;
}

/******************************************************************
 * Previously used function, error handling is now handled by GUI *
 *                                                                *
 *                                                                *
int generator::setLength(int length)
{
    int obligatoryCharsetLength = 0;

    for (tuple<int,string> t : obligatoryCharset)
    {
        int minimum;
        tie(minimum, ignore) = t;

        obligatoryCharsetLength += minimum;
    }

    if (length >= obligatoryCharsetLength)
    {
        this->length = length;
    }

    return this->length;
}
 *                                                                *
 ******************************************************************/

int generator::getLength()
{
    return this->length;
}

void generator::setCharSet(string charset)
{
    this->charset = charset;
}

void generator::addObligatoryChars(int minimum, string charset)
{
    this->obligatoryCharset.push_back(make_tuple(minimum, charset));
}

void generator::clearObligatoryChars()
{
    this->obligatoryCharset.clear();
}

string generator::generateSinglePassword()
{
    string password = "";

    //First we add our obligatory characters to password
    for (tuple<int, string> t : obligatoryCharset)
    {
        int minimum;
        string charset;

        tie(minimum, charset) = t;

        for (int i = 0; i < minimum; i++)
        {
            password += charset[rand() % charset.size()];
        }
    }

    //Now fill the password with default charset until disired length is reached
    for (int i = password.length(); i < this->length; i++ )
    {
        password += this->charset[rand() % this->charset.size()];
    }

    //Disorder!
    random_shuffle(begin(password), end(password));

    return password;
}

vector<string> generator::generateMultiplePasswords(int amount)
{
    vector<string> passwords;

    for (int i = 0; i < amount; i++)
    {
        passwords.push_back(this->generateSinglePassword());
    }

    return passwords;
}
