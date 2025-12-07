#pragma once
#include "BaseWindow.h"

class EquationWindow : public BaseWindow {
public:
    EquationWindow(const sf::Vector2u& windowSize);
    ~EquationWindow() override = default;

protected:
    void createWindow(const sf::Vector2u& windowSize) override;
    void handleEvent(const sf::Event& event) override;
};