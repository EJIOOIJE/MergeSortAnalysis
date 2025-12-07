#pragma once
#ifndef EQUATIONWIDGET_H
#define EQUATIONWIDGET_H

#include "BaseWidget.h"
#include "EquationData.h"

class EquationWidget : public BaseWidget {
public:
    struct WindowParams {
        sf::Vector2u windowSize{ 1280, 720 };
        std::string headerText{ "Regression coefficient estimation" };
    };

    EquationWidget();
    ~EquationWidget() override;

    void show(tgui::Gui& gui) override;
    tgui::Container::Ptr getRootWidget() const;
    void assignParameters() override;

protected:
    void create() override;

private:
    WindowParams windowParams;
    EquationData data;

    tgui::Label::Ptr headerLabel;
    tgui::ScrollablePanel::Ptr table;
    tgui::VerticalLayout::Ptr tableContent;
    tgui::VerticalLayout::Ptr rightContainer;
    tgui::EditBox::Ptr sizeeditbox;

    tgui::EditBox::Ptr firstRow[2];
    tgui::EditBox::Ptr secondRow[2];
    tgui::EditBox::Ptr thirdRow[2];
    tgui::EditBox::Ptr forthRow[2];

    tgui::Picture::Ptr image;
    sf::Texture sftexture;
    tgui::Texture tgtexture;
};

#endif // EQUATIONWIDGET_H