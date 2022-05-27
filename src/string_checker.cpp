#include "string_checker.h"

bool check_username(std::string username)
{
    if((username.length() > 3) && (username.length() < 21)){
        return true;
    }
    return false;
}
bool check_password(std::string password)
{
    if(password.length() > 3){
        return true;
    }
    return false;
}