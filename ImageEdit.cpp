#include "ImageEdit.h"

#define EPS 1e-6

ImageEdit::ImageEdit()
{

}

Image *ImageEdit::brightAdjust(Image *img, int delta) {
    return ImageEdit::brightAdjust(img, delta, delta, delta);
}

Image *ImageEdit::brightAdjust(Image *img, int deltaR, int deltaG, int deltaB) {
    if ((img == NULL) || (img->height * img->width <= 0))
        return NULL;
    Image *ans = new Image();
    int h, w;
    h = ans->height = img->height;
    w = ans->width = img->width;
    ans->R = new int[h*w];
    ans->G = new int[h*w];
    ans->B = new int[h*w];
    for (int i=0; i<h*w; ++i) {
        ans->R[i] = img->R[i] + deltaR;
        ans->G[i] = img->G[i] + deltaG;
        ans->B[i] = img->B[i] + deltaB;
        if (ans->R[i] > 255) ans->R[i] = 255;
        if (ans->R[i] < 0) ans->R[i] = 0;
        if (ans->G[i] > 255) ans->G[i] = 255;
        if (ans->G[i] < 0) ans->G[i] = 0;
        if (ans->B[i] > 255) ans->B[i] = 255;
        if (ans->B[i] < 0) ans->B[i] = 0;
    }
    return ans;
}

Image *ImageEdit::contrastAdjust(Image *img, int minPoint, int maxPoint) {
    if ((img == NULL) || (img->height * img->width <= 0))
        return NULL;

    int *lookUpTable = new int[256];
    if (minPoint < 0) minPoint = 0;
    if (minPoint > 255) minPoint = 255;
    if (maxPoint < 0) maxPoint = 0;
    if (maxPoint > 255) maxPoint = 255;
    if (minPoint <= maxPoint) {
        for (int i=0; i<minPoint; ++i) lookUpTable[i] = 0;
        for (int i=maxPoint; i<256; ++i) lookUpTable[i] = 255;
        for (int i=minPoint; i<maxPoint; ++i)
            lookUpTable[i] = 255*(i-minPoint) / (maxPoint-minPoint);
    } else {
        for (int i=0; i<maxPoint; ++i) lookUpTable[i] = 255;
        for (int i=minPoint; i<256; ++i) lookUpTable[i] = 0;
        for (int i=maxPoint; i<minPoint; ++i)
            lookUpTable[i] = 255*(minPoint-i) / (minPoint-maxPoint);
    }

    Image *ans = new Image();
    int h, w;
    h = ans->height = img->height;
    w = ans->width = img->width;
    ans->R = new int[h*w];
    ans->G = new int[h*w];
    ans->B = new int[h*w];
    for (int i=0; i<h*w; ++i) {
        ans->R[i] = lookUpTable[img->R[i]];
        ans->G[i] = lookUpTable[img->G[i]];
        ans->B[i] = lookUpTable[img->B[i]];
    }

    delete[] lookUpTable;

    return ans;
}

Image *ImageEdit::gammaAdjust(Image *img, double gamma) {
    if ((img == NULL) || (img->height * img->width <= 0))
        return NULL;
    if (gamma < 0.0f) return NULL;

    int *lookUpTable = new int[256];
    for (int i=0; i<256; ++i) {
        lookUpTable[i] = (int)((double)255.0f * pow((double)(i) / 255.0f, gamma) + 0.5f);
        if (lookUpTable[i] > 255) lookUpTable[i] = 255;
        if (lookUpTable[i] < 0) lookUpTable[i] = 0;
    }

    Image *ans = new Image();
    int h, w;
    h = ans->height = img->height;
    w = ans->width = img->width;
    ans->R = new int[h*w];
    ans->G = new int[h*w];
    ans->B = new int[h*w];
    for (int i=0; i<h*w; ++i) {
        ans->R[i] = lookUpTable[img->R[i]];
        ans->G[i] = lookUpTable[img->G[i]];
        ans->B[i] = lookUpTable[img->B[i]];
    }

    delete[] lookUpTable;

    return ans;
}

