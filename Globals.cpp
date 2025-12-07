#include "UserController.h"
#include "WindowController.h"
#include "Globals.h"

namespace fs = std::filesystem;

fs::path EXE_PATH = fs::current_path();
fs::path USER_FOLDER = EXE_PATH / "users";
fs::path IMG_FOLDER = EXE_PATH / "img";
fs::path ARRAY_FOLDER = EXE_PATH / "arrays";
fs::path TEMP_FOLDER = EXE_PATH / "temp";

User G_USER;
UserController G_UC((USER_FOLDER).string());
WindowController G_WC;