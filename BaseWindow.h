#pragma once
#include <memory>
#include "BaseWidget.h"

class BaseWindow {
public:
    BaseWindow(const sf::Vector2u& windowSize);
    virtual ~BaseWindow();

    void update();

    void update(const BaseWidget::WindowParams& params);

    void show();

    tgui::Gui& getGui();

    sf::RenderWindow& getWindow();

    BaseWidget& getWidget();

    virtual void handleEvent(const sf::Event& event);

    void setSize(const sf::Vector2u& newSize);

    void setTitle(const std::string& title);

    void stop();

    void setWidget(std::unique_ptr<BaseWidget> newWidget);

    std::unique_ptr<BaseWidget> releaseWidget();

protected:
    sf::RenderWindow window;
    tgui::Gui gui;
    std::unique_ptr<BaseWidget> widget;
    sf::Vector2u size;

    virtual void createWindow(const sf::Vector2u& windowSize);
    void prepareWidget();
};