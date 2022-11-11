#include "filter_controller.h"
#include "../filter/crop/crop_filter.h"
#include "../filter/grayscale/grayscale_filter.h"
#include "../filter/negative/negative_filter.h"
#include "../filter/sharpening/sharpening_filter.h"
#include "../filter/edge_detection/edge_detection_filter.h"
#include "../filter/gaussian_blur/gaussian_blur_filter.h"
#include "../filter/twirl/twirl_filter.h"

FilterController::FilterController(const std::vector<std::pair<std::string, std::vector<std::string>>>& args) {
    for (const auto& [filter_name, filter_params] : args) {
        if (filter_name == "-crop") {
            filters_.emplace_back(
                std::make_unique<CropFilter>(CropFilter(std::stoi(filter_params[0]), std::stoi(filter_params[1]))));
        } else if (filter_name == "-gs") {
            filters_.emplace_back(std::make_unique<GrayscaleFilter>(GrayscaleFilter()));
        } else if (filter_name == "-neg") {
            filters_.emplace_back(std::make_unique<NegativeFilter>(NegativeFilter()));
        } else if (filter_name == "-sharp") {
            filters_.emplace_back(std::make_unique<SharpeningFilter>(SharpeningFilter()));
        } else if (filter_name == "-edge") {
            filters_.emplace_back(
                std::make_unique<EdgeDetectionFilter>(EdgeDetectionFilter(std::stod(filter_params[0]))));
        } else if (filter_name == "-blur") {
            filters_.emplace_back(
                std::make_unique<GaussianBlurFilter>(GaussianBlurFilter(std::stod(filter_params[0]))));
        } else if (filter_name == "-twirl") {
            filters_.emplace_back(std::make_unique<TwirlFilter>(TwirlFilter(std::stod(filter_params[0]))));
        }
    }
}

void FilterController::ApplyFilters(Image& image) {
    for (const auto& filter : filters_) {
        filter->ProcessImage(image);
    }
}