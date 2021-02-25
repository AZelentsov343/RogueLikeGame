#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION

#include "outer_includes/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "outer_includes/stb_image_write.h"

#include <iostream>


Image::Image(const std::string &a_path) {
    if ((data = (Pixel *) stbi_load(a_path.c_str(), &width, &height, &channels, sizeof(Pixel))) != nullptr) {
        size = width * height * channels;
        shown_data = data;
    }
}

Image::Image(int a_width, int a_height, int a_channels) {
    data = new Pixel[a_width * a_height]{};
    width = a_width;
    height = a_height;
    size = a_width * a_height * a_channels;
    channels = a_channels;
    self_allocated = true;
    shown_data = data;

    makeDefault();
}

void Image::makeDefault() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            data[i * height + j] = Pixel{static_cast<uint8_t>(i + j), static_cast<uint8_t>(i - j),
                                           static_cast<uint8_t>(i * j), 255};
        }
    }
}

void Image::cutOut(int x_start, int y_start, int x_fin, int y_fin) {
    int sizeOfCut = index(x_fin, y_fin) - index(x_start, y_start);
    if (sizeOfCut < 0) {
        throw std::runtime_error("sizeOfCut < 0");
    }
    auto* new_data = new Pixel[size]{};
    for (int x = x_start; x < x_fin; x++) {
        for (int y = y_start; y < y_fin; y++) {
            new_data[index(x - x_start, y - y_start)] = data[index(x, y)];
        }
    }

    shown_data = new_data;
}


int Image::Save(const std::string &a_path) {
    auto extPos = a_path.find_last_of('.');
    if (a_path.substr(extPos, std::string::npos) == ".png" || a_path.substr(extPos, std::string::npos) == ".PNG") {
        stbi_write_png(a_path.c_str(), width, height, channels, data, width * channels);
    } else if (a_path.substr(extPos, std::string::npos) == ".jpg" ||
               a_path.substr(extPos, std::string::npos) == ".JPG" ||
               a_path.substr(extPos, std::string::npos) == ".jpeg" ||
               a_path.substr(extPos, std::string::npos) == ".JPEG") {
        stbi_write_jpg(a_path.c_str(), width, height, channels, data, 100);
    } else {
        std::cerr << "Unknown file extension: " << a_path.substr(extPos, std::string::npos) << "in file name" << a_path
                  << "\n";
        return 1;
    }

    return 0;
}

Image::~Image() {
    if (self_allocated)
        delete[] data;
    else {
        stbi_image_free(data);
    }
}