#include "crop_filter.h"

CropFilter::CropFilter() {
    crop_width_ = 0;
    crop_height_ = 0;
}

CropFilter::CropFilter(int32_t w, int32_t h) {
    crop_width_ = w;
    crop_height_ = h;
}

void CropFilter::ProcessImage(Image& image) const {
    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();
    if (crop_width_ < width || crop_height_ < height) {
        std::vector<Color> new_pixel_data;
        for (int32_t i = std::max(height - crop_height_, 0); i < height; ++i) {
            for (int32_t j = 0; j < std::min(crop_width_, width); ++j) {
                new_pixel_data.push_back(image[i * width + j]);
            }
        }
        if (!new_pixel_data.empty()) {
            image.SetPixelData(new_pixel_data);
            image.SetHeight(std::min(crop_height_, height));
            image.SetWidth(std::min(crop_width_, width));
        }
    }
}