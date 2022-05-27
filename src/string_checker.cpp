#include "string_checker.h"
#include <iostream>
#include <math.h>

bool check_username(const std::string& username)
{
    if((username.length() > 3) && (username.length() < 21)){
        return true;
    }
    return false;
}
bool check_password(const std::string& password)
{
    if(password.length() > 3){
        return true;
    }
    return false;
}
std::string password_hasher(const std::string& password)
{
    int password_length = password.length();
    std::string hashed_password;
    for(int i = 0; i < 32; i++){
        int k = i%password_length;
        int elem = static_cast<int>(password.at(k));
        int addition = static_cast<int>(password.at((k+1)%password_length));
        long long resulting_value = ((elem*std::pow(2, (i+4))) + addition)/(10*i);
        char resulting_character = static_cast<char>((resulting_value%64)+64);
        hashed_password = hashed_password + resulting_character;
    }
    return hashed_password;
}