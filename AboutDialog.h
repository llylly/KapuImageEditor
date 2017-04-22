#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "Constants.h"

class AboutDialog: public QDialog
{
public:
    AboutDialog();
    AboutDialog(QWidget *widget);

private:
    void init();

    QVBoxLayout *mainLayout;
    QLabel *label;
    QPushButton *okButton;

    const static string aboutCaption;
};

#endif // ABOUTDIALOG_H
