#include "mainwindow.h"

#include <QApplication>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// TODO - Add textures
// TODO - Add a spaceship, which flies across the screen when a button is pushed, this can also our convex model with normals.
// TODO - Add a stary background
// TODO - Space items out a bit better, so it looks a bit nicer

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(750, 750);
    w.show();
    return a.exec();
}
