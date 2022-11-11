#pragma once
#include "../bitmap_processing/bitmap_data.h"

class Image {
    Image();
    BitmapData data_;

public:
    Image(const BitmapData& data) : data_(data) {
    }
    int32_t GetWidth();
    int32_t GetHeight();
    void SetWidth(int32_t width);
    void SetHeight(int32_t height);
    void SetPixelData(const std::vector<Color>& new_data);
    void Save(const std::string& filepath);
    Color& operator[](size_t i);
    Color operator[](size_t i) const;
};