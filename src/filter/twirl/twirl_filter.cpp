#include "./twirl_filter.h"
#include <cmath>

TwirlFilter::TwirlFilter(double angle) : angle_(angle) {
}

void TwirlFilter::ProcessImage(Image& image) const {
    const int32_t height = image.GetHeight();
    const int32_t width = image.GetWidth();
    const int32_t center_x = width / 2;
    const int32_t center_y = height / 2;
    std::vector<Color> new_pixel_data;
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            int distance_x = j - center_x;
            int distance_y = i - center_y;
            double radian_angle = angle_ * (M_PI / 180);

            double distance = sqrt(distance_x * distance_x + distance_y * distance_y);
            double calculated_angle =
                atan2(distance_y, distance_x) + radian_angle * ((center_y - distance) / (center_y));

            int rotation_y = (center_y) + distance * sin(calculated_angle);
            int rotation_x = (center_x) + distance * cos(calculated_angle);

            int32_t new_y = std::clamp(rotation_y, 0, height - 1);
            int32_t new_x = std::clamp(rotation_x, 0, width - 1);

            new_pixel_data.push_back(image[new_y * width + new_x]);
        }
    }
    image.SetPixelData(new_pixel_data);
}