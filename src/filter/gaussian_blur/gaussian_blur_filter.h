#pragma once
#include <vector>
#include "../filter.h"
#include "../../image/Image.h"

class GaussianBlurFilter : public Filter {
    double sigma_;
    std::vector<double> g_values_;
    double GaussianFunction(size_t x);

public:
    GaussianBlurFilter();
    GaussianBlurFilter(double sigma);
    void ProcessImage(Image& image) const override;
};