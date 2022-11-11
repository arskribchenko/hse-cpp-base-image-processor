#include "./grayscale_filter.h"

void GrayscaleFilter::ProcessImage(Image& image) const {
    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            Color c = image[i * width + j];
            double gray_value = 0.299 * c.r + 0.587 * c.g + 0.114 * c.b;
            Color new_c = Color(gray_value, gray_value, gray_value);
            image[i * width + j] = new_c;
        }
    }
}