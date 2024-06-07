#pragma once
#include "calendar.h"
#include "interface.h"
#include "user.h"

// function that makes an interface to work in settings mode (first run, adding users etc.)
int InitMode();

// function that makes an interface to work for already existing user
int UserMode(User &user);

// function that takes care of navigating through menu and call proper functionalities of program
int UserMenu(Interface &interface, Calendar &calendar, User &user);

User getUser(std::string fileUsers);
void deleteUser(std::string fileUsers);
void displayUsers(std::string fileUsers);

bool inUserList(std::string& checkName, std::string fileUsers);
User createUser(std::string fileUsers);
std::vector<User> loadUsers(std::string fileUsers);
void saveUsers(std::vector<User> users, std::string fileUsers);