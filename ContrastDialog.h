#ifndef CONTRASTDIALOG_H
#define CONTRASTDIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QMessageBox>
#include "Constants.h"

class ContrastDialog: public QDialog
{
    Q_OBJECT

public:
    ContrastDialog();
    ContrastDialog(QWidget* parent);

    bool available;
    int minV, maxV;

private:
    void init();

    int getValue(QLineEdit *edit);

    QGridLayout *mainLayout;
    QLabel *minLabel, *maxLabel, *cautionLabel;
    QLineEdit *minEdit, *maxEdit;
    QPushButton *okButton;

private slots:
    void onClose();

};

#endif // CONTRASTDIALOG_H
