#include "BaseWindow.h"

BaseWindow::BaseWindow(const sf::Vector2u& windowSize) {
    createWindow(windowSize);
    window.setFramerateLimit(60);
    gui.setWindow(window);
    prepareWidget();
}

void BaseWindow::createWindow(const sf::Vector2u& windowSize) {
    window.create(
        sf::VideoMode({ windowSize.x, windowSize.y }),
        "TGUI example - SFML_GRAPHICS backend",
        sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close,
        sf::State::Windowed
    );
    gui.setTarget(window);
    widget = std::make_unique<BaseWidget>();
}

BaseWindow::~BaseWindow() {
    window.close();
}

tgui::Gui& BaseWindow::getGui() {
    return gui;
}

sf::RenderWindow& BaseWindow::getWindow() {
    return window;
}

BaseWidget& BaseWindow::getWidget() {
    return *widget;
}

void BaseWindow::update() {
    if (widget) {
        widget->update();
    }
}

void BaseWindow::update(const BaseWidget::WindowParams& params) {
    if (widget) {
        widget->update(params);
    }
}

void BaseWindow::show() {
    if (widget)
        widget->show(gui);
}

void BaseWindow::handleEvent(const sf::Event& event) {

}

void BaseWindow::setSize(const sf::Vector2u& newSize) {
    size = newSize;
    window.setSize(sf::Vector2u(newSize.x, newSize.y));
}

void BaseWindow::setTitle(const std::string& title) {
    window.setTitle(title);
}

void BaseWindow::stop() {
    window.close();
}

void BaseWindow::prepareWidget() {
    widget->update();
    widget->show(gui);
}

void BaseWindow::setWidget(std::unique_ptr<BaseWidget> newWidget) {
    widget = std::move(newWidget);

    if (widget) {
        prepareWidget();
    }
}

std::unique_ptr<BaseWidget> BaseWindow::releaseWidget() {
    return std::move(widget);
}