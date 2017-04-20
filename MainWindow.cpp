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
                this->undoButton = new QPushButton(this);
                this->undoButton->setText(Constants::UNDO_CAPTION.c_str());
                this->ioLayout->addWidget(this->undoButton);
            this->buttonLayout->addWidget(this->ioGroupBox);
            this->histogramGroupBox = new QGroupBox(this);
            this->histogramLayout = new QGridLayout();
            this->histogramGroupBox->setLayout(this->histogramLayout);
                this->showHistogramButton = new QPushButton(this);
                this->showHistogramButton->setText(Constants::SHOW_HISTOGRAM_CAPTION.c_str());
                this->histogramLayout->addWidget(this->showHistogramButton, 0, 0, 1, 1);
                this->contrastButton = new QPushButton(this);
                this->contrastButton->setText(Constants::CONTRAST_CAPTION.c_str());
                this->histogramLayout->addWidget(this->contrastButton, 0, 1, 1, 1);
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
            this->resamplingLayout = new QGridLayout();
            this->resamplingGroupBox->setLayout(this->resamplingLayout);
                this->blurButton = new QPushButton(this);
                this->blurButton->setText(Constants::BLUR_CAPTION.c_str());
                this->resamplingLayout->addWidget(this->blurButton, 0, 0, 1, 1);
                this->resamplingButton = new QPushButton(this);
                this->resamplingButton->setText(Constants::RESAMPLING_CAPTION.c_str());
                this->resamplingLayout->addWidget(this->resamplingButton, 0, 1, 1, 1);
                this->PSNRButton = new QPushButton(this);
                this->PSNRButton->setText(Constants::PSNR_CAPTION.c_str());
                this->resamplingLayout->addWidget(this->PSNRButton, 1, 0, 1, 2);
            this->resamplingGroupBox->setTitle(Constants::RESAMPLING_GROUP_TITLE.c_str());
            this->buttonLayout->addWidget(this->resamplingGroupBox);
            this->rotateGroupBox = new QGroupBox(this);
            this->rotateLayout = new QVBoxLayout();
            this->rotateGroupBox->setLayout(this->rotateLayout);
                this->rotateButton = new QPushButton(this);
                this->rotateButton->setText(Constants::ROTATE_CAPTION.c_str());
                this->rotateLayout->addWidget(this->rotateButton);
                this->sphereButton = new QPushButton(this);
                this->sphereButton->setText(Constants::SPHERE_CAPTION.c_str());
                this->rotateLayout->addWidget(this->sphereButton);
            this->rotateGroupBox->setTitle(Constants::ROTATE_GROUP_TITLE.c_str());
            this->buttonLayout->addWidget(this->rotateGroupBox);
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

    this->histogramDialog = new HistogramDialog(this);
    this->brightDialog = new BrightDialog(this);
    this->contrastDialog = new ContrastDialog(this);

    this->zoomDialog = new ZoomDialog(this);

    this->statusBar = new QStatusBar(this);
    this->setStatusBar(this->statusBar);
    this->statusBar->showMessage(Constants::DEFAULT_STATUS_BAR.c_str());

    connect(openImageButton, SIGNAL(clicked(bool)), this, SLOT(loadImage()));
    connect(saveImageButton, SIGNAL(clicked(bool)), this, SLOT(saveImage()));
    connect(undoButton, SIGNAL(clicked(bool)), this, SLOT(undo()));
    connect(showHistogramButton, SIGNAL(clicked(bool)), this, SLOT(showHistogram()));
    connect(contrastButton, SIGNAL(clicked(bool)), this, SLOT(contrastShow()));
    connect(brightButton, SIGNAL(clicked(bool)), this, SLOT(brightShow()));
    connect(gammaButton, SIGNAL(clicked(bool)), this, SLOT(gammaShow()));
    connect(histogramEqualizationButton, SIGNAL(clicked(bool)), this, SLOT(histogramEqualization()));
    connect(histogramMatchButton, SIGNAL(clicked(bool)), this, SLOT(histogramMatch()));
    connect(blurButton, SIGNAL(clicked(bool)), this, SLOT(blurShow()));
    connect(resamplingButton, SIGNAL(clicked(bool)), this, SLOT(resamplingShow()));
    connect(PSNRButton, SIGNAL(clicked(bool)), this, SLOT(PSNRCalcShow()));
}

void MainWindow::loadImage() {
    QString fileName = QFileDialog::getOpenFileName(this, QString::fromStdString(Constants::OPEN_IMAGE_DIALOG), "", QString::fromStdString(Constants::OPEN_IMAGE_FILTER));
    if (!fileName.isEmpty()) {
        QImage *qimg = new QImage();
        if (qimg->load(fileName)) {
            Image::addImage(Image::fromQImage(qimg));
            this->showImage();
        }
        delete qimg;
    }
}

