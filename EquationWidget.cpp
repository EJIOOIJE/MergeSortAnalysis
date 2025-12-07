#include "matplotlibcpp.h"
#include "EquationWidget.h"
#include "Globals.h"

namespace plt = matplotlibcpp;
namespace fs = std::filesystem;

EquationWidget::EquationWidget() {
}

EquationWidget::~EquationWidget() {
}

void EquationWidget::assignParameters() {
    if (!widget)
        return;

    widget->setSize({ static_cast<float>(windowParams.windowSize.x), static_cast<float>(windowParams.windowSize.y) });

    if (headerLabel) {
        headerLabel->setText(windowParams.headerText);
        headerLabel->getRenderer()->setTextColor(tgui::Color::Yellow);
    }

    const int rowHeight = 30;
    tableContent->removeAllWidgets();

    std::vector<long long> time = data.getTime();
    std::vector<long long> size = data.getSize();
    std::vector<long long> sqx = data.getSqx();
    std::vector<long long> xmulty = data.getXmulty();

    long long m = time.size();
    long long n = m - 1;
    for (long long i = 0; i < m; ++i) {

        auto row = tgui::HorizontalLayout::create();
        row->setSize("100%", rowHeight);
        row->getRenderer()->setSpaceBetweenWidgets(0);

        auto cell1 = tgui::Label::create((i == n) ? "Total" : std::to_string(i));
        cell1->setSize("20%", rowHeight);
        cell1->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);

        auto cell2 = tgui::Label::create(std::to_string(time[i]));
        cell2->setSize("20%", rowHeight);
        cell2->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);

        auto cell3 = tgui::Label::create(std::to_string(size[i]));
        cell3->setSize("20%", rowHeight);
        cell3->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);

        auto cell4 = tgui::Label::create(std::to_string(sqx[i]));
        cell4->setSize("20%", rowHeight);
        cell4->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);

        auto cell5 = tgui::Label::create(std::to_string(xmulty[i]));
        cell5->setSize("20%", rowHeight);
        cell5->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);

        row->add(cell1);
        row->add(cell2);
        row->add(cell3);
        row->add(cell4);
        row->add(cell5);

        tableContent->add(row);
    }
    float totalHeight = rowHeight * n;
    tableContent->setSize("100%", totalHeight);
    table->setContentSize({ tableContent->getSize().x, totalHeight });
}

