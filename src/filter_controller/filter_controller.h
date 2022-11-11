#pragma once
#include <memory>
#include "../filter/filter.h"
#include "../image/Image.h"

class FilterController {
    std::vector<std::unique_ptr<Filter>> filters_;
    FilterController();

public:
    FilterController(const std::vector<std::pair<std::string, std::vector<std::string>>>& args);
    void ApplyFilters(Image& image);
};