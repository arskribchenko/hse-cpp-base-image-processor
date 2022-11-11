#include "matrix_filter.h"
#include <algorithm>

MatrixFilter::MatrixFilter(const std::vector<std::vector<int>>& matrix) : matrix_(matrix) {
}

Color MatrixFilter::ApplyMatrix(Image& image, int32_t x, int32_t y) const {
    int32_t offset = matrix_.size() / 2;
    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();
    double r = 0;
    double g = 0;
    double b = 0;
    for (int32_t k = 0; k < matrix_.size(); ++k) {
        for (int32_t l = 0; l < matrix_[k].size(); ++l) {
            int32_t ix = std::clamp(x - offset + l, 0, width - 1);
            int32_t iy = std::clamp(y - offset + k, 0, height - 1);
            r += image[iy * width + ix].r * matrix_[k][l];
            g += image[iy * width + ix].g * matrix_[k][l];
            b += image[iy * width + ix].b * matrix_[k][l];
        }
    }
    r = std::min(1.0, std::max(0.0, r));
    g = std::min(1.0, std::max(0.0, g));
    b = std::min(1.0, std::max(0.0, b));
    return Color(r, g, b);
}