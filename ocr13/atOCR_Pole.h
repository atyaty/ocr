#ifndef ATOCR_POLE_H
#define ATOCR_POLE_H


#include "iostream"
#include <gtkmm.h>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#include <at_File.h>
#include <at_Konfiguracja.h>
#include <atOCR_Vertical.h>

using namespace std;
using namespace cv;
class atOCR;
typedef atOCR atOCR;

//---------------------------------------------------------------------------
class atOCR_Pole {
private:
    Mat *imgGray;
    int wierszMin,wierszMax;
    int colMin,colMax;
    at_Konfiguracja * cnf;
    string tekst;

public:
    atOCR_Pole( int minR, int maxR, int minC, int maxC, Mat *i,at_Konfiguracja * c){wierszMin=minR;wierszMax=maxR;colMin=minC;colMax=maxC;imgGray=i;cnf=c;}
    void analiza();
    int getWierszMin() {return wierszMin;}
    int getWierszMax() {return wierszMax;}
    int getColMin() {return colMin;}
    int getColMax() {return colMax;}
    string getTekst() {return tekst;}
    int getColSize() {return colMax-colMin;}
    int getRowSize() {return wierszMax-wierszMin;}
};

#endif // ATOCR_POLE_H
