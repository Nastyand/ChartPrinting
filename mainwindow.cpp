#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Задание минимального размера окна
    setMinimumSize(500, 300);
    // Задание стандартного размера окна
    resize(800, 600);

    // Создание QWidget
    std::unique_ptr<QWidget> widget = std::make_unique<QWidget>(this);

    // Создание кнопки "открыть папку"
    openFolderButton = std::make_unique<QPushButton>("Открыть папку", this);
    openFolderButton->setStyleSheet("border: 1px solid black; padding: 4px;");

    // Создание метки "тип диаграммы"
    chartTypeLabel = std::make_unique<QLabel>("Тип диаграммы:", this);
    chartTypeLabel->setStyleSheet("border: 1px solid black; padding: 3px;");

    // Создание списка типов диаграмм
    chartTypesComboBox = std::make_unique<QComboBox>(this);
    chartTypesComboBox->addItem("Столбчатая диаграмма");
    chartTypesComboBox->addItem("Круговая диаграмма");
    chartTypesComboBox->setStyleSheet("border: 1px solid black; padding: 3px;");

    // Создание флажка для выбора черно-белой диаграммы
    chartBWCheckBox = std::make_unique<QCheckBox>("Черно-белая диаграмма", this);
    chartBWCheckBox->setStyleSheet("border: 1px solid black; padding: 4px;");

    // Создание кнопки "печать"
    printingButton = std::make_unique<QPushButton>("Печать", this);
    printingButton->setStyleSheet("border: 1px solid black; padding: 4px;");

    // Создание разделителя
    QTableView *tableView1 = new QTableView;
    QTableView *tableView2 = new QTableView;

    splitter = std::make_unique<QSplitter>();
    splitter->addWidget(tableView1);
    splitter->addWidget(tableView2);

    // Создание QHBoxLayout
    std::unique_ptr<QHBoxLayout> hLayout = std::make_unique<QHBoxLayout>();
    hLayout->addWidget(openFolderButton.get());
    hLayout->addWidget(chartTypeLabel.get());
    hLayout->addWidget(chartTypesComboBox.get());
    hLayout->addWidget(chartBWCheckBox.get());
    hLayout->addWidget(printingButton.get());

    // Создание QVBoxLayout
    std::unique_ptr<QVBoxLayout> vLayout = std::make_unique<QVBoxLayout>();
    vLayout->addLayout(hLayout.release());
    vLayout->addWidget(splitter.release());

    // Установка QVBoxLayout в виджет
    widget->setLayout(vLayout.release());
    setCentralWidget(widget.release());
}

MainWindow::~MainWindow()
{
    delete ui;
}

