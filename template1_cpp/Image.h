#ifndef MAIN_IMAGE_H
#define MAIN_IMAGE_H

#include <string>
#include <stdexcept>
#include "shared.h"

constexpr Pixel backgroundColor{0, 0, 0, 0};

struct Image {
    explicit Image(const std::string &a_path);

    Image(int a_width, int a_height, int a_channels);

    Image(const Image& other);

    int Save(const std::string &a_path);

    int Width() const { return width; }

    int Height() const { return height; }

    int Channels() const { return channels; }

    size_t Size() const { return size; }

    Pixel * Data() const { return shown_data; }

    void cutOut(int x_start, int y_start, int x_fin, int y_fin);

    Pixel GetPixel(int x, int y) { return shown_data[index(x, y)]; }

    void PutPixel(int x, int y, const Pixel &pix) { shown_data[index(x, y)] = pix; }

    int index(int x, int y) const {return height * y + x;}

    void makeDefault();

    ~Image();

private:
    int width = -1;
    int height = -1;
    int channels = 3;
    size_t size = 0;
    size_t shown_size = 0;
    Pixel *data = nullptr;
    Pixel *shown_data = nullptr;
    bool self_allocated = false;
};


#endif //MAIN_IMAGE_H
