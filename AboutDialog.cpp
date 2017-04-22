#include "AboutDialog.h"

const string AboutDialog::aboutCaption =
        "Written by lly\n"
        "limyik.li96@gmail.com\n"
        "DSP Project I";

AboutDialog::AboutDialog()
{
    init();
}

AboutDialog::AboutDialog(QWidget *widget): QDialog(widget) {
    init();
}

void AboutDialog::init() {
    mainLayout = new QVBoxLayout();
    label = new QLabel(AboutDialog::aboutCaption.c_str());
    label->setAlignment(Qt::AlignCenter);
    okButton = new QPushButton(Constants::OK.c_str());
    mainLayout->addWidget(label);
    mainLayout->addWidget(okButton);
    this->setLayout(mainLayout);
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    this->setFixedSize(Constants::ABOUT_DIALOG_WIDTH, Constants::ABOUT_DIALOG_HEIGHT);
}