bool MainWindow::editImagePrecheck() {
    if (Image::getCurEntry() == NULL) {
        QMessageBox::information(this, QString::fromStdString(Constants::SAVE_IMAGE_CAPTION), QString::fromStdString(Constants::SAVE_IMAGE_INFO), QMessageBox::Ok);
        return false;
    }
    return true;
}

void MainWindow::showImage() {
    graphicsView->loadImage();
    if (Image::getCurEntry() == NULL)
        this->statusBar->showMessage(Constants::EMPTY_IMAGE_STATUS_BAR.c_str());
    else
        this->statusBar->showMessage(Constants::IMAGE_STATUS_BAR(Image::getCurImage()->height, Image::getCurImage()->width).c_str());
}

void MainWindow::saveImage() {
    if (!this->editImagePrecheck()) return;
    QString fileName = QFileDialog::getSaveFileName(this, QString::fromStdString(Constants::SAVE_IMAGE_DIALOG), "", QString::fromStdString(Constants::SAVE_IMAGE_FILTER));
    if (!fileName.isEmpty()) {
        Image::getCurImage()->save(fileName.toStdString());
    }
}

void MainWindow::undo() {
    if (!this->editImagePrecheck()) return;
    Image::deleteEntry();
    this->showImage();
}

void MainWindow::showHistogram() {
    if (!this->editImagePrecheck()) return;
    Image::getCurImage()->calcHistogram();
    if (!Image::getCurImage()->histogramAvailable) {
        QMessageBox::information(this, QString::fromStdString(Constants::ERROR), QString::fromStdString(Constants::HISTOGRAM_DIALOG), QMessageBox::Ok);
        return;
    }
    histogramDialog->setHistogram(Image::getCurImage()->histogram);
    histogramDialog->reDraw();
    histogramDialog->show();
}

void MainWindow::brightShow() {
    if (!this->editImagePrecheck()) return;
    brightDialog->type = BrightDialog::NoType;
    brightDialog->exec();
    if (brightDialog->type == BrightDialog::UniformType) {
        Image *newI = ImageEdit::brightAdjust(Image::getCurImage(), brightDialog->value0);
        Image::addImage(newI);
        this->showImage();
    }
    if (brightDialog->type == BrightDialog::SeparateType) {
        Image *newI = ImageEdit::brightAdjust(Image::getCurImage(), brightDialog->value0, brightDialog->value1, brightDialog->value2);
        Image::addImage(newI);
        this->showImage();
    }
}

void MainWindow::contrastShow() {
    if (!this->editImagePrecheck()) return;
    contrastDialog->available = false;
    contrastDialog->exec();
    if (contrastDialog->available) {
        Image *newI = ImageEdit::contrastAdjust(Image::getCurImage(), contrastDialog->minV, contrastDialog->maxV);
        Image::addImage(newI);
        this->showImage();
    }
}

void MainWindow::gammaShow() {
    if (!this->editImagePrecheck()) return;
    bool *b = new bool(false);
    QString str = QInputDialog::getText(this, Constants::GAMMA_CAPTION.c_str(), Constants::GAMMA_DIALOG_CAPTION.c_str(), QLineEdit::Normal, "1.0", b);
    if (b) {
        string s = str.toStdString();
        double d;
        bool legal = true;
        for (int i=0; i < s.length(); ++i)
            if (((s[i] >= '0') && (s[i] <= '9')) || (s[i] == '.')) ; else legal = false;
        if (legal) {
            d = atof(s.c_str());
            if (d < 0.0f) legal = false;
        }
        if (!legal) {
            QMessageBox::information(this, Constants::GAMMA_CAPTION.c_str(), Constants::ILLEGAL_VALUE.c_str(), QMessageBox::Ok);
        } else {
            Image *newI = ImageEdit::gammaAdjust(Image::getCurImage(), d);
            Image::addImage(newI);
            this->showImage();
        }
    }
}

void MainWindow::histogramEqualization() {
    if (!this->editImagePrecheck()) return;
    Image *newI = ImageEdit::histogramEqualization(Image::getCurImage());
    Image::addImage(newI);
    this->showImage();
}

void MainWindow::histogramMatch() {
    if (!this->editImagePrecheck()) return;
    QString fileName = QFileDialog::getOpenFileName(this, QString::fromStdString(Constants::STYLIZE_DIALOG), "", QString::fromStdString(Constants::OPEN_IMAGE_FILTER));
    if (!fileName.isEmpty()) {
        QImage *qimg = new QImage();
        if (qimg->load(fileName)) {
            Image *refer = Image::fromQImage(qimg);
            Image *newI = ImageEdit::histogramStylize(Image::getCurImage(), refer);
            Image::addImage(newI);
            this->showImage();
            delete refer;
            delete qimg;
        }
    }
}

void MainWindow::blurShow() {

}

void MainWindow::resamplingShow() {
    zoomDialog->exec();
}

void MainWindow::PSNRCalcShow() {

}

MainWindow::~MainWindow()
{

}
