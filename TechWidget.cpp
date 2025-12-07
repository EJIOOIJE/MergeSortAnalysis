#include "TechWidget.h"
#include "WindowController.h"
#include "Globals.h" 

TechWidget::TechWidget() {

}

TechWidget::~TechWidget() {

}

void TechWidget::assignParameters() {
    if (!widget) return;

    widget->setSize({ (float)windowParams.windowSize.x, (float)windowParams.windowSize.y });

    if (centerTextLabel)
        centerTextLabel->setText(windowParams.centerText);
    if (exitButton)
        exitButton->setText(windowParams.exitButtonText);
}

void TechWidget::create() {
    widget = tgui::Group::create();
    widget->setSize({ (float)windowParams.windowSize.x, (float)windowParams.windowSize.y });

    centerTextLabel = tgui::Label::create();
    centerTextLabel->setText(windowParams.centerText);
    centerTextLabel->setSize({ "100%", "12%" });
    centerTextLabel->setPosition({ "0%", "2%" });
    centerTextLabel->getRenderer()->setTextSize(22);
    centerTextLabel->getRenderer()->setTextColor(sf::Color::Yellow);
    centerTextLabel->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    centerTextLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
    widget->add(centerTextLabel);

    centerImageGroup = tgui::Group::create();
    centerImageGroup->setSize({ "95%", "70%" });
    centerImageGroup->setPosition({ "2.5%", "20%" });
    widget->add(centerImageGroup);

    sftexture1.loadFromFile(windowParams.leftImagePath);
    tgtexture1 = tgui::Texture::Texture();
    tgtexture1.loadFromPixelData(
        sftexture1.getSize(),
        sftexture1.copyToImage().getPixelsPtr()
    );
    leftImage = tgui::Picture::create();
    leftImage->getRenderer()->setTexture(tgtexture1);
    leftImage->setSize({ "48%", "100%" });
    leftImage->setPosition({ "0%", "0%" });
    centerImageGroup->add(leftImage);

    sftexture2.loadFromFile(windowParams.leftImagePath);
    tgtexture2 = tgui::Texture::Texture();
    tgtexture2.loadFromPixelData(
        sftexture2.getSize(),
        sftexture2.copyToImage().getPixelsPtr()
    );
    rightImage = tgui::Picture::create();
    rightImage->getRenderer()->setTexture(tgtexture1);
    rightImage->setSize({ "48%", "100%" });
    rightImage->setPosition({ "52%", "0%" });
    centerImageGroup->add(rightImage);

    exitButton = tgui::Button::create(windowParams.exitButtonText);
    exitButton->getRenderer()->setTextSize(20);
    exitButton->setSize({ "20%", "6%" });
    exitButton->setPosition({ "40%", "92%" });
    widget->add(exitButton);

    exitButton->onClick([this]() {
        G_WC.removeWindow("TechWindow");
        });
}

void TechWidget::show(tgui::Gui& gui) {
    BaseWidget::show(gui);
}

tgui::Container::Ptr TechWidget::getRootWidget() const {
    return widget;
}