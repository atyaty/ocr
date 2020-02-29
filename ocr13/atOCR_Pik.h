#ifndef ATOCR_PIK_H
#define ATOCR_PIK_H


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
//class atOCR;
//typedef atOCR atOCR;
class atOCR_Vertical;
typedef atOCR_Vertical atOCR_Vertical;


class atOCR_Pik
{
protected:
    unsigned iMax,iMinL,iMinR,iSrL,iSrR;       //położenie piku: max, min z Lewej min z prawej, przejścia przez wartość średnią
    uchar wysMax,wysL,wysR,wysSrL,wysSrR;      //wysokości bezwzględne
    unsigned szerokosc;                        //szerokość piku na poziomie średniej sygnału (liczone z: isrR - iSrL
    uchar wysokosc;                            //wysokość ponad średnią
    unsigned iSC;                              //położenie "środka ciężkości"

    bool checked;
    atOCR_Pik* next;
    atOCR_Pik* prev;
    atOCR_Vertical * parent;

    uchar wysMaxNach;                         //wysokość linii maksymalnego machylenia
    unsigned iMaxNachL,iMaxNachR;             //współrzędne linii maksymalnego nachylenia

public:
    atOCR_Pik(  unsigned max, unsigned minL, unsigned isL,unsigned isR, uchar w, uchar wL, uchar sL, uchar sR,atOCR_Vertical * p);
    ~atOCR_Pik( );


    unsigned get_iSrL()     {return iSrL;}
    unsigned get_iSrR()     {return iSrR;}
    unsigned get_iMinL()    {return iMinL;}
    unsigned get_iMinR()    {return iMinR;}
    unsigned get_iMax()     {return iMax;}
    unsigned get_iMaxNachL(){return iMaxNachL;}
    unsigned get_iMaxNachR(){return iMaxNachR;}
    uchar get_WysR()        { return wysR;}            //
    uchar get_WysL()        { return wysL;}            //
    uchar get_WysSrR()      { return wysSrR;}            //
    uchar get_WysSrL()      { return wysSrL;}            //
    uchar get_WysMax()      { return wysMax;}    //
    uchar get_WysMaxNach()  { return wysMaxNach;}    //
    uchar get_Wysokosc()    { return wysokosc;}    //
    unsigned get_Szerokosc(){ return szerokosc;}    //
    unsigned get_SC()       { return iSC;}    //

    bool isChecked() {return checked;}
    void setChecked(bool c) {checked=c;}
    void setNext(atOCR_Pik* n) {next=n;}
    void setPrev(atOCR_Pik* p) {prev=p;}
    atOCR_Pik* getNext() {return next;}
    atOCR_Pik* getPrev() {return prev;}
    atOCR_Vertical * getParent() {return parent;}

    void set_WysR( unsigned minR,  uchar wR);   //
    void set_Wysokosc(unsigned max, unsigned minL, unsigned isL,unsigned isR, uchar w, uchar wL, uchar sL, uchar sR);    //


    unsigned porownajPiki( atOCR_Pik* g ) ;
    void obliczNachylenie( unsigned n );
};

#endif // ATOCR_PIK_H
