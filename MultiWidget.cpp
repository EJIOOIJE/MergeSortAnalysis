#include "MultiWidget.h"

MultiWidget::MultiWidget() {}

MultiWidget::~MultiWidget() {}

void MultiWidget::addWidget(std::shared_ptr<BaseWidget> widget) {
    widgets.push_back(widget);
}

const std::vector<std::shared_ptr<BaseWidget>>& MultiWidget::getWidgets() const {
    return widgets;
}

void MultiWidget::show(tgui::Gui& gui) {
    BaseWidget::show(gui);
}

void MultiWidget::update() {
    removeWidgets();
    for (auto& w : widgets) {
        w->update();
    }
}

void MultiWidget::update(std::shared_ptr<BaseWidget> widget) {
    if (widget) {
        widget->update();
    }
}

void MultiWidget::update(std::shared_ptr<BaseWidget> widget, const WindowParams& params) {
    if (widget) {
        widget->update(params);
    }
}