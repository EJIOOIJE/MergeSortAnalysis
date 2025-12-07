#include "BaseWidget.h"

BaseWidget::BaseWidget() {

}

BaseWidget::~BaseWidget() {
    deleteWidgets();
}

void BaseWidget::show(tgui::Gui& gui) {
    if (widget)
        gui.add(widget);
}

tgui::Container::Ptr BaseWidget::getWidget() const {
    return widget;
}

void BaseWidget::update() {
    removeWidgets();
    create();
    assignParameters();
}

void BaseWidget::update(const WindowParams& params) {
    windowParams = params;
    update();
}

void BaseWidget::removeWidgets() {
    if (widget)
        widget->removeAllWidgets();
}

void BaseWidget::deleteWidgets() {
    if (widget) {
        widget->removeAllWidgets();
        widget.reset();
    }
}

void BaseWidget::create() {

}