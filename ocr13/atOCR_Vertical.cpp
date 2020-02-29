#include "atOCR_Vertical.h"
#include "atOCR.h"
#include "atOCR_Pik.h"

//-----------------------------------------
atOCR_Vertical::atOCR_Vertical( int min, int max, atOCR* o){
    next=nullptr;
    ocr=o;
    verticalMin=min;
    verticalMax=max;
    rowSzerokosc=ocr->getRowSzerokosc();
    szerokosc_usrednienia=5*rowSzerokosc;
    analizaWierszy();
}
//-----------------------------------------
atOCR_Vertical::~atOCR_Vertical( ){
    for(unsigned i=0; i<piki.size();i++){delete piki[i];}

}
//-----------------------------------------
int atOCR_Vertical::getRowGranica() {return (double)maxRow*ocr->getRowPoziom();}
//-------------------------------------------
void atOCR_Vertical::sumowanieWierszy(){
    Mat* imgGray=ocr->getImageGray();
    minRow=255;
    maxRow=0;
    rows.clear();
    for(int i=0; i<imgGray->rows ; i++) {
        int long sumRow=0;
        for(int j=verticalMin; j<verticalMax ; j++) {  sumRow+=imgGray->at<uchar>(i,j);    }
        int y1=256-sumRow/(verticalMax-verticalMin);
        if(y1<minRow) minRow=y1;
        if(y1>maxRow) maxRow=y1;
        rows.push_back(y1);
    }
}

//-------------------------------------------
//obliczamy wartości średnie
void atOCR_Vertical::usrednienie(){
    int long Suma_do_usrednienia=0;
    unsigned n=0;
    int ii=rows.size();
    for(int i=-szerokosc_usrednienia; i<ii; i++){
        if((i+szerokosc_usrednienia)<rows.size()){Suma_do_usrednienia+=rows[i+szerokosc_usrednienia];n++;}
        if((i-(int)szerokosc_usrednienia)>=0){
            Suma_do_usrednienia-=rows[i-szerokosc_usrednienia];n--;}
        if(i>=0)
            rowsSr.push_back(Suma_do_usrednienia/n);

    }
}

//-------------------------------------------
void atOCR_Vertical::analizaWierszy(){
    sumowanieWierszy();
    usrednienie();

    unsigned iMax      = 0;             //zerowe maximum
    unsigned iMin      = 0;             //zerowe minimum
    unsigned iSL      = 0;             //zerowe minimum
    unsigned maxValue  = rows[0];       //wartosc w zerowym maximum
    unsigned minValue  = rows[0];
    unsigned sLValue  = rows[0];

    bool szukamyMax=false;
    for(unsigned i=0; i<rows.size(); i++) {
        if(!szukamyMax) {  //--------------- szukamy Min
          if(rows[i]>rowsSr[i] || i==(rows.size()-1)){
//              if(piki.size()!=0)  piki[piki.size()-1]->set_WysR(iMin,i,minValue,rows[i]); //uzupełnienie poprzedniego piku przed resetem
              if(piki.size()!=0)  piki[piki.size()-1]->set_WysR(iMin,minValue); //uzupełnienie poprzedniego piku przed resetem
              iSL=i; sLValue=rows[i];                                                     //zapamiętane do konstrukcji nowego piku
              szukamyMax=true; maxValue=rows[i]; iMax=i;                                 //reset
          }
          else if(rows[i]<minValue){  minValue=rows[i];  iMin=i;      }
        }
        else{ //----------------------------- szukamy Max
          if(rows[i]<rowsSr[i] ){
              piki.push_back( new atOCR_Pik(iMax, iMin, iSL, i, maxValue, minValue, sLValue, rows[i], this) ); //przed resetem
              szukamyMax=false;  minValue=rows[i]; iMin=i;                             //reset minimalnych wartości
          }
          else if(rows[i]>maxValue) {  maxValue=rows[i]; iMax=i;      }
        }
    }

}

//-------------------------------------------
unsigned long  atOCR_Vertical::getPikSize()               {return piki.size();}
atOCR_Pik*     atOCR_Vertical::getPik(unsigned long i)    {return piki[i]; }

//-------------------------------------------
//pętla po garbach bez kontekstu jedzie po wszystkich, które nie są zaznaczone jako sprawdzone
void atOCR_Vertical::znajdzGarby(  ) {
    for(unsigned i=0;i<piki.size();i++){
       // piki[i]->obliczNachylenie( 5 );  //debug
        if( !piki[i]->isChecked() ){
            piki[i]->setChecked(true);
            ocr->addGarb(piki[i]);
            if( next!=nullptr) next->znajdzGarb(piki[i]);  //szukamy w następnym verticalu
        }
    }
}
//-------------------------------------------
//petla szukająca piku zgodnego z przekazanym w parametrze
void atOCR_Vertical::znajdzGarb( atOCR_Pik* g ) {
    unsigned stykPrev=0;
    for(unsigned i=0;i<piki.size();i++){
     /*   if( !piki[i]->isChecked() && piki[i]->znajdzGarb(g) ){
            piki[i]->setChecked(true);
            piki[i]->setPrev(g);
            g->setNext(piki[i]);
            ocr->addGarb(piki[i]);
            if( next!=nullptr) next->znajdzGarb(piki[i]); //szukamy w następnym verticalu
            return;
        }*/
        if( !piki[i]->isChecked()) {
           int styk=piki[i]->porownajPiki(g) ;
           if(stykPrev>0 && styk>stykPrev) return;  //jeśli odległość od g rośnie, to znaczy, że już nie ma sensu szukać dalej
           stykPrev=styk;
        }
    }
}
unsigned atOCR_Vertical::get_dSzerokosc()  {return ocr->get_dSzerokosc();}
unsigned atOCR_Vertical::get_dWysokosc()   {return ocr->get_dWysokosc();}
unsigned atOCR_Vertical::get_dPozycja()    {return ocr->get_dPozycja();}
unsigned atOCR_Vertical::get_dNachylenie() {return ocr->get_dNachylenie();}
