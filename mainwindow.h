#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <hashset.h>
#include <QMdiArea>
#include "documentwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionLoad_triggered();

    void on_actionSave_triggered();

    void on_add_triggered();

    void on_remove_triggered();

    void on_doLists_triggered();

private:
    Ui::MainWindow *ui;
    void openSubWindow(HashSet hashSet);
    DocumentWindow* getActiveWindow();
};
#endif // MAINWINDOW_H
