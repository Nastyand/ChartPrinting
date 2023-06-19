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

    // Соединение сигналов со слотами
    connect(openFolderButton.get(), &QPushButton::clicked, this, &MainWindow::OpenFolder);
    connect(chartTypesComboBox.get(), &QComboBox::currentIndexChanged, this, &MainWindow::DrawChart);
    connect(chartBWCheckBox.get(), &QCheckBox::stateChanged, this, &MainWindow::ColorChange);
    connect(printingButton.get(), &QPushButton::clicked, this, &MainWindow::PrintChart);
}


void MainWindow::OpenFolder()
{
    // Открытие диалогового окна
    QString filePath = QFileDialog::getExistingDirectory(this, "Выбор папки", QDir::homePath());

    // Проверка на пустоту папки
    QDir folder(filePath);
    if (folder.isEmpty())
    {
        QMessageBox::information(nullptr, "Ошибка", "Папка пуста");
        return;
    }

    leftPartModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    leftPartModel->setRootPath(filePath);

    // Фильтр типов файлов
    QStringList filter;
    filter << "*.sqlite" << "*.json" << "*.csv";
    leftPartModel->setNameFilters(filter);

    // Установка модели данных для отображения
    listView->setModel(leftPartModel.get());
    listView->setRootIndex(leftPartModel->index(filePath));

    // Соединение сигналов со слотами
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

    else if (fileType == "csv")
    {
        // Регистрирация IDataReading с классом CsvDataReading
        ioc.RegisterInstance<IDataReading, CsvDataReading>();
    }

    DataReader dataRead (ioc.GetObject<IDataReading>());
    data=dataRead.GetData(filePath); // Создание объекта, хранящего данные
}


void MainWindow::DrawChart()
{
    // Проверка установленного типа диаграммы
    if (chartTypesComboBox->currentText() == "Столбчатая диаграмма") {
        ioc.RegisterInstance<Charts, BarCharts>(); // Регистрация ICharts с классом BarCharts
    }
    else if (chartTypesComboBox->currentText() == "Круговая диаграмма") {
        ioc.RegisterInstance<Charts, PieCharts>(); // Регистрация ICharts с классом PieCharts
    }
    ioc.GetObject<Charts>()->ChartDrawing(data, chartView, limit); // Рисование диаграммы нужного типа
}

void MainWindow::ColorChange()
{
    if (chartBWCheckBox->isChecked()) {
        std::unique_ptr<QGraphicsColorizeEffect> color = std::make_unique<QGraphicsColorizeEffect>(); // Создание объекта для раскрашивания диаграммы
        color->setColor(Qt::black); // Установка черного цвета
        chartView->chart()->setGraphicsEffect(color.release()); // Применение цвета к диаграмме
    }
    else {
        chartView->chart()->setGraphicsEffect(nullptr); // Возврат исходных цветов диаграммы
    }
}

void MainWindow::PrintChart()
{
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Печать", "", "PDF (*.pdf)"); // Создание имени файла
    if (!filePath.isEmpty()) // Если имя задано, то есть строка не пустая
    {
        QPdfWriter pdfWriter(filePath); // Создание средства записи PDF
        QPainter painter(&pdfWriter); // Создание объекта для рисования
        chartView->render(&painter); // Рисование диаграммы в pdf
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

