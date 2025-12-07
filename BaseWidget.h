#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class BaseWidget {
public:
    struct WindowParams { sf::Vector2u windowSize{ 0, 0 }; };

    BaseWidget();
    virtual ~BaseWidget();

    BaseWidget(const BaseWidget&) = delete;
    BaseWidget& operator=(const BaseWidget&) = delete;

    virtual void show(tgui::Gui& gui);

    void update();
    void update(const WindowParams& params);

    virtual void assignParameters() {}

    tgui::Container::Ptr getWidget() const;

protected:
    tgui::Container::Ptr widget;

    void removeWidgets();

    void deleteWidgets();

    virtual void create();
private:
    WindowParams windowParams;
};