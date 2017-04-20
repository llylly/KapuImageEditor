#include "ZoomDialog.h"

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
    type1Radio = new QRadioButton();
    type1Radio->setText(Constants::ZOOM_NEAREST_NEIGHBOR.c_str());
    type2Radio = new QRadioButton();
    type2Radio->setText(Constants::ZOOM_BILINEAR.c_str());
    type3Radio = new QRadioButton();
    type3Radio->setText(Constants::ZOOM_BICUBIC.c_str());
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
    bottomLayout = new QHBoxLayout();
    spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding);
    okButton = new QPushButton(Constants::OK.c_str());
    bottomLayout->addSpacerItem(spacer);
    bottomLayout->addWidget(okButton);
    mainLayout->addLayout(upperLayout);
    mainLayout->addLayout(middleLayout);
    mainLayout->addLayout(bottomLayout);
    this->setLayout(mainLayout);

    this->setFixedSize(Constants::ZOOM_DIALOG_WIDTH, Constants::ZOOM_DIALOG_HEIGHT);;

    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(onClose()));
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
    this->close();
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

}
