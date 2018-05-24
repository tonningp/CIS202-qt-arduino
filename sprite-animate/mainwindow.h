#ifndef MAINWINDOW_H
#define MAINWINDOW_H
// https://doc.qt.io/qt-5/qtimer.html
#include "ballanimation.h"
#include "sprite.h"
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>

class Console;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void animate();

public slots:
    void onbutton1Press(bool toggled);


private:
    QPushButton *button[3];
    QLabel *label[3];
    int m_led_state[54];
    QString m_buffer;
    Console *m_console = nullptr;
    void processMessage(const QString &b);
    void toggle_it(bool toggled,int button,int led_pin);
    Sprite *sprite;
};

#endif // MAINWINDOW_H
