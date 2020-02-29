#include "atOCR_Pole.h"



//-----------------------------------------
void atOCR_Pole::analiza(){

    int paddingCol=cnf->getInt("colPadding");
    int paddingRow=cnf->getInt("rowPadding");
    int Col_min=colMin+paddingCol;
    int Col_max=colMax-paddingCol;
    int Row_min=wierszMin+paddingRow;
    int Row_max=wierszMax-paddingRow;
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    if (api->Init(NULL, "eng")) { return;   }                       //BŁAD
    api->SetImage(imgGray->data, imgGray->cols, imgGray->rows, 3, imgGray->step);
    api->SetRectangle(Col_min,Row_min,Col_max-Col_min,Row_max-Row_min);
    char* ocrResult = api->GetUTF8Text();
    tekst=ocrResult;
    api->End();
    return;
}
