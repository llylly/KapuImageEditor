#include "KImageView.h"

const int KImageView::width = 1;
const QBrush KImageView::back = QBrush(QColor(255, 162, 162, 100));
const QBrush KImageView::line = QBrush(QColor(255, 0, 0));
const QPen KImageView::linePen = QPen(KImageView::line, KImageView::width);
const int KImageView::pointRadius = 6;

KImageView::KImageView(QWidget *parent): QGraphicsView(parent)
{
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    scene = new QGraphicsScene();
    this->setScene(scene);
}

KImageView::KImageView(QWidget *parent, Image *img): QGraphicsView(parent) {
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    scene = new QGraphicsScene();
    this->setScene(scene);
    loadImage(img);
}

KImageView::~KImageView() {
    delete scene;
}

void KImageView::loadImage(Image *img) {
    if (img != NULL) {
        scene->clear();
        scene->setSceneRect(0, 0, img->width, img->height);
        scene->addPixmap(*(img->toQPixmap()));
        for (vector<KeyPoint>::iterator ite = img->pointSet.begin(); ite != img->pointSet.end(); ++ite) {
            scene->addEllipse(ite->c - KImageView::pointRadius / 2, ite->r - KImageView::pointRadius / 2,
                              pointRadius, pointRadius, KImageView::linePen, KImageView::back);
        }
        this->show();
    } else
        scene->clear();
}

void KImageView::loadImage() {
    Image *img = Image::getCurImage();
    return KImageView::loadImage(img);
}
