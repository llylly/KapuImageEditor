#include "ZoomDialog.h"

const int ZoomDialog::NEAREST_NEIGHBOR = 1;
const int ZoomDialog::BILINEAR = 2;
const int ZoomDialog::BICUBIC = 3;
const int ZoomDialog::NO_TYPE = -1;

ZoomDialog::ZoomDialog() {
    init();
}

ZoomDialog::ZoomDialog(QWidget *parent): QDialog(parent) {
    init();
}

void ZoomDialog::init() {
    this->setWindowTitle(Constants::ZOOM_TITLE.c_str());

    mainLayout = new QVBoxLayout();
    upperLayout = new QHBoxLayout();
    typeGroup = new QButtonGroup();
    type1Radio = new QRadioButton();
    type1Radio->setText(Constants::ZOOM_NEAREST_NEIGHBOR.c_str());
    type2Radio = new QRadioButton();
    type2Radio->setText(Constants::ZOOM_BILINEAR.c_str());
    type3Radio = new QRadioButton();
    type3Radio->setText(Constants::ZOOM_BICUBIC.c_str());
    typeGroup->addButton(type1Radio);
    typeGroup->addButton(type2Radio);
    typeGroup->addButton(type3Radio);
    upperLayout->addWidget(type1Radio);
    upperLayout->addWidget(type2Radio);
    upperLayout->addWidget(type3Radio);
    middleLayout = new QGridLayout();
    originalGroup = new QGroupBox(Constants::ZOOM_ORIGINAL_SIZE.c_str());
    originalLayout = new QGridLayout();
    originalWLabel = new QLabel(Constants::ZOOM_WIDTH.c_str());
    originalHLabel = new QLabel(Constants::ZOOM_HEIGHT.c_str());
    originalWidth = new QLabel(Constants::ZOOM_UNKNOWN.c_str());
    originalHeight = new QLabel(Constants::ZOOM_UNKNOWN.c_str());
    originalLayout->addWidget(originalWLabel, 0, 0, 1, 1);
    originalLayout->addWidget(originalWidth, 0, 1, 1, 1);
    originalLayout->addWidget(originalHLabel, 1, 0, 1, 1);
    originalLayout->addWidget(originalHeight, 1, 1, 1, 1);
    originalGroup->setLayout(originalLayout);
    middleLayout->addWidget(originalGroup, 0, 0, 2, 1);
    byRatioRadio = new QRadioButton(Constants::ZOOM_BY_RATIO.c_str());
    middleLayout->addWidget(byRatioRadio, 0, 1, 1, 1);
    bySizeRadio = new QRadioButton(Constants::ZOOM_BY_SIZE.c_str());
    middleLayout->addWidget(bySizeRadio, 0, 2, 1, 1);
    byGroup = new QButtonGroup();
    byGroup->addButton(byRatioRadio);
    byGroup->addButton(bySizeRadio);
    ratioGroup = new QGroupBox(Constants::ZOOM_RATIO.c_str());
    ratioLayout = new QGridLayout();
    ratioWLabel = new QLabel(Constants::ZOOM_WIDTH.c_str());
    ratioWEdit = new QLineEdit("1.0");
    ratioHLabel = new QLabel(Constants::ZOOM_HEIGHT.c_str());
    ratioHEdit = new QLineEdit("1.0");
    ratioLayout->addWidget(ratioWLabel, 0, 0, 1, 1);
    ratioLayout->addWidget(ratioWEdit, 0, 1, 1, 1);
    ratioLayout->addWidget(ratioHLabel, 1, 0, 1, 1);
    ratioLayout->addWidget(ratioHEdit, 1, 1, 1, 1);
    ratioGroup->setLayout(ratioLayout);
    middleLayout->addWidget(ratioGroup, 1, 1, 1, 1);
    sizeGroup = new QGroupBox(Constants::ZOOM_SIZE.c_str());
    sizeLayout = new QGridLayout();
    sizeWLabel = new QLabel(Constants::ZOOM_WIDTH.c_str());
    sizeWEdit = new QLineEdit("0");
    sizeHLabel = new QLabel(Constants::ZOOM_HEIGHT.c_str());
    sizeHEdit = new QLineEdit("0");
    sizeLayout->addWidget(sizeWLabel, 0, 0, 1, 1);
    sizeLayout->addWidget(sizeWEdit, 0, 1, 1, 1);
    sizeLayout->addWidget(sizeHLabel, 1, 0, 1, 1);
    sizeLayout->addWidget(sizeHEdit, 1, 1, 1, 1);
    sizeGroup->setLayout(sizeLayout);
    middleLayout->addWidget(sizeGroup, 1, 2, 1, 1);
    cautionLabel = new QLabel(Constants::ZOOM_CAUTION.c_str());
    bottomLayout = new QHBoxLayout();
    spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding);
    okButton = new QPushButton(Constants::OK.c_str());
    bottomLayout->addSpacerItem(spacer);
    bottomLayout->addWidget(okButton);
    mainLayout->addLayout(upperLayout);
    mainLayout->addLayout(middleLayout);
    mainLayout->addWidget(cautionLabel);
    mainLayout->addLayout(bottomLayout);
    this->setLayout(mainLayout);

    this->setFixedSize(Constants::ZOOM_DIALOG_WIDTH, Constants::ZOOM_DIALOG_HEIGHT);;

    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(onClose()));
    connect(byRatioRadio, SIGNAL(toggled(bool)), this, SLOT(statRefresh()));
    connect(bySizeRadio, SIGNAL(toggled(bool)), this, SLOT(statRefresh()));
    connect(ratioWEdit, SIGNAL(textEdited(QString)), this, SLOT(statRefresh()));
    connect(ratioHEdit, SIGNAL(textEdited(QString)), this, SLOT(statRefresh()));
    connect(sizeWEdit, SIGNAL(textEdited(QString)), this, SLOT(statRefresh()));
    connect(sizeHEdit, SIGNAL(textEdited(QString)), this, SLOT(statRefresh()));

}

