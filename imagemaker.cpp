#include "imagemaker.h"
#include <vector>
#include "QString"
#include "bitmap.h"
#include "QDirIterator"
#include <cassert>
#include <cmath>
#include <QDebug>

//Проверка расширения картинки
bool ImageMaker::checkFileExtenson(QString filename)
{
    for(auto extension = this->goodExtension.begin(); extension != this->goodExtension.end(); ++extension) {
        if(filename.endsWith(*extension)) {
            return true;
        }
    }
    return false;
}
//Контур изображения
void ImageMaker::generatePixels()
{
    for(auto filePath = imagePaths.begin(); filePath != imagePaths.end(); ++filePath) {
        Bitmap bitmap = Bitmap(*filePath);

        if (this->averagePixels.size() != 0) {
            assert(this->smallImageH == bitmap.height && this->smallImageW == bitmap.width);
        }
        this->smallImageH = bitmap.height;
        this->smallImageW = bitmap.width;
        Pixel averagePixel = bitmap.averagePixel();
        this->averagePixels.push_back(averagePixel);
    }
    assert(this->averagePixels.size() == this->imagePaths.size());
}
//Подбирает наиболее подходящее изображение для замены пиксела
QString ImageMaker::getNearestImage(Pixel pixel)
{
    Pixel smallest = this->averagePixels.front();
    QString smallestPath = this->imagePaths.front();

    for(int imageIndex = 0; imageIndex < this->averagePixels.size(); ++imageIndex) {
        Pixel currentPixel = this->averagePixels[imageIndex];
        double smallestDistance = fabs(smallest.red - pixel.red) + fabs(smallest.green - pixel.green) + fabs(smallest.blue - pixel.blue);
        double currentDistance = fabs(currentPixel.red - pixel.red) + fabs(currentPixel.green - pixel.green) + fabs(currentPixel.blue - pixel.blue);
        if (currentDistance < smallestDistance) {
            smallest = currentPixel;
            smallestPath = this->imagePaths[imageIndex];
        }
    }
    return smallestPath;
}
//Собирает изображение из предподсчитынных маленьких
Bitmap ImageMaker::constructImage(std::vector<QString> replacingImages, int wCount, int hCount, QImage::Format imageFormat)
{
    assert(replacingImages.size() == wCount * hCount);
    int newBitmapH = this->smallImageH * (hCount);
    int newBitmapW = this->smallImageW * (wCount);
    std::vector<Pixel> pixels(newBitmapH * newBitmapW, Pixel(0, 0, 0));

    Bitmap resultBitmap = Bitmap(newBitmapW, newBitmapH, pixels, imageFormat);

    for(int imageIndexH = 0; imageIndexH < hCount; ++imageIndexH) {
        for(int imageIndexW = 0; imageIndexW < wCount; ++imageIndexW) {
            int selectedIndex = imageIndexH * wCount + imageIndexW;
            // каждый раз загружать с диска - долго, можно оптимизировать
            Bitmap image = Bitmap(replacingImages[selectedIndex]);
            int startH = image.height * imageIndexH;
            int startW = image.width * imageIndexW;
            for(int dH = 0; dH < image.height; ++dH) {
                for(int dW = 0; dW < image.width; ++dW) {
                    int posH = startH + dH;
                    int posW = startW + dW;
                    assert(posH < resultBitmap.height);
                    assert(posW < resultBitmap.width);

                    Pixel pixel = image.getPixel(dW, dH);

                    resultBitmap.setPixel(posW, posH, pixel);
                }
            }
        }
    }

    return resultBitmap;
}
//Конструктор создает объект ImageMaker, где imagePaths - пути к изображениям
ImageMaker::ImageMaker(std::vector<QString> imagePaths)
{
    this->imagePaths = imagePaths;
    this->generatePixels();
}
//Путь к папке с изображениями (все изображения должны быть одинакового размера)
ImageMaker::ImageMaker(QString imageFolderPath)
{
    QDirIterator directoryIterator(imageFolderPath);
    while(directoryIterator.hasNext()) {
        QString currentFileName = directoryIterator.next();
        if(this->checkFileExtenson(currentFileName)) {
            this->imagePaths.push_back(currentFileName);
        }
    }
    this->generatePixels();
}
//Создает коллаж из маленьких изображений, fromPath - путь к файлу изображения, который хотим создать, scaleValue - коэффициент, на который будут помножены линейные размеры изображения
Bitmap ImageMaker::makeImage(QString fromPath, double scaleValue)
{
    Bitmap bitmap(fromPath, scaleValue);
    int wCount = bitmap.width / this->smallImageW;
    int hCount = bitmap.height / this->smallImageH;
    assert(wCount != 0 && hCount != 0);

    std::vector<QString> replacingImages;

    for(int hIndex = 0; hIndex < hCount; ++hIndex) {
        for(int wIndex = 0; wIndex < wCount; ++wIndex) {
            // Начальные координаты отрезка.
            int h = hIndex * this->smallImageH;
            int w = wIndex * this->smallImageW;

            long long red = 0;
            long long green = 0;
            long long blue = 0;
            for(size_t subImageH = 0; subImageH < this->smallImageH; ++subImageH) {
                for(size_t subImageW = 0; subImageW < this->smallImageW; ++subImageW) {
                    int newH = h + subImageH;
                    int newW = w + subImageW;

                    //check, maybe (newH, newW);
                    Pixel pixel = bitmap.getPixel(newW, newH);
                    red += pixel.red;
                    green += pixel.green;
                    blue += pixel.blue;
                }
            }
            int pixCount = this->smallImageH * this->smallImageW;
            red /= pixCount, green /= pixCount, blue /= pixCount;
            Pixel averagePixel = Pixel(red, green, blue);

            replacingImages.push_back(this->getNearestImage(averagePixel));
        }
    }
    Bitmap output = this->constructImage(replacingImages, wCount, hCount, bitmap.imageFormat);
    return output;
}
