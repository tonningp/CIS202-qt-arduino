#include "mainwindow.h"
#include "console.h"
#include <QDebug>
#include <QMessageBox>
#include <sstream>      // std::stringstream

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_serial(new QSerialPort(this)),
    m_console(new Console(this)),
    m_wiper(new Wiper(this))
{
    button[0] = new QPushButton("LED 1",this);
    button[0]->setCheckable(true);
    label[0] = new QLabel("Off",this);
    label[0]->move(button[0]->pos()+QPoint(button[0]->width()+5,0));
    button[1] = new QPushButton("LED 2",this);
    button[1]->move(button[0]->pos()+QPoint(0,button[0]->height()+5));
    button[1]->setCheckable(true);
    label[1] = new QLabel("Off",this);
    label[1]->move(button[0]->pos()+QPoint(button[0]->width()+5,button[0]->height()+5));
    button[2] = new QPushButton("LED 3",this);
    button[2]->move(button[1]->pos()+QPoint(0,button[1]->height()+5));
    button[2]->setCheckable(true);
    label[2] = new QLabel("Off",this);
    label[2]->move(button[1]->pos()+QPoint(button[1]->width()+5,button[1]->height()+5));
    m_console->move(button[2]->pos()+QPoint(0,button[2]->height()+5));
    m_console->setEnabled(true);
    connect(button[0],SIGNAL(toggled(bool)),this,SLOT(onbutton1Press(bool)));
    connect(button[1],SIGNAL(toggled(bool)),this,SLOT(onbutton2Press(bool)));
    connect(button[2],SIGNAL(toggled(bool)),this,SLOT(onbutton3Press(bool)));
    connect(m_serial, &QSerialPort::errorOccurred, this, &MainWindow::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    openSerialPort();
    m_led_state[0] = 0;
    m_led_state[1] = 0;
    m_led_state[2] = 0;
    setFixedSize(800,600);
    m_wiper->move(m_console->pos()+QPoint(button[2]->width(),m_console->height()+5));

}

MainWindow::~MainWindow()
{
   closeSerialPort();
}

void MainWindow::onbutton1Press(bool toggled)
{
    toggle_it(toggled,0,3);
}

void MainWindow::onbutton2Press(bool toggled)
{
    toggle_it(toggled,1,5);
}

void MainWindow::onbutton3Press(bool toggled)
{
  toggle_it(toggled,2,6);
}

void MainWindow::sendData(const QString &data)
{
    m_serial->write((data+"\n").toUtf8());
}

void MainWindow::processMessage(const QString &b)
{

    auto values = b.split(":");
    if(values[0] == "V") {
        float cel = values[1].toInt()/4 * 0.48828125;
        float fahr = cel * 9.0/5.0 + 32;
        m_wiper->setDegree(360/1023.0*values[1].toFloat());
        std::stringstream ss;
        ss << values[1].toInt() << " " << cel << " " << fahr;
        m_console->setText(ss.str().c_str());
    }
}

void MainWindow::toggle_it(bool toggled,int button,int led_pin)
{
    if(toggled) {
        label[button]->setText("On");
        m_led_state[led_pin] = 255;
    }
    else {
        label[button]->setText("Off");
        m_led_state[led_pin] = 0;
    }
    sendData(QString("%1:%2").arg(led_pin).arg(m_led_state[led_pin]));

}

void MainWindow::readData()
{
    //const QByteArray data = m_serial->readAll();
    m_buffer += QString( m_serial->readAll());
    if(m_buffer.contains('\n') && m_buffer.contains('\r'))
    {
        m_buffer.chop(2);
        processMessage(m_buffer);
        m_buffer = "";
    }
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::openSerialPort()
{
    m_serial->setPortName("tty.usbmodem1441");
    m_serial->setBaudRate(QSerialPort::Baud9600);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Serial Opened";
    } else {
        QMessageBox::critical(this, tr("Error"), m_serial->errorString());
    }
}

void MainWindow::closeSerialPort()
{
    if (m_serial->isOpen())
        m_serial->close();
    qDebug() << "Serial Closed";
}
