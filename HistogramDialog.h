#ifndef HISTOGRAMDIALOG_H
#define HISTOGRAMDIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpacerItem>
#include <QResizeEvent>
#include "Constants.h"
#include "HistogramView.h"

class HistogramDialog : public QDialog
{
private:
    HistogramView *mainView;
    QPushButton *okButton;
    QVBoxLayout *mainLayout;
    QHBoxLayout *bottomLayout;
    QSpacerItem *bottomSpacer;

public:
    HistogramDialog(QWidget *parent);
    void setHistogram(Histogram *hist);

    void resizeEvent(QResizeEvent* size);

public slots:
    void reDraw();
};

#endif // HISTOGRAMDIALOG_H
