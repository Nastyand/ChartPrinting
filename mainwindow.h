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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::unique_ptr<QPushButton> openFolderButton; // Кнопка "открыть папку"
    std::unique_ptr<QLabel> chartTypeLabel;        // Метка "тип диаграммы"
    std::unique_ptr<QComboBox> chartTypesComboBox; // Типы диаграмм
    std::unique_ptr<QCheckBox> chartBWCheckBox;    // Выбор черно-белой диаграммы
    std::unique_ptr<QPushButton> printingButton;   // Кнопка "печать"
    std::unique_ptr<QSplitter> splitter;           // Разделитель
};
#endif // MAINWINDOW_H
