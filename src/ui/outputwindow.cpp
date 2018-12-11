#include "outputwindow.h"
#include "ui_outputwindow.h"

outputWindow::outputWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::outputWindow)
{
    ui->setupUi(this);
}

outputWindow::~outputWindow()
{
    delete ui;
}

void outputWindow::appendOut(QString text)
{
    ui->txb_out->append(text);
}
