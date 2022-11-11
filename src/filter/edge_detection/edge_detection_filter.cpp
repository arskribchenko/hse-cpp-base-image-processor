#include "./edge_detection_filter.h"

EdgeDetectionFilter::EdgeDetectionFilter() : MatrixFilter({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}) {
    threshold_ = 0;
}

EdgeDetectionFilter::EdgeDetectionFilter(double threshold) : MatrixFilter({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}) {
    threshold_ = threshold;
}

void EdgeDetectionFilter::ProcessImage(Image& image) const {
    int32_t height = image.GetHeight();
    int32_t width = image.GetWidth();

    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            Color c = image[i * width + j];
            double gray_value = 0.299 * c.r + 0.587 * c.g + 0.114 * c.b;
            Color new_c = Color(gray_value, gray_value, gray_value);
            image[i * width + j] = new_c;
        }
    }

    std::vector<Color> new_data;
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            Color c = ApplyMatrix(image, j, i);

            if (c.r > threshold_) {
                c.r = 1;
                c.g = 1;
                c.b = 1;
            } else {
                c.r = 0;
                c.g = 0;
                c.b = 0;
            }

            new_data.push_back(c);
        }
    }
    image.SetPixelData(new_data);
}