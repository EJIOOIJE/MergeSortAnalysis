#pragma once
#include "UserController.h"
#include <filesystem>

extern User G_USER;

namespace fs = std::filesystem;

UserController::UserController(const std::string& folderPath) : usersFolderPath(folderPath) {
    if (!fs::exists(usersFolderPath)) {
        fs::create_directories(usersFolderPath);
    }
}

bool UserController::saveUser(const User& user, const std::string& fileName) const {
    std::string fullPath = (fs::path(usersFolderPath) / fileName).string();
    return user.saveJSON(fullPath);
}

bool UserController::loadUser(User& user, const std::string& fileName) const {
    std::string fullPath = (fs::path(usersFolderPath) / fileName).string();
    return user.loadJSON(fullPath);
}

bool UserController::saveUser(const User& user) const {
    std::string fileName = getFileName(user);
    return saveUser(user, fileName);
}

bool UserController::loadUser(User& user) const {
    std::string fileName = getFileName(user);
    return loadUser(user, fileName);
}

bool UserController::isUserEqual(const User& user, const std::string& fileName) const {
    User loadedUser;
    if (!loadUser(loadedUser, fileName)) {
        return false;
    }
    return user.isEqualTo(loadedUser);
}

bool UserController::loginUser(const std::string& login, std::string& password) const {
    User  u = createUser(login, login, password);
    std::string filename = getFileName(u);
    User  fu;
    if (!loadUser(fu, filename)) {
        return false;
    }

    if (!u.isEqualTo(fu)) {
        return false;
    }

    G_USER = fu;

    return true;
}

bool UserController::isLoggedIn() const {
    return !G_USER.isEmpty();
}

std::string UserController::getFileName(const User& user) const {
    return user.name + ".json";
}

User UserController::createUser(const std::string& name, const std::string& login, const std::string& password, const bool isAdmin) const {
    User user;
    user.name = name;
    user.login = login;
    user.setPassword(password);
    user.isAdmin = isAdmin;
    return user;
}