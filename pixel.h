#ifndef PIXEL_H
#define PIXEL_H

// Точка на изображении.
// Фильтры используют различные операции над точками, поэтому реализованы арифметические операции.

struct Pixel
{
private:
    // в RGB значение каждого из параметров лежит в перделах (0..255).
    // Функция проверяет это.
    static double checkBounds(double value)
    {
        return std::max(0.0, std::min(255.0, value));
    }
public:
    // Проверяем, что точка готова к отрисовке, т.е нет параметров выходящих за пределы.
    void validate()
    {
        this->red = Pixel::checkBounds(this->red);
        this->green = Pixel::checkBounds(this->green);
        this->blue = Pixel::checkBounds(this->blue);
    }

    Pixel(double red, double green, double blue): red(red), green(green), blue(blue) { }
    double red;
    double green;
    double blue;

    Pixel& operator += (Pixel const& other)
    {
        this->red += other.red;
        this->green += other.green;
        this->blue += other.blue;
        return *this;
    }
    Pixel& operator -= (Pixel const& other)
    {
        this->red -= other.red;
        this->green -= other.green;
        this->blue -= other.blue;
        return *this;
    }

    Pixel& operator *= (Pixel const& other)
    {
        this->red *= other.red;
        this->green *= other.green;
        this->blue *= other.blue;
        return *this;
    }
    Pixel& operator /= (Pixel const& other)
    {
        this->red /= other.red;
        this->green /= other.green;
        this->blue /= other.blue;
        return *this;
    }

    Pixel& operator += (double rhs)
    {
        Pixel newPixel = Pixel(rhs, rhs, rhs);
        *this += newPixel;
        return *this;
    }

    Pixel& operator -= (double rhs)
    {
        Pixel newPixel = Pixel(rhs, rhs, rhs);
        *this -= newPixel;
        return *this;
    }
    Pixel& operator *= (double rhs)
    {
        Pixel newPixel = Pixel(rhs, rhs, rhs);
        *this *= newPixel;
        return *this;
    }
    Pixel& operator /= (double rhs)
    {
        Pixel newPixel = Pixel(rhs, rhs, rhs);
        *this /= newPixel;
        return *this;
    }

    friend bool operator == (Pixel const& a, Pixel const& b)
    {
        return a.red == b.red && a.green == b.green && a.blue == b.blue;
    }
    friend bool operator != (Pixel const& a, Pixel const& b)
    {
        return !(a == b);
    }
};

inline Pixel operator + (Pixel a, Pixel const& b)
{
    Pixel pixel = a;
    return pixel += b;
}
inline Pixel operator - (Pixel a, Pixel const& b)
{
    Pixel pixel = a;
    return pixel -= b;
}

inline Pixel operator + (Pixel a, double b)
{
    Pixel pixel = a;
    return pixel += b;
}
inline Pixel operator - (Pixel a, double b)
{
    Pixel pixel = a;
    return pixel -= b;
}
inline Pixel operator * (Pixel a, double b)
{
    Pixel pixel = a;
    return pixel *= b;
}
inline Pixel operator / (Pixel a, double b)
{
    Pixel pixel = a;
    return pixel /= b;
}

bool operator == (Pixel const& a, Pixel const& b);
bool operator != (Pixel const& a, Pixel const& b);

#endif // PIXEL_H
