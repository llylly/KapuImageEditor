#ifndef PSNRDIALOG_H
#define PSNRDIALOG_H

#include <iostream>
#include <sstream>
#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "ImageEdit.h"
#include "Constants.h"

using namespace std;

class PSNRDialog: public QDialog
{
public:
    PSNRDialog(QWidget *parent);
    PSNRDialog();

    void initData(PSNRData data);

private:
    QVBoxLayout *mainLayout;
    QLabel *mainLabel;
    QPushButton *okButton;

    void init();
};

#endif // PSNRDIALOG_H
