#pragma once
#include <vector>
#include "filter.h"
#include "../image/Image.h"

class MatrixFilter : public Filter {
protected:
    MatrixFilter(const std::vector<std::vector<int>>& matrix);
    std::vector<std::vector<int>> matrix_;
    Color ApplyMatrix(Image& image, int32_t x, int32_t y) const;
};