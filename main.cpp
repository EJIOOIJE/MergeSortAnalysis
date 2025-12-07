#pragma execution_character_set("utf-8")
#include <locale>
#include "Widgets.h"   
#include "Windows.h"
#include "UserController.h"
#include "WindowController.h"
#include "Globals.h"

using namespace sf;
using namespace std;
using namespace tgui;

/*
struct WindowSize
{
    unsigned int Width;
    unsigned int Height;
};

static WindowSize MAIN_WINDOW_SIZE = { 1280, 720 };
*/

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    auto main = std::make_shared<MainWindow>(sf::Vector2u(1280, 720));
    G_WC.addWindow("MainWindow", main);
    G_WC.start();

    return 0;
}
/*
int main(int argc, char* argv[])
{

    //User u;
    //u.login = "admin";
    //u.name = "admin";
    //u.setPassword("admin");
    //G_UC.saveUser(u);
    //u.login = "user";
    //u.name = "user";
    //u.setPassword("user");
    //G_UC.saveUser(u);

    RenderWindow mainWindow(
        VideoMode({ MAIN_WINDOW_SIZE.Width, MAIN_WINDOW_SIZE.Height }),
        "TGUI example - SFML_GRAPHICS backend",
        Style::Titlebar | Style::Resize | Style::Close,
        State::Windowed
    );
    mainWindow.setFramerateLimit(60);
    Gui mainWindowGui{ mainWindow };
    LoginWidget loginWidget;
    loginWidget.update();
    loginWidget.show(mainWindowGui);

    while (mainWindow.isOpen())
    {
        while (const optional event = mainWindow.pollEvent())
        {
            auto eventHandler = mainWindowGui.handleEvent(*event);

            if (event->is<sf::Event::Closed>())
                mainWindow.close();
        }

        mainWindow.clear();
        mainWindowGui.draw();
        mainWindow.display();
    }

    return 0;
}
*/