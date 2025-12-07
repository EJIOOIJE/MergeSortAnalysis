#pragma once
#include "BaseWidget.h"
#include <vector>
#include <memory>

class MultiWidget : public BaseWidget {
public:
    struct WindowParams : public BaseWidget::WindowParams {

    };

    MultiWidget();
    ~MultiWidget() override;

    void addWidget(std::shared_ptr<BaseWidget> widget);
    const std::vector<std::shared_ptr<BaseWidget>>& getWidgets() const;

    void show(tgui::Gui& gui) override;
    void update();

    void update(std::shared_ptr<BaseWidget> widget);
    void update(std::shared_ptr<BaseWidget> widget, const WindowParams& params);
private:
    std::vector<std::shared_ptr<BaseWidget>> widgets;
};