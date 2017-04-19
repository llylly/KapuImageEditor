#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <QObject>
#include <QImage>
#include <QRgb>
#include <QPixmap>
#include "Histogram.h"

using namespace std;

#define I(i,j,h) ((i)*(h)+(j))

class Image;

/**
 * @brief The ImageEntry class
 * Global image link list entry
 */
class ImageEntry {
public:
    ImageEntry *prev;
    ImageEntry *next;
    Image *value;

    ImageEntry() {
        prev = NULL;
        next = NULL;
        value = 0;
    }
};

/**
 * @brief The Image class
 */
class Image
{
public:
    static void addImage(Image* img);
    static Image *getCurImage();
    static void deleteEntry();
    static ImageEntry *getCurEntry();

    static Image *fromQImage(QImage *qimg);
    uchar *toUcharArr();
    QImage *toQImage();
    QPixmap *toQPixmap();

    void save(string path);

    void printImg();

    void calcHistogram(bool recalc = false);

    Image();
    ~Image();

    int height, width;
    int *R, *G, *B;

    bool histogramAvailable;
    Histogram *histogram;

private:
    static ImageEntry *head, *tail;


};

#endif // IMAGE_H
