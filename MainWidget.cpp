#include "MainWidget.h"
#include "WindowController.h"  
#include "Windows.h"
#include "Globals.h" 

MainWidget::MainWidget() {

}

MainWidget::~MainWidget() {

}

void MainWidget::assignParameters() {
    if (!widget)
        return;

    widget->setSize({ (float)windowParams.windowSize.x, (float)windowParams.windowSize.y });

    if (techSpecButton)
        techSpecButton->setText(windowParams.techSpecButtonText);
    if (appButton)
        appButton->setText(windowParams.appButtonText);
    if (exitButton)
        exitButton->setText(windowParams.exitButtonText);
}

void MainWidget::create() {
    widget = tgui::Group::create();
    widget->setSize({ (float)windowParams.windowSize.x, (float)windowParams.windowSize.y });

    auto techButton = tgui::Button::create(windowParams.techSpecButtonText);
    auto& techRenderer = *techButton->getRenderer();
    techRenderer.setTextSize(18);
    techButton->setSize({ "10%", "100%" });
    techButton->setPosition({ "0%", "0%" });
    widget->add(techButton);

    auto rightButtonsContainer = tgui::VerticalLayout::create();
    rightButtonsContainer->setSize({ "10%", "100%" });
    rightButtonsContainer->setPosition({ "90%", "0%" });
    widget->add(rightButtonsContainer);

    appButton = tgui::Button::create(windowParams.appButtonText);
    auto& appRenderer = *appButton->getRenderer();
    appRenderer.setTextSize(18);
    appButton->setSize({ "100%", "10%" });
    rightButtonsContainer->add(appButton);

    auto verticalSpacer = tgui::Label::create();
    verticalSpacer->setSize({ "100%", "80%" });
    rightButtonsContainer->add(verticalSpacer);

    exitButton = tgui::Button::create(windowParams.exitButtonText);
    auto& exitRenderer = *exitButton->getRenderer();
    exitRenderer.setTextSize(18);
    exitButton->setSize({ "100%", "10%" });
    rightButtonsContainer->add(exitButton);

    sftexture.loadFromFile(windowParams.imagePath);
    tgtexture = tgui::Texture::Texture();
    tgtexture.loadFromPixelData(
        sftexture.getSize(),
        sftexture.copyToImage().getPixelsPtr()
    );
    centerImage = tgui::Picture::create();
    centerImage->getRenderer()->setTexture(tgtexture);
    centerImage->setSize({ "80%", "100%" });
    centerImage->setPosition({ "10%", "0%" });
    widget->add(centerImage);

    exitButton->onClick([this]() {
        G_WC.removeWindow("MainWindow");
    });

    appButton->onClick([this]() {
        auto tech = std::make_shared<AppWindow>(sf::Vector2u(1280, 720));
        G_WC.addWindow("AppWindow", tech);
    });

    techButton->onClick([this]() {
        auto tech = std::make_shared<TechWindow>(sf::Vector2u(1280, 720));
        G_WC.addWindow("TechWindow", tech);
    });
}

void MainWidget::show(tgui::Gui& gui) {
    BaseWidget::show(gui);
}

tgui::Container::Ptr MainWidget::getRootWidget() const {
    return widget;
}