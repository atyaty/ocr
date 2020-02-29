#include "mainwindow.h"
//-------------------------------------------------------------------------
mainwindow::mainwindow() {
 //------------------------------
 atInit();
 ocr.atInit(cnf);
 img=NULL;
 im=NULL;
 //-------------------------------
 this->set_border_width(10);
 this->set_default_size(500,800);
 //-------------------------------------------
 image1.set("../image/fractal_image.png");
 m_imagebox.add(image1);
 m_imagebox.set_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK);
 m_ScrolledImage.set_size_request(800,400);
 m_ScrolledImage.add(m_imagebox);
 m_ScrolledImage.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
 g.attach(m_ScrolledImage,0,1,1,1);

 //-----------------------------
 m_refTextBuffer = Gtk::TextBuffer::create();
 m_refTextBuffer->set_text(  "Dzień dobry, tu program OCR.\nWczytaj plik, a potem myszką zaznacz fragment do analizy OCR.");
 m_TextView.set_buffer(m_refTextBuffer);
 m_ScrolledWindow.set_size_request(800,400);
 m_ScrolledWindow.add(m_TextView);
 m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
 g.attach(m_ScrolledWindow,1,1,1,1);
 //----------------------------------
 b.add_label("Wczytaj");
 b.signal_pressed().connect(sigc::mem_fun(*this,&mainwindow::onWczytaj));
 b1.add_label("Przelicz");
// b1.signal_pressed().connect(sigc::mem_fun(*this,&mainwindow::onPrzelicz));
// g.attach(b,0,0,1,1);//siatka
 //---------------------------------------
 g1.attach(b,0,0,1,1);
 g1.attach(b1,1,0,1,1);

 //------------------------------------------------
 g.attach(g1,0,0,1,1);
 g.set_column_spacing(10);
 //------------------------------------------
 g.show_all();
 add(g);
}
//-------------------------------------------------
mainwindow::~mainwindow() {
   // delete canvas;  delete plot; delete plot_data1;
}
//-------------------------------------------------
void mainwindow::onWczytaj(){
    Gtk::FileChooserDialog dialog("Wybierz plik",Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_OK);
    int result = dialog.run();
    if(result==Gtk::RESPONSE_OK){
        filename = dialog.get_filename();
        img = cv::imread(filename);
        img.copyTo(im);
        ocr.wczytaj(filename); //wczytanie i analiza pliku
        atPokaz();
        Glib::RefPtr<Gdk::Pixbuf>  pixbuf = Gdk::Pixbuf::create_from_data(  (guint8*)im.data, Gdk::COLORSPACE_RGB, false,8, im.cols, im.rows, (int)im.step );
        image1.set(pixbuf);

     }
}
//-----------------------------------------------------------------
void mainwindow::atInit(){
    cnf = new at_Konfiguracja("../config/config");
}
//-----------------------------------------------------------------
void mainwindow::atPokaz(){
 //   atPokazSr();
    atPokazPiki();
    atPokazGarby();

  //rysowanie falbanek vertykali
  for(unsigned long j=0; j<ocr.getVerticaleSize(); j++) {
      atOCR_Vertical* V=ocr.getVertical(j);
      int punkt0x=V->getVerticalMin()+V->getRow(0);
      int punkt0y=0;
      for(unsigned long i=1; i<V->getRowsSize(); i++) { //falbanka vertykala j
         Scalar color=Scalar(255,0,255);
         if(V->getRow(i)>V->getRowSr(i) ) color=Scalar(255,0,0);
         line( im, Point(punkt0x,punkt0y), Point(V->getVerticalMin()+V->getRow(i),i), color, 2, 8, 0 );
         //line( im, Point(0,i), Point(ocr.getRow(i),i), color, 2, 8, 0 );
         punkt0x=V->getVerticalMin()+V->getRow(i);
         punkt0y=i;

      }
  }


}
//-----------------------------------------------------------------
void mainwindow::atPokazPiki(){
  for(unsigned long j=0; j<ocr.getVerticaleSize(); j++) {
      atOCR_Vertical* V=ocr.getVertical(j);
      for(unsigned long i=0; i<V->getPikSize(); i++) {
          atOCR_Pik *pik=V->getPik(i);
          atPokazNachylenie(pik,Scalar(255,0,0));
          atPokazPik(pik);

      }
  }


}
//-----------------------------------------------------------------
void mainwindow::atPokazPik(atOCR_Pik *pik){
    atOCR_Vertical* V=pik->getParent();
    double ySL=V->getVerticalMin()+V->getRow(pik->get_iSrL());
    double ySR=V->getVerticalMin()+V->getRow(pik->get_iSrR());
    double yL=V->getVerticalMin()+V->getRow(pik->get_iMinL());
    double y=V->getVerticalMin()+V->getRow(pik->get_iMax());
    double yR=V->getVerticalMin()+V->getRow(pik->get_iMinR());
     //     line( im, Point(ySL,pik->get_iSrL()), Point(V->getVerticalMax(),pik->get_iSrL() ), Scalar(255,255,255), 1, 8, 0 );
     //     line( im, Point(ySR,pik->get_iSrR()), Point(V->getVerticalMax(),pik->get_iSrR() ), Scalar(255,255,255), 1, 8, 0 );
          line( im, Point(y,pik->get_iMax()), Point(V->getVerticalMax(),pik->get_iMax() ), Scalar(255,255,0), 1, 8, 0 );
          line( im, Point(y,pik->get_SC()), Point(V->getVerticalMax(),pik->get_SC() ), Scalar(0,255,0), 1, 8, 0 );
      //    line( im, Point(V->getVerticalMin(),pik->get_iMinL()), Point(yL,pik->get_iMinL() ), Scalar(0,255,255), 1, 8, 0 );
     //     line( im, Point(yR,pik->get_iMinR()), Point(V->getVerticalMax(),pik->get_iMinR() ), Scalar(255,255,0), 1, 8, 0 );
          putText(im, to_string(pik->get_iMax()).c_str(), Point(V->getVerticalMin(), pik->get_iMax()), FONT_HERSHEY_PLAIN,1.0,CV_RGB(255, 255, 255), 1);

}
//-----------------------------------------------------------------
void mainwindow::atPokazNachylenie(atOCR_Pik *pik,Scalar color){
    atOCR_Vertical* V=pik->getParent();
    line( im, Point(V->getVerticalMin(),pik->get_iMaxNachL()), Point(V->getVerticalMax(),pik->get_iMaxNachR() ), color, 1, 8, 0 );
    string s=to_string(pik->get_WysMax())+"/"+to_string(pik->get_WysMaxNach());
    putText(im, s.c_str(), Point(V->getVerticalMin()+200, pik->get_iMax()), FONT_HERSHEY_PLAIN,1.0,CV_RGB(100, 255, 255), 1);

}
//-----------------------------------------------------------------
void mainwindow::atPokazGarby(){
  for(unsigned long j=0; j<ocr.getGarbySize(); j++) {
      atOCR_Pik* P=ocr.getGarbPik(j);
      atPokazGarb(P,Scalar(255,255,255));


  }
}
//-----------------------------------------------------------------
void mainwindow::atPokazGarb(atOCR_Pik* P,Scalar color){
    atOCR_Pik* N=P->getNext();
    if(N!=nullptr || P->getPrev()!=nullptr) atPokazNachylenie(P,color);
    if(N!=nullptr) atPokazGarb(N,color);

}

