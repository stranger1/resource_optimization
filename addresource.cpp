#include "addresource.h"
#include "ui_addresource.h"

AddResource::AddResource(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddResource)
{
    ui->setupUi(this);
}

AddResource::~AddResource()
{
    delete ui;
}

void AddResource::on_okButton_clicked()
{
    parentWidget()->setEnabled(true);
    this->close();
}
