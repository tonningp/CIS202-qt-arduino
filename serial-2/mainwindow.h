#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QSerialPort>

class Console;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void openSerialPort();
    void closeSerialPort();
    void handleError(QSerialPort::SerialPortError error);
    void readData();

public slots:
    void onbutton1Press(bool toggled);
    void onbutton2Press(bool toggled);
    void onbutton3Press(bool toggled);


private:
    QPushButton *button[3];
    QLabel *label[3];
    QSerialPort *m_serial = nullptr;
    int m_led_state[54];
    QString m_buffer;
    Console *m_console = nullptr;
    void sendData(const QString &data);
    void processMessage(const QString &b);
    void toggle_it(bool toggled,int button,int led_pin);
};

#endif // MAINWINDOW_H
