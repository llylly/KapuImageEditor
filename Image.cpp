#include "Image.h"

ImageEntry *Image::head = NULL;
ImageEntry *Image::tail = NULL;

const int Image::W = 2;
const double Image::threshold = 0.010;

void Image::addImage(Image* img) {
    if ((img == NULL) || (img->height * img->width <= 0)) return;
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

void Image::calcKeyPoint(bool reCalc) {
    if (this->height * this->width <= 0) return;
    if ((reCalc) || (!keypointAvailable)) {
        freopen("/Users/lly/Main/tmp/tmp.txt", "w", stdout);
        pointSet.clear();

        vector<Image*> *tower = new vector<Image*>();
        vector<KeyPoint*> *points = new vector<KeyPoint*>();
        tower->push_back(this);
        points->push_back(new KeyPoint[this->width * this->height]);

        Image *p = this;
        while ((p->height >= 2) && (p->width >= 2)) {
            p = ImageEdit::bilinear(p, p->width >> 1, p->height >> 1);
            tower->push_back(p);
            points->push_back(new KeyPoint[p->width * p->height]);
        }

        int cnt = 0;
        for (int i=0; i<tower->size(); ++i) {
            Image *now = (*tower)[i];
            for (int r=0; r<now->height; ++r)
                for (int c=0; c<now->width; ++c) {
                    ++cnt;
                    KeyPoint *kp = calcPixel(now, r, c);
                    (*points)[i][I(r,c,now->width)] = *kp;
                    delete kp;
                }
        }
        printf("%d\n", cnt);

        for (int k=tower->size() - 1; k>=0; --k)
            for (int i=0; i<(*tower)[k]->height; ++i)
                for (int j=0; j<(*tower)[k]->width; ++j)
                    if ((*points)[k][I(i,j,(*tower)[k]->width)].value > Image::threshold) {
                        KeyPoint kp;
                        kp.r = (i << k) + (1 << ((k>0)?(k-1):k));
                        kp.c = (j << k) + (1 << ((k>0)?(k-1):k));
                        kp.scale = 1 << k;
                        kp.value = (*points)[k][I(i,j,(*tower)[k]->width)].value;
                        this->pointSet.push_back(kp);
                        printf("KP %d %d scale:%d value:%lf\n", kp.r, kp.c, kp.scale, kp.value);
                    }

        for (int i=1; i<tower->size(); ++i)
            delete (*tower)[i];
        for (int i=0; i<points->size(); ++i)
            delete (*points)[i];

        keypointAvailable = true;
        fclose(stdout);
    }
}

KeyPoint *Image::calcPixel(Image *img, int r, int c) {
    KeyPoint *ans = new KeyPoint();

    if (img == NULL) return NULL;
    double a11 = 0.0f, a12 = 0.0f, a21 = 0.0f, a22 = 0.0f;
    double v = 0.0f;;
    for (int channel = 0; channel < 3; ++channel) {
        for (int i = r-W; i<=r+W; ++i)
            for (int j = c-W; j<=c+W; ++j) {
                vec2 d = Image::getDelta(img, channel, i, j);
                //cerr << d.x << " " << d.y << endl;
                a11 += d.x * d.x;
                a12 += d.x * d.y;
                a21 += d.y * d.x;
                a22 += d.y * d.y;
            }
        a11 /= ((W << 1) + 1) * ((W << 1) + 1);
        a12 /= ((W << 1) + 1) * ((W << 1) + 1);
        a21 /= ((W << 1) + 1) * ((W << 1) + 1);
        a22 /= ((W << 1) + 1) * ((W << 1) + 1);
        if (a11 + a22 != 0)
            v += (a11 * a22 - a12 * a21) / (a11 + a22);
    }

    ans->r = r;
    ans->c = c;
    ans->value = v / 3.0f;

    printf("%d %d %lf\n", ans->r, ans->c, ans->value);
    return ans;
}

vec2 Image::getDelta(Image *img, int channel, int r, int c) {
    if ((img == NULL) || (img->height * img->width <= 0)
        || (r < 0) || (r >= img->height)
        || (c < 0) || (c >= img->width)) return vec2();

    int *arr = NULL;
    switch (channel) {
        case 0: arr = img->R; break;
        case 1: arr = img->G; break;
        case 2: arr = img->B; break;
    }
    if (arr == NULL) return vec2();

    vec2 ans;
    if ((r < 0) || (img->height == 1)) ans.x = 0.0f;
    else if (r == 0) ans.x = arr[I(r + 1, c, img->width)] - arr[I(r, c, img->width)];
    else if (r == (img->height - 1)) ans.x = arr[I(r, c, img->width)] - arr[I(r - 1, c, img->width)];
    else ans.x = (double)(arr[I(r+1, c, img->width)] - arr[I(r-1, c, img->width)]) / 2.0f;

    if ((c < 0) || (img->width == 1)) ans.y = 0.0f;
    else if (c == 0) ans.y = arr[I(r, c + 1, img->width)] - arr[I(r, c, img->width)];
    else if (c == (img->width - 1)) ans.y = arr[I(r, c, img->width)] - arr[I(r, c - 1, img->width)];
    else ans.y = (double)(arr[I(r, c+1, img->width)] - arr[I(r, c-1, img->width)]) / 2.0f;

    ans.x /= 255.0f, ans.y /= 255.0f;
    return ans;
}

Image::Image()
{
    height = width = 0;
    R = G = B = NULL;
    histogram = NULL;
    histogramAvailable = false;
    pointSet.clear();
    keypointAvailable = false;
}

Image::~Image() {
    delete[] R;
    delete[] G;
    delete[] B;
}

