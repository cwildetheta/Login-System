#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED
#include <iostream>

class login{
    private:
        std::string username, password, secret_message;

    public:
        login(std::string, std::string, std::string);
        void change_password();
        void change_secret_message();
        void set_password(std::string);
        void set_secret_message(std::string);
        std::string get_secret_message();
        bool match_username(std::string);
        bool match_password(std::string);
};


#endif //LOGIN_H_INCLUDED