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
    socket = NULL;

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
    ui->green_light->setEnabled(true);
    socket = server->nextPendingConnection();
    connect(socket,SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket,SIGNAL(disconnected()), this, SLOT(disconnect()));
}

void MainWindow::readyRead()
{
    QByteArray data = socket->readAll();
    QStringList dataValues = QString(data).split(":");
    ui->connection_label->setText(data);
    const QString& analog_number = QString::number(ui->AnalogRead->currentIndex());

    if(QString(data).startsWith("A"+analog_number))
    {
        ui->AnalogReadValue->setText(dataValues[1]);
        ui->progressBar->setValue(dataValues[1].toInt());
    }

    const QString& digital_number = QString(ui->digitalRead->currentText()[1]);

    if(QString(data).startsWith("D"+digital_number))
    {
        ui->digitalReadValue->setText(dataValues[1]);
    }
}

void MainWindow::disconnect()
{
    ui->green_light->setEnabled(false);
    socket->deleteLater();
    socket = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendButton_clicked()
{
    if(socket)
    {
        QString pinMode = "P"+QString::number(ui->pinMode->currentIndex())+":";
        pinMode+=QString::number(ui->pinModeValue->currentIndex());
        socket->write(pinMode.toStdString().data());
        socket->flush();

        QString digitalWrite = "D"+QString::number(ui->digitalWrite->currentIndex())+":";
        digitalWrite+=QString::number(ui->digitalWriteValue->currentIndex());
        socket->write(digitalWrite.toStdString().data());
        socket->flush();
    }
}
