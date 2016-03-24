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
    std::vector<Pixel> averagePixels;
    std::vector<QString> goodExtension = {QString(".png"), QString(".jpg"), QString(".jpeg")};
    size_t smallImageH;
    size_t smallImageW;
    //Проверка расширения картинки
    bool checkFileExtenson(QString filename);
    //Контур изображения
    void generatePixels();
    //Подбираем маленькое изображения для коллажа
    QString getNearestImage(Pixel pixel);
    //Создание нового изображения
    Bitmap constructImage(std::vector<QString> replacingImages, int wCount, int hCount, QImage::Format imageFormat);
public:

    ImageMaker(std::vector<QString> imagePaths);

    ImageMaker(QString imageFolderPath);
    //Данные для нового изображения
    Bitmap makeImage(QString fromPath, double scaleValue);
};

#endif // IMAGEMAKER_H
