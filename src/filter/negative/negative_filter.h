#pragma once
#include "../filter.h"
#include "../../image/Image.h"

class NegativeFilter : public Filter {
public:
    void ProcessImage(Image& image) const override;
};