Image *ImageEdit::histogramEqualization(Image *img) {
    if ((img == NULL) || (img->height * img->width <= 0))
        return NULL;
    img->calcHistogram();

    srand(time(0));

    int *lookR = new int[256];
    int *lookG = new int[256];
    int *lookB = new int[256];
    for (int i=0; i<256; ++i) {
        lookR[i] = int(img->histogram->sumArrR[i] * 255.0f + 0.5f);
        lookG[i] = int(img->histogram->sumArrG[i] * 255.0f + 0.5f);
        lookB[i] = int(img->histogram->sumArrB[i] * 255.0f + 0.5f);
        if (lookR[i] > 255) lookR[i] = 255;
        if (lookG[i] > 255) lookG[i] = 255;
        if (lookB[i] > 255) lookB[i] = 255;
    }

    Image *ans = new Image();
    int h, w;
    h = ans->height = img->height;
    w = ans->width = img->width;
    ans->R = new int[h*w];
    ans->G = new int[h*w];
    ans->B = new int[h*w];
    int tmp, tmpr;
    for (int i=0; i<h*w; ++i) {
        if (img->R[i] == 0) tmp = 0; else tmp = lookR[img->R[i]-1] + 1;
        tmpr = lookR[img->R[i]];
        if (tmp >= tmpr) ans->R[i] = tmpr; else
            ans->R[i] = tmp + rand() % (tmpr - tmp + 1);

        if (img->G[i] == 0) tmp = 0; else tmp = lookG[img->G[i]-1] + 1;
        tmpr = lookG[img->G[i]];
        if (tmp >= tmpr) ans->G[i] = tmpr; else
            ans->G[i] = tmp + rand() % (tmpr - tmp + 1);

        if (img->B[i] == 0) tmp = 0; else tmp = lookB[img->B[i]-1] + 1;
        tmpr = lookB[img->B[i]];
        if (tmp >= tmpr) ans->B[i] = tmpr; else
            ans->B[i] = tmp + rand() % (tmpr - tmp + 1);
    }

    delete[] lookR;
    delete[] lookG;
    delete[] lookB;

    return ans;
}

Image *ImageEdit::histogramStylize(Image *img, Image *refer) {
    if ((img == NULL) || (img->height * img->width <= 0))
        return NULL;
    if ((refer == NULL) || (refer->height * refer->width <= 0))
        return NULL;

    img->calcHistogram();
    refer->calcHistogram();

    srand(time(0));

    int *lookR = new int[256];
    int *lookG = new int[256];
    int *lookB = new int[256];

    int p = 0;
    double mer = 0.0f;
    for (int i=0; i<256; ++i) {
        mer = img->histogram->sumArrR[i];
        while ((p < 255) && (refer->histogram->sumArrR[p+1] <= mer + EPS)) ++p;
        lookR[i] = p;
    }
    p=0;
    for (int i=0; i<256; ++i) {
        mer = img->histogram->sumArrG[i];
        while ((p < 255) && (refer->histogram->sumArrG[p+1] <= mer + EPS)) ++p;
        lookG[i] = p;
    }
    p=0;
    for (int i=0; i<256; ++i) {
        mer = img->histogram->sumArrB[i];
        while ((p < 255) && (refer->histogram->sumArrB[p+1] <= mer + EPS)) ++p;
        lookB[i] = p;
    }

    Image *ans = new Image();
    int h, w;
    h = ans->height = img->height;
    w = ans->width = img->width;
    ans->R = new int[h*w];
    ans->G = new int[h*w];
    ans->B = new int[h*w];

    int tmp, tmpr;
    for (int i=0; i<h*w; ++i) {
        if (img->R[i] == 0) tmp = 0; else tmp = lookR[img->R[i]-1] + 1;
        tmpr = lookR[img->R[i]];
        if (tmp >= tmpr) ans->R[i] = tmpr; else
            ans->R[i] = tmp + rand() % (tmpr - tmp + 1);

        if (img->G[i] == 0) tmp = 0; else tmp = lookG[img->G[i]-1] + 1;
        tmpr = lookG[img->G[i]];
        if (tmp >= tmpr) ans->G[i] = tmpr; else
            ans->G[i] = tmp + rand() % (tmpr - tmp + 1);

        if (img->B[i] == 0) tmp = 0; else tmp = lookB[img->B[i]-1] + 1;
        tmpr = lookB[img->B[i]];
        if (tmp >= tmpr) ans->B[i] = tmpr; else
            ans->B[i] = tmp + rand() % (tmpr - tmp + 1);
    }

    delete[] lookR;
    delete[] lookG;
    delete[] lookB;

    return ans;
}
