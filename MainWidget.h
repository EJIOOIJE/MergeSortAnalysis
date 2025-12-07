#pragma once
#include "BaseWidget.h"
#include <functional>
#include "Globals.h"

class MainWidget : public BaseWidget {
public:
    struct WindowParams {
        sf::Vector2u windowSize{ 1280, 720 };
        std::string techSpecButtonText{ "T\ne\nc\nh\nn\ni\nc\na\nl\n \nS\np\ne\nc\ni\nf\ni\nc\na\nt\ni\no\nn" };
        std::string appButtonText{ "A\np\np\nl\ni\nc\na\nt\ni\no\nn" };
        std::string exitButtonText{ "E\nx\ni\nt" };
        std::string imagePath{ (IMG_FOLDER / "front.png").string() };
    };

    MainWidget();
    ~MainWidget() override;

    void show(tgui::Gui& gui) override;
    tgui::Container::Ptr getRootWidget() const;
    void assignParameters() override;

protected:
    void create() override;

private:
    WindowParams windowParams;

    tgui::Button::Ptr techSpecButton;
    tgui::Button::Ptr appButton;
    tgui::Button::Ptr exitButton;
    tgui::Picture::Ptr centerImage;
    sf::Texture sftexture;
    tgui::Texture tgtexture;
};