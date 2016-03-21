#include <QCoreApplication>
#include "bitmap.h"
#include <iostream>
#include "QDirIterator"
#include <string>
#include <vector>
#include <cmath>
QString name[3] = {QString(".png"), QString(".jpg"), QString(".jpeg")};
const int sizename = 3;
std::vector<Pixel> pix;
std::vector<QString> nameFiles;
std::vector<QString> newImageNames;
std::vector<Pixel> newImage;
int main(int argc, char *argv[])
{
//    Bitmap bitmap = Bitmap(QString(argv[0]));
    std::cout << std::endl;
    for(int i = 1; i < argc; i++) {
        std::cout << i << " " << argv[i] << std::endl;
  }
    QDirIterator it(argv[2]);

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
           //std::cout << red << " " << green << " " << blue << " " << std::endl;
        }
    }
    int w = 0;
    int h = 0;
    int n = 0;
    int m = 0;
    std::cout << "будь зайкой, напиши дважды колличество пикселей";
    std::cin >> w >> h;
    Bitmap bitmap = Bitmap(QString(argv[0]));
    m = (int) (bitmap.width/w);
    n = (int) (bitmap.height/h);

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

    Bitmap outputImage = Bitmap(m*w, n*h, newImage, bitmap.imageFormat);
    for(int i = 0; i < (int)newImageNames.size(); i++) {
        QImage(newImageNames[i]).scaled(w,h);
        Bitmap part = Bitmap(newImageNames[i]);
        for(int k = 0; k < h; k++) {
            for(int j = 0; j < w; j++) {
                outputImage.setPixel(k + (i % m)*w, j + (((int) i / n) * h),part.getPixel(k,j));
            }
        }
    }
}
///Users/annafrolova/Desktop/images/
