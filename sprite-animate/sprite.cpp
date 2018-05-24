#include "sprite.h"

#include <QPaintEvent>
#include <QPainter>

Sprite::Sprite(QWidget *parent) : QWidget(parent)
{
    sprite_sheet = QPixmap(":/orc_01.png");
    for(int i=0;i<9;i++)
    {
        //frames[i] = new QRect(i*64,0,64,64); // arm flap
        frames[i] = new QRect(i*64,11*64,64,64); // arm flap

    }
    current_frame=0;
    setFixedSize(200,200);
}

void Sprite::advance()
{
    current_frame++;
    if(current_frame == 6)
    {
        current_frame = 0;
    }
    repaint();
}

void Sprite::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(event->rect(),sprite_sheet,*frames[current_frame]);
}
