#include "Image.h"

ImageEntry *Image::head = NULL;
ImageEntry *Image::tail = NULL;

void Image::addImage(Image* img) {
    if (Image::head == NULL) {
        Image::head = Image::tail = new ImageEntry();
        Image::tail->value = img;
    } else {
        ImageEntry *newEntry = new ImageEntry();
        newEntry->prev = Image::tail;
        Image::tail = newEntry;
        newEntry->value = img;
    }
}

Image *Image::getCurImage() {
    if (Image::tail != NULL) return Image::tail->value; else return NULL;
}

void Image::deleteEntry() {
    if (Image::tail != NULL) {
        if (Image::tail != Image::head) {
            ImageEntry *tmp = Image::tail->prev;
            delete Image::tail;
            Image::tail = tmp;
        } else {
            delete Image::tail;
            Image::head = Image::tail = NULL;
        }
    }
}

ImageEntry *Image::getCurEntry() {
    return Image::tail;
}

Image *Image::fromQImage(QImage *qimg) {
    Image *img = new Image();
    int h, w;
    img->height = h = qimg->height();
    img->width = w = qimg->width();
    img->R = new int[h * w];
    img->G = new int[h * w];
    img->B = new int[h * w];
    for (int i=0; i<img->height; ++i)
        for (int j=0; j<img->width; ++j) {
            img->R[I(i,j,w)] = qRed(qimg->pixel(j,i));
            img->G[I(i,j,w)] = qGreen(qimg->pixel(j,i));
            img->B[I(i,j,w)] = qBlue(qimg->pixel(j,i));
        }
    return img;
}

uchar *Image::toUcharArr() {
    if (height*width == 0) return NULL;
    QRgb *arr = new QRgb[height * width];
    for (int i=0; i<height*width; ++i) {
        arr[i] = qRgb(R[i], G[i], B[i]);
    }
    return (uchar*)arr;
}

QImage *Image::toQImage() {
    if (height*width == 0) return NULL;
    QImage *qimg = new QImage(width, height, QImage::Format_RGB32);
    for (int i=0; i<height; ++i)
        for (int j=0; j<width; ++j) {
            qimg->setPixelColor(j, i, QColor(R[I(i,j,width)], G[I(i,j,width)], B[I(i,j,width)]));
        }
    return qimg;
}

QPixmap *Image::toQPixmap() {
    if (height*width == 0) return NULL;
    QImage *qimg;
    QPixmap *qpixmap = new QPixmap(QPixmap::fromImage(*(qimg=toQImage())));
    delete qimg;
    return qpixmap;
}

void Image::save(string path) {
    QImage *image = this->toQImage();
    image->save(QString::fromStdString(path));
    delete image;
}

void Image::printImg() {
    QRgb *arr = (QRgb*)toUcharArr();
    for (int i=0; i<height; ++i) {
        for (int j=0; j<width; ++j) {
            printf("(%d,%d,%d,%d,%d) ", i, j, qRed(arr[I(i,j,width)]), qGreen(arr[I(i,j,width)]), qBlue(arr[I(i,j,width)]));
        }
        printf("\n");
    }
    delete[] arr;
}

void Image::calcHistogram(bool recalc) {
    if (recalc == true) {
        if (histogramAvailable) {
            histogramAvailable = false;
            delete histogram;
        }
    }
    if (this->histogramAvailable == false) {
        if (height * width > 0) {
            histogram = new Histogram();
            for (int i=0; i<height*width; ++i) {
                histogram->arrR[R[i]]+=1.0f;
                histogram->arrG[G[i]]+=1.0f;
                histogram->arrB[B[i]]+=1.0f;
            }
            histogram->sumArrR[0] = histogram->arrR[0];
            histogram->sumArrG[0] = histogram->arrG[0];
            histogram->sumArrB[0] = histogram->arrB[0];
            for (int i=0; i<Histogram::maxV; ++i) {
                histogram->sumArrR[i+1] = histogram->sumArrR[i] + histogram->arrR[i+1];
                histogram->sumArrG[i+1] = histogram->sumArrG[i] + histogram->arrG[i+1];
                histogram->sumArrB[i+1] = histogram->sumArrB[i] + histogram->arrB[i+1];
            }
            histogram->divide(Histogram::R, height*width);
            histogram->divide(Histogram::G, height*width);
            histogram->divide(Histogram::B, height*width);
            histogram->divide(Histogram::sumR, height*width);
            histogram->divide(Histogram::sumG, height*width);
            histogram->divide(Histogram::sumB, height*width);
            this->histogramAvailable = true;
        }
    }
}

Image::Image()
{
    height = width = 0;
    R = G = B = NULL;
    histogram = NULL;
    histogramAvailable = false;
}

Image::~Image() {
    delete[] R;
    delete[] G;
    delete[] B;
}

