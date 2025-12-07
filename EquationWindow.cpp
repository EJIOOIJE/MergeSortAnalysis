#include "EquationWindow.h"
#include "EquationWidget.h"

EquationWindow::EquationWindow(const sf::Vector2u& windowSize)
    : BaseWindow(windowSize)
{
    createWindow(windowSize);
    window.setFramerateLimit(60);
    gui.setWindow(window);
    prepareWidget();
}

void EquationWindow::createWindow(const sf::Vector2u& windowSize) {
    window.create(
        sf::VideoMode({ windowSize.x, windowSize.y }),
        "Connection equation",
        sf::Style::Titlebar | sf::Style::Close,
        sf::State::Windowed
    );
    gui.setTarget(window);
    widget = std::make_unique<EquationWidget>();
}

void EquationWindow::handleEvent(const sf::Event& event) {

}