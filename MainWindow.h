#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include "Constants.h"
#include "Image.h"
#include "KImageView.h"
#include "HistogramDialog.h"
#include "BrightDialog.h"
#include "ImageEdit.h"
#include "ContrastDialog.h"
#include "ZoomDialog.h"
#include "PSNRDialog.h"
#include "BlurDialog.h"
#include "AboutDialog.h"
#include "DifferenceDialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QWidget *centralWidget;
    QHBoxLayout *mainLayout;
    QVBoxLayout *buttonLayout;

    KImageView *graphicsView;

    QStatusBar *statusBar;

    QGroupBox *ioGroupBox;
    QGroupBox *histogramGroupBox;
    QGroupBox *resamplingGroupBox;
    QGroupBox *rotateGroupBox;
    QGroupBox *forgreyGroupBox;
    QGroupBox *aboutGroupBox;

    QPushButton *openImageButton;
    QPushButton *saveImageButton;
    QPushButton *undoButton;
    QVBoxLayout *ioLayout;

    QPushButton *showHistogramButton;
    QPushButton *brightButton;
    QPushButton *contrastButton;
    QPushButton *gammaButton;
    QPushButton *histogramEqualizationButton;
    QPushButton *histogramMatchButton;
    QGridLayout *histogramLayout;

    QPushButton *blurButton;
    QPushButton *resamplingButton;
    QPushButton *PSNRButton;
    QGridLayout *resamplingLayout;

    QPushButton *rotateButton;
    QPushButton *sphereButton;
    QVBoxLayout *rotateLayout;

    QPushButton *pointDetectButton;
    QPushButton *differenceDetectButton;
    QVBoxLayout *forgreyLayout;

    QPushButton *aboutButton;
    QVBoxLayout *aboutLayout;

    HistogramDialog *histogramDialog;
    BrightDialog *brightDialog;
    ContrastDialog *contrastDialog;
    PSNRDialog *pSNRDialog;
    DifferenceDialog *diffDialog;
    AboutDialog *aboutDialog;

    ZoomDialog *zoomDialog;
    BlurDialog *blurDialog;

    bool editImagePrecheck();
    void showImage();

private slots:
    void loadImage();
    void saveImage();
    void undo();
    void showHistogram();
    void brightShow();
    void contrastShow();
    void gammaShow();
    void histogramEqualization();
    void histogramMatch();
    void blurShow();
    void resamplingShow();
    void PSNRCalcShow();
    void keyPointShow();
    void diffShow();
    void aboutShow();

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H
