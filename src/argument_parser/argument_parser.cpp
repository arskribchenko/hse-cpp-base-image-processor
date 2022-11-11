#include <stdexcept>
#include "argument_parser.h"

ArgumentParser::ArgumentParser(const std::unordered_map<std::string, int32_t>& allowed_args)
    : allowed_args_(allowed_args) {
}

ArgumentParser::ArgData ArgumentParser::ParseArguments(int argc, char* argv[]) {
    ArgData args;

    if (argc < 3) {
        throw std::invalid_argument("At least two arguments required - {input path} and {output path}");
    }

    args.push_back(std::make_pair("input", std::vector<std::string>{argv[1]}));
    args.push_back(std::make_pair("output", std::vector<std::string>{argv[2]}));

    std::string current_argument = "";
    int current_args_count = 0;
    std::vector<std::string> current_values;

    std::string last_checked_arg;
    bool number_flag = false;

    for (int i = 3; i < argc; ++i) {
        number_flag = false;
        last_checked_arg = argv[i];
        try {
            double value = std::stod(argv[i]);
            number_flag = true;
            if (value < 0) {
                throw std::invalid_argument(std::to_string(value));
            }
            current_values.push_back(argv[i]);
            current_args_count += 1;

        } catch (const std::invalid_argument& e) {
            if (number_flag) {
                throw std::invalid_argument("Filter parameters must be non-negative");
            }
            if (allowed_args_.find(argv[i]) == allowed_args_.end()) {
                throw std::invalid_argument("Unknown argument: " + last_checked_arg);
                break;
            }
            if (!current_argument.empty()) {
                if (current_args_count != allowed_args_[current_argument]) {
                    throw std::invalid_argument(current_argument + " argument count: expected " +
                                                std::to_string(allowed_args_[current_argument]) + ", got " +
                                                std::to_string(current_args_count));
                    break;
                }
                args.push_back(std::make_pair(current_argument, current_values));
                current_values.clear();
                current_args_count = 0;
            }
            current_argument = argv[i];
        }
    }
    if (!current_argument.empty()) {
        if (current_args_count != allowed_args_[current_argument]) {
            throw std::invalid_argument(current_argument + " argument count: expected " +
                                        std::to_string(allowed_args_[current_argument]) + ", got " +
                                        std::to_string(current_args_count));
        }
        args.push_back(std::make_pair(current_argument, current_values));
    }

    return args;
}