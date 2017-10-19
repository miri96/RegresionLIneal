// Linear Regression Method Program V 1.0.0 / Programa del metodo de regresion lineal V 1.0.0
#ifndef REGLIN_H
#define REGLIN_H

#include <QMainWindow>

namespace Ui {
class RegLin;
}

class RegLin : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegLin(QWidget *parent = 0);
    ~RegLin();
    // Variables declaration.
    double matrix[7][2];// This matrix will save the points provided by the user
    double rmatrix[7][2];// This another matrix will save the found dispersion results.
    double xsum, ysum, xysum, x2sum, y2sum;// These five variables will save different summations.
    double xprom, yprom;// These variables will save the average of "x" and "y" points.
    double a0, a1;// These variables will save terms for the straight equation.
    double errore, sxy, sr, r;// These variables will save different error results.
    int npuntos;// This variable will function as a point counter.
    int i,j;// Variables for cycles.
public slots:
    // Slots declaration.
    void ejecutar();// This slot will run the method.
    void limpiar();// This slot will clear all user interface fields.
    void cargar();// This slot will take and save data from table widget.
private:
    Ui::RegLin *ui;
};

#endif // REGLIN_H
