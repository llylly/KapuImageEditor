#include "DifferenceDialog.h"

DifferenceDialog::DifferenceDialog()
{
    init();
}

DifferenceDialog::DifferenceDialog(QWidget *parent) {
    init();
}

void DifferenceDialog::load(Image *left, Image *right) {
    scene->clear();
    int sceneWidth = left->width + right->width;
    int sceneHeight = max(left->height, right->height);
    int l1posw, l1posh, l2posw, l2posh;
    scene->setSceneRect(0, 0, sceneWidth, sceneHeight);
    QGraphicsPixmapItem* item1 = scene->addPixmap(*(left->toQPixmap()));
    item1->setPos(l1posw = 0, l1posh = (sceneHeight - left->height)/2);
    QGraphicsPixmapItem* item2 = scene->addPixmap(*(right->toQPixmap()));
    item2->setPos(l2posw = left->width, l2posh = (sceneHeight - right->height)/2);
    for (vector<KeyPoint>::iterator ite = left->pointSet.begin(); ite != left->pointSet.end(); ++ite) {
        if (ite->matched < 0)
            scene->addEllipse(l1posw + ite->c - ite->scale / 2, l1posh + ite->r - ite->scale / 2,
                              ite->scale, ite->scale, KImageView::linePen, KImageView::back);
        else
            scene->addEllipse(l1posw + ite->c - ite->scale / 2, l1posh + ite->r - ite->scale / 2,
                              ite->scale, ite->scale, KImageView::matchLinePen, KImageView::matchBack);
    }
    for (vector<KeyPoint>::iterator ite = right->pointSet.begin(); ite != right->pointSet.end(); ++ite) {
        if (ite->matched < 0) {
            scene->addEllipse(l2posw + ite->c - ite->scale / 2, l2posh + ite->r - ite->scale / 2,
                              ite->scale, ite->scale, KImageView::linePen, KImageView::back);
        } else {
            scene->addEllipse(l2posw + ite->c - ite->scale / 2, l2posh + ite->r - ite->scale / 2,
                              ite->scale, ite->scale, KImageView::matchLinePen, KImageView::matchBack);
            scene->addLine(l2posw + ite->c, l2posh + ite->r,
                           l1posw + (left->pointSet)[ite->matched].c, l1posh + (left->pointSet)[ite->matched].r,
                           KImageView::linkLinePen);
        }
    }
    view->show();
}

void DifferenceDialog::init() {
    mainLayout = new QVBoxLayout();
    imageLayout = new QHBoxLayout();
    view = new QGraphicsView();
    scene = new QGraphicsScene();
    imageLayout->addWidget(view);
    mainLayout->addLayout(imageLayout);
    okButton = new QPushButton(Constants::OK.c_str());
    okButton->setMaximumWidth(100);
    mainLayout->addWidget(okButton);
    this->setLayout(mainLayout);
    view->setScene(scene);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    this->setWindowTitle(Constants::DIFFERENCE_CAPTION.c_str());
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(close()));
}
