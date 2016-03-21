#include "bitmap.h"
#include <QImage>
#include <QRgb>
#include <QPixmap>
#include <vector>

#include <iostream>

Bitmap::Bitmap()
{

}

// Загрузка изображения из файла.

Bitmap::Bitmap(QString filename)
{
    this->pixels.clear();
    QImage image;
    // Загрузка изображения в QImage. Избавляет от кучи проблем с декодированием.
    image.load(filename);
    // Сохраняем формат изображения. Понадобится при сохранении.
    this->imageFormat = image.format();
    for(int x = 0; x < image.width(); ++x) {
        for(int y = 0; y < image.height(); ++y) {
            QRgb value = image.pixel(x, y);
            int red = qRed(value);
            int green = qGreen(value);
            int blue = qBlue(value);
            this->pixels.push_back(Pixel(red, green, blue));
        }
    }
    this->height = image.height();
    this->width = image.width();
}

// Конструктор копирования
Bitmap::Bitmap(const Bitmap &other)
{
    pixels = other.pixels;
    width = other.width;
    height = other.height;
    imageFormat = other.imageFormat;
}

Bitmap::Bitmap(size_t width, size_t height, std::vector<Pixel> pixels, QImage::Format format)
{
    this->height = height;
    this->width = width;
    this->pixels = pixels;
    this->imageFormat = format;
}

// Экспорт в QPixmap --- формат, используемый QT для вывода изображений на экран, сохранения.

const QPixmap Bitmap::toPixmap()
{
    QImage image = QImage(this->width, this->height, this->imageFormat);
    // Изображение должно быть проинициализировано хоть чем-то перед тем как с ним работать.
    image.fill(Qt::gray);
    // Перебор всех точек, затем установка значений в image.
    for(size_t x = 0; x < this->width; ++x) {
        for(size_t y = 0; y < this->height; ++y) {
            Pixel pixel = this->getPixel(x, y);
            image.setPixel(x, y, qRgba(pixel.red, pixel.green, pixel.blue, 1));
        }
    }
    const QPixmap pixmap = QPixmap::fromImage(image);
    return pixmap;
}

// Доступ к точке по ее координатам.
Pixel Bitmap::getPixel(int x, int y)
{
    int position = x * this->height + y;
    Pixel pixel = this->pixels[position];
    return pixel;
}

// Устанавливает значение точки.
void Bitmap::setPixel(int x, int y, Pixel pixel)
{
    int position = x * this->height + y;
    pixel.validate();
    this->pixels[position] = pixel;
}


