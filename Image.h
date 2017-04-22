#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <vector>
#include <QObject>
#include <QImage>
#include <QRgb>
#include <QPixmap>
#include "Histogram.h"
#include "ImageEdit.h"

using namespace std;

#define I(i,j,h) ((i)*(h)+(j))

class Image;

struct KeyPoint {
    int r, c;
    int scale;
    double value;
    double orient;
    KeyPoint(int rr, int cc): r(rr), c(cc), value(0.0f) { }
    KeyPoint(): value(0.0f) { }
};

struct vec2 {
    double x, y;
    vec2(): x(0.0f), y(0.0f) { }
    vec2(int _x, int _y): x(_x), y(_y) { }
};

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

    const static double threshold;
    const static int W;
    bool keypointAvailable;
    vector<KeyPoint> pointSet;
    void calcKeyPoint(bool reCalc = 0);

private:
    static ImageEntry *head, *tail;

    static KeyPoint *calcPixel(Image *img, int r, int c);

    static vec2 getDelta(Image *img, int channel, int r, int c);

};

#endif // IMAGE_H
