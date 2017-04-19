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
#include <QMessageBox>
#include <QFileDialog>
#include "Constants.h"
#include "Image.h"
#include "KImageView.h"
#include "HistogramDialog.h"

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
    QGroupBox *fourierGroupBox;
    QGroupBox *forgreyGroupBox;
    QGroupBox *aboutGroupBox;

    QPushButton *openImageButton;
    QPushButton *saveImageButton;
    QVBoxLayout *ioLayout;

    QPushButton *showHistogramButton;
    QPushButton *brightButton;
    QPushButton *gammaButton;
    QPushButton *histogramEqualizationButton;
    QPushButton *histogramMatchButton;
    QGridLayout *histogramLayout;

    QPushButton *resamplingButton;
    QVBoxLayout *resamplingLayout;

    QPushButton *showFourierButton;
    QPushButton *fourierFusionButton;
    QVBoxLayout *fourierLayout;

    QPushButton *pointDetectButton;
    QPushButton *differenceDetectButton;
    QVBoxLayout *forgreyLayout;

    QPushButton *aboutButton;
    QVBoxLayout *aboutLayout;

    HistogramDialog *histogramDialog;

    bool editImagePrecheck();
    void showImage();

private slots:
    void loadImage();
    void saveImage();
    void showHistogram();

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H
