#pragma once

#include <string>
#include <string_view>
#include <istream>

namespace rfc2047 {

auto decode(std::istream &in) -> std::string;
auto decode(const std::string &in) -> std::string;
auto decode(const std::string_view in) -> std::string;

}

