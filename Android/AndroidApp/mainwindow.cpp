#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();

    server = new QTcpServer(this);

    connect(server,SIGNAL(newConnection()), this, SLOT(newConnection()));

    if (!server->listen(QHostAddress::Any,4568)) {
        QMessageBox::critical(this, tr("ADK Server"),
                            tr("Unable to start ADK the server: %1.")
                            .arg(server->errorString()));
        close();
        return;
    }
    ui->progressBar->setMaximum(1023);
    ui->progressBar->setValue(0);

}

void MainWindow::newConnection()
{
    socket = server->nextPendingConnection();
    connect(socket,SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void MainWindow::readyRead()
{
    QByteArray data = socket->readAll();
    ui->datavalue->setText(data);

    ui->progressBar->setValue(data.toInt());
}

MainWindow::~MainWindow()
{
    delete ui;
}
