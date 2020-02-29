#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "iostream"
#include <gtkmm.h>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#include <at_File.h>
#include <at_Konfiguracja.h>
#include <atOCR.h>
//#include <atOCR_Pik.h>

using namespace std;
using namespace cv;

//-------------------------------------------------------------------------
class mainwindow: public Gtk::Window  {
public:
    mainwindow();
    ~mainwindow();

protected:
    Gtk::Grid     g;                               //siatka
    Gtk::Button   b;                               //klawisz wczytania
    Gtk::EventBox m_imagebox;                      //pole zdarzeń dla obrazka. Powyższa klasa nie (Gtk::Image) nie obsługuje zdarzeń myszki. żeby to robić musi być wstawiona do EventBox'a
    Gtk::Label label1;                             //napis oddzielający

    Gtk::ScrolledWindow m_ScrolledWindow;          //przewijak do pola tekstowego
    Gtk::TextView m_TextView;                      //pole tekstowe
    Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer; //bufor tekstu do współpracy z polem

    Gtk::ScrolledWindow m_ScrolledImage;           //przewijak do obrazka
    Gtk::Image    image1;                          //obrazek do wyswietlenia

    Gtk::Grid g1;
    Gtk::Label l1;
    Gtk::Button b1;


    //-------------------------------------------------------------------------------
    void        onWczytaj();           //procedura wczytania obrazka z pliku
    void        atInit();              //szukanie bloków tekstu
    string      analizaWiersza(int min, int max, Mat* dst);        //OCR wybranego wiersza
    string      analizaKolumny(int Row_min,int Row_max, int Col_min, int Col_max,  Mat* dst);
    void        atPokaz();
    void        atPokazSr();
    void        atPokazPiki();
    void        atPokazGarby();
    void        atPokazGarb(atOCR_Pik* P, Scalar color);
    void        atPokazNachylenie(atOCR_Pik *pik, Scalar color);
    void        atPokazPik(atOCR_Pik *pik);
    string filename;                   //nazwa plkiu do analizy
    cv::Mat img,im;                    //objekt obrazka (img-czysty, im-z dorysowanym prostoktem zaznaczenia)
    atOCR ocr;

    //----------------------------------------------------------
    at_Konfiguracja * cnf;

};

#endif // MAINWINDOW_H
