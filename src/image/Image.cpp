#include "./Image.h"

int32_t Image::GetWidth() {
    return data_.dib_header.width;
}

int32_t Image::GetHeight() {
    return data_.dib_header.height;
}

void Image::SetWidth(int32_t width) {
    data_.dib_header.width = width;

}

void Image::SetHeight(int32_t height) {
    data_.dib_header.height = height;

}

void Image::SetPixelData(const std::vector<Color>& new_data) {
    data_.pixel_data = new_data;
}

void Image::Save(const std::string& filepath) {
    data_.Export(filepath);
}

Color& Image::operator[](size_t i) {
    return data_.pixel_data.at(i);
}

Color Image::operator[](size_t i) const {
    return data_.pixel_data[i];
}
