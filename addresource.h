#ifndef ADDRESOURCE_H
#define ADDRESOURCE_H

#include <QDialog>

namespace Ui {
class AddResource;
}

class AddResource : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddResource(QWidget *parent = 0);
    ~AddResource();
    
private slots:
    void on_okButton_clicked();

private:
    Ui::AddResource *ui;
};

#endif // ADDRESOURCE_H
