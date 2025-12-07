#pragma once
#include "BaseWidget.h"
#include <functional>
#include "Globals.h"

class TechWidget : public BaseWidget {
public:
    struct WindowParams {
        sf::Vector2u windowSize{ 1280, 720 };
        std::string centerText{
            "Data sorting. Merge sort method.\nProbability distribution law of random\nvariables 'Fisk'."
        };
        std::string exitButtonText{ "Exit" };
        std::string leftImagePath{ (IMG_FOLDER / "left.png").string() };
        std::string rightImagePath{ (IMG_FOLDER / "right.png").string() };
    };

    TechWidget();
    ~TechWidget() override;

    void show(tgui::Gui& gui) override;
    tgui::Container::Ptr getRootWidget() const;
    void assignParameters() override;

protected:
    void create() override;

private:
    WindowParams windowParams;

    tgui::Label::Ptr centerTextLabel;
    tgui::Button::Ptr exitButton;
    tgui::Picture::Ptr leftImage;
    tgui::Picture::Ptr rightImage;
    tgui::Group::Ptr centerImageGroup;
    sf::Texture sftexture1;
    tgui::Texture tgtexture1;
    sf::Texture sftexture2;
    tgui::Texture tgtexture2;
};