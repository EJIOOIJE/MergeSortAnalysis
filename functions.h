#pragma once
#include <string>

#define pass (void)0

std::wstring stringToWstring(const std::string& s);

std::string wstringToString(const std::wstring& ws);

bool is_long_long(const std::string& s);

bool is_double(const std::string& s);

std::string dtoslim(double d, int precision = 2);

bool OpenFileDialog(std::wstring& selectedFile, const std::wstring& initialDir);

void generateUsers();

