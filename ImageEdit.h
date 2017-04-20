#ifndef IMAGEEDIT_H
#define IMAGEEDIT_H

#include <cstdlib>
#include <ctime>
#include "Image.h"

class ImageEdit
{
public:
    ImageEdit();

    static Image *brightAdjust(Image *img, int delta);
    static Image *brightAdjust(Image *img, int deltaR, int deltaG, int deltaB);
    static Image *contrastAdjust(Image *img, int minPoint, int maxPoint);
    static Image *gammaAdjust(Image *img, double gamma);
    static Image *histogramEqualization(Image *img);
    static Image *histogramStylize(Image *img, Image *refer);
};

#endif // IMAGEEDIT_H
