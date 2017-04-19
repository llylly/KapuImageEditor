#include "KImageView.h"

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
        this->show();
    }
}

void KImageView::loadImage() {
    Image *img = Image::getCurImage();
    return KImageView::loadImage(img);
}
