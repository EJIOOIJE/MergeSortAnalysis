#pragma once
#include <filesystem>

namespace fs = std::filesystem;

extern fs::path EXE_PATH;
extern fs::path USER_FOLDER;
extern fs::path IMG_FOLDER;
extern fs::path ARRAY_FOLDER;
extern fs::path TEMP_FOLDER;

class User;
class UserController;
class WindowController;

extern User G_USER;
extern UserController G_UC;
extern WindowController G_WC;