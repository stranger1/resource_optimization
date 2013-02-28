#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "simplex.h"
#include "resultwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int M;
    void sort_simplex(Simplex &smplx);
public:
    double func(const Point &a);
    bool point_satisfies_restriction(const Point &a);
    QStandardItemModel *model_resource;
    void set_M(int new_M) {M = new_M;}
    unsigned N_DIM;
    Point simplex_min(Simplex& smplx, double eps);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButton_clicked();

    void on_push_add_resource_clicked();

    void on_push_add_resource_2_clicked();

private:

    Ui::MainWindow *ui;
};
/*
class Restrictions {
    std::vector<double> stock;
    std::vector<double> price;
};*/

#endif // MAINWINDOW_H
