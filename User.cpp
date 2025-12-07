#include "User.h"
#include <openssl/evp.h>
#include <openssl/err.h>
#include <iomanip>
#include <sstream>

static std::string sha256(const std::string& str) {
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int lengthOfHash = 0;

    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx) {
        ERR_print_errors_fp(stderr);
        return "";
    }

    if (EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr) != 1) {
        ERR_print_errors_fp(stderr);
        EVP_MD_CTX_free(ctx);
        return "";
    }

    if (EVP_DigestUpdate(ctx, str.c_str(), str.size()) != 1) {
        ERR_print_errors_fp(stderr);
        EVP_MD_CTX_free(ctx);
        return "";
    }

    if (EVP_DigestFinal_ex(ctx, hash, &lengthOfHash) != 1) {
        ERR_print_errors_fp(stderr);
        EVP_MD_CTX_free(ctx);
        return "";
    }

    EVP_MD_CTX_free(ctx);

    std::stringstream ss;
    for (unsigned int i = 0; i < lengthOfHash; ++i)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];

    return ss.str();
}

bool User::isEqualTo(const User& other) const {
    return login == other.login &&
        passwordHash == other.passwordHash;
}

void User::setPassword(const std::string& password) {
    passwordHash = sha256(password);
}

bool User::checkPassword(const std::string& password) const {
    return sha256(password) == passwordHash;
}

bool User::isEmpty() const {
    return login.empty() && name.empty() && passwordHash.empty();
}

json User::toJson() const {
    return json{
        {"name", name},
        {"login", login},
        {"passwordHash", passwordHash},
        {"isAdmin", isAdmin}
    };
}

void User::fromJson(const json& j) {
    name = j.value("name", "");
    login = j.value("login", "");
    passwordHash = j.value("passwordHash", "");
    isAdmin = j.value("isAdmin", false);
}