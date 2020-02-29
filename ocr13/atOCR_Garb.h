#ifndef ATOCR_GARB_H
#define ATOCR_GARB_H



#include "iostream"
#include <gtkmm.h>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#include <at_File.h>
#include <at_Konfiguracja.h>
#include <atOCR_Pik.h>

using namespace std;
using namespace cv;

//------------------------
class atOCR_Garb {
private:
    atOCR_Pik* pik;
    unsigned len; //długość garbu
public:
    atOCR_Garb(atOCR_Pik* p){pik=p;}
    atOCR_Pik* getPik(){ return pik;}
    unsigned getLen(){ return len; }
    unsigned countLen();

};
#endif // ATOCR_GARB_H
