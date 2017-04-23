#ifndef KIMAGEVIEW_H
#define KIMAGEVIEW_H

#include <vector>
#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QBrush>
#include <QPen>
#include "Image.h"

using namespace std;

class KImageView : public QGraphicsView
{
public:
    static const int width;
    static const QBrush back, line;
    static const QBrush matchBack, matchLine;
    static const QPen linePen;
    static const QPen matchLinePen;
    static const QPen linkLinePen;
    static const int pointRadius;

    KImageView(QWidget *parent);
    KImageView(QWidget *parent, Image *img);
    ~KImageView();
    void loadImage(Image *img);
    void loadImage();

private:
    QGraphicsScene *scene;
};

#endif // KIMAGEVIEW_H
