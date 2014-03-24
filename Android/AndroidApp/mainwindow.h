#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpServer* server;
    QTcpSocket* socket;
private slots:
    void newConnection();
    void readyRead();
    void disconnect();

    void on_sendButton_clicked();
};

#endif // MAINWINDOW_H
