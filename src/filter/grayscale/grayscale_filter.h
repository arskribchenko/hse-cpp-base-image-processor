#pragma once
#include "../filter.h"
#include "../../image/Image.h"

class GrayscaleFilter : public Filter {
public:
    void ProcessImage(Image& image) const override;
};