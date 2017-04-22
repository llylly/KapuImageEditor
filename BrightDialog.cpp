#include "BrightDialog.h"

#define ILLEGAL_V -2147483648

const int BrightDialog::NoType = 0;
const int BrightDialog::UniformType = 1;
const int BrightDialog::SeparateType = 2;

BrightDialog::BrightDialog(QWidget *parent): QDialog(parent) {
    init();
}


BrightDialog::BrightDialog() {
    init();
}

void BrightDialog::radioChanged() {
    if (!uniformRadio->isChecked())
        uniformWidget->setVisible(false);
    if (!separateRadio->isChecked())
        separateWidget->setVisible(false);
    if (uniformRadio->isChecked())
        uniformWidget->setVisible(true);
    if (separateRadio->isChecked())
        separateWidget->setVisible(true);
}

void BrightDialog::init() {
    type = BrightDialog::NoType;
    value0 = value1 = value2 = 0;

    mainLayout = new QVBoxLayout();
    upperLayout = new QHBoxLayout();
    uniformRadio = new QRadioButton();
    uniformRadio->setText(Constants::BRIGHT_UNIFORM.c_str());
    uniformRadio->setChecked(true);
    separateRadio = new QRadioButton();
    separateRadio->setText(Constants::BRIGHT_SEPARATE.c_str());
    separateRadio->setChecked(false);
    upperLayout->addWidget(uniformRadio);
    upperLayout->addWidget(separateRadio);
    mainLayout->addLayout(upperLayout);
    uniformWidget = new QGroupBox();
    uniformGridLayout = new QGridLayout();
    uniformWidget->setLayout(uniformGridLayout);
    uniformLabel = new QLabel(Constants::BRIGHT_DELTA.c_str());
    uniformEdit = new QLineEdit();
    uniformGridLayout->addWidget(uniformLabel, 0, 0, 1, 1);
    uniformGridLayout->addWidget(uniformEdit, 1, 0, 1, 1);
    mainLayout->addWidget(uniformWidget);
    separateWidget = new QGroupBox();
    separateGridLayout = new QGridLayout();
    separateWidget->setLayout(separateGridLayout);
    RLabel = new QLabel(Constants::BRIGHT_RDELTA.c_str());
    REdit = new QLineEdit();
    GLabel = new QLabel(Constants::BRIGHT_GDELTA.c_str());
    GEdit = new QLineEdit();
    BLabel = new QLabel(Constants::BRIGHT_BDELTA.c_str());
    BEdit = new QLineEdit();
    separateGridLayout->addWidget(RLabel, 0, 0, 1, 1);
    separateGridLayout->addWidget(GLabel, 0, 1, 1, 1);
    separateGridLayout->addWidget(BLabel, 0, 2, 1, 1);
    separateGridLayout->addWidget(REdit, 1, 0, 1, 1);
    separateGridLayout->addWidget(GEdit, 1, 1, 1, 1);
    separateGridLayout->addWidget(BEdit, 1, 2, 1, 1);
    mainLayout->addWidget(separateWidget);
    cautionLabel = new QLabel(Constants::BRIGHT_DIALOG_CAPTION.c_str());
    mainLayout->addWidget(cautionLabel);
    spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding);
    okButton = new QPushButton(Constants::OK.c_str());
    bottomLayout = new QHBoxLayout();
    bottomLayout->addSpacerItem(spacer);
    bottomLayout->addWidget(okButton);
    mainLayout->addLayout(bottomLayout);
    this->setLayout(mainLayout);
    this->setMaximumSize(Constants::BRIGHT_DIALOG_W, Constants::BRIGHT_DIALOG_H);
    this->setMinimumSize(Constants::BRIGHT_DIALOG_W, Constants::BRIGHT_DIALOG_H);
    mainLayout->setSpacing(2);

    uniformEdit->setText("0");
    REdit->setText("0");
    GEdit->setText("0");
    BEdit->setText("0");

    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(onClose()));
    connect(uniformRadio, SIGNAL(toggled(bool)), this, SLOT(radioChanged()));
    connect(separateRadio, SIGNAL(toggled(bool)), this, SLOT(radioChanged()));
    radioChanged();
}

void BrightDialog::onClose() {
    if (uniformRadio->isChecked()) {
        int x = getValue(uniformEdit);
        if (x != ILLEGAL_V) {
            type = BrightDialog::UniformType;
            value0 = x;
            this->close();
        }
    } else
    if (separateRadio->isChecked()) {
        int v0 = getValue(REdit), v1 = getValue(GEdit), v2 = getValue(BEdit);
        if ((v0 != ILLEGAL_V) && (v1 != ILLEGAL_V) && (v2 != ILLEGAL_V)) {
            type = BrightDialog::SeparateType;
            value0 = v0;
            value1 = v1;
            value2 = v2;
            this->close();
        }
    } else {
        type = BrightDialog::NoType;
        this->close();
    }
}

int BrightDialog::getValue(QLineEdit *edit) {
    string s = edit->text().toStdString();
    bool legal = true;
    for (int i=0; i<s.length(); ++i)
        if ((s[i] >= '0' && s[i] <= '9') || (s[i] == '-')) ; else legal = false;
    int v;
    if (legal) {
        v = atoi(s.c_str());
        if ((v < -255) || (v > 255)) legal = false;
    }
    if (legal) return v; else {
        QMessageBox::information(this, Constants::BRIGHT_CAPTION.c_str(), Constants::ILLEGAL_VALUE.c_str(), QMessageBox::Ok);
        return ILLEGAL_V;
    }
}