void EquationWidget::create() {
    widget = tgui::Group::create();
    widget->setSize({ static_cast<float>(windowParams.windowSize.x), static_cast<float>(windowParams.windowSize.y) });

    auto mainLayout = tgui::VerticalLayout::create();
    mainLayout->setSize("100%", "100%");
    mainLayout->getRenderer()->setSpaceBetweenWidgets(10);
    mainLayout->getRenderer()->setPadding({ 10, 10, 10, 10 });
    widget->add(mainLayout);

    headerLabel = tgui::Label::create(windowParams.headerText);
    headerLabel->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    headerLabel->setTextSize(24);
    headerLabel->setSize("100%", 20);
    headerLabel->getRenderer()->setPadding({ 0, 0, 0, 0 });
    mainLayout->add(headerLabel, "header");

    auto middleContainer = tgui::HorizontalLayout::create();
    middleContainer->setSize("100%", "70%");
    middleContainer->getRenderer()->setSpaceBetweenWidgets(10);
    mainLayout->add(middleContainer, "middleContainer");

    auto leftContainer = tgui::VerticalLayout::create();
    leftContainer->setSize("50%", "100%");
    leftContainer->getRenderer()->setSpaceBetweenWidgets(0);
    middleContainer->add(leftContainer);

    auto topRow = tgui::HorizontalLayout::create();
    topRow->setSize("100%", 20);
    topRow->getRenderer()->setSpaceBetweenWidgets(10);
    topRow->getRenderer()->setPadding({ 0, 0, 0, 0 });
    leftContainer->add(topRow);

    auto labelInRow = tgui::Label::create("Sample size");
    labelInRow->setSize(50, 20);
    labelInRow->setTextSize(18);
    labelInRow->getRenderer()->setTextColor(tgui::Color::Yellow);
    topRow->add(labelInRow);

    sizeeditbox = tgui::EditBox::create();
    sizeeditbox->setSize(100, 20);
    sizeeditbox->setText(std::to_string(data.getN()));
    sizeeditbox->setInputValidator(tgui::EditBox::Validator::All);
    topRow->add(sizeeditbox);

    auto tableContainer = tgui::VerticalLayout::create();
    tableContainer->setSize("35%", "auto");
    tableContainer->getRenderer()->setSpaceBetweenWidgets(0);
    leftContainer->add(tableContainer);

    auto tableHeader = tgui::Label::create();
    tableHeader->setText("Initial statistical data");
    tableHeader->setTextSize(18);
    tableHeader->getRenderer()->setTextColor(tgui::Color::Yellow);
    tableHeader->setSize("100%", 20);
    tableHeader->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    tableContainer->add(tableHeader);

    auto columnNamesContainer = tgui::HorizontalLayout::create();
    columnNamesContainer->setSize("100%", 20);
    columnNamesContainer->getRenderer()->setSpaceBetweenWidgets(5);

    auto columnLabel1 = tgui::Label::create("Number");
    columnLabel1->setSize("20%", 20);
    columnLabel1->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    columnLabel1->getRenderer()->setTextColor(tgui::Color::Yellow);
    columnNamesContainer->add(columnLabel1);

    auto columnLabel2 = tgui::Label::create("Time, y");
    columnLabel2->setSize("20%", 20);
    columnLabel2->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    columnLabel2->getRenderer()->setTextColor(tgui::Color::Yellow);
    columnNamesContainer->add(columnLabel2);

    auto columnLabel3 = tgui::Label::create("Array size, x");
    columnLabel3->setSize("20%", 20);
    columnLabel3->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    columnLabel3->getRenderer()->setTextColor(tgui::Color::Yellow);
    columnNamesContainer->add(columnLabel3);

    auto columnLabel4 = tgui::Label::create("x*x");
    columnLabel4->setSize("20%", 20);
    columnLabel4->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    columnLabel4->getRenderer()->setTextColor(tgui::Color::Yellow);
    columnNamesContainer->add(columnLabel4);

    auto columnLabel5 = tgui::Label::create("x*y");
    columnLabel5->setSize("20%", 20);
    columnLabel5->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    columnLabel5->getRenderer()->setTextColor(tgui::Color::Yellow);
    columnNamesContainer->add(columnLabel5);

    tableContainer->add(columnNamesContainer);

    table = tgui::ScrollablePanel::create();
    table->setSize("100%", "auto");
    table->getRenderer()->setBorderColor(tgui::Color::Black);
    table->getRenderer()->setBorders({ 1, 1, 1, 1 });
    table->setVerticalScrollAmount(5);
    tableContainer->add(table);

    tableContent = tgui::VerticalLayout::create();
    tableContent->setSize("100%", "auto");
    table->add(tableContent);

    rightContainer = tgui::VerticalLayout::create();
    rightContainer->setSize("50%", "100%");
    rightContainer->getRenderer()->setSpaceBetweenWidgets(10);
    middleContainer->add(rightContainer);

    auto rightLabel = tgui::Label::create("Scatter plot and connection equation");
    rightLabel->setSize("100%", 20);
    rightLabel->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    rightLabel->setTextSize(18);
    rightLabel->getRenderer()->setTextColor(tgui::Color::Yellow);
    rightContainer->add(rightLabel);

    auto graphWidget = tgui::Group::create();
    graphWidget->setSize("100%", "80%");
    rightContainer->add(graphWidget);

    sftexture.loadFromFile(data.imagePath);
    tgtexture = tgui::Texture::Texture();
    tgtexture.loadFromPixelData(
        sftexture.getSize(),
        sftexture.copyToImage().getPixelsPtr()
    );
    image = tgui::Picture::create();
    image->getRenderer()->setTexture(tgtexture);
    image->setSize({ "100%", "100%" });
    graphWidget->add(image);

    auto bottomContainer = tgui::VerticalLayout::create();
    bottomContainer->setSize("auto", "100%");
    bottomContainer->getRenderer()->setSpaceBetweenWidgets(20);
    mainLayout->add(bottomContainer, "bottomContainer");

    // Первая строка: лейбл, лейбл, поле, лейбл, поле
    
    auto row1 = tgui::HorizontalLayout::create();
    row1->setSize("100%", 30);
    row1->getRenderer()->setSpaceBetweenWidgets(5);

    auto label11 = tgui::Label::create("Connection equation coefficients");
    label11->setSize(100, "100%");
    label11->setTextSize(16);
    label11->getRenderer()->setTextColor(tgui::Color::Yellow);
    row1->add(label11);

    auto groupContainer1 = tgui::HorizontalLayout::create();
    groupContainer1->setSize("auto", "100%");
    groupContainer1->getRenderer()->setSpaceBetweenWidgets(5);

    auto label21 = tgui::Label::create("a0");
    label21->setSize(10, "100%");
    label21->setTextSize(16);
    label21->getRenderer()->setTextColor(tgui::Color::Yellow);
    groupContainer1->add(label21);

    firstRow[0] = tgui::EditBox::create();
    firstRow[0]->setSize(200, "100%");
    firstRow[0]->setInputValidator(tgui::EditBox::Validator::All);
    firstRow[0]->setText(std::to_string(data.getA0()));
    groupContainer1->add(firstRow[0]);

    auto label31 = tgui::Label::create("a1");
    label31->setSize(10, "100%");
    label31->setTextSize(16);
    label31->getRenderer()->setTextColor(tgui::Color::Yellow);
    groupContainer1->add(label31);

    firstRow[1] = tgui::EditBox::create();
    firstRow[1]->setSize(200, "100%");
    firstRow[1]->setInputValidator(tgui::EditBox::Validator::All);
    firstRow[1]->setText(std::to_string(data.getA1()));
    groupContainer1->add(firstRow[1]);

    row1->add(groupContainer1);
    bottomContainer->add(row1);
    

    // Вторая строка: лейбл, лейбл, поле, лейбл, поле, лейбл
    
    auto row2 = tgui::HorizontalLayout::create();
    row2->setSize("100%", 30);
    row2->getRenderer()->setSpaceBetweenWidgets(10);

    auto label12 = tgui::Label::create("Connection equation");
    label12->setSize(100, "100%");
    label12->setTextSize(16);
    label12->getRenderer()->setTextColor(tgui::Color::Yellow);
    row2->add(label12);

    auto groupContainer2 = tgui::HorizontalLayout::create();
    groupContainer2->setSize("auto", "100%");
    groupContainer2->getRenderer()->setSpaceBetweenWidgets(5);

    auto label22 = tgui::Label::create("y = ");
    label22->setSize(10, "100%");
    label22->setTextSize(16);
    label22->getRenderer()->setTextColor(tgui::Color::Yellow);
    groupContainer2->add(label22);

    secondRow[0] = tgui::EditBox::create();
    secondRow[0]->setSize(200, "100%");
    secondRow[0]->setInputValidator(tgui::EditBox::Validator::All);
    secondRow[0]->setText(std::to_string(data.getA0()));
    groupContainer2->add(secondRow[0]);

    auto label32 = tgui::Label::create("+");
    label32->setSize(10, "100%");
    label32->setTextSize(16);
    label32->getRenderer()->setTextColor(tgui::Color::Yellow);
    groupContainer2->add(label32);

    secondRow[1] = tgui::EditBox::create();
    secondRow[1]->setSize(200, "100%");
    secondRow[1]->setInputValidator(tgui::EditBox::Validator::All);
    secondRow[1]->setText(std::to_string(data.getA1()));
    groupContainer2->add(secondRow[1]);

    auto label42 = tgui::Label::create("x");
    label42->setSize(10, "100%");
    label42->setTextSize(16);
    label42->getRenderer()->setTextColor(tgui::Color::Yellow);
    groupContainer2->add(label42);

    row2->add(groupContainer2);
    bottomContainer->add(row2);
    

    // Третья строка: лейбл, поле, лейбл, поле
    
    auto row3 = tgui::HorizontalLayout::create();
    row3->setSize("100%", 30);
    row3->getRenderer()->setSpaceBetweenWidgets(10);

    auto label13 = tgui::Label::create("Correlation coefficient");
    label13->setSize(100, "100%");
    label13->setTextSize(16);
    label13->getRenderer()->setTextColor(tgui::Color::Yellow);
    row3->add(label13);

    thirdRow[0] = tgui::EditBox::create();
    thirdRow[0]->setSize(100, "100%");
    thirdRow[0]->setInputValidator(tgui::EditBox::Validator::All);
    thirdRow[0]->setText(std::to_string(data.getCorr()));
    row3->add(thirdRow[0]);

    auto label23 = tgui::Label::create("Determination coefficient");
    label23->setSize(100, "100%");
    label23->setTextSize(16);
    label23->getRenderer()->setTextColor(tgui::Color::Yellow);
    row3->add(label23);

    thirdRow[1] = tgui::EditBox::create();
    thirdRow[1]->setSize(100, "100%");
    thirdRow[1]->setInputValidator(tgui::EditBox::Validator::All);
    thirdRow[1]->setText(std::to_string(data.getDet()));
    row3->add(thirdRow[1]);

    bottomContainer->add(row3);
    

    // Четвертая строка: лейбл, поле, лейбл, поле
    
    auto row4 = tgui::HorizontalLayout::create();
    row4->setSize("100%", 30);
    row4->getRenderer()->setSpaceBetweenWidgets(10);

    auto label14 = tgui::Label::create("Elasticity coefficient");
    label14->setSize(100, "100%");
    label14->setTextSize(16);
    label14->getRenderer()->setTextColor(tgui::Color::Yellow);
    row4->add(label14);

    forthRow[0] = tgui::EditBox::create();
    forthRow[0]->setSize(100, "100%");
    forthRow[0]->setInputValidator(tgui::EditBox::Validator::All);
    forthRow[0]->setText(std::to_string(data.getElast()));
    row4->add(forthRow[0]);

    auto label24 = tgui::Label::create("Beta coefficient");
    label24->setSize(100, "100%");
    label24->setTextSize(16);
    label24->getRenderer()->setTextColor(tgui::Color::Yellow);
    row4->add(label24);

    forthRow[1] = tgui::EditBox::create();
    forthRow[1]->setSize(100, "100%");
    forthRow[1]->setInputValidator(tgui::EditBox::Validator::All);
    forthRow[1]->setText(std::to_string(data.getBeta()));
    row4->add(forthRow[1]);

    bottomContainer->add(row4);
    
    image->onClick([this]() {
        data.plotDataAndRegression();
        plt::show();
    });
}

void EquationWidget::show(tgui::Gui& gui) {
    BaseWidget::show(gui);
}

tgui::Container::Ptr EquationWidget::getRootWidget() const {
    return widget;
}