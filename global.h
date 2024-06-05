#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>
#include <QPushButton>

inline void setGradient(QWidget *widget)
{
    QLinearGradient gradient(0, 0, 0, widget->height());
    gradient.setColorAt(0, QColor(3, 76, 140));
    gradient.setColorAt(1, QColor(39, 140, 122));
    QBrush brush(gradient);
    QPalette palette;
    palette.setBrush(QPalette::Window, brush);
    widget->setPalette(palette);
}

inline void goBack(QWidget *widget)
{
    if (widget){
        widget->hide();
    }
}

#endif // GLOBAL_H
