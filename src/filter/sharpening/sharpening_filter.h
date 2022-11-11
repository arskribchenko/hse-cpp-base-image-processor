#pragma once
#include "../matrix_filter.h"
#include "../../image/Image.h"

class SharpeningFilter : public MatrixFilter {

public:
    SharpeningFilter();
    void ProcessImage(Image& image) const override;
};