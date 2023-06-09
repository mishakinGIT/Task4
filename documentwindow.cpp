#include "documentwindow.h"
#include <QGridLayout>

DocumentWindow::DocumentWindow(HashSet hashSet, QWidget* parent)
{
    this->hashSet = hashSet;
    QGridLayout *gridLayout = new QGridLayout(this);
    this->setLayout(gridLayout);
    label = new QLabel(QString::fromStdString(hashSet.toString()) , this);
    gridLayout->addWidget(label);
    this->setWindowTitle((QString::fromStdString("hashSet")));
}

HashSet *DocumentWindow::getSet()
{
    return &hashSet;
}

void DocumentWindow::resetText()
{
    label->setText(QString::fromStdString(hashSet.toString()));
}

