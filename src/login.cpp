#include "login.h"

login::login(std::string u_input, std::string p_input, std::string m_input) : username(u_input), password(p_input), secret_message(m_input) {}
void login::change_password(){}
void login::change_secret_message(){}
void login::set_password(std::string){}
void login::set_secret_message(std::string input_string){secret_message = input_string;}
std::string login::get_secret_message(){return secret_message;}
bool login::match_username(std::string test_username)
{
    if(test_username == username){
        return true;
    }
    else{
        return false;
    }
}
bool login::match_password(std::string test_password)
{
    if(test_password == password){
        return true;
    }
    else{
        return false;
    }
}