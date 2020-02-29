#ifndef ATOCR_VERTICAL_H
#define ATOCR_VERTICAL_H

#include "iostream"
#include <gtkmm.h>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

using namespace std;
using namespace cv;

class atOCR;
typedef atOCR atOCR;

class atOCR_Pik;
typedef atOCR_Pik atOCR_Pik;

//-------------------------------------------------------
//pasek pionowy
class atOCR_Vertical {
private:
    int minRow, maxRow;            //maxymalne wartości w falbance wiersza
    int verticalMin,verticalMax;   //zakres verticala
    unsigned szerokosc_usrednienia; //z konfiguracji
    unsigned rowSzerokosc;          //

    vector <atOCR_Pik*> piki;
    vector <uchar> rows;
    vector <uchar> rowsSr;         //uśrednienie
    atOCR * ocr;                   //parent
    atOCR_Vertical * next;         // zmienna robocza do organizowania pętli po vertikalach
public:

    atOCR_Vertical(int min, int max, atOCR* o);
    virtual ~atOCR_Vertical();
    void     analizaWierszy();
    void     sumowanieWierszy();
    void     usrednienie();
    void     znajdzGarby();
    void     znajdzGarb( atOCR_Pik* g);
    void     setNext(atOCR_Vertical * v){ next=v;}
    unsigned long  getPikSize();
    atOCR_Pik*     getPik(unsigned long i);
    unsigned long  getRowsSize()              {return rows.size();}
    uchar          getRow(unsigned long i)    {return rows[i]; }
    uchar          getRowSr(unsigned long i)  {return rowsSr[i]; }
    int            getRowGranica();
    int            getVerticalMin()           { return verticalMin;}
    int            getVerticalMax()           { return verticalMax;}
    atOCR_Vertical * getNext(){ return next;}

    unsigned get_dSzerokosc();
    unsigned get_dWysokosc();
    unsigned get_dPozycja();
    unsigned get_dNachylenie();

    atOCR * getOCR() {return ocr;}
};

#endif // ATOCR_VERTICAL_H
