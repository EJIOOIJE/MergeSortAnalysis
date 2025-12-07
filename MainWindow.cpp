#include "MainWindow.h"
#include "LoginWidget.h"

MainWindow::MainWindow(const sf::Vector2u& windowSize)
    : BaseWindow(windowSize)
{
    createWindow(windowSize);
    window.setFramerateLimit(60);
    gui.setWindow(window);
    prepareWidget();
}

void MainWindow::createWindow(const sf::Vector2u& windowSize) {
    window.create(
        sf::VideoMode({ windowSize.x, windowSize.y }),
        "Log in to application",
        sf::Style::Titlebar | sf::Style::Close,
        sf::State::Windowed
    );
    gui.setTarget(window);
    widget = std::make_unique<LoginWidget>();
}

void MainWindow::handleEvent(const sf::Event& event) {

}