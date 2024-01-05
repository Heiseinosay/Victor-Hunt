#include "mainwindow.h"
#include "qdatetime.h"
#include "ui_mainwindow.h"
#include "QThread"

#include <QPixmap>
#include <QPainter>
#include "inputform.h"


#include <QMessageBox>
#include <QTextStream>
#include <QTextBlock>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    setWindowFlag(Qt::FramelessWindowHint);

    ui->setupUi(this);
    // Disable Resize
    this->setFixedSize(QSize(526, 303));

    // SET FONT
    int id = QFontDatabase::addApplicationFont(":/font/fonts/MarsBrandsMain.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont marsBrandsMain(family, 28);
    ui->label->setFont(marsBrandsMain);
    ui->label_3->setFont(marsBrandsMain);




    ui->btCreate->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show()
{
    QMainWindow::show();
    qDebug() << "Hellow";
    ui->btCreate->click();
}



void MainWindow::on_btCreate_clicked()
{
    for (int counter = 0; counter <= 200; counter ++){
        QThread::msleep(10);
        ui->progressBar->setValue(counter);
        qApp->processEvents(QEventLoop::AllEvents);
    }
    close();
    InputForm inputForm;
    inputForm.setModal(true);
    inputForm.exec();
    qApp->exit();
}

