#include "HistogramView.h"

const QColor HistogramView::BG = QColor(255, 255, 255);
const QColor HistogramView::RLine = QColor(255, 0, 0);
const QColor HistogramView::GLine = QColor(0, 151, 0);
const QColor HistogramView::BLine = QColor(0, 0, 255);
const QColor HistogramView::RBgLine = QColor(255, 184, 184);
const QColor HistogramView::GBgLine = QColor(179, 255, 179);
const QColor HistogramView::BBgLine = QColor(179, 224, 255);

HistogramView::HistogramView(QWidget *parent): QGridLayout(parent) {
    init();
}

HistogramView::HistogramView() {
    init();
}

void HistogramView::init()
{
    RView = new QGraphicsView();
    RView->setFrameStyle(QFrame::NoFrame);
    RView->setDragMode(QGraphicsView::NoDrag);
    GView = new QGraphicsView();
    GView->setFrameStyle(QFrame::NoFrame);
    GView->setDragMode(QGraphicsView::NoDrag);
    BView = new QGraphicsView();
    BView->setFrameStyle(QFrame::NoFrame);
    BView->setDragMode(QGraphicsView::NoDrag);
    RScene = new QGraphicsScene();
    GScene = new QGraphicsScene();
    BScene = new QGraphicsScene();
    RLabel = new QLabel(Constants::RED.c_str());
    RLabel->setAlignment(Qt::AlignHCenter);
    GLabel = new QLabel(Constants::GREEN.c_str());
    GLabel->setAlignment(Qt::AlignHCenter);
    BLabel = new QLabel(Constants::BLUE.c_str());
    BLabel->setAlignment(Qt::AlignHCenter);
    this->addWidget(RView, 0, 0, 1, 1);
    this->addWidget(GView, 0, 1, 1, 1);
    this->addWidget(BView, 0, 2, 1, 1);
    this->addWidget(RLabel, 1, 0, 1, 1);
    this->addWidget(GLabel, 1, 1, 1, 1);
    this->addWidget(BLabel, 1, 2, 1, 1);

    histogram = NULL;
}

void HistogramView::setHistogram(Histogram *hist) {
    if (histogram != NULL) delete histogram;
    this->histogram = new Histogram(*hist);
}

void HistogramView::reDraw() {

    QImage *RImage = new QImage(RView->size().width(), RView->size().height(), QImage::Format_RGB32);
    RImage->fill(HistogramView::BG);
    double rmax = this->histogram->getMax(Histogram::R);
    double rratio = 1.0f;
    if (rmax <= 0.5) rratio = 0.5f / rmax;
    double rstep = ((double)Histogram::maxV) / ((double)((RImage->width() > 1) ? (RImage->width() - 1) : 1));
    double rp = 0.0f;
    for (int i=0; i<RImage->width(); ++i, rp+=rstep) {
        double v = this->histogram->getValue(Histogram::R, rp);
        int upper = (int)(v * rratio * (RImage->height() - 1) + 0.5f);
        for (int j=RImage->height()-1; j >= RImage->height()-upper; --j)
            RImage->setPixelColor(i, j, HistogramView::RBgLine);
    }
    rp = 0.0f; int rpre = 0;
    for (int i=0; i<RImage->width(); ++i, rp+=rstep) {
        double v = this->histogram->getValue(Histogram::sumR, rp);
        int pix = (int)(v * (RImage->height() - 1) + 0.5f);
        for (int j=rpre+1; j<=pix; ++j)
            RImage->setPixelColor(i, RImage->height() - 1 - j, HistogramView::RLine);
        if (rpre == pix)
            RImage->setPixelColor(i, RImage->height() - 1 - rpre, HistogramView::RLine);
        rpre = pix;
    }
    RScene->clear();
    RScene->addPixmap(QPixmap::fromImage(*RImage));
    RScene->setSceneRect(0, 0, RImage->width(), RImage->height());
    RView->setScene(RScene);

    QImage *GImage = new QImage(GView->size().width(), GView->size().height(), QImage::Format_RGB32);
    GImage->fill(HistogramView::BG);
    double gmax = this->histogram->getMax(Histogram::G);
    double gratio = 1.0f;
    if (gmax <= 0.5) gratio = 0.5f / gmax;
    double gstep = ((double)Histogram::maxV) / ((double)((GImage->width() > 1) ? (GImage->width() - 1) : 1));
    double gp = 0.0f;
    for (int i=0; i<GImage->width(); ++i, gp+=gstep) {
        double v = this->histogram->getValue(Histogram::G, gp);
        int upper = (int)(v * gratio * (GImage->height() - 1) + 0.5f);
        for (int j=GImage->height()-1; j >= GImage->height()-upper; --j)
            GImage->setPixelColor(i, j, HistogramView::GBgLine);
    }
    gp = 0.0f; int gpre = 0;
    for (int i=0; i<GImage->width(); ++i, gp+=gstep) {
        double v = this->histogram->getValue(Histogram::sumG, gp);
        int pix = (int)(v * (GImage->height() - 1) + 0.5f);
        for (int j=gpre+1; j<=pix; ++j)
            GImage->setPixelColor(i, GImage->height() - 1 - j, HistogramView::GLine);
        if (gpre == pix)
            GImage->setPixelColor(i, GImage->height() - 1 - gpre, HistogramView::GLine);
        gpre = pix;
    }
    GScene->clear();
    GScene->addPixmap(QPixmap::fromImage(*GImage));
    GScene->setSceneRect(0, 0, GImage->width(), GImage->height());
    GView->setScene(GScene);

    QImage *BImage = new QImage(BView->size().width(), BView->size().height(), QImage::Format_RGB32);
    BImage->fill(HistogramView::BG);
    double bmax = this->histogram->getMax(Histogram::B);
    double bratio = 1.0f;
    if (bmax <= 0.5) bratio = 0.5f / bmax;
    double bstep = ((double)Histogram::maxV) / ((double)((BImage->width() > 1) ? (BImage->width() - 1) : 1));
    double bp = 0.0f;
    for (int i=0; i<BImage->width(); ++i, bp+=bstep) {
        double v = this->histogram->getValue(Histogram::B, bp);
        int upper = (int)(v * bratio * (BImage->height() - 1) + 0.5f);
        for (int j=BImage->height()-1; j >= BImage->height()-upper; --j)
            BImage->setPixelColor(i, j, HistogramView::BBgLine);
    }
    bp = 0.0f; int bpre = 0;
    for (int i=0; i<BImage->width(); ++i, bp+=bstep) {
        double v = this->histogram->getValue(Histogram::sumB, bp);
        int pix = (int)(v * (BImage->height() - 1) + 0.5f);
        for (int j=bpre+1; j<=pix; ++j)
            BImage->setPixelColor(i, BImage->height() - 1 - j, HistogramView::BLine);
        if (bpre == pix)
            BImage->setPixelColor(i, BImage->height() - 1 - bpre, HistogramView::BLine);
        bpre = pix;
    }
    BScene->clear();
    BScene->addPixmap(QPixmap::fromImage(*BImage));
    BScene->setSceneRect(0, 0, BImage->width(), BImage->height());
    BView->setScene(BScene);
}
