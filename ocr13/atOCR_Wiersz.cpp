#include "atOCR_Wiersz.h"
#include "atOCR.h"


//-----------------------------------------
atOCR_Wiersz::atOCR_Wiersz( int min, int max, atOCR* o){
    wierszMin=min;
    wierszMax=max;
    imgGray=o->getImageGray();
    ocr=o;
   // cnf=o->getCnf();
}
int atOCR_Wiersz::getColGranica() {return (double)maxCol*ocr->getColPoziom();}
//-------------------------------------------------------------------
void atOCR_Wiersz::sumowanieKolumn(){

    minCol=255;
    maxCol=0;
    cols.clear();
    for(int i=0; i<imgGray->cols ; i++) {
        int long sumCol=0;
        for(int j=wierszMin; j<wierszMax ; j++) {   sumCol+=imgGray->at<uchar>(j,i);     }
        int x1=256-sumCol/(wierszMax-wierszMin);
        if(x1<minCol) minCol=x1;
        if(x1>maxCol) maxCol=x1;
        cols.push_back(x1);
    }
}
//--------------------------------------------------------------------------------
void atOCR_Wiersz::analizaKolumn(){
    sumowanieKolumn();
    int colSzerokosc=ocr->getColSzerokosc();//cnf->getInt("colSzerokosc");
    double colPoziom=ocr->getColPoziom();   //cnf->getFloat("colPoziom");
    int maxGranica=getColGranica();
    int ostatniDuzy=0;
    for(int i=1; i<cols.size(); i++) {
       if(cols.at(i)>maxGranica){
           if(i>ostatniDuzy+colSzerokosc){
               //analizaKolumny(min,max, ostatniDuzy, i, dst);
               atOCR_Pole pole=atOCR_Pole(wierszMin,wierszMax,ostatniDuzy, i, imgGray,ocr->getCnf());
               pole.analiza();
               //pola.push_back(pole);
           }
           ostatniDuzy=i;
       }


    }
}

