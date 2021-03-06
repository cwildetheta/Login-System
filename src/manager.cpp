#include "manager.h"
#include "login.h"
#include "string_checker.h"
#include "json.hpp"
#include <thread>
#include <chrono>
#include <vector>
#include <functional>
#include <fstream>

using json = nlohmann::json;

manager::manager()
{
    std::ifstream test;
    test.open("accounts.json", std::ifstream::binary);
    if(test){
        json read_in;
        test >> read_in;
        for(int i = 0; i < read_in["Number of accounts"]; i++){
            std::string object_name = "Account " + std::to_string(i+1);
            accounts.push_back(login(read_in[object_name]["Username"], read_in[object_name]["Hashed password"], read_in[object_name]["Secret message"]));
            if(read_in[object_name]["Admin Status"] == true){
                std::vector<login>::iterator i1 = accounts.end();
                --i1;
                i1->set_admin_status(true);
            }
        }
    }
    else{
        accounts.push_back(login("Admin", password_hasher("Adminpassword"), "This is the admin account."));
        accounts.begin()->set_admin_status(true);
        accounts.push_back(login("Test", password_hasher("Test"), "Test"));
    }
}
void manager::system_loop(){
    bool in_system_loop = true;
    while(in_system_loop == true){
        system("cls");
        std::cout << "Welcome to the Login System. There are currently " << accounts.size() << " accounts in the system." << std::endl;
        std::cout << "Would you like to: a. Add an account." << std::endl;
        std::cout << "                   l. Attempt a login." << std::endl;
        std::cout << "                   q. Exit the system." << std::endl;
        char entry;
        std::cin >> entry;
        std::cin.ignore();
        switch(entry){
            case 'a':
            case 'A':{
                add_account();
                break;
            }
            case 'l':
            case 'L':{
                attempt_login();
                break;
            }
            case 'q':
            case 'Q':{
                quit();
                in_system_loop = false;
                break;
            }
            default:{
                break;
            }
        }
    }
}
void manager::add_account(){
    system("cls");
    std::string username, password, secret_message;
    std::cout << "What would you like your username to be?" << std::endl;
    std::getline(std::cin, username);
    std::cout << "What would you like your password to be?" << std::endl;
    std::getline(std::cin, password);
    std::cout << "What would you like your secret message to be?" << std::endl;
    std::getline(std::cin, secret_message);
    system("cls");
    bool repeat_username = false;
    for(auto elem : accounts){ //Doesn't need to be a reference, not changing anything.
        if(username == elem.get_username()){
            repeat_username = false;
        }
    }
    if(repeat_username == true){
        std::cout << "Error, an account with this username already exists." << std::endl;
    }
    else if(check_username(username) == false){
        std::cout << "Error, username must have betwee 4 and 20 characters." << std::endl;
    }
    else if(check_password(password) == false){
        std::cout << "Error, password must have more than 4 characters." << std::endl;
    }
    else{
        std::cout << "Creating user " << username << "." << std::endl;
        accounts.push_back(login(username, password_hasher(password), secret_message));
    }
    system("pause");
}
void manager::attempt_login(){
    system("cls");
    std::string username, password;
    std::cout << "Please enter your username: ";
    std::getline(std::cin, username);
    std::cout << "Please enter your password: ";
    std::getline(std::cin, password);
    system("cls");
    if(check_password(password) == false){
        std::cout << "Entered details do not match any account in the system." << std::endl;
        system("pause");
    }
    else{
        if(check_accounts(username, password) == false){
            std::cout << "Entered details do not match any account in the system." << std::endl;
            system("pause");
        }
    }
}
bool manager::check_accounts(std::string username, std::string password){
    for(auto &elem : accounts){
        if(elem.match_username(username) == true){
            if(elem.match_password(password_hasher(password)) == true){
                if(elem.get_locked_status() == false){
                    if(elem.get_admin_status() == true){
                        elem.account_loop(accounts);
                    }
                    else{
                        std::vector<login> temp;
                        elem.account_loop(temp);
                    }
                }
                else{
                    std::cout << "This account is currently locked. It will be unlocked in " << elem.query_lock_time() << " seconds. Please try again then." << std::endl;
                    system("pause");
                }
                return true;
            }
        }
    }
    return false;
}
void manager::quit(){
    system("cls");
    std::cout << "Exiting the system." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    json account_json;
    account_json["Number of accounts"] = accounts.size();
    int i = 1;
    for(auto elem : accounts){
        std::string object_name = "Account " + std::to_string(i);
        account_json[object_name] = {
            {"Username", elem.get_username()},
            {"Hashed password", elem.get_password()},
            {"Secret message", elem.get_secret_message()},
            {"Admin Status", elem.get_admin_status()}
        };
        i++;
    }
    std::ofstream account_json_file;
    account_json_file.open("accounts.json");
    account_json_file << std::setw(4) << account_json << std::endl;
    account_json_file.close();
    system("cls");
}