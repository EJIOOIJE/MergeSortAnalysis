#pragma once
#include <unordered_map>
#include <memory>
#include "BaseWindow.h"

class WindowController {
public:
    WindowController();
    ~WindowController();

    void stop();

    void addWindow(const std::string& id, std::shared_ptr<BaseWindow> window);

    void removeWindow(const std::string& id);

    void start();

    void update(const std::string& id);

    void update(const std::string& id, const BaseWidget::WindowParams& params);

    void setSize(const std::string& id, const sf::Vector2u& newSize);

    void setTitle(const std::string& id, const std::string& title);

    void setWidget(const std::string& id, std::unique_ptr<BaseWidget> newWidget);

    void swapWidgets(const std::string& id, std::unique_ptr<BaseWidget>& newWidget);

private:
    std::unordered_map<std::string, std::shared_ptr<BaseWindow>> windows;
    bool isRunning;
    std::vector<std::string> windowsToRemove;

    void processRemovals();
};