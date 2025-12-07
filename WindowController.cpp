#include "WindowController.h"
#include <iostream>

WindowController::WindowController() : isRunning(false) {

}

WindowController::~WindowController() {
    for (auto& pair : windows) {
        auto& windowPtr = pair.second;
        if (windowPtr->getWindow().isOpen()) {
            windowPtr->getWindow().close();
        }
    }
}

void WindowController::addWindow(const std::string& id, std::shared_ptr<BaseWindow> window) {
    auto it = windows.find(id);
    if (it != windows.end()) {
        window->stop();
        return;
    }

    windows[id] = std::move(window);
}

void WindowController::removeWindow(const std::string& id) {
    windowsToRemove.push_back(id);
}

void WindowController::processRemovals() {
    for (const auto& id : windowsToRemove) {
        auto it = windows.find(id);
        if (it != windows.end()) {
            it->second->getWindow().close();
        }
        windows.erase(id);
    }
    windowsToRemove.clear();
}

void WindowController::start() {
    isRunning = true;
    while (isRunning && !windows.empty())
    {
        bool open = false;
        for (auto& pair : windows)
        {
            auto& container = pair.second;
            sf::RenderWindow& window = container->getWindow();
            tgui::Gui& gui = container->getGui();
            BaseWidget& widget = container->getWidget();

            if (window.isOpen()) {
                open = true;
                window.setActive(true);

                while (const std::optional event = window.pollEvent())
                {
                    auto eventHandler = gui.handleEvent(*event);

                    if (event->is<sf::Event::Closed>()) {
                        removeWindow(pair.first);
                    }

                    container->handleEvent(*event);
                }

                try {
                    if (&widget != nullptr)
                        widget.assignParameters();
                }
                catch (const std::exception& ex) {
                    std::cout << "Exception in assignParameters: " << ex.what() << std::endl;
                }
                catch (...) {
                    std::cout << "Unknown exception in assignParameters" << std::endl;
                }

                window.clear();
                gui.draw();
                window.display();
            }
        }

        processRemovals();
        isRunning = open;
        sf::sleep(sf::milliseconds(16));
    }
}

void WindowController::stop() {
    isRunning = false;
}

void WindowController::update(const std::string& id) {
    auto it = windows.find(id);
    if (it != windows.end()) {
        it->second->update();
    }
}

void WindowController::update(const std::string& id, const BaseWidget::WindowParams& params) {
    auto it = windows.find(id);
    if (it != windows.end()) {
        it->second->update(params);
    }
}

void WindowController::setSize(const std::string& id, const sf::Vector2u& newSize) {
    auto it = windows.find(id);
    if (it != windows.end()) {
        it->second->setSize(newSize);
    }
}

void WindowController::setTitle(const std::string& id, const std::string& title) {
    auto it = windows.find(id);
    if (it != windows.end()) {
        it->second->setTitle(title);
    }
}

void WindowController::setWidget(const std::string& id, std::unique_ptr<BaseWidget> newWidget) {
    auto it = windows.find(id);
    if (it != windows.end()) {
        it->second->setWidget(std::move(newWidget));
    }
}

void WindowController::swapWidgets(const std::string& id, std::unique_ptr<BaseWidget>& newWidget) {
    auto it = windows.find(id);
    if (it != windows.end()) {
        std::unique_ptr<BaseWidget> oldWidget = it->second->releaseWidget();
        it->second->setWidget(std::move(newWidget));
        newWidget = std::move(oldWidget);
    }
}