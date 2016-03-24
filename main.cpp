#include <QCoreApplication>
#include "bitmap.h"
#include <iostream>
#include "QDirIterator"
#include <string>
#include <vector>
#include <cmath>
#include <qpixmap.h>
#include <imagemaker.h>
#include <QDebug>
#include <QImage>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString pathToImages = QString(argv[1]);
    QString inputPath = QString(argv[2]);
    QString outputPath = QString(argv[3]);

    ImageMaker maker(pathToImages);
    Bitmap bitmap = maker.makeImage(inputPath, 10);
    QImage pixmap = bitmap.toImage();

    QFile file(outputPath);
    file.open(QIODevice::WriteOnly);
    pixmap.save(&file);
    qDebug() << "ok";
}
