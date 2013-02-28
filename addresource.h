#ifndef ADDRESOURCE_H
#define ADDRESOURCE_H

#include <QDialog>
#include <QStandardItemModel>
#include "mainwindow.h"

namespace Ui {
class AddResource;
}

class AddResource : public QDialog
{
    Q_OBJECT
    
public:
    MainWindow *mw;
    explicit AddResource(QWidget *parent = 0);
    ~AddResource();
    
private slots:
    void on_okButton_clicked();

private:
    Ui::AddResource *ui;
};

#endif // ADDRESOURCE_H
