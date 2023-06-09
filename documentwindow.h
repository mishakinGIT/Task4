#ifndef DOCUMENTWINDOW_H
#define DOCUMENTWINDOW_H

#include"hashset.h"
#include<QWidget>
#include <QMdiArea>
#include <QMainWindow>


class DocumentWindow: public QWidget
{
public:
    DocumentWindow(HashSet hashSet, QWidget *parent = nullptr);
    HashSet *getSet();
    void resetText();
private:
    QLabel *label;
    HashSet hashSet;
};

#endif // DOCUMENTWINDOW_H
