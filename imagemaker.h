#ifndef IMAGEMAKER_H
#define IMAGEMAKER_H

#include <vector>
#include "pixel.h"
#include "QString"
#include "bitmap.h"

class ImageMaker
{
private:
    //Контур изображения
    std::vector<QString> imagePaths;
    //Среднее значение пикселей изображения
    std::vector<Pixel> averagePixels;
    //Хорошие расширения изображения
    std::vector<QString> goodExtension = {QString(".png"), QString(".jpg"), QString(".jpeg")};
    //Размер маленьких изображений в коллаже
    size_t smallImageH;
    size_t smallImageW;
    //Проверка расширения изображения
    bool checkFileExtenson(QString filename);
    //Контур изображения
    void generatePixels();
    //Подбирает наиболее подходящее изображение для замены пиксела
    QString getNearestImage(Pixel pixel);
    //Собирает изображение из предподсчитынных маленьких
    Bitmap constructImage(std::vector<QString> replacingImages, size_t wCount, size_t hCount, QImage::Format imageFormat);
public:
    //Конструктор создает объект ImageMaker, где imagePaths - пути к изображениям
    ImageMaker(std::vector<QString> imagePaths);
    //Путь к папке с изображениями (все изображения должны быть одинакового размера)
    ImageMaker(QString imageFolderPath);
    //Создает коллаж из маленьких изображений, fromPath - путь к файлу изображения, который хотим создать, scaleValue - коэффициент, на который будут помножены линейные размеры изображения
    Bitmap makeImage(QString fromPath, double scaleValue);
};

#endif // IMAGEMAKER_H
