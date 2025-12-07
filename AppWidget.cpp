#include "WindowController.h"  
#include "EquationWidget.h"
#include "EquationWindow.h"
#include "Globals.h"
#include "AppWidget.h"
#include "Algorithm.h"
#include "functions.h"
#include <windows.h>
#include <commdlg.h> 

AppWidget::AppWidget() {
}

AppWidget::~AppWidget() {
}

void AppWidget::assignParameters() {
    if (!widget)
        return;

    widget->setSize({ static_cast<float>(windowParams.windowSize.x), static_cast<float>(windowParams.windowSize.y) });

    if (headerLabel) {
        headerLabel->setText(windowParams.headerText);
        headerLabel->getRenderer()->setTextColor(tgui::Color::Yellow);
    }

    for (int i = 0; i < 3; ++i) {
        if (leftLabels[i]) {
            leftLabels[i]->setText(windowParams.leftLabels[i]);
            leftLabels[i]->getRenderer()->setTextColor(tgui::Color::Yellow);
        }
        if (bottomLabels[i]) {
            bottomLabels[i]->setText(windowParams.bottomLabels[i]);
            bottomLabels[i]->getRenderer()->setTextColor(tgui::Color::Yellow);
        }
    }

    if (rightHeaders[0]) {
        rightHeaders[0]->setText(windowParams.rightContainer1Header);
        rightHeaders[0]->getRenderer()->setTextColor(tgui::Color::Yellow);
    }
    if (rightHeaders[1]) {
        rightHeaders[1]->setText(windowParams.rightContainer2Header);
        rightHeaders[1]->getRenderer()->setTextColor(tgui::Color::Yellow);
    }

    for (int i = 0; i < 6; ++i) {
        if (buttons[i])
            buttons[i]->setText(windowParams.buttonTexts[i]);
    }

    const int rowHeight = 30;
    for (int col = 0; col < 2; ++col) {
        tableContent[col]->removeAllWidgets();

        std::vector<double> data = (col == 0) ? orig.getData() : sorted.getData();
        long long  n = data.size();
        for (long long i = 0; i < n; ++i) {
            auto row = tgui::HorizontalLayout::create();
            row->setSize("100%", rowHeight);
            row->getRenderer()->setSpaceBetweenWidgets(0);

            auto cell1 = tgui::Label::create(std::to_string(i));
            cell1->setSize("50%", rowHeight);
            cell1->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);

            auto cell2 = tgui::Label::create(dtoslim(data[i], 4));
            cell2->setSize("50%", rowHeight);
            cell2->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);

            row->add(cell1);
            row->add(cell2);

            tableContent[col]->add(row);
        }
        float totalHeight = rowHeight * n;
        tableContent[col]->setSize("100%", totalHeight);
        rightTables[col]->setContentSize({ tableContent[col]->getSize().x, totalHeight });
    }

    if (bottomEditBoxes[0] && (res.elapsedTimeMs.count() > 0)) {
        bottomEditBoxes[0]->setText(std::to_string(static_cast<long long>(res.elapsedTimeMs.count())) + " мс");
    }

    if (bottomEditBoxes[1] && (res.comparisons > 0)) {
        bottomEditBoxes[1]->setText(std::to_string(res.comparisons));
    }

    if (bottomEditBoxes[2] && (res.swaps > 0)) {
        bottomEditBoxes[2]->setText(std::to_string(res.swaps));
    }

    if (leftEditBoxes[0] && (params.N > 0)) {
        leftEditBoxes[0]->setText(std::to_string(params.N));
    }

    if (leftEditBoxes[1] && (params.A > 0)) {
        leftEditBoxes[1]->setText(std::to_string(params.A));
    }

    if (leftEditBoxes[2] && (params.C > 0)) {
        leftEditBoxes[2]->setText(std::to_string(params.C));
    }
}