//-----------------------------------------------------------------
void mainwindow::atPokazSr(){
  //rysowanie falbanek średnich vertykali
  for(unsigned long j=0; j<ocr.getVerticaleSize(); j++) {
      atOCR_Vertical* V=ocr.getVertical(j);
      int punkt0x=V->getVerticalMin()+V->getRowSr(0);
      int punkt0y=0;
      Scalar color=Scalar(255,255,255);
      for(unsigned long i=1; i<V->getRowsSize(); i++) { //falbanka sr
         line( im, Point(punkt0x,punkt0y), Point(V->getVerticalMin()+V->getRowSr(i),i), color, 1, 8, 0 );
         punkt0x=V->getVerticalMin()+V->getRowSr(i);
         punkt0y=i;

      }
  }


}



//----------------------------------------------------------------------------------
string  mainwindow::analizaWiersza(int min, int max, Mat* dst){
    if(filename==""){ m_refTextBuffer->set_text(""); return ""; }
    cv::rectangle(im, cv::Rect( 0,min,img.cols-300,max-min), cv::Scalar(255,255,0), 1, 8,  0);
    //------------------------------------
    int minCol=255;
    int maxCol=0;
    vector <uchar> cols;
    for(int i=0; i<dst->cols ; i++) {
        int long sumCol=0;
        for(int j=min; j<max ; j++) {
            sumCol+=dst->at<uchar>(j,i);
        }

        int x1=256-sumCol/(max-min);
        if(x1<minCol) minCol=x1;
        if(x1>maxCol) maxCol=x1;

        cols.push_back(x1);
    }

    string s;
    int maxGranica=(maxCol*4)/5;
    int ostatniDuzy=0;
    int punkt0x=0;
    int punkt0y=min+cols.at(0);
    for(int i=1; i<cols.size(); i++) {
       Scalar color=Scalar(0,255,255);
       if(cols.at(i)>maxGranica){
           color=Scalar(255,0,0);
           if(i>ostatniDuzy+10){
               s+=analizaKolumny(min,max, ostatniDuzy, i, dst);
           }
           ostatniDuzy=i;
       }

       line( im, Point(punkt0x,punkt0y), Point(i,min+cols.at(i)), color, 2, 8, 0 );
       punkt0x=i;
       punkt0y=min+cols.at(i);

    }




    return s;
}
//---------------------------------------------------------------------------
string   mainwindow::analizaKolumny(int row_min,int row_max, int col_min, int col_max, Mat* dst){
    int paddingX=5;
    int paddingY=5;
    int Col_min=col_min+paddingX;
    int Col_max=col_max-paddingX;
    int Row_min=row_min+paddingY;
    int Row_max=row_max-paddingY;
    int subStringMax=50;

    if(filename==""){ m_refTextBuffer->set_text(""); return ""; }
    cv::rectangle(im, cv::Rect( Col_min,Row_min,Col_max-Col_min,Row_max-Row_min), cv::Scalar(255,0,255), 1, 8,  0);
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    if (api->Init(NULL, "eng")) { m_refTextBuffer->set_text("BŁĄD! inicjowanie tesseract"); return "";   }
    api->SetImage(img.data, img.cols, img.rows, 3, img.step);
    api->SetRectangle(Col_min,Row_min,Col_max-Col_min,Row_max-Row_min);
    char* ocrResult = api->GetUTF8Text();
    string s=ocrResult;
    api->End();
    putText( im, s.substr(0,subStringMax).c_str(), Point(Col_min+2, Row_min+10), FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(118, 185, 0),  2);
    return"";
}


