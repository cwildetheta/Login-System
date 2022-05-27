#ifndef STRING_CHECKER_H_INCLUDED
#define STRING_CHECKER_H_INCLUDED
#include <string>

bool check_username(const std::string&);
bool check_password(const std::string&);
std::string password_hasher(const std::string&);

#endif //STRING_CHECKER_H_INCLUDED