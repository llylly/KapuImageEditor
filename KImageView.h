#ifndef KIMAGEVIEW_H
#define KIMAGEVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "Image.h"

class KImageView : public QGraphicsView
{
public:
    KImageView(QWidget *parent);
    KImageView(QWidget *parent, Image *img);
    ~KImageView();
    void loadImage(Image *img);
    void loadImage();

private:
    QGraphicsScene *scene;
};

#endif // KIMAGEVIEW_H
