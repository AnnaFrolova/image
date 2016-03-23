#include <QCoreApplication>
#include "bitmap.h"
#include <iostream>
#include "QDirIterator"
#include <string>
#include <vector>
#include <cmath>
#include <qpixmap.h>
QString name[3] = {QString(".png"), QString(".jpg"), QString(".jpeg")};
const int sizename = 3;
std::vector<Pixel> pix;
std::vector<QString> nameFiles;
std::vector<QString> newImageNames;
std::vector<Pixel> newImage;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::cout << std::endl;


    QString filename = QString("/Users/annafrolova/Desktop/pic.jpeg");
    QString pathToImages = QString("/Users/annafrolova/Desktop/images/");
    QString pathToOutput = QString("/Users/annafrolova/Desktop/output.jpeg");

    QDirIterator it(pathToImages);
    //считаем среднее значение для каждой картинки
    while(it.hasNext()) {
       QString lastname = it.next();

       bool correctFile = false;

       for(int k = 0; k < sizename; k++) {
           if(lastname.endsWith(name[k])) {
               correctFile = true;
           }
       }

       if (correctFile) {
           std::cout << lastname.toStdString() << std::endl;

           Bitmap bitmap = Bitmap(lastname);
           long long red = 0;
           long long green = 0;
           long long blue = 0;


           for(int j = 0; j < (int) bitmap.pixels.size(); j++) {
               Pixel current = bitmap.pixels[j];
               red += current.red;
               green += current.green;
               blue += current.blue;
           }

           red /= bitmap.pixels.size();
           green /= bitmap.pixels.size();
           blue /= bitmap.pixels.size();
           pix.push_back(Pixel(red, green, blue));
           nameFiles.push_back(lastname);
        }
    }
    int w = 0; //длина маленьких картинок в коллаже в pix
    int h = 0; //ширина маленьких картинок в коллаже в pix
    int n = 0; //количество маленьких картинок в коллаже по длине
    int m = 0; //количество маленьких картинок в коллаже по ширине
    std::cout << filename.toStdString() << std::endl;
    std::cout << "будь зайкой, напиши дважды количество пикселей" << std::endl;
    std::cin >> w >> h;
    Bitmap bitmap = Bitmap(filename);
    m = (int) (bitmap.width/w);
    n = (int) (bitmap.height/h);

    //подбираем изображения для коллажа
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            long long red = 0;
            long long green = 0;
            long long blue = 0;
            for(int ii = 0; ii < h; ii++) {
                for(int jj = 0; jj < w; jj++) {
                    Pixel current = bitmap.getPixel(j*w + jj, i*h + ii);
                    red += current.red;
                    green += current.green;
                    blue += current.blue;
                }
            }
            red /= w*h;
            green /= w*h;
            blue /= w*h;
            int minim = 1000000;
            QString ourname;
            for(int x = 0; x < (int) pix.size(); x++) {
                int sum = 0;
                sum = abs((int) red - (int) pix[x].red) + abs((int) blue - (int) pix[x].blue) + abs((int) green - (int) pix[x].green);
                if (minim > sum) {
                    ourname = nameFiles[x];
                    minim = sum;
                }
            }
            newImageNames.push_back(ourname);
        }
    }
    //создаем коллаж
    Bitmap outputImage = Bitmap(m*w, n*h, newImage, bitmap.imageFormat);
    for(int i = 0; i < (int)newImageNames.size(); i++) {
        //QImage(newImageNames[i]).scaled(w,h);
        Bitmap part = Bitmap(newImageNames[i]);
        for(int k = 0; k < h; k++) {
            for(int j = 0; j < w; j++) {
                long long red = 0;
                long long green = 0;
                long long blue = 0;
                int wi = part.width/m;
                int he = part.height/n;

                for(int a = 0; a < he; a++) {
                    for(int b = 0; b < wi; b++) {
                        Pixel current = part.getPixel(j*wi + b, k*he + a);
                        red += current.red;
                        green += current.green;
                        blue += current.blue;
                    }
                }
                red /= wi*he;
                green /= wi*he;
                blue /= wi*he;
                Pixel smallPix = Pixel(red,green,blue);
                int xmap = j + (int) (i % m) * w;
                int ymap = k + (int) (i / n) * h;
                outputImage.setPixel(xmap, ymap, smallPix);
            }
        }
    }
    QPixmap pixmap;
    pixmap = outputImage.toPixmap();
    QFile file(pathToOutput);
    file.open(QIODevice::WriteOnly);
    pixmap.save(&file, "JPG");

}
///Users/annafrolova/Desktop/images/
