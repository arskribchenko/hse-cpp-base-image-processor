#include "./sharpening_filter.h"
#include <algorithm>

SharpeningFilter::SharpeningFilter() : MatrixFilter({{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}}) {
}

void SharpeningFilter::ProcessImage(Image& image) const {
    std::vector<Color> new_data;
    int32_t height = image.GetHeight();
    int32_t width = image.GetWidth();
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            new_data.push_back(ApplyMatrix(image, j, i));
        }
    }
    image.SetPixelData(new_data);
}