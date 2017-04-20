#include "BlurDialog.h"

const int BlurDialog::NO_TYPE = 0;
const int BlurDialog::UNIFORM = 1;
const int BlurDialog::GAUSSIAN = 2;
const int BlurDialog::MOSAIC = 3;

BlurDialog::BlurDialog()
{
    init();
}

BlurDialog::BlurDialog(QWidget *parent): QDialog(parent) {
    init();
}

void BlurDialog::init() {
    type = false;
    radius = 0;
    mainLayout = new QVBoxLayout();
    upperLayout = new QHBoxLayout();
    type1Radio = new QRadioButton(Constants::BLUR_UNIFORM.c_str());
    type2Radio = new QRadioButton(Constants::BLUR_GAUSSIAN.c_str());
    type3Radio = new QRadioButton(Constants::BLUR_MOSAIC.c_str());
    upperLayout->addWidget(type1Radio);
    upperLayout->addWidget(type2Radio);
    upperLayout->addWidget(type3Radio);
    mainLayout->addLayout(upperLayout);
    radiusLabel = new QLabel(Constants::BLUR_RADIUS.c_str());
    mainLayout->addWidget(radiusLabel);
    mainEdit = new QLineEdit("1");
    mainLayout->addWidget(mainEdit);
    okButton = new QPushButton(Constants::OK.c_str());
    mainLayout->addWidget(okButton);
    this->setLayout(mainLayout);
    this->setFixedSize(Constants::BLUR_DIALOG_W, Constants::BLUR_DIALOG_H);
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(onClose()));
}

void BlurDialog::onClose() {
    if (type1Radio->isChecked()) {
        type = BlurDialog::UNIFORM;
    } else
    if (type2Radio->isChecked()) {
        type = BlurDialog::GAUSSIAN;
    } else
    if (type3Radio->isChecked()) {
        type = BlurDialog::MOSAIC;
    } else {
        type = BlurDialog::NO_TYPE;
        QMessageBox::information(this, Constants::BLUR_CAPTION.c_str(), Constants::BLUR_NO_CHOOSE.c_str(), QMessageBox::Ok);
        return;
    }

    bool *ok = new bool(false);
    int value = this->mainEdit->text().toInt(ok);
    if ((!ok) || (value <= 0) || (value > Constants::BLUR_LIMIT)) {
        QMessageBox::information(this, Constants::BLUR_CAPTION.c_str(), Constants::BLUR_ILLEGAL_VALUE.c_str(), QMessageBox::Ok);
    } else {
        radius = value;
        this->close();
    }
}
