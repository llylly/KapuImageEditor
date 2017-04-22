#ifndef BLURDIALOG_H
#define BLURDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QMessageBox>
#include "Constants.h"

class BlurDialog: public QDialog
{
    Q_OBJECT
public:
    static const int NO_TYPE;
    static const int UNIFORM;
    static const int GAUSSIAN;
    static const int MOSAIC;

    int type;
    int radius;

    BlurDialog();
    BlurDialog(QWidget *parent);

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *upperLayout;
    QRadioButton *type1Radio, *type2Radio, *type3Radio;
    QLabel *radiusLabel;
    QLineEdit *mainEdit;
    QPushButton *okButton;

    void init();

private slots:
    void onClose();
};

#endif // BLURDIALOG_H
