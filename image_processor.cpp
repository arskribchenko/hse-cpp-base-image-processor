#include <iostream>
#include "./src/bitmap_processing/bitmap_data.h"
#include "./src/image/Image.h"
#include "./src/argument_parser/argument_parser.h"
#include "./src/filter_controller/filter_controller.h"

void PrintInfo() {
    std::cout << "usage: ./image_processor {input path} {output path} [-{filter name 1} "
                 "[filter param 1] [filter param 2] ...] [-{filter name 2} [filter param 1] [filter "
                 "param 2] ...] ..."
              << std::endl;
    std::cout << "Input file must be a 24-bit BMP file" << std::endl;
    std::cout << "Filters and their parameters:" << std::endl;
    std::cout << "-crop: [width] (integer), [height] (integer) - crops the image to the given width and height "
                 "(from top-left corner)"
              << std::endl;
    std::cout << "-gs: no parameters - grayscale filter" << std::endl;
    std::cout << "-neg: no parameters - negative filter" << std::endl;
    std::cout << "-sharp: no parameters - sharpening filter" << std::endl;
    std::cout << "-edge: [threshold] (double) - edge detection filter (detects boundaries between image areas)"
              << std::endl;
    std::cout << "-blur: [sigma] (double) - gaussian blur filter" << std::endl;
    std::cout << "-twirl: [angle] (double) - twirl filter (creates a twirl of given angle at the center of the image)"
              << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        PrintInfo();
        return 0;
    }

    try {
        std::unordered_map<std::string, int> expected = {{"-crop", 2}, {"-gs", 0},   {"-neg", 0},  {"-sharp", 0},
                                                         {"-edge", 1}, {"-blur", 1}, {"-twirl", 1}};
        ArgumentParser parser(expected);
        auto args = parser.ParseArguments(argc, argv);

        const std::string input = args[0].second[0];
        const std::string output = args[1].second[0];
        
        BitmapData br(input);
        Image image(br);

        FilterController controller(args);
        controller.ApplyFilters(image);

        image.Save(output);
        std::cout << "Image was successfully saved!" << std::endl;
    } catch (std::ios_base::failure const& e) {
        std::cout << e.what() << std::endl;
    } catch (std::invalid_argument const& e) {
        std::cout << e.what() << std::endl;
        PrintInfo();
    }
    return 0;
}
