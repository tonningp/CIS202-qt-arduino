#include "mainwindow.h"
#include "console.h"
#include <QDebug>
#include <QMessageBox>
#include <QTime>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QLayout>
#include <sstream>      // std::stringstream

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    //m_console(new Console(this))
{
    //m_console->setEnabled(true);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(readData()));
    timer->start(1000);
    setFixedSize(800,600);
    QtCharts::QLineSeries *series = new QtCharts::QLineSeries();

    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart,this);
    chartView->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *vbox = new QVBoxLayout(this->centralWidget());
    vbox->setGeometry(QRect(0,0,640,480));
    vbox->addWidget(chartView);
    chartView->show();
}

MainWindow::~MainWindow()
{
}




void MainWindow::processMessage(const QString &b)
{

}

void MainWindow::readData()
{
    //const QByteArray data = m_serial->readAll();
    //m_buffer = QString("%1" ).arg( QDateTime::currentDateTime().toTime_t() );
    //processMessage(m_buffer);
    //m_buffer = "";
}

