#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include "loggingcategories.h"
#include <QGridLayout>
#include <QLabel>
#include <QInputDialog>
#include <QFileDialog>
#include <QMdiSubWindow>
#include <QList>
#include <fstream>
#include <sstream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openSubWindow(HashSet hashSet)
{
    QWidget *widget = new DocumentWindow(hashSet, ui->mdiArea);
    ui->mdiArea->addSubWindow(widget);
    widget->show();
}

DocumentWindow* MainWindow::getActiveWindow()
{
    QMdiSubWindow* subWindow = ui->mdiArea->activeSubWindow();
    return dynamic_cast<DocumentWindow*>(subWindow->widget());
}

void MainWindow::on_actionLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("Text files (*.txt)"));
    if (fileName == "")
        return;
    HashSet hashSet = HashSet(fileName);
    if (!this->ui->actionSave->isEnabled()) {
        this->ui->actionSave->setEnabled(true);
        this->ui->add->setEnabled(true);
        this->ui->remove->setEnabled(true);
        this->ui->doLists->setEnabled(true);
    }
    openSubWindow(hashSet);
    qInfo(logInfo()) << "loaded";
}


void MainWindow::on_actionSave_triggered()
{
    DocumentWindow* activeWindow = getActiveWindow();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open file"), "", tr("Text files (*.txt)"));
    fstream myfile;
    myfile.open(fileName.toStdString(), ios::out | ios::trunc);
    myfile << activeWindow->getSet()->toString();
    myfile.close();
    qInfo(logInfo()) << "saved";
}

void MainWindow::on_add_triggered()
{
    if(ui->mdiArea->subWindowList().size() == 0)
        return;
    QString word = QInputDialog::getMultiLineText(this, QString::fromUtf8("Input word"),
                                                 QString::fromUtf8("Word:"));
    if(word == "")
        return;
    DocumentWindow* activeWindow = getActiveWindow();
    activeWindow->getSet()->insert(word.toStdString());
    activeWindow->resetText();
    qInfo(logInfo()) << "added";
}

void MainWindow::on_remove_triggered()
{
    if(ui->mdiArea->subWindowList().size() == 0)
        return;
    QString word = QInputDialog::getMultiLineText(this, QString::fromUtf8("Input word"),
                                                 QString::fromUtf8("Word:"));
    if(word == "")
        return;
    DocumentWindow* activeWindow = getActiveWindow();
    activeWindow->getSet()->erase(word.toStdString());
    activeWindow->resetText();
    qInfo(logInfo()) << "removed";
}

string ToString(list<string> list)
{
    stringstream ss;
    for(auto item: list)
    {
        ss << item << endl;
    }
    return ss.str();
}

void MainWindow::on_doLists_triggered()
{   
    if (ui->mdiArea->subWindowList().size() == 0)
        return;
    DocumentWindow* activeWindow = getActiveWindow();
    list<string> listWithWordsLessFive = activeWindow->getSet()->getWordsLessFiveList();
    listWithWordsLessFive.sort();
    string textWithWordsLessFive = ToString(listWithWordsLessFive);
    QInputDialog::getMultiLineText(this, QString::fromUtf8("Слова меньше 5 букв"),
                                                 QString::fromUtf8("Words:"), QString::fromStdString(textWithWordsLessFive));


    list<string> flippersList = activeWindow->getSet()->getFlippersList();
    flippersList.sort();
    string textWithFlippers = ToString(flippersList);
    QInputDialog::getMultiLineText(this, QString::fromUtf8("Перевёртыши"),
                                                 QString::fromUtf8("Words:"), QString::fromStdString(textWithFlippers));

}


