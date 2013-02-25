#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    std::vector<unsigned> M_count(N_DIM+1);
    for (unsigned i=0; i<=N_DIM; i++)
        M_count[i] = 0;
    Point::n = N_DIM;
    M = 1.65*N_DIM + 0.05*N_DIM*N_DIM;
    while(!smplx.QuitCase(smplx, eps))
    {
        smplx.sort();
        f_l = func(smplx.get_l());
        f_g = func(smplx.get_g());
        f_h = func(smplx.get_h());
        smplx.set_reflected(smplx.get_c()*(1 + alpha) - smplx.get_h() * alpha);
        f_reflected = func(smplx.get_reflected());
        if (f_l < f_reflected && f_reflected < f_g) theta = alpha;
        if (f_relflected <= f_l) theta = gamma;
        if (f_g <= f_reflected && f_reflected < f_h)
            theta = beta;
        else if(f_reflected >= f_h) theta = -beta;
    }
}
