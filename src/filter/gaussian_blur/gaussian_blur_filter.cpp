#include "gaussian_blur_filter.h"
#include <cmath>

GaussianBlurFilter::GaussianBlurFilter() {
    sigma_ = 0;
}

GaussianBlurFilter::GaussianBlurFilter(double sigma) {
    sigma_ = sigma;
    size_t length = ceil(sigma_ * 3);
    for (size_t i = 0; i < length; ++i) {
        g_values_.push_back(GaussianFunction(i));
    }
}

double GaussianBlurFilter::GaussianFunction(size_t x) {
    double pow = -((x * x) * 1.0 / (2 * sigma_ * sigma_));
    return exp(pow) / sqrt(2 * M_PI * sigma_ * sigma_);
}

void GaussianBlurFilter::ProcessImage(Image& image) const {
    std::vector<Color> new_data;
    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();

    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            new_data.push_back(Color(0, 0, 0));
            double sum = 0;
            for (int32_t k = 0; k < g_values_.size(); ++k) {
                if (j - k >= 0) {
                    new_data.back().r += g_values_[k] * image[i * width + j - k].r;
                    new_data.back().g += g_values_[k] * image[i * width + j - k].g;
                    new_data.back().b += g_values_[k] * image[i * width + j - k].b;
                    sum += g_values_[k];
                }
                if (k > 0 && j + k <= width - 1) {
                    new_data.back().r += g_values_[k] * image[i * width + j + k].r;
                    new_data.back().g += g_values_[k] * image[i * width + j + k].g;
                    new_data.back().b += g_values_[k] * image[i * width + j + k].b;
                    sum += g_values_[k];
                }
            }
            new_data.back().r /= sum;
            new_data.back().g /= sum;
            new_data.back().b /= sum;
        }
    }

    image.SetPixelData(new_data);

    for (int32_t i = 0; i < width; ++i) {
        for (int32_t j = 0; j < height; ++j) {
            double sum = 0;
            new_data[j * width + i].r = 0;
            new_data[j * width + i].g = 0;
            new_data[j * width + i].b = 0;
            for (int32_t k = 0; k < g_values_.size(); ++k) {
                if (j - k >= 0) {
                    new_data[j * width + i].r += g_values_[k] * image[(j - k) * width + i].r;
                    new_data[j * width + i].g += g_values_[k] * image[(j - k) * width + i].g;
                    new_data[j * width + i].b += g_values_[k] * image[(j - k) * width + i].b;
                    sum += g_values_[k];
                }
                if (k > 0 && j + k <= height - 1) {
                    new_data[j * width + i].r += g_values_[k] * image[(j + k) * width + i].r;
                    new_data[j * width + i].g += g_values_[k] * image[(j + k) * width + i].g;
                    new_data[j * width + i].b += g_values_[k] * image[(j + k) * width + i].b;
                    sum += g_values_[k];
                }
            }
            new_data[j * width + i].r /= sum;
            new_data[j * width + i].g /= sum;
            new_data[j * width + i].b /= sum;
        }
    }

    image.SetPixelData(new_data);
}
