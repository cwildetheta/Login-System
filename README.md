Login System simulation, done for The Software Institute training.

There are five cpp files, which handle:
main.cpp: Creates the manager object, and then runs the manager object loop.

base_functions.cpp: Has two functions, one which takes and sanitises an integer input, and the other which calls that function but ensures the entered value is within a given range.

string_checker.cpp: Has functions to check that entered usernames and passwords meet the entry requirements, and a currently unused function for hashing the passwords.

login.cpp: Contains the login class, which has the login details, as well as the methods for the account loop and functionality, such as viewing and changing the secret message, as well as the admin functionality, if the account is an admin, such as locking and deleting non-admin accounts.

manager.cpp: Contains the manager class, which has a vector of accounts, and contains methods for the system UI, adding accounts and attempting to log into accounts.