void AppWidget::create() {
    widget = tgui::Group::create();
    widget->setSize({ static_cast<float>(windowParams.windowSize.x), static_cast<float>(windowParams.windowSize.y) });

    auto mainLayout = tgui::VerticalLayout::create();
    mainLayout->setSize("100%", "100%");
    mainLayout->setPosition(0, 0);
    mainLayout->getRenderer()->setSpaceBetweenWidgets(5);
    mainLayout->getRenderer()->setPadding({ 10, 10, 10, 10 });
    widget->add(mainLayout);

    headerLabel = tgui::Label::create(windowParams.headerText);
    headerLabel->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    headerLabel->setTextSize(24);
    headerLabel->setSize("100%", "5%");
    mainLayout->add(headerLabel, "header");

    auto middleContainer = tgui::HorizontalLayout::create();
    middleContainer->setSize("100%", "55%");
    middleContainer->getRenderer()->setSpaceBetweenWidgets(10);
    mainLayout->add(middleContainer, "middleContainer");

    auto leftContainer = tgui::HorizontalLayout::create();
    leftContainer->setSize("30%", "100%");
    middleContainer->add(leftContainer);

    auto leftLabelColumn = tgui::VerticalLayout::create();
    leftLabelColumn->setSize("30%", "100%");
    leftLabelColumn->getRenderer()->setSpaceBetweenWidgets(15);
    leftContainer->add(leftLabelColumn);

    auto leftEditColumn = tgui::VerticalLayout::create();
    leftEditColumn->setSize("70%", "100%");
    leftEditColumn->getRenderer()->setSpaceBetweenWidgets(10);
    leftContainer->add(leftEditColumn);

    for (int i = 0; i < 3; ++i) {
        leftLabels[i] = tgui::Label::create(windowParams.leftLabels[i]);
        leftLabels[i]->setSize("100%", 30);
        leftLabels[i]->setTextSize(24);
        leftLabels[i]->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);
        leftLabelColumn->add(leftLabels[i]);

        leftEditBoxes[i] = tgui::EditBox::create();
        leftEditBoxes[i]->setSize("100%", 30);
        leftEditBoxes[i]->setInputValidator(tgui::EditBox::Validator::All);
        leftEditColumn->add(leftEditBoxes[i]);
    }

    for (int col = 0; col < 2; ++col) {
        auto rightContainer = tgui::VerticalLayout::create();
        rightContainer->setSize("35%", "auto");
        rightContainer->getRenderer()->setSpaceBetweenWidgets(0);
        middleContainer->add(rightContainer);

        rightHeaders[col] = tgui::Label::create();
        rightHeaders[col]->setText(col == 0 ? windowParams.rightContainer1Header : windowParams.rightContainer2Header);
        rightHeaders[col]->setTextSize(18);
        rightHeaders[col]->setSize("100%", 20);
        rightHeaders[col]->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
        rightContainer->add(rightHeaders[col]);

        auto columnNamesContainer = tgui::HorizontalLayout::create();
        columnNamesContainer->setSize("100%", 20);
        columnNamesContainer->getRenderer()->setSpaceBetweenWidgets(5);

        auto columnLabel1 = tgui::Label::create("Number");
        columnLabel1->setSize("50%", 20);
        columnLabel1->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
        columnLabel1->getRenderer()->setTextColor(tgui::Color::Yellow);
        columnNamesContainer->add(columnLabel1);

        auto columnLabel2 = tgui::Label::create("Element");
        columnLabel2->setSize("50%", 20);
        columnLabel2->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
        columnLabel2->getRenderer()->setTextColor(tgui::Color::Yellow);
        columnNamesContainer->add(columnLabel2);

        rightContainer->add(columnNamesContainer);

        rightTables[col] = tgui::ScrollablePanel::create();
        rightTables[col]->setSize("100%", "auto");
        rightTables[col]->getRenderer()->setBorderColor(tgui::Color::Black);
        rightTables[col]->getRenderer()->setBorders({ 1, 1, 1, 1 });
        rightTables[col]->setVerticalScrollAmount(5);
        rightContainer->add(rightTables[col]);

        tableContent[col] = tgui::VerticalLayout::create();
        tableContent[col]->setSize("100%", "auto"); 
        rightTables[col]->add(tableContent[col]);
    }

    auto bottomTopContainer = tgui::HorizontalLayout::create();
    bottomTopContainer->setSize("100%", "20%");
    bottomTopContainer->getRenderer()->setSpaceBetweenWidgets(10);
    mainLayout->add(bottomTopContainer);

    auto bottomLabelsColumn = tgui::VerticalLayout::create();
    bottomLabelsColumn->setSize("35%", "100%");
    bottomLabelsColumn->getRenderer()->setSpaceBetweenWidgets(10);
    bottomTopContainer->add(bottomLabelsColumn);

    for (int i = 0; i < 3; ++i) {
        bottomLabels[i] = tgui::Label::create(windowParams.bottomLabels[i]);
        bottomLabels[i]->setSize("100%", 30);
        bottomLabels[i]->setTextSize(24);
        bottomLabels[i]->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);
        bottomLabelsColumn->add(bottomLabels[i]);
    }

    auto bottomEditColumn = tgui::VerticalLayout::create();
    bottomEditColumn->setSize("65%", "100%");
    bottomEditColumn->getRenderer()->setSpaceBetweenWidgets(10);
    bottomTopContainer->add(bottomEditColumn);

    for (int i = 0; i < 3; ++i) {
        bottomEditBoxes[i] = tgui::EditBox::create();
        bottomEditBoxes[i]->setSize("100%", 30);
        bottomEditBoxes[i]->setInputValidator(tgui::EditBox::Validator::All);
        bottomEditColumn->add(bottomEditBoxes[i]);
    }

    auto buttonContainer = tgui::HorizontalLayout::create();
    buttonContainer->setSize("100%", "2%");
    buttonContainer->getRenderer()->setSpaceBetweenWidgets(20);
    mainLayout->add(buttonContainer);

    for (int i = 0; i < 6; ++i) {
        buttons[i] = tgui::Button::create(windowParams.buttonTexts[i]);
        buttons[i]->setSize(70, 15);
        buttonContainer->add(buttons[i]);
    }

    buttons[5]->onClick([this]() {
        G_WC.removeWindow("AppWindow");
    });

    buttons[4]->onClick([this]() {
        auto equ = std::make_shared<EquationWindow>(sf::Vector2u(1280, 720));
        G_WC.addWindow("EquationWindow", equ);
    });

    buttons[3]->onClick([this]() {
        for (int i = 0; i < 3; ++i) {
            if (leftEditBoxes[i]) {
                leftEditBoxes[i]->setText("");
            }
        }

        for (int i = 0; i < 3; ++i) {
            if (bottomEditBoxes[i]) {
                bottomEditBoxes[i]->setText("");
            }
        }

        orig.clearData();
        sorted.clearData();
        res = SortResult{};
        params = SortParams{};
    });

    buttons[2]->onClick([this]() {
        std::string initialDir = ARRAY_FOLDER.string();
        std::wstring initialDirW = stringToWstring(initialDir);
        std::string filename;
        std::wstring filenameW;

        if (!fs::exists(initialDir)) {
            fs::create_directories(initialDir);
        }

        if (OpenFileDialog(filenameW, initialDirW)) {
            filename = wstringToString(filenameW);
            SortData pair;
            if (pair.loadJSON(filename)) {
                orig = pair.getFirst();
                sorted = pair.getSecond();
                res = pair.getSortResult();
                params = pair.getSortParams();
            }
            else {
                MessageBoxA(
                    nullptr,
                    ("Failed to read file: " + filename).c_str(),
                    "Error",
                    MB_OK | MB_ICONERROR
                );
            }
        }
    });

    buttons[1]->onClick([this]() {
        if (orig.getData().empty()) {
            MessageBoxA(
                nullptr,
                "Cannot save to file, empty data",
                "Error",
                MB_OK | MB_ICONERROR
            );
            return;
        }

        SortData pair(orig, sorted, res, params);
        std::string filename = pair.getFileName();
        std::string fullPath = pair.getFullName(filename);
        pair.saveJSON(fullPath);
    });

    buttons[0]->onClick([this]() {
        bool valueError = false;
        long long N;
        double A, C;

        if (leftEditBoxes[0]) {
            std::string value = leftEditBoxes[0]->getText().toStdString();
            if (is_long_long(value))
                N = std::stoll(value);
            else {
                valueError = true;
            }
        }

        if (leftEditBoxes[1]) {
            std::string value = leftEditBoxes[1]->getText().toStdString();
            if (is_double(value))
                A = std::stod(value);
            else {
                valueError = true;
            }
        }

        if (leftEditBoxes[2]) {
            std::string value = leftEditBoxes[2]->getText().toStdString();
            if (is_double(value))
                C = std::stod(value);
            else {
                valueError = true;
            }
        }

        if (valueError) {
            MessageBoxA(
                nullptr,
                "Incorrect data entered",
                "Error",
                MB_OK | MB_ICONERROR
            );
            return;
        }

        params = SortParams(N, A, C);
        orig.setData(Algorithm::generateFiskArray(N, A, C));
        std::vector<double> dataCopy = orig.getData();
        res = Algorithm::mergeSort(dataCopy);
        sorted.setData(dataCopy);
    });
}

void AppWidget::show(tgui::Gui& gui) {
    BaseWidget::show(gui);
}

tgui::Container::Ptr AppWidget::getRootWidget() const {
    return widget;
}