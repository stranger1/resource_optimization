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
//    const double alpha = 1.0;
//    const double beta = 0.5;
//    const double gamma = 2.0;
//    double theta;
    double f_l, f_g, f_h, f_c, f_reflected;
    const int M_max = 1.65*N_DIM + 0.05*N_DIM*N_DIM;

    Point::n = N_DIM;
    unsigned iter=0;//for debug purposes
    while(!smplx.QuitCase(smplx, eps))
    {
        sort_simplex(smplx);
        f_l = func(smplx.get_l());
        f_g = func(smplx.get_g());
        f_h = func(smplx.get_h());
//        Point a = (smplx.get_c()*(1 + alpha)); Point b = (smplx.get_h() * alpha);
//        smplx.set_reflected(a - b);
        Point reflected = smplx.get_c()*2 - smplx.get_h();
        smplx.set_reflected(reflected); //test reflection
//        f_reflected = func(smplx.get_reflected());
        smplx.set_vertex_h(smplx.get_reflected());
        ++iter;
        if (smplx.inc_allvertex_M(M_max))
            smplx.reduction();
        if (iter > 1500)
        {
            qDebug()<<"x="<<smplx.get_h().coord[0];
            qDebug()<<"y="<<smplx.get_h().coord[1];
            break;
        }
//        smplx.set_vertex_h(smplx.get_h() + (smplx.get_c() - smplx.get_h())*(1 + theta));
    }
    qDebug()<<"iterations"<<iter;
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
    if (a.coord[0]*5 + a.coord[1]*8 < 190)
        if (a.coord[0]*10 + a.coord[1]*5 < 200)
            if (a.coord[0]*30 + a.coord[1]*20 < 904)
                if (a.coord[0]*150 + a.coord[1]*200 < 4520)
                    return true;
    return false;
}

double MainWindow::func(const Point &a)   //TODO: function generator
{
    if (point_satisfies_restriction(a))
        return (-220*a.coord[0] - 225*a.coord[1]);
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
    Point answ = simplex_min(smplx, 0.0001);
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
