#pragma once
#include "../matrix_filter.h"
#include "../../image/Image.h"

class EdgeDetectionFilter : public MatrixFilter {
    double threshold_;

public:
    EdgeDetectionFilter();
    EdgeDetectionFilter(double threshold);
    void ProcessImage(Image& image) const override;
};