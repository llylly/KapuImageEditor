#include "ContrastDialog.h"

#define ILLEGAL_V -2147483648

ContrastDialog::ContrastDialog()
{
    init();
}

ContrastDialog::ContrastDialog(QWidget *parent): QDialog(parent) {
    init();
}

void ContrastDialog::init() {
    available = false;
    minV = maxV = 0;
    mainLayout = new QGridLayout();
    minLabel = new QLabel(Constants::CONTRAST_MIN.c_str());
    maxLabel = new QLabel(Constants::CONTRAST_MAX.c_str());
    cautionLabel = new QLabel(Constants::CONTRAST_DIALOG_CAPTION.c_str());
    minEdit = new QLineEdit();
    maxEdit = new QLineEdit();
    okButton = new QPushButton(Constants::OK.c_str());
    mainLayout->addWidget(minLabel, 0, 0, 1, 1);
    mainLayout->addWidget(maxLabel, 0, 1, 1, 1);
    mainLayout->addWidget(minEdit, 1, 0, 1, 1);
    mainLayout->addWidget(maxEdit, 1, 1, 1, 1);
    mainLayout->addWidget(cautionLabel, 2, 0, 1, 2);
    mainLayout->addWidget(okButton, 3, 1, 1, 1);
    this->setLayout(mainLayout);
    this->setFixedSize(Constants::CONTRAST_DIALOG_W, Constants::CONTRAST_DIALOG_H);
    minEdit->setText("0");
    maxEdit->setText("255");
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(onClose()));
}

int ContrastDialog::getValue(QLineEdit *edit) {
    string s = edit->text().toStdString();
    bool legal = true;
    for (int i=0; i<s.length(); ++i)
        if (s[i] >= '0' && s[i] <= '9') ; else legal = false;
    int v;
    if (legal) {
        v = atoi(s.c_str());
        if ((v < 0) || (v > 255)) legal = false;
    }
    if (legal) return v; else {
        QMessageBox::information(this, Constants::BRIGHT_CAPTION.c_str(), Constants::ILLEGAL_VALUE.c_str(), QMessageBox::Ok);
        return ILLEGAL_V;
    }
}

void ContrastDialog::onClose() {
    int v0 = getValue(minEdit);
    int v1 = getValue(maxEdit);
    if (v0 != ILLEGAL_V && v1 != ILLEGAL_V) {
        minV = v0, maxV = v1, available = true;
        this->close();
    }
}
