#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    if (this->objectName().isEmpty())
        this->setObjectName(Constants::PROJ_NAME.c_str());
    this->resize(Constants::DEFAULT_WIDTH, Constants::DEFAULT_HEIGHT);
    this->move((QApplication::desktop()->width() - this->width()) / 2, (QApplication::desktop()->height() - this->height()) / 2);
    this->setWindowTitle(Constants::PROJ_NAME.c_str());

    this->centralWidget = new QWidget(this);
    this->centralWidget->setEnabled(true);
    this->mainLayout = new QHBoxLayout(this->centralWidget);
    this->mainLayout->setSpacing(6);
    this->mainLayout->setContentsMargins(11, 11, 11, 11);
        this->graphicsView = new KImageView(centralWidget);
        this->mainLayout->addWidget(this->graphicsView);
        this->buttonLayout = new QVBoxLayout();
            this->ioGroupBox = new QGroupBox(this);
            this->ioGroupBox->setTitle(Constants::IO_GROUP_TITLE.c_str());
            this->ioLayout = new QVBoxLayout();
            this->ioGroupBox->setLayout(this->ioLayout);
                this->openImageButton = new QPushButton(this);
                this->openImageButton->setText(Constants::OPEN_IMAGE_CAPTION.c_str());
                this->ioLayout->addWidget(this->openImageButton);
                this->saveImageButton = new QPushButton(this);
                this->saveImageButton->setText(Constants::SAVE_IMAGE_CAPTION.c_str());
                this->ioLayout->addWidget(this->saveImageButton);
            this->buttonLayout->addWidget(this->ioGroupBox);
            this->histogramGroupBox = new QGroupBox(this);
            this->histogramLayout = new QGridLayout();
            this->histogramGroupBox->setLayout(this->histogramLayout);
                this->showHistogramButton = new QPushButton(this);
                this->showHistogramButton->setText(Constants::SHOW_HISTOGRAM_CAPTION.c_str());
                this->histogramLayout->addWidget(this->showHistogramButton, 0, 0, 1, 2);
                this->brightButton = new QPushButton(this);
                this->brightButton->setText(Constants::BRIGHT_CAPTION.c_str());
                this->histogramLayout->addWidget(this->brightButton, 1, 0, 1, 1);
                this->gammaButton = new QPushButton(this);
                this->gammaButton->setText(Constants::GAMMA_CAPTION.c_str());
                this->histogramLayout->addWidget(this->gammaButton, 1, 1, 1, 1);
                this->histogramEqualizationButton = new QPushButton(this);
                this->histogramEqualizationButton->setText(Constants::HISTOGRAM_EQUALIZATION_CAPTION.c_str());
                this->histogramLayout->addWidget(this->histogramEqualizationButton, 2, 0, 1, 1);
                this->histogramMatchButton = new QPushButton(this);
                this->histogramMatchButton->setText(Constants::HISTOGRAM_MATCH_CAPTION.c_str());
                this->histogramLayout->addWidget(this->histogramMatchButton, 2, 1, 1, 1);
            this->histogramGroupBox->setTitle(Constants::HISTOGRAM_GROUP_TITLE.c_str());
            this->buttonLayout->addWidget(this->histogramGroupBox);
            this->resamplingGroupBox = new QGroupBox(this);
            this->resamplingLayout = new QVBoxLayout();
            this->resamplingGroupBox->setLayout(this->resamplingLayout);
                this->resamplingButton = new QPushButton(this);
                this->resamplingButton->setText(Constants::RESAMPLING_CAPTION.c_str());
                this->resamplingLayout->addWidget(this->resamplingButton);
            this->resamplingGroupBox->setTitle(Constants::RESAMPLING_GROUP_TITLE.c_str());
            this->buttonLayout->addWidget(this->resamplingGroupBox);
            this->fourierGroupBox = new QGroupBox(this);
            this->fourierLayout = new QVBoxLayout();
            this->fourierGroupBox->setLayout(this->fourierLayout);
                this->showFourierButton = new QPushButton(this);
                this->showFourierButton->setText(Constants::SHOW_FOURIER_CAPTION.c_str());
                this->fourierLayout->addWidget(this->showFourierButton);
                this->fourierFusionButton = new QPushButton(this);
                this->fourierFusionButton->setText(Constants::FOURIER_FUSION_CAPTION.c_str());
                this->fourierLayout->addWidget(this->fourierFusionButton);
            this->fourierGroupBox->setTitle(Constants::FOURIER_GROUP_TITLE.c_str());
            this->buttonLayout->addWidget(this->fourierGroupBox);
            this->forgreyGroupBox = new QGroupBox(this);
            this->forgreyLayout = new QVBoxLayout();
            this->forgreyGroupBox->setLayout(this->forgreyLayout);
                this->pointDetectButton = new QPushButton(this);
                this->pointDetectButton->setText(Constants::POINT_DETECT_CAPTION.c_str());
                this->forgreyLayout->addWidget(this->pointDetectButton);
                this->differenceDetectButton = new QPushButton(this);
                this->differenceDetectButton->setText(Constants::DIFFERENCE_CAPTION.c_str());
                this->forgreyLayout->addWidget(this->differenceDetectButton);
            this->forgreyGroupBox->setTitle(Constants::FORGREY_GROUP_TITLE.c_str());
            this->buttonLayout->addWidget(this->forgreyGroupBox);
            this->aboutGroupBox = new QGroupBox(this);
            this->aboutLayout = new QVBoxLayout();
            this->aboutGroupBox->setLayout(this->aboutLayout);
                this->aboutButton = new QPushButton(this);
                this->aboutButton->setText(Constants::ABOUT_CAPTION.c_str());
                this->aboutLayout->addWidget(this->aboutButton);
            this->aboutGroupBox->setTitle(Constants::ABOUT_GROUP_TITLE.c_str());
            this->buttonLayout->addWidget(this->aboutGroupBox);
        this->mainLayout->addLayout(this->buttonLayout);
    this->setCentralWidget(this->centralWidget);

    connect(openImageButton, SIGNAL(clicked(bool)), this, SLOT(loadImage()));
    connect(saveImageButton, SIGNAL(clicked(bool)), this, SLOT(saveImage()));
}

void MainWindow::loadImage() {
    QString fileName = QFileDialog::getOpenFileName(this, QString::fromStdString(Constants::OPEN_IMAGE_DIALOG), "", QString::fromStdString(Constants::OPEN_IMAGE_FILTER));
    if (!fileName.isEmpty()) {
        QImage *qimg = new QImage();
        if (qimg->load(fileName)) {
            Image::addImage(Image::fromQImage(qimg));
            graphicsView->loadImage();
        }
        delete qimg;
    }
}

bool MainWindow::loadImagePrecheck() {
    if (Image::getCurEntry() == NULL) {
        QMessageBox::information(this, QString::fromStdString(Constants::SAVE_IMAGE_CAPTION), QString::fromStdString(Constants::SAVE_IMAGE_INFO), QMessageBox::Ok);
        return false;
    }
    return true;
}

void MainWindow::saveImage() {
    if (!this->loadImagePrecheck()) return;
    QString fileName = QFileDialog::getSaveFileName(this, QString::fromStdString(Constants::SAVE_IMAGE_DIALOG), "", QString::fromStdString(Constants::SAVE_IMAGE_FILTER));
    if (!fileName.isEmpty()) {
        Image::getCurImage()->save(fileName.toStdString());
    }
}

MainWindow::~MainWindow()
{

}
