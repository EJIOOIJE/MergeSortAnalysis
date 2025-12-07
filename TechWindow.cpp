#include "TechWindow.h"
#include "TechWidget.h"

TechWindow::TechWindow(const sf::Vector2u& windowSize)
    : BaseWindow(windowSize)
{
    createWindow(windowSize);
    window.setFramerateLimit(60);
    gui.setWindow(window);
    prepareWidget();
}

void TechWindow::createWindow(const sf::Vector2u& windowSize) {
    window.create(
        sf::VideoMode({ windowSize.x, windowSize.y }),
        "Technical specification",
        sf::Style::Titlebar | sf::Style::Close,
        sf::State::Windowed
    );
    gui.setTarget(window);
    widget = std::make_unique<TechWidget>();
}

void TechWindow::handleEvent(const sf::Event& event) {

}