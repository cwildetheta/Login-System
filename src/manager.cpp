#include "manager.h"
#include "login.h"
#include <thread>
#include <chrono>

manager::manager(){}
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
                system("cls");
                std::cout << "Exiting the system." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
                in_system_loop = false;
                system("cls");
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
    std::cin.ignore();
    std::getline(std::cin, username);
    std::cout << "What would you like your password to be?" << std::endl;
    std::getline(std::cin, password);
    std::cout << "What would you like your username to be?" << std::endl;
    std::getline(std::cin, secret_message);
    system("cls");
    std::cout << "Creating user " << username << "." << std::endl;
    accounts.push_back(login(username, password, secret_message));
}
void manager::attempt_login(){
    system("cls");
    std::string username, password;
    std::cout << "Please enter your username: ";
    std::cin.ignore();
    std::getline(std::cin, username);
    std::cout << "Please enter your password: ";
    std::getline(std::cin, password);
    system("cls");
    std::cout << check_accounts(username, password) << std::endl;
    system("pause");
}
std::string manager::check_accounts(std::string username, std::string password){
    for(auto elem : accounts){
        if(elem.match_username(username) == true){
            if(elem.match_password(password) == true){
                return elem.get_secret_message();
            }
        }
    }
    return "Entered details do not match any account in the system.";
}