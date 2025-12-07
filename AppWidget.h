#pragma once
#include "BaseWidget.h"
#include "SortData.h"
#include "SortResult.h"
#include "SortParams.h"
#include <functional>

class AppWidget : public BaseWidget {
public:
    struct WindowParams {
        sf::Vector2u windowSize{ 1280, 720 };
        std::string headerText{ "Data sort" };

        std::array<std::string, 3> leftLabels{ "N", "A", "C" };

        std::string rightContainer1Header{ "Original array" };
        std::string rightContainer2Header{ "Sorted array" };

        std::array<std::string, 3> bottomLabels{ "Execution time", "Number of comparisons", "Number of permutations" };

        std::array<std::string, 6> buttonTexts{ "Sort", "Save", "Load", "Clear","Connection equation", "Exit" };
    };

    AppWidget();
    ~AppWidget() override;

    void show(tgui::Gui& gui) override;
    tgui::Container::Ptr getRootWidget() const;
    void assignParameters() override;

protected:
    void create() override;

private:
    WindowParams windowParams;

    tgui::Label::Ptr headerLabel;

    tgui::EditBox::Ptr leftEditBoxes[3];
    tgui::Label::Ptr leftLabels[3];

    tgui::Label::Ptr rightHeaders[2];
    tgui::ScrollablePanel::Ptr rightTables[2];
    tgui::VerticalLayout::Ptr tableContent[2];
    tgui::Scrollbar::Ptr rightScrollbars[2];
    SortableArray orig;
    SortableArray sorted;
    SortResult res;
    SortParams params;

    tgui::EditBox::Ptr bottomEditBoxes[3];
    tgui::Label::Ptr bottomLabels[3];

    tgui::Button::Ptr buttons[6];
};