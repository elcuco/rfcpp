#pragma once

#include <string>
#include <istream>

namespace rfc2045 {

auto encode(const std::string &s) ->  std::string;
auto decode(const std::string &s) -> std::string;

}

namespace QuotedPrintable=rfc2045;
