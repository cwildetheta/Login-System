#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED
#include "login.h"
#include <iostream>
#include <vector>

class manager{
    private:
        std::vector<login> accounts;

    public:
        manager();
        void system_loop();
        void add_account();
        void attempt_login();
        std::string check_accounts(std::string, std::string);
};

#endif //MANAGER_H_INCLUDED