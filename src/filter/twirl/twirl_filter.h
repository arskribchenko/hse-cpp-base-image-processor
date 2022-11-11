#pragma once
#include "../filter.h"

class TwirlFilter : public Filter {
    double angle_;

public:
    TwirlFilter(double angle_);
    void ProcessImage(Image& image) const override;
};