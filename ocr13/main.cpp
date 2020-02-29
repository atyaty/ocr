/*
skończyliśmy na napisaniu funkcji void atOCR_Vertical::analizaWierszy()
porównujemy wysokość znalezionego PIKu z minimalną wysokością

*/
#include <mainwindow.h>
#include <gtkmm.h>

using namespace Gtk;
int main(int argc, char* argv[]) {
    Main app = Main(argc, argv); // Initialize gtkmm
    mainwindow w;              // Create the window
    app.run(w);         // Start main loop

    return 0;
}
