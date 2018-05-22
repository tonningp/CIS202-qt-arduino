#include "wiper.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>

const int R=200;
Wiper::Wiper(QWidget *parent) :
    QWidget(parent),
    m_origin(QPoint(R,R))
{
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::white);
    p.setColor(QPalette::Text, Qt::black);
    setPalette(p);
    setFixedSize(600,600);
}

void Wiper::setDegree(int degree)
{
    double rad = degree * M_PI/180.0;
    m_endpoint.setX(R*qCos(rad)+R);
    m_endpoint.setY(R*qSin(rad)+R);
    update();
}

void Wiper::paintEvent(QPaintEvent *paint)
{
    Q_UNUSED(paint);
    QPainter painter(this);
    painter.drawEllipse(m_origin,R,R);
    painter.drawLine(m_origin,m_endpoint);
}

