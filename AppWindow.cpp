#include "AppWindow.h"
#include "AppWidget.h"

AppWindow::AppWindow(const sf::Vector2u& windowSize)
    : BaseWindow(windowSize)
{
    createWindow(windowSize);
    window.setFramerateLimit(60);
    gui.setWindow(window);
    prepareWidget();
}

void AppWindow::createWindow(const sf::Vector2u& windowSize) {
    window.create(
        sf::VideoMode({ windowSize.x, windowSize.y }),
        "Method Merge Sort",
        sf::Style::Titlebar | sf::Style::Close,
        sf::State::Windowed
    );
    gui.setTarget(window);
    widget = std::make_unique<AppWidget>();
}

void AppWindow::handleEvent(const sf::Event& event) {

}