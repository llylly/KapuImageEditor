#ifndef DIFFERENCEDIALOG_H
#define DIFFERENCEDIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "Constants.h"
#include "KImageView.h"
#include "Image.h"

class DifferenceDialog: public QDialog
{
public:
    DifferenceDialog();
    DifferenceDialog(QWidget *parent);

    void load(Image *left, Image *right);

private:
    void init();

    QGraphicsView *view;
    QGraphicsScene *scene;
    QVBoxLayout *mainLayout;
    QHBoxLayout *imageLayout;
    QPushButton *okButton;
};

#endif // DIFFERENCEDIALOG_H
