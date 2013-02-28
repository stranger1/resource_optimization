#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTextCodec>
#include "addresource.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QStandardItemModel *model_product = new QStandardItemModel(0, 2, this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

Point MainWindow::simplex_min(Simplex &smplx, double eps) { //number of simplex vertexes: N_DIM + 1
    const double alpha = 1.0;
    const double beta = 0.5;
    const double gamma = 2.0;
    double theta;
    double f_l, f_g, f_h, f_c, f_reflected;

    Point::n = N_DIM;
    unsigned iter=0;
    while(!smplx.QuitCase(smplx, eps))
    {
        sort_simplex(smplx);
        f_l = func(smplx.get_l());
        f_g = func(smplx.get_g());
        f_h = func(smplx.get_h());
//        Point a = (smplx.get_c()*(1 + alpha)); Point b = (smplx.get_h() * alpha);
//        smplx.set_reflected(a - b);
        Point a = (smplx.get_c()*(1 + alpha)) - (smplx.get_h() * alpha);
        smplx.set_reflected(a); //test reflection
        f_reflected = func(smplx.get_reflected());
        if (f_l < f_reflected && f_reflected < f_g) theta = alpha;
        if (f_reflected <= f_l) theta = gamma;
        if (f_g <= f_reflected && f_reflected < f_h)
            theta = beta;
        else if(f_reflected >= f_h) theta = -beta;
        Point temp = smplx.get_h() + (smplx.get_c() - smplx.get_h())*(1 + theta);
        smplx.set_vertex_h(temp);
        ++iter;
        if (iter > 1000)
        {
            qDebug()<<"x="<<smplx.get_h().coord[0];
            qDebug()<<"y="<<smplx.get_h().coord[1];
            break;
        }
//        smplx.set_vertex_h(smplx.get_h() + (smplx.get_c() - smplx.get_h())*(1 + theta));
    }
    return smplx.get_l();
}

void MainWindow::sort_simplex(Simplex &smplx)
{
    unsigned ar_size = smplx.get_number_of_vertexes();   //sort
    for (unsigned j=0; j<ar_size-1; j++)
        for (unsigned i=0; i<ar_size-1; i++)
            if (func(smplx.get_vertex(i)) > func(smplx.get_vertex(i+1)))
                std::swap(smplx.m_array[i], smplx.m_array[i+1]);
    smplx.set_h(smplx.get_vertex(ar_size-1));   //set h,g,l
    smplx.set_g(smplx.get_vertex(ar_size-2));
    smplx.set_l(smplx.get_vertex(0));
    Point c;     //calculate center of mass
    for (unsigned i=0; i<ar_size-1; i++)
        c += smplx.m_array[i];
//    c = std::accumulate(m_array.begin(), m_array.end() - 1, 0) /(ar_size - 1);
    c /= ar_size-1;
    smplx.set_c(c);

//    std::sort(m_array.begin(), m_array.end(), comparator_by_f);
}

bool MainWindow::point_satisfies_restriction(const Point &a)
{
    if (a.coord[0]*5 + a.coord[1]*20 < 100)
        if (a.coord[0]*8 + a.coord[1]*13 < 50)
            if (a.coord[0]*2 + a.coord[1]*1 < 20)
                return true;
    return false;
}

double MainWindow::func(const Point &a)   //TODO: function generator
{
    if (point_satisfies_restriction(a))
        return (-150*a.coord[0] - 175*a.coord[1]);
    else
        return 9999.99;
}

void MainWindow::on_pushButton_clicked()
{
    N_DIM = 2;
    Point::n = N_DIM;
    Point b;
    b.coord[0] = 0; b.coord[1] = 0;
    Simplex smplx(b, 1);
    Point answ = simplex_min(smplx, 0.1);
    qDebug()<<answ.coord[0];
    qDebug()<<answ.coord[1];
    qDebug()<<func(answ);

}

void MainWindow::on_push_add_resource_clicked()
{
    this->setEnabled(false);
    AddResource *res_add = new AddResource(this);
    res_add->mw = this;
    res_add->show();
}

void MainWindow::on_push_add_resource_2_clicked()
{
    ResultWindow *resWindow = new ResultWindow(this);
    resWindow->show();
}
