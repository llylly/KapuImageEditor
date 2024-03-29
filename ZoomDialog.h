#ifndef ZOOMDIALOG_H
#define ZOOMDIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QButtonGroup>
#include <QShowEvent>
#include <QMessageBox>
#include "Constants.h"
#include "Image.h"

class ZoomDialog: public QDialog
{
    Q_OBJECT
public:
    const static int NEAREST_NEIGHBOR;
    const static int BILINEAR;
    const static int BICUBIC;
    const static int NO_TYPE;

    int type;
    int newWidth, newHeight;

    ZoomDialog();
    ZoomDialog(QWidget *parent);

    int oldWidth, oldHeight;

private:
    QButtonGroup *typeGroup, *byGroup;
    QVBoxLayout *mainLayout;
    QLabel *cautionLabel;
    QHBoxLayout *upperLayout;
    QRadioButton *type1Radio, *type2Radio, *type3Radio;
    QGridLayout *middleLayout;
    QRadioButton *byRatioRadio, *bySizeRadio;
    QGroupBox *originalGroup, *ratioGroup, *sizeGroup;
    QGridLayout *originalLayout, *ratioLayout, *sizeLayout;
    QLabel *originalWLabel, *originalHLabel, *ratioWLabel, *ratioHLabel, *sizeWLabel, *sizeHLabel;
    QLabel *originalWidth, *originalHeight;
    QLineEdit *ratioWEdit, *ratioHEdit, *sizeWEdit, *sizeHEdit;
    QHBoxLayout *bottomLayout;
    QSpacerItem *spacer;
    QPushButton *okButton;

    void init();
    void updateImageStat();
    void ratioCheckInit();

private slots:
    void onClose();
    void statRefresh();

public:
    void showEvent(QShowEvent *event);

};

#endif // ZOOMDIALOG_H
