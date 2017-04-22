#include "PSNRDialog.h"

PSNRDialog::PSNRDialog()
{
    this->init();
}

PSNRDialog::PSNRDialog(QWidget *parent): QDialog(parent) {
    this->init();
}

void PSNRDialog::init() {
    mainLayout = new QVBoxLayout();
    mainLabel = new QLabel();
    okButton = new QPushButton(Constants::OK.c_str());
    mainLayout->addWidget(mainLabel);
    mainLayout->addWidget(okButton);
    this->setLayout(mainLayout);
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    this->setFixedSize(Constants::PSNR_DIALOG_W, Constants::PSNR_DIALOG_H);
}

void PSNRDialog::initData(PSNRData data) {
    string s;
    ostringstream os(s);
    if (!data.avail)
        os << "Invalid PSNR data." << endl;
    else {
        os << "Mean Squared Error (MSE):" << endl;
        os << "    R Channel: " << data.RMSE << endl;
        os << "    G Channel: " << data.GMSE << endl;
        os << "    B Channel: " << data.BMSE << endl;
        os << "-------------------------" << endl;
        os << "Peak Signal-To-Noise Ratio (PSNR):" << endl;
        os << "    R Channel: " << data.RPSNR << " dB" << endl;
        os << "    G Channel: " << data.GPSNR << " dB" << endl;
        os << "    B Channel: " << data.BPSNR << " dB" << endl;
        os << "-------------------------" << endl;
        os << "Overall PSNR: " << data.PSNR << " dB" << endl;
    }
    os.flush();
    mainLabel->setText(QString::fromStdString(os.str()));
}
