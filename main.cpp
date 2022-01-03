#include "mainwindow.h"

#include <QApplication>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// TODO - get the rest of the remaining textures
// TODO - Add rings to saturn I reckon
// TODO - Add a stary background (BIG MAYBE)
// TODO - Space items out a bit better, so it looks a bit nicer

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(750, 750);
    w.show();
    return a.exec();
}
