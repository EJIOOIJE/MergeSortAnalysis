#pragma once
#include "BaseWindow.h"

class TechWindow : public BaseWindow {
public:
    TechWindow(const sf::Vector2u& windowSize);
    ~TechWindow() override = default;

protected:
    void createWindow(const sf::Vector2u& windowSize) override;
    void handleEvent(const sf::Event& event) override;
};