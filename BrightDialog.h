#ifndef BRIGHTDIALOG_H
#define BRIGHTDIALOG_H

#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QPushButton>
#include <QMessageBox>
#include "Constants.h"


class BrightDialog : public QDialog
{
    Q_OBJECT

public slots:
    void radioChanged();
    void onClose();

private:
    void init();
    int getValue(QLineEdit *edit);

    QRadioButton *uniformRadio;
    QRadioButton *separateRadio;
    QLabel *uniformLabel;
    QLabel *RLabel;
    QLabel *GLabel;
    QLabel *BLabel;
    QLineEdit *uniformEdit;
    QLineEdit *REdit;
    QLineEdit *GEdit;
    QLineEdit *BEdit;
    QLabel *cautionLabel;
    QSpacerItem *spacer;
    QPushButton *okButton;
    QVBoxLayout *mainLayout;
    QHBoxLayout *upperLayout;
    QGroupBox *uniformWidget;
    QGridLayout *uniformGridLayout;
    QGroupBox *separateWidget;
    QGridLayout *separateGridLayout;
    QHBoxLayout *bottomLayout;


public:
    static const int NoType;
    static const int UniformType;
    static const int SeparateType;

    BrightDialog(QWidget *parent);
    BrightDialog();

    int type;
    int value0, value1, value2;


};

#endif // BRIGHTDIALOG_H
