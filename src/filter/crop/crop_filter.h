#pragma once
#include "../filter.h"
#include "../../image/Image.h"

class CropFilter : public Filter {
    int32_t crop_width_;
    int32_t crop_height_;

public:
    CropFilter();
    CropFilter(int32_t w, int32_t h);
    void ProcessImage(Image& image) const override;
};