#include "login.h"
#include "base_functions.h"
#include "string_checker.h"
#include <thread>
#include <chrono>
#include <vector>
#include <iomanip>
#include <thread>

login::login(std::string u_input, std::string p_input, std::string m_input) : username(u_input), password(p_input), secret_message(m_input)
{
    is_admin = false;
    is_locked = false;
}
void login::account_loop(std::vector<login>& accounts)
{
    bool in_account_loop = true;
    while(in_account_loop == true){
        system("cls");
        if(is_admin == true){
            std::cout << "Current admin account: " << username << std::endl;
        }
        else{
            std::cout << "Current user account: " << username << std::endl;
        }
        std::cout << "Would you like to: 1. View the secret message." << std::endl;
        std::cout << "                   2. Change the secret message." << std::endl;
        std::cout << "                   3. Change the password." << std::endl;
        if(is_admin == true){
            std::cout << "                   4. Access admin privileges." << std::endl;
        }
        std::cout << "                   0. Exit the account." << std::endl;
        int response;
        if(is_admin == true){
            response = int_value_checker("Enter a response between 0 and 4: ", 0, 4);
        }
        else{
            response = int_value_checker("Enter a response between 0 and 3: ", 0, 3);
        }
        switch(response){
            case 0:{
                in_account_loop = false;
                break;
            }
            case 1:{
                std::cout << get_secret_message() << std::endl;
                system("pause");
                break;
            }
            case 2:{
                change_secret_message();
                break;
            }
            case 3:{
                change_password();
                break;
            }
            case 4:{
                admin_loop(accounts);
                break;
            }
            default:{
                break;
            }
        }
    }
}
void login::admin_loop(std::vector<login>& accounts)
{
    bool in_admin_loop = true;
    while(in_admin_loop == true){
        system("cls");
        std::cout << "Admin menu for " << username << std::endl;
        std::cout << "Would you like to: 1. View accounts' locking status." << std::endl;
        std::cout << "                   2. Delete user accounts." << std::endl;
        std::cout << "                   0. Exit the admin menu." << std::endl;
        int response = int_value_checker("Enter a response between 0 and 2: ", 0, 2);
        switch(response){
            case 1:{
                lock_accounts(accounts);
                break;
            }
            case 2:{
                delete_accounts(accounts);
                break;
            }
            case 0:{
                in_admin_loop = false;
                break;
            }
            default:{
                break;
            }
        }
    }
}
void login::lock_accounts(std::vector<login>& accounts)
{
    bool in_lock_accounts = true;
    while(in_lock_accounts == true){
        system("cls");
        std::cout << "Current accounts:" << std::boolalpha << std::endl;
        for(auto elem : accounts){
            std::cout << std::setw(20) << elem.get_username() << "     " << "Locked: " << std::setw(5) << elem.get_locked_status() << "     " << "Admin: " << elem.get_admin_status() << std::endl;
        }
        std::cout << std::noboolalpha << std::endl << "Enter the name of the account you want to change the lock status of, or 'q' to exit: ";
        std::string to_lock;
        std::getline(std::cin, to_lock);
        if((to_lock == "q") || (to_lock == "Q")){
            in_lock_accounts = false;
        }
        else{
            bool has_matched = false;
            for(auto &elem : accounts){
                if(to_lock == elem.get_username()){
                    has_matched = true;
                    if(elem.get_locked_status() == true){
                        elem.set_locked_status(false);
                        std::cout << "Unlocking " << elem.get_username() << std::endl;
                    }
                    else{
                        if(elem.get_admin_status() == true){
                            std::cout << "You can't lock an admin account." << std::endl;
                        }
                        else{
                            elem.lock();
                            std::cout << "Locking " << elem.get_username() << std::endl;
                        }
                    }
                }
            }
            if(has_matched == false){
                std::cout << "Error, that username is not on the list of accounts." << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
}
void login::delete_accounts(std::vector<login>& accounts)
{
    bool in_delete_accounts = true;
    while(in_delete_accounts == true){
        system("cls");
        std::cout << "Current accounts:" << std::boolalpha << std::endl;
        for(auto elem : accounts){
            std::cout << std::setw(20) << elem.get_username() << "     " << "Locked: " << std::setw(5) << elem.get_locked_status() << "     " << "Admin: " << elem.get_admin_status() << std::endl;
        }
        std::cout << std::noboolalpha << std::endl << "Enter the name of the account you want to delete, or 'q' to exit: ";
        std::string to_lock;
        std::getline(std::cin, to_lock);
        if((to_lock == "q") || (to_lock == "Q")){
            in_delete_accounts = false;
        }
        else{
            bool has_matched = false, will_delete = false;
            std::vector<login>::iterator it = accounts.begin();
            for(auto &elem : accounts){
                if(to_lock == elem.get_username()){
                    has_matched = true;
                    if(elem.get_admin_status() == true){
                        std::cout << "You can't delete an admin account." << std::endl;
                    }
                    else{
                        will_delete = true;
                        std::cout << "Deleting " << elem.get_username() << std::endl;
                    }
                }
                if(has_matched == false){
                    ++it;
                }
            }
            if(has_matched == false){
                std::cout << "Error, that username is not on the list of accounts." << std::endl;
            }
            else if(will_delete == true){
                accounts.erase(it);
            }
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
}
void login::change_password()
{
    std::cout << "What would you like your new password to be?" << std::endl;
    std::string entry;
    std::getline(std::cin, entry);
    if(password_hasher(entry) != password){
        if(check_password(entry) == true){
            set_password(password_hasher(entry));
            system("cls");
            std::cout << "New password set." << std::endl;
        }
        else{
            std::cout << "Error, password must have more than 4 characters." << std::endl;
        }
    }
    else{
        system("cls");
        std::cout << "The new password must be different to the old password." << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
void login::change_secret_message()
{
    std::cout << "What would you like your new secret message to be?" << std::endl;
    std::string entry;
    std::getline(std::cin, entry);
    set_secret_message(entry);
    system("cls");
    std::cout << "New secret message set." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
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
void login::lock()
{
    set_lock_time(clock());
    set_locked_status(true);
    std::thread lock_timer(&login::monitor_lock, this);
    lock_timer.detach();
}
int login::query_lock_time()
{
    return static_cast<int>(60 - ((clock() - lock_time) / CLOCKS_PER_SEC));
}
void login::monitor_lock()
{
    while(true){
        if(query_lock_time() < 1){
            set_locked_status(false);
            break;
        }
    }
}

void login::set_password(std::string input_string){password = input_string;}
void login::set_secret_message(std::string input_string){secret_message = input_string;}
void login::set_admin_status(bool bool_input){is_admin = bool_input;}
void login::set_locked_status(bool bool_input){is_locked = bool_input;}
void login::set_lock_time(clock_t time_input){lock_time = time_input;}

std::string login::get_username(){return username;}
std::string login::get_password(){return password;}
std::string login::get_secret_message(){return secret_message;}
bool login::get_admin_status(){return is_admin;}
bool login::get_locked_status(){return is_locked;}
clock_t login::get_lock_time(){return lock_time;}