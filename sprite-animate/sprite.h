#ifndef SPRITE_H
#define SPRITE_H

#include <QWidget>
#include <QPixmap>

class Sprite : public QWidget
{
    Q_OBJECT
public:
    explicit Sprite(QWidget *parent = nullptr);
    void advance();

signals:

public slots:
    void paintEvent(QPaintEvent* event);

private:
    QPixmap sprite_sheet;
    QRect *frames[7];
    int current_frame;
};

#endif // SPRITE_H
