// Linear Regression Method Program V 1.0.0 / Programa del metodo de regresion lineal V 1.0.0
#include "reglin.h"
#include "ui_reglin.h"
#include <QTableWidgetItem> // Class for allow the use of Items from Table Widget.
#include <QString> // Class for allow the use of text strings.

RegLin::RegLin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegLin)
{
    ui->setupUi(this);
    setWindowTitle("Método de Regresion Lineal");// Prints the method's name at window title.
    //Connections between push button clicked signals and slots.
    connect(ui->inicia,SIGNAL(clicked()),this,SLOT(ejecutar()));// Start button with slot for run the method.
    connect(ui->limpia,SIGNAL(clicked()),this,SLOT(limpiar()));// Clear button with slot for clear fields.
    connect(ui->carga,SIGNAL(clicked()),this,SLOT(cargar()));// Load button with slot for add data.
    ui->inicia->setDisabled(true);// Disables the start button till the user press the Load button.
    ui->limpia->setDisabled(true);// Diables the clear button till the user press the Load button.
}
void RegLin::cargar(){// This slot will save the data from table widget to a matrix, when the Load button been clicked.
    npuntos=0, xsum=0, ysum=0, xysum=0, x2sum=0, y2sum=0;// These six variables starts from zero.
    for(i=0;i<8;i++){// This cycle saves data from table widget items to a matrix:
        QTableWidgetItem* posicionx=ui->Tablap->item(i,0);// Creates a temporal variable for save each item value from the first table column.
        QTableWidgetItem* posiciony=ui->Tablap->item(i,1);// Creates a temporal variable for save each item value from the secound table column.
        if((!posicionx)||(!posiciony)){// If the table widget item isn't null (empty), the cycle continues.
            continue;
        }
        matrix[i][0]=posicionx->text().toDouble();// Saves the value from table item to a matrix position (for "x").
        xsum=xsum+matrix[i][0];// "xsum" saves the "x" points summation.
        x2sum=x2sum+(matrix[i][0]*matrix[i][0]);// "x2sum saves the squared "x" points summation.
        matrix[i][1]=posiciony->text().toDouble();// Saves the value from table item to a matrix position (for "y").
        ysum=ysum+matrix[i][1];// "ysum" saves the "y" points summation.
        y2sum=y2sum+(matrix[i][1]*matrix[i][1]);// "y2sum saves the squared "y" points summation.
        xysum=xysum+(matrix[i][0]*matrix[i][1]);// "xysum" saves the x*y sumation.
        npuntos++;// Sums one to point counter.
    }
    if(npuntos<3){// If the user introduced less than 3 points:
        ui->Tablap->setDisabled(false);// The first table widget keeps activate, till the user adds at least 3 points.
    }
    else{// If the user added at least 3 points:
        ui->carga->setDisabled(true);//Disables the Load button.
        ui->inicia->setDisabled(false);// Enables the start button.
        ui->Tablap->setDisabled(true);// Disables the first table widget.
    }
    ui->limpia->setDisabled(false);// Enables the clear button.
}

void RegLin::ejecutar(){// This slot will run the method, when the Start button been clicked after data introduction.
    sr=0, a0=0, a1=0, sxy=0, r=0;// These five variables starts from zero.
    xprom=xsum/npuntos;// Calculates the "x points" average.
    yprom=ysum/npuntos;// Calculates the "y points" average.
    a1=((npuntos*xysum)-(xsum*ysum))/((npuntos*x2sum)-(xsum*xsum));// Calculates the dependent term for straight line equation.
    a0=yprom-(a1*xprom);// Calculates the independent term for straigh line equation.
    for(i=0;i<npuntos;i++){// This cycle saves dispersion results in a new matrix.
        rmatrix[i][0]=(matrix[i][1]-yprom)*(matrix[i][1]-yprom);// Calculates the dispersion between points for each position.
        rmatrix[i][1]=(matrix[i][1]-a0-(a1*matrix[i][0]))*(matrix[i][1]-a0-(a1*matrix[i][0]));// Calculates the dispersion between each point and the found straight line.
        sr=sr+rmatrix[i][1];// "sr" saves the dispersion point-straight line summation.
        ui->Tablat->setItem(i,0,new QTableWidgetItem(QString::number(rmatrix[i][0])));// Show each dispersion between points value in the respective table widget position.
        ui->Tablat->setItem(i,1,new QTableWidgetItem(QString::number(rmatrix[i][1])));// Show each dispersion point-straight line in the respective table widget position.
    }
    sxy=sqrt(sr/(npuntos-2));// Calculates the estimated standard error, and saves it on "sxy".
    // Calculates the linear correlation coefficient, and saves it on "r".
    r=((npuntos*xysum)-(xsum*ysum))/(sqrt((npuntos*x2sum)-(xsum*xsum))*sqrt((npuntos*y2sum)-(ysum*ysum)));
    QString temp1, temp2, temp3, temp4, temp5;// Creates temporal text variables.
    //Creates a text srting with the found values.
    temp1.append("La ecuacion de la recta es: \n y= ").append(temp2.setNum(a0)).append("+").append(temp3.setNum(a1)).append("x").append(temp4.append("\n El coeficiente de correlacion lineal (r)=").append(temp5.setNum(r)));
    ui->textores->setText(temp1);// Shows the found straight line equation and the linear correlation coefficient at text browser.
}
void RegLin::limpiar(){// This slot will clear all user interface fields, when the Clear button been clicked.
    // Clears both table widgets.
    ui->Tablap->clearContents();
    ui->Tablat->clearContents();
    ui->textores->clear();// Clears text browser.
    ui->inicia->setDisabled(true);// Disables the start button.
    ui->limpia->setDisabled(true);// Disables the clear button.
    ui->carga->setDisabled(false);// Enables the load button.
    ui->Tablap->setDisabled(false);// Enables the first table widget.
}

RegLin::~RegLin()
{
    delete ui;
}
