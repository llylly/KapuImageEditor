#ifndef HISTOGRAMVIEW_H
#define HISTOGRAMVIEW_H

#include <QObject>
#include <QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QColor>
#include "Constants.h"
#include "Histogram.h"

class HistogramView : public QGridLayout
{
    Q_OBJECT

private:
    static const QColor BG, RLine, GLine, BLine, RBgLine, GBgLine, BBgLine;

    QGraphicsView *RView;
    QGraphicsView *GView;
    QGraphicsView *BView;
    QGraphicsScene *RScene;
    QGraphicsScene *GScene;
    QGraphicsScene *BScene;
    QLabel *RLabel, *GLabel, *BLabel;

    Histogram *histogram;

    void init();

public:
    HistogramView(QWidget *parent);
    HistogramView();
    void setHistogram(Histogram *hist);

public slots:
    void reDraw();
};

#endif // HISTOGRAMVIEW_H
