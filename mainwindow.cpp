#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Point MainWindow::simplex_min(Simplex &smplx) { //number of simplex vertexes: N_DIM + 1
    const double eps = 0.01;
    const double alpha = 1.0;
    const double beta = 0.5;
    const double gamma = 2.0;
    double theta;
    double f_l, f_g, f_h, f_c, f_reflected;

    Point::n = N_DIM;
    while(!smplx.QuitCase(smplx, eps))
    {
        smplx.sort();
        f_l = smplx.func(smplx.get_l());
        f_g = smplx.func(smplx.get_g());
        f_h = smplx.func(smplx.get_h());
//        Point a = (smplx.get_c()*(1 + alpha)); Point b = (smplx.get_h() * alpha);
//        smplx.set_reflected(a - b);
        smplx.set_reflected((smplx.get_c()*(1 + alpha)) - (smplx.get_h() * alpha)); //test reflection
        f_reflected = smplx.func(smplx.get_reflected());
        if (f_l < f_reflected && f_reflected < f_g) theta = alpha;
        if (f_reflected <= f_l) theta = gamma;
        if (f_g <= f_reflected && f_reflected < f_h)
            theta = beta;
        else if(f_reflected >= f_h) theta = -beta;
        Point temp = (smplx.get_c() - smplx.get_h())*(1 + theta);
        smplx.set_vertex_h(smplx.get_h() + temp);
//        smplx.set_vertex_h(smplx.get_h() + (smplx.get_c() - smplx.get_h())*(1 + theta));
    }
    return smplx.get_l();
}

void MainWindow::on_pushButton_clicked()
{
    N_DIM = 2;
    Point::n = N_DIM;
    Point b;
    b.coord[0] = 2; b.coord[1] = 0;
    Simplex smplx(b, 1);
    Point answ = simplex_min(smplx);
    qDebug()<<answ.coord[0];
    qDebug()<<answ.coord[1];

}
