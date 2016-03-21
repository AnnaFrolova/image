#ifndef BITMAP_H
#define BITMAP_H

#include <vector>
#include "pixel.h"
#include <QImage>

// Предсталвение изображения в виде массива точек.
// Заметим, что точка с координатами (0, 0) находится в левом верхнем углу изображения
// Ось Х горизонтальна, ось Y вертикальна

class Bitmap
{
public:
    // Формат исходного изображения, нужен при декодировании
    QImage::Format imageFormat;
public:
    // Все точки лежат в одномерном массиве.
    std::vector<Pixel> pixels;
    size_t width;
    size_t height;

    Bitmap();
    // загрузка изображения по имени файла.
    Bitmap(QString filename);
    // конструктор копирования
    Bitmap(Bitmap const & other);
    Bitmap(size_t width, size_t height, std::vector<Pixel> pixels, QImage::Format format);

    // Декодирование к формуту, используемому QT для показа изображений на экране.
    const QPixmap toPixmap();

    // Т.к точки лежат в однгомерном массиве, нужны функции для доступа к точкам по координатам.
    Pixel getPixel(int x, int y);
    void setPixel(int x, int y, Pixel pixel);
};


#endif // BITMAP_H
