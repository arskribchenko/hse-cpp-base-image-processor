#pragma once
#include <vector>
#include <unordered_map>
#include <string>

class ArgumentParser {
    std::unordered_map<std::string, int> allowed_args_;

public:
    using ArgData = typename std::vector<std::pair<std::string, std::vector<std::string>>>;
    ArgumentParser(const std::unordered_map<std::string, int32_t>& allowed_args);
    ArgData ParseArguments(int argc, char* argv[]);
};