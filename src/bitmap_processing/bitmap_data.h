#pragma once
#include <vector>
#include <string>
#include "../shared/Color.h"

class BitmapData {
    BitmapData();
    void ReaduInt16_t(uint16_t& value, unsigned char* p);
    void ReaduInt32_t(uint32_t& value, unsigned char* p);
    void ReadInt32_t(int32_t& value, unsigned char* p);
    void WriteuInt16_t(unsigned char* p, uint16_t& value);
    void WriteuInt32_t(unsigned char* p, uint32_t& value);
    void WriteInt32_t(unsigned char* p, int32_t& value);

public:
    class BitmapHeader {
    public:
        uint16_t id_field;
        uint32_t size;
        uint16_t specific_1;
        uint16_t specific_2;
        uint32_t offset;
    };
    class DIBHeader {
    public:
        uint32_t header_size;
        int32_t width;
        int32_t height;
        uint16_t planes_number;
        uint16_t bits_per_pixel;
        uint32_t compression;
        uint32_t bitmap_data_size;
        uint32_t print_resolution_h;
        uint32_t print_resolution_v;
        uint32_t palette_colors_count;
        uint32_t important_colors_count;
    };

    BitmapHeader bitmap_header;
    DIBHeader dib_header;
    std::vector<Color> pixel_data;
    int32_t padding;

    BitmapData(const std::string& filepath);
    void Export(const std::string& filepath);
};