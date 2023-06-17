#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datareading.h"
#include "charts.h"
int IOCContainer::s_nextTypeId = 115094801;

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

    // Определение модели файловой системы
    leftPartModel = std::make_shared<QFileSystemModel>(this);

    // Показать в виде списка
    listView = std::make_unique<QListView>(this);
    listView->resize(390, 0);

    // Определение объекта для отображения диаграммы
    chartView=std::make_shared<QChartView>(this);
    chartView->resize(610, 0);

    // Создание разделителя
    splitter = std::make_unique<QSplitter>();
    splitter->addWidget(listView.get());
    splitter->addWidget(chartView.get());

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

    // Соединение сигнала со слотом
    // Открытие папки по нажатию кнопки
    connect(openFolderButton.get(), &QPushButton::clicked, this, &MainWindow::OpenFolder);

}


void MainWindow::OpenFolder()
{
    // Открытие диалогового окна
    QString filePath = QFileDialog::getExistingDirectory(this, "Выбор папки", QDir::homePath());

    leftPartModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    leftPartModel->setRootPath(filePath);

    // Установка модели данных для отображения
    listView->setModel(leftPartModel.get());
    listView->setRootIndex(leftPartModel->index(filePath));

    // Отслеживание выбранных элементов в представлении listView
    selectionModel = listView->selectionModel();

    connect(listView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::ReadData);
    connect(listView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::DrawChart);
}

void MainWindow::ReadData(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);

    // Получение списка индексов
    QModelIndexList indexes = selected.indexes();

    // Выделение первого индекса
    filePath = leftPartModel->filePath(indexes.first());

    // Проверка на тип файла
    QFileInfo fileInfo(filePath);
    QString fileType = fileInfo.suffix();

    if (fileType == "sqlite")
    {
        // Регистрирация IDataReading с классом SqlDataReading
        ioc.RegisterInstance<IDataReading, SqlDataReading>();
    }

    else if (fileType == "json")
    {
        // Регистрирация IDataReading с классом JsonDataReading
        ioc.RegisterInstance<IDataReading, JsonDataReading>();
    }

    data = ioc.GetObject<IDataReading>()->GetData(filePath, 15); // Создание объекта, хранящего данные
}



void MainWindow::DrawChart()
{
    if (chartTypesComboBox->currentText() == "Столбчатая диаграмма") { // Проверка установленного типа диаграммы
        ioc.RegisterInstance<ICharts, BarCharts>(); // Регистрация ICharts с классом BarCharts
    }
    ioc.GetObject<ICharts>()->ChartDrawing(data, chartView); // Рисование диаграммы нужного типа



}



MainWindow::~MainWindow()
{
    delete ui;
}

