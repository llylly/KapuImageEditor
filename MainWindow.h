#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QWidget *centralWidget;
    QHBoxLayout *mainLayout;
    QGraphicsView *graphicsView;
    QVBoxLayout *buttonLayout;
    QGroupBox *ioGroupBox;
    QGroupBox *histogramGroupBox;
    QGroupBox *resamplingGroupBox;
    QGroupBox *fourierGroupBox;
    QGroupBox *forgreyGroupBox;
    QGroupBox *aboutGroupBox;

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H
