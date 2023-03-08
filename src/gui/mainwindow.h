#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static void scrollToBottom();

private slots:

    void on_actionQuit_triggered();

    void on_actionNew_Tab_triggered();

    void on_tabWidget_tabCloseRequested(int index);

    void on_actionClose_Worksheet_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
