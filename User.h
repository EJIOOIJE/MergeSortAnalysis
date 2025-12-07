#ifndef USER_H
#define USER_H

#include "Serializable.h"
#include <string>

class User : public Serializable {
public:
    std::string name;
    std::string login;
    bool isAdmin = false;

private:
    std::string passwordHash;

public:
    bool isEqualTo(const User& other) const;

    void setPassword(const std::string& password);

    bool checkPassword(const std::string& password) const;
    bool isEmpty() const;

    json toJson() const override;
    void fromJson(const json& j) override;
};

#endif // USER_H