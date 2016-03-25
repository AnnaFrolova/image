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
int toInt(char *str)
{
    std::string s(str);
    std::string::size_type sz;
    return std::stoi(s, &sz);
}

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);
    if(argc != 5)
    {
        std::cout << "Argument error";
        return -1;
    }
    QString pathToImages = QString(argv[2]); //Путь к изображениям, которые мы используем для создания коллажа
    QString inputPath = QString(argv[1]); //Путь к изображению, коллаж которого мне нужно получить
    QString outputPath = QString(argv[3]); //Путь к коллажу
    int zoom = toInt(argv[4]); //Увеличение изображения в zoom раз
    ImageMaker maker(pathToImages);
    Bitmap bitmap = maker.makeImage(inputPath, zoom); //Данные для коллажа
    QImage pixmap = bitmap.toImage(); //Создание коллажа

    QFile file(outputPath);
    file.open(QIODevice::WriteOnly);
    pixmap.save(&file);
    qDebug() << "ok";
}