void ZoomDialog::updateImageStat() {
    if (Image::getCurImage() != NULL) {
        QString widthStr = QString::number(this->oldWidth = Image::getCurImage()->width);
        QString heightStr = QString::number(this->oldHeight = Image::getCurImage()->height);
        originalWidth->setText(widthStr);
        originalHeight->setText(heightStr);
        sizeWEdit->setText(widthStr);
        sizeHEdit->setText(heightStr);
    }
}

void ZoomDialog::onClose() {
    this->type = NO_TYPE;
    if (type1Radio->isChecked() || type2Radio->isChecked() || type3Radio->isChecked()) {
        int wpix = -1, hpix = -1;
        bool *ok = new bool(true);
        if (byRatioRadio->isChecked()) {
            double w = ratioWEdit->text().toDouble(ok);
            if (ok) {
                wpix = (int)(w * oldWidth + 0.5f);
            }
            double h = ratioHEdit->text().toDouble(ok);
            if (ok) {
                hpix = (int)(h * oldHeight + 0.5f);
            }
        } else
        if (bySizeRadio->isChecked()) {
            wpix = sizeWEdit->text().toInt(ok);
            if (!ok) wpix = -1;
            hpix = sizeHEdit->text().toInt(ok);
            if (!ok) hpix = -1;
        }
        if ((wpix <= 0) || (hpix <= 0)) wpix = hpix = -1;
        delete ok;
        if ((wpix <= 0) || (hpix <= 0) || (wpix > Constants::ZOOM_LIMIT) || (hpix > Constants::ZOOM_LIMIT)) {
            QMessageBox::information(this, Constants::ZOOM_TITLE.c_str(), Constants::ILLEGAL_VALUE.c_str(), QMessageBox::Ok);
        } else {
            if (type1Radio->isChecked()) type = NEAREST_NEIGHBOR; else
            if (type2Radio->isChecked()) type = BILINEAR; else
            if (type3Radio->isChecked()) type = BICUBIC; else
                type = NO_TYPE;
            newWidth = wpix, newHeight = hpix;
            this->close();
        }
    } else
        QMessageBox::information(this, Constants::ZOOM_TITLE.c_str(), Constants::ZOOM_NO_CHOOSE.c_str(), QMessageBox::Ok);
}

void ZoomDialog::showEvent(QShowEvent *event) {
    QDialog::showEvent(event);
    updateImageStat();
    ratioCheckInit();
    statRefresh();
}

void ZoomDialog::ratioCheckInit() {
    byRatioRadio->setChecked(true);
    bySizeRadio->setChecked(false);
}

void ZoomDialog::statRefresh() {
    if (byRatioRadio->isChecked()) {
        ratioGroup->setEnabled(true);
        sizeGroup->setEnabled(false);
        bool *ok = new bool(false);
        double w = ratioWEdit->text().toDouble(ok);
        if ((ok) && (w > 0.0f)) {
            int width = oldWidth * w + 0.5f;
            sizeWEdit->setText(QString::number(width));
        }
        double h = ratioHEdit->text().toDouble(ok);
        if ((ok) && (h > 0.0f)) {
            int height = oldHeight * h + 0.5f;
            sizeHEdit->setText(QString::number(height));
        }
        delete ok;
    } else
    if (bySizeRadio->isChecked()) {
        ratioGroup->setEnabled(false);
        sizeGroup->setEnabled(true);
        bool *ok = new bool(false);
        int wpix = sizeWEdit->text().toInt(ok);
        if ((ok) && (wpix > 0)) {
            double w = (double)wpix / (double)oldWidth;
            ratioWEdit->setText(QString::number(w, 'f', 3));
        }
        int hpix = sizeHEdit->text().toInt(ok);
        if ((ok) && (hpix > 0)) {
            double h = (double)hpix / (double)oldHeight;
            ratioHEdit->setText(QString::number(h, 'f', 3));
        }
        delete ok;
    }
}
