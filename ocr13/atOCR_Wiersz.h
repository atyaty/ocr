#ifndef ATOCR_WIERSZ_H
#define ATOCR_WIERSZ_H


#include "iostream"
#include <gtkmm.h>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <atOCR_Pole.h>


using namespace std;
using namespace cv;
class atOCR;
typedef atOCR atOCR;

//-----------------------------------------------------------------
class atOCR_Wiersz {
private:
    Mat *imgGray;
    int wierszMin,wierszMax;//zakres wiersza
    int minCol,maxCol; //maxymalne wartosci w falbance

//    vector <atOCR_Pole> pola;
    vector <uchar> cols;
    atOCR * ocr;
public:
    atOCR_Wiersz( int min, int max, atOCR* o);
    void analizaKolumn();
    void sumowanieKolumn();
//    unsigned long  getSize() {return pola.size();}
 //   atOCR_Pole *getPole(unsigned long i) {return &(pola[i]); }
    unsigned long  getColsSize()           { return cols.size();}
    uchar          getCol(unsigned long i) { return cols[i]; }
    int getColGranica();
    int getWierszMin() {return wierszMin;}
    int getWierszMax() {return wierszMax;}
    void setMaxRow(int r){ wierszMax=r;}    //metoda służy do zmiany zakresu w istniejącym objekcie

};

#endif // ATOCR_WIERSZ_H
