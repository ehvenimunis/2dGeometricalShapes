#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QColorDialog"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    update_ui();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_ui(){
    this->ui->spinScale->setValue(this->ui->renderArea->scale());
    this->ui->spinInterval->setValue(this->ui->renderArea->interval());
    this->ui->spincount->setValue(this->ui->renderArea->stepCount());
}

void MainWindow::on_btnAstroid_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Astroid);
    //this->ui->renderArea->setBackgroundColor(Qt::red);
    this->ui->renderArea->repaint();
    update_ui();

}

void MainWindow::on_btnCicloid_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Cycloid);
    //this->ui->renderArea->setBackgroundColor(Qt::green);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnHuygens_clicked()
{
    this->ui->renderArea->setShape(RenderArea::HuygensCycloid);
    //this->ui->renderArea->setBackgroundColor(Qt::blue);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnHypo_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Hypocycloid);
    //this->ui->renderArea->setBackgroundColor(Qt::yellow);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnLine_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Line);
    //this->ui->renderArea->setBackgroundColor(Qt::blue);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_spinScale_valueChanged(double scale)
{
    this->ui->renderArea->setScale (scale);
}

void MainWindow::on_spinInterval_valueChanged(double interval)
{
    this->ui->renderArea->setInterval (interval);
}

void MainWindow::on_spincount_valueChanged(int count)
{
    this->ui->renderArea->setStepCount (count);
}

void MainWindow::on_btnBackground_clicked()
{
    QColor color = QColorDialog::getColor(ui->renderArea->backgroundColor(), this, "Select Color");
    ui->renderArea->setBackgroundColor(color);

}

void MainWindow::on_btnLinecolor_clicked()
{
    QColor color = QColorDialog::getColor(ui->renderArea->shapeColor (), this, "Select Color");
    ui->renderArea->setShapeColor(color);
}
