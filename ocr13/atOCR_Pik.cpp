#include "atOCR_Pik.h"
#include "atOCR.h"


//----------------------------------------------------------
atOCR_Pik::atOCR_Pik( unsigned max, unsigned minL, unsigned isL,unsigned isR, uchar w, uchar wL, uchar sL, uchar sR,atOCR_Vertical * p){
    set_Wysokosc(max,minL,isL,isR,w,wL,sL,sR);
    iMinR=0;
    wysR=0;
    szerokosc=0;
    wysokosc=0;
    checked =false;
    parent=p;
    next=nullptr;
    prev=nullptr;
}
//---------------------------------------------------
void atOCR_Pik::set_WysR( unsigned minR,  uchar wR){
    wysR=wR;
    iMinR=minR;
    szerokosc=abs(iSrR-iSrL);
    wysokosc=abs( wysMax - ((wysL+wysR)/2) );
    iSC=(iSrR+iSrL)/2;
    obliczNachylenie( 5 );

}    //
//---------------------------------------------------
void atOCR_Pik::set_Wysokosc(unsigned max, unsigned minL, unsigned isL,unsigned isR, uchar w, uchar wL, uchar sL, uchar sR){
    wysMax =w;
    wysL   =wL;
    iMax   =max;
    iMinL  =minL;
    iSrL   =isL;
    wysSrL =sL;
    iSrR   =isR;
    wysSrR =sR;

}    //
//---------------------------------------------------
atOCR_Pik::~atOCR_Pik( ){}
//-------------------------------------------------------
//zwracamy odległosc pomiędzy pikami,
//lub 0 jeśli pętla ma byc przerwana,
unsigned atOCR_Pik::porownajPiki( atOCR_Pik*  g ){
    unsigned styk=abs((int) (iMaxNachL - g->get_iMaxNachR()) );
    unsigned nach=abs((int) ((iMaxNachR-iMaxNachL) - (g->get_iMaxNachR()-g->get_iMaxNachL())));
    if( styk<parent->get_dPozycja() && nach<parent->get_dNachylenie() ){
        checked=true;
        prev=g;
        g->setNext(this);
        if( parent->getNext()!=nullptr) parent->getNext()->znajdzGarb(this); //szukamy w następnym verticalu
        return 0;   //przerywamy pętlę bo znaleziono garb
    }
    return styk;

}
//-------------------------------------------------------
//zlicza sumy kontrolne z obszaru o wymiarach X na Y
//środek obszaru w osi x: X0,
//środek dla y liczony jest podwójnie: Y0=iSC oraz Y1=iMax
//znajdowana jest największa wartość sygnału dla zakresu kierunków oaz tych dwóch środków obrotu
void atOCR_Pik::obliczNachylenie(     unsigned n ){

    wysMaxNach=wysMax; iMaxNachL=iSC; iMaxNachR=iSC;
    atOCR* ocr =parent->getOCR();
    Mat* img =ocr->getImageGray();
    unsigned X0=(unsigned)((parent->getVerticalMax()+parent->getVerticalMin())/2);  //środek obszaru
    unsigned X=(unsigned)(parent->getVerticalMax()-parent->getVerticalMin());       //zakres współrzędnych X
    unsigned dX=X/(n*2+1);
    unsigned ddX=dX/(n*2+1);
    unsigned Y0=iMax;
    unsigned Y1=iSC;
    int Y=szerokosc*2;                                                         //zakres współrzędnych Y
    if( ((int)Y0-Y/2)<0 || ((int)Y0+Y/2)>=img->cols ) { return; }

    for(unsigned i=0; i<=(2*n); i++){
        unsigned sum0=0;
        unsigned sum1=0;
        for(unsigned j=0; j<=(2*n); j++){
            int jx= (j-n)*dX - (i-n)*ddX;
            int iy= (((jx * Y)/(int)X)*(int)(i-n))/(int)(2*n+1);
            sum0+=img->at<uchar>(Y0+iy,X0+jx);
            sum1+=img->at<uchar>(Y1+iy,X0+jx);
        }
        uchar wys0=256-sum0/(2*n+1);
        uchar wys1=256-sum1/(2*n+1);
        int iy=(Y/2)*((int)(i-n))/(int)(2*n+1);

        if(wysMaxNach<wys0) { wysMaxNach=wys0; iMaxNachL=Y0-iy; iMaxNachR=Y0+iy;    }
        if(wysMaxNach<wys1) { wysMaxNach=wys1; iMaxNachL=Y1-iy; iMaxNachR=Y1+iy;    }
    }

}
