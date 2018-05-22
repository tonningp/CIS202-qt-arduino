#ifndef WIPER_H
#define WIPER_H

#include <QWidget>

class Wiper : public QWidget
{
    Q_OBJECT
public:
    explicit Wiper(QWidget *parent = nullptr);
    void setDegree(int degree);

protected:
    void paintEvent(QPaintEvent* paint) override;

private:
    QPoint m_origin;
    QPoint m_endpoint;
};

#endif // WIPER_H
