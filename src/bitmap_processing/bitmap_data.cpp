#include "bitmap_data.h"
#include <fstream>

BitmapData::BitmapData(const std::string& filepath) {
    std::ifstream f;
    f.open(filepath, std::ios::in | std::ios::binary);
    if (!f) {
        throw std::ios_base::failure("Unable to open the file");
    }

    unsigned char header_bytes[14];
    f.read(reinterpret_cast<char*>(header_bytes), 14);

    ReaduInt16_t(bitmap_header.id_field, header_bytes);

    if (bitmap_header.id_field != 19778) {
        throw std::invalid_argument("Input file is not a BMP file");
    }

    ReaduInt32_t(bitmap_header.size, header_bytes + 2);
    ReaduInt16_t(bitmap_header.specific_1, header_bytes + 6);
    ReaduInt16_t(bitmap_header.specific_2, header_bytes + 8);
    ReaduInt32_t(bitmap_header.offset, header_bytes + 10);

    unsigned char dib_header_bytes[40];
    f.read(reinterpret_cast<char*>(dib_header_bytes), 40);

    ReaduInt32_t(dib_header.header_size, dib_header_bytes);
    ReadInt32_t(dib_header.width, dib_header_bytes + 4);
    ReadInt32_t(dib_header.height, dib_header_bytes + 8);
    ReaduInt16_t(dib_header.planes_number, dib_header_bytes + 12);
    ReaduInt16_t(dib_header.bits_per_pixel, dib_header_bytes + 14);
    ReaduInt32_t(dib_header.compression, dib_header_bytes + 16);
    ReaduInt32_t(dib_header.bitmap_data_size, dib_header_bytes + 20);
    ReaduInt32_t(dib_header.print_resolution_h, dib_header_bytes + 24);
    ReaduInt32_t(dib_header.print_resolution_v, dib_header_bytes + 28);
    ReaduInt32_t(dib_header.palette_colors_count, dib_header_bytes + 32);
    ReaduInt32_t(dib_header.important_colors_count, dib_header_bytes + 36);

    f.seekg(bitmap_header.offset, f.beg);
    padding = (4 - ((dib_header.width * 3) % 4)) % 4;
    for (int32_t i = 0; i < dib_header.height; ++i) {
        for (int32_t j = 0; j < dib_header.width; ++j) {
            unsigned char pixel[3];
            f.read(reinterpret_cast<char*>(pixel), 3);
            double red = static_cast<double>(pixel[2]) / 255.0;
            double green = static_cast<double>(pixel[1]) / 255.0;
            double blue = static_cast<double>(pixel[0]) / 255.0;
            pixel_data.push_back(Color(red, green, blue));
        }
        f.ignore(padding);
    }

    f.close();
}

void BitmapData::Export(const std::string& filepath) {
    std::ofstream f;
    f.open(filepath, std::ios::out | std::ios::binary);

    if (!f) {
        throw std::ios_base::failure("Unable to save the file");
    }

    unsigned char header_bytes[14];

    WriteuInt16_t(header_bytes, bitmap_header.id_field);
    WriteuInt32_t(header_bytes + 2, bitmap_header.size);
    WriteuInt16_t(header_bytes + 6, bitmap_header.specific_1);
    WriteuInt16_t(header_bytes + 8, bitmap_header.specific_2);
    WriteuInt32_t(header_bytes + 10, bitmap_header.offset);

    unsigned char dib_header_bytes[40];

    WriteuInt32_t(dib_header_bytes, dib_header.header_size);
    WriteInt32_t(dib_header_bytes + 4, dib_header.width);
    WriteInt32_t(dib_header_bytes + 8, dib_header.height);
    WriteuInt16_t(dib_header_bytes + 12, dib_header.planes_number);
    WriteuInt16_t(dib_header_bytes + 14, dib_header.bits_per_pixel);
    WriteuInt32_t(dib_header_bytes + 16, dib_header.compression);
    WriteuInt32_t(dib_header_bytes + 20, dib_header.bitmap_data_size);
    WriteuInt32_t(dib_header_bytes + 24, dib_header.print_resolution_h);
    WriteuInt32_t(dib_header_bytes + 28, dib_header.print_resolution_v);
    WriteuInt32_t(dib_header_bytes + 32, dib_header.palette_colors_count);
    WriteuInt32_t(dib_header_bytes + 36, dib_header.important_colors_count);

    f.write(reinterpret_cast<char*>(header_bytes), 14);
    f.write(reinterpret_cast<char*>(dib_header_bytes), 40);

    padding = (4 - ((dib_header.width * 3) % 4)) % 4;
    std::vector<uint8_t> padding_vector(padding);
    for (int32_t i = 0; i < dib_header.height; ++i) {
        for (int32_t j = 0; j < dib_header.width; ++j) {
            Color c = pixel_data[dib_header.width * i + j];
            unsigned char pixel[] = {static_cast<unsigned char>(c.b * 255.0), static_cast<unsigned char>(c.g * 255.0),
                                     static_cast<unsigned char>(c.r * 255.0)};
            f.write(reinterpret_cast<char*>(pixel), 3);
        }
        f.write(reinterpret_cast<char*>(padding_vector.data()), padding_vector.size());
    }
    f.close();
}

void BitmapData::ReaduInt16_t(uint16_t& value, unsigned char* p) {
    value = *p + (*(p + 1) << 8);
}

void BitmapData::ReaduInt32_t(uint32_t& value, unsigned char* p) {
    value = *p + (*(p + 1) << 8) + (*(p + 2) << 16) + (*(p + 3) << 24);
}

void BitmapData::ReadInt32_t(int32_t& value, unsigned char* p) {
    value = *p + (*(p + 1) << 8) + (*(p + 2) << 16) + (*(p + 3) << 24);
}

void BitmapData::WriteuInt16_t(unsigned char* p, uint16_t& value) {
    *p = value;
    *(p + 1) = (value >> 8);
}

void BitmapData::WriteuInt32_t(unsigned char* p, uint32_t& value) {
    *p = value;
    *(p + 1) = (value >> 8);
    *(p + 2) = (value >> 16);
    *(p + 3) = (value >> 24);
}

void BitmapData::WriteInt32_t(unsigned char* p, int32_t& value) {
    *p = value;
    *(p + 1) = (value >> 8);
    *(p + 2) = (value >> 16);
    *(p + 3) = (value >> 24);
}