#ifndef MAINWINDOW_H
#define MAINWINDOW_H
// https://doc.qt.io/qt-5/qtimer.html
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
    void readData();



private:
    QString m_buffer;
    Console *m_console = nullptr;
    void processMessage(const QString &b);
};

#endif // MAINWINDOW_H
