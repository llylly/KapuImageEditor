#include "HistogramDialog.h"

HistogramDialog::HistogramDialog(QWidget *parent): QDialog(parent)
{
    mainView = new HistogramView();
    bottomLayout = new QHBoxLayout();
    bottomSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding);
    okButton = new QPushButton(this);
    okButton->setText(Constants::OK.c_str());
    okButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    bottomLayout->addSpacerItem(bottomSpacer);
    bottomLayout->addWidget(okButton);
    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(mainView);
    mainLayout->addLayout(bottomLayout);
    mainLayout->setMargin(5);
    this->setLayout(mainLayout);
    this->setModal(true);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);
    this->setWindowTitle(Constants::HISTOGRAM_DIALOG.c_str());
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(hide()));
}

void HistogramDialog::setHistogram(Histogram *hist) {
    mainView->setHistogram(hist);
}

void HistogramDialog::resizeEvent(QResizeEvent *event) {
    this->mainView->reDraw();
    QDialog::resizeEvent(event);
}

void HistogramDialog::reDraw() {
    this->mainView->reDraw();
}
