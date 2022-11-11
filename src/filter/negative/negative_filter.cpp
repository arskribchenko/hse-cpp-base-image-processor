#include "./negative_filter.h"

void NegativeFilter::ProcessImage(Image& image) const {
    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            Color c = image[i * width + j];
            Color new_c = Color(1 - c.r, 1 - c.g, 1 - c.b);
            image[i * width + j] = new_c;
        }
    }
}