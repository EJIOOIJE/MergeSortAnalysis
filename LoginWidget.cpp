#include "LoginWidget.h"
#include "MainWidget.h"
#include "WindowController.h"
#include "UserController.h"
#include "Globals.h"
#include <windows.h>
#include <commdlg.h> 

LoginWidget::LoginWidget() {

}

LoginWidget::~LoginWidget() {

}

void LoginWidget::assignParameters() {
    if (!widget)
        return;

    widget->setSize({ static_cast<float>(windowParams.windowSize.x), static_cast<float>(windowParams.windowSize.y) });

    if (loginEdit)
        loginEdit->setDefaultText(windowParams.loginDefaultText);
    if (passwordEdit)
        passwordEdit->setDefaultText(windowParams.passwordDefaultText);
    if (loginButton)
        loginButton->setText(windowParams.loginButtonText);
    if (exitButton)
        exitButton->setText(windowParams.exitButtonText);
}

void LoginWidget::create() {
    widget = tgui::Group::create();
    widget->setSize({ static_cast<float>(windowParams.windowSize.x), static_cast<float>(windowParams.windowSize.y) });

    auto mainLayout = tgui::VerticalLayout::create();
    mainLayout->setSize({ "80%", "80%" });
    mainLayout->setPosition({ "10%", "10%" });
    widget->getRenderer()->setTextSize(24);
    widget->add(mainLayout);

    auto formLayout = tgui::VerticalLayout::create();
    formLayout->setSize({ "100%", "50%" });
    formLayout->getRenderer()->setSpaceBetweenWidgets(10);
    mainLayout->add(formLayout);

    loginEdit = tgui::EditBox::create();
    loginEdit->setSize({ "50%", 30 });
    loginEdit->setDefaultText(windowParams.loginDefaultText);
    formLayout->add(loginEdit, "login");

    passwordEdit = tgui::EditBox::create();
    passwordEdit->setSize({ "50%", 30 });
    passwordEdit->setPasswordCharacter('*');
    passwordEdit->setDefaultText(windowParams.passwordDefaultText);
    formLayout->add(passwordEdit, "password");

    auto spacer = tgui::Label::create();
    spacer->setSize({ "100%", "100%" });
    mainLayout->add(spacer, "spacer");

    auto buttonLayout = tgui::HorizontalLayout::create();
    buttonLayout->setSize({ "30%", "20%" });
    buttonLayout->setPosition({ "0%", "80%" });
    buttonLayout->getRenderer()->setSpaceBetweenWidgets(20);
    mainLayout->add(buttonLayout);

    loginButton = tgui::Button::create(windowParams.loginButtonText);
    loginButton->setSize({ "20%", 40 });
    buttonLayout->add(loginButton);

    exitButton = tgui::Button::create(windowParams.exitButtonText);
    exitButton->setSize({ "20%", 40 });
    buttonLayout->add(exitButton);

    exitButton->onClick([this]() {
        G_WC.removeWindow("MainWindow");
    }); 

    loginButton->onClick([this]() { triggerLogin(); });
}

void LoginWidget::show(tgui::Gui& gui) {
    BaseWidget::show(gui);
}

tgui::Container::Ptr LoginWidget::getRootWidget() const {
    return widget;
}

void LoginWidget::triggerLogin() {
    std::string inputLogin = loginEdit->getText().toStdString();
    std::string inputPassword = passwordEdit->getText().toStdString();

    User tempUser = G_UC.createUser(inputLogin, inputLogin, inputPassword, false);
    std::string filename = G_UC.getFileName(tempUser);
    std::string fullPath = (USER_FOLDER / filename).string();

    if (inputLogin.empty() && inputPassword.empty()) {
        MessageBoxA(
            nullptr,
            "Input login data",
            "Error",
            MB_OK | MB_ICONERROR
        );
        return;
    }

    if (!fs::exists(fullPath)) {
        MessageBoxA(
            nullptr,
            ("There is no such user with login: " + inputLogin).c_str(),
            "Error",
            MB_OK | MB_ICONERROR
        );
        return;
    }

    User loadedUser;
    if (!G_UC.loadUser(loadedUser, filename)) {
        MessageBoxA(
            nullptr,
            "Eroor loading user data",
            "Error",
            MB_OK | MB_ICONERROR
        );
        return;
    }

    if (!tempUser.isEqualTo(loadedUser)) {
        MessageBoxA(
            nullptr,
            "Incorrect login data",
            "Error",
            MB_OK | MB_ICONERROR
        );
        return;
    }

    G_USER = loadedUser;

    std::unique_ptr<BaseWidget> newWidget = std::make_unique<MainWidget>();
    G_WC.setWidget("MainWindow", std::move(newWidget));
    G_WC.setTitle("MainWindow", "Course paper");
}