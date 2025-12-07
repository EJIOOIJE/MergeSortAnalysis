#include "functions.h"
#include <sstream>
#include <windows.h>
#include <commdlg.h> 
#include "UserController.h"
#include "Globals.h"

namespace fs = std::filesystem;

std::wstring stringToWstring(const std::string& s)
{
    if (s.empty()) return L"";

    int sizeNeeded = MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, NULL, 0);
    std::wstring wstrTo(sizeNeeded, 0);
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, &wstrTo[0], sizeNeeded);

    if (!wstrTo.empty() && wstrTo.back() == L'\0') {
        wstrTo.pop_back();
    }
    return wstrTo;
}

std::string wstringToString(const std::wstring& ws)
{
    if (ws.empty()) return "";

    int sizeNeeded = WideCharToMultiByte(CP_ACP, 0, ws.c_str(), -1, NULL, 0, NULL, NULL);
    std::string strTo(sizeNeeded - 1, 0); // -1 потому что в `sizeNeeded` включен нулевой символ
    WideCharToMultiByte(CP_ACP, 0, ws.c_str(), -1, &strTo[0], sizeNeeded - 1, NULL, NULL);
    return strTo;
}

bool is_long_long(const std::string& s) {
    try {
        std::stoll(s);
        return true;
    }
    catch (const std::invalid_argument& e) {
        return false;
    }
    catch (const std::out_of_range& e) {
        return false;
    }
}

bool is_double(const std::string& s) {
    try {
        std::stod(s);
        return true;
    }
    catch (const std::invalid_argument& e) {
        return false;
    }
    catch (const std::out_of_range& e) {
        return false;
    }
}

std::string dtoslim(double d, int precision) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << d;

    return ss.str();
}

bool OpenFileDialog(std::wstring& selectedFile, const std::wstring& initialDir)
{
    OPENFILENAMEW ofn;
    WCHAR szFile[MAX_PATH] = { 0 };

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile) / sizeof(WCHAR);
    ofn.lpstrFilter = L"JSON Files\0*.json\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = initialDir.c_str();
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetOpenFileNameW(&ofn) == TRUE)
    {
        selectedFile = szFile;
        return true;
    }
    return false;
}

void generateUsers() {
    User u;
    u.login = "user";
    u.name = "user";
    u.setPassword("user");
    G_UC.saveUser(u);
    u.login = "admin";
    u.name = "admin";
    u.setPassword("admin");
    u.isAdmin = true;
    G_UC.saveUser(u);
}