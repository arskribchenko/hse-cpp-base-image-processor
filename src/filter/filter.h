#pragma once
#include "../image/Image.h"

class Filter {
public:
    virtual void ProcessImage(Image& image) const = 0;
    virtual ~Filter() {
    }
};