#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QSplitter>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTableView>

#include <QFileSystemModel>
#include <QListView>
#include <QFileDialog>
#include <QItemSelectionModel>
#include <QFileInfo>
#include <QDebug>
#include "ioccontainer.h"
#include "datareading.h"
#include <QChartView>
#include <QGraphicsColorizeEffect>
#include <QPdfWriter>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void OpenFolder(); // Слот для открытия папки
    void ReadData(const QItemSelection &selected, const QItemSelection &deselected); // Слот для извлечения данных из выбранного файла
    void DrawChart(); // Слот для рисования диаграммы выбранного типа
    void ColorChange(); // Слот для смены цвета диаграммы
    void PrintChart(); // Слот для печати диаграммы

private:
    Ui::MainWindow *ui;

    QString filePath; // Путь к файлу

    std::unique_ptr<QPushButton> openFolderButton; // Кнопка "открыть папку"
    std::unique_ptr<QLabel> chartTypeLabel;        // Метка "тип диаграммы"
    std::unique_ptr<QComboBox> chartTypesComboBox; // Типы диаграмм
    std::unique_ptr<QCheckBox> chartBWCheckBox;    // Выбор черно-белой диаграммы
    std::unique_ptr<QPushButton> printingButton;   // Кнопка "печать"
    std::unique_ptr<QSplitter> splitter;           // Разделитель

    std::shared_ptr<QFileSystemModel>leftPartModel;// Модель файловой системы
    std::unique_ptr<QListView>listView;            // Представление файлов
    QItemSelectionModel* selectionModel;           // Отслеживание выбранных элементов
    IOCContainer ioc;                              // IOC контейнер
    QMap<QString, double> data;                    // Множество данных в формате ключ-значение
    std::shared_ptr<QChartView> chartView;         // Представление диаграммы

};
#endif // MAINWINDOW_H
