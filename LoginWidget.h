#pragma once
#include "BaseWidget.h"
#include <functional>

class LoginWidget : public BaseWidget {
public:
    struct WindowParams {
        sf::Vector2u windowSize{ 1280, 720 };
        std::string loginDefaultText{ "Username" };
        std::string passwordDefaultText{ "Password" };
        std::string loginButtonText{ "Login" };
        std::string exitButtonText{ "Exit" };
    };

    LoginWidget();
    ~LoginWidget() override;

    void show(tgui::Gui& gui) override;

    tgui::Container::Ptr getRootWidget() const;
    void assignParameters() override;

protected:
    void create() override;

private:
    WindowParams windowParams;

    tgui::EditBox::Ptr loginEdit;
    tgui::EditBox::Ptr passwordEdit;
    tgui::Button::Ptr loginButton;
    tgui::Button::Ptr exitButton;

    void triggerLogin();
};