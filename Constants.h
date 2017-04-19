#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

using namespace std;

class Constants
{
public:
    static string PROJ_NAME;
    static int DEFAULT_WIDTH;
    static int DEFAULT_HEIGHT;
    static string IO_GROUP_TITLE;
    static string HISTOGRAM_GROUP_TITLE;
    static string RESAMPLING_GROUP_TITLE;
    static string FOURIER_GROUP_TITLE;
    static string FORGREY_GROUP_TITLE;
    static string ABOUT_GROUP_TITLE;
    static string OPEN_IMAGE_CAPTION;
    static string SAVE_IMAGE_CAPTION;
    static string SHOW_HISTOGRAM_CAPTION;
    static string BRIGHT_CAPTION;
    static string GAMMA_CAPTION;
    static string HISTOGRAM_EQUALIZATION_CAPTION;
    static string HISTOGRAM_MATCH_CAPTION;
    static string RESAMPLING_CAPTION;
    static string SHOW_FOURIER_CAPTION;
    static string FOURIER_FUSION_CAPTION;
    static string POINT_DETECT_CAPTION;
    static string DIFFERENCE_CAPTION;
    static string ABOUT_CAPTION;
    static string OPEN_IMAGE_DIALOG;
    static string OPEN_IMAGE_FILTER;
    static string SAVE_IMAGE_DIALOG;
    static string SAVE_IMAGE_FILTER;
    static string SAVE_IMAGE_INFO;

    Constants();
};

#endif // CONSTANTS_H
