#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED
#include <iostream>
#include <vector>

class login{
    private:
        std::string username, password, secret_message;
        std::size_t hashed_password;
        bool is_admin, is_locked;
        clock_t lock_time;

    public:
        login(std::string, std::string, std::string);
        void account_loop(std::vector<login>&);
        void admin_loop(std::vector<login>&);
        void lock_accounts(std::vector<login>&);
        void delete_accounts(std::vector<login>&);
        void change_password();
        void change_secret_message();
        bool match_username(std::string);
        bool match_password(std::string);
        void lock();
        int query_lock_time();
        void monitor_lock();

        void set_password(std::string);
        void set_secret_message(std::string);
        void set_admin_status(bool);
        void set_locked_status(bool);
        void set_lock_time(clock_t);

        std::string get_username();
        std::string get_secret_message();
        bool get_admin_status();
        bool get_locked_status();
        clock_t get_lock_time();
};

#endif //LOGIN_H_INCLUDED