#pragma once
#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include "User.h"

class UserController {
private:
    const std::string usersFolderPath;

public:
    explicit UserController(const std::string& folderPath);

    bool saveUser(const User& user) const;

    bool loadUser(User& user) const;

    bool saveUser(const User& user, const std::string& fileName) const;

    bool loadUser(User& user, const std::string& fileName) const;

    bool isUserEqual(const User& user, const std::string& fileName) const;

    bool loginUser(const std::string& login, std::string& password) const;

    bool isLoggedIn() const;

    std::string getFileName(const User& user) const;

    User createUser(const std::string& name, const std::string& login, const std::string& password, const bool isAdmin = false) const;
};

#endif // USERCONTROLLER_H