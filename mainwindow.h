#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simplex.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int M;
public:
    void set_M(int new_M) {M = new_M;}
    unsigned N_DIM;
    Point simplex_min(Simplex& smplx);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
