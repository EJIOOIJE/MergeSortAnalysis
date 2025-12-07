#pragma once
#include "BaseWindow.h"

class AppWindow : public BaseWindow {
public:
    AppWindow(const sf::Vector2u& windowSize);
    ~AppWindow() override = default;

protected:
    void createWindow(const sf::Vector2u& windowSize) override;
    void handleEvent(const sf::Event& event) override;
};