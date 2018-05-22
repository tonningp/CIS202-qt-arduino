#ifndef CONSOLE_H
#define CONSOLE_H

#include <QTextBrowser>
class Console : public QTextBrowser
{
    Q_OBJECT

signals:
    void getData(const QByteArray &data);

public:
    explicit Console(QWidget *parent = nullptr);

    void putData(const QString &data);
    void setLocalEchoEnabled(bool set);

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    void contextMenuEvent(QContextMenuEvent *e) override;

private:
    bool m_localEchoEnabled = false;
};

#endif // CONSOLE_H
