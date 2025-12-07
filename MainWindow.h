#pragma once

#include "BaseWindow.h"

class MainWindow : public BaseWindow {
public:
    MainWindow(const sf::Vector2u& windowSize);
    ~MainWindow() override = default;

protected:
    void createWindow(const sf::Vector2u& windowSize) override;
    void handleEvent(const sf::Event& event) override;
};