#pragma once

#include <string>

// Base64 related functions
namespace rfc4648 {

    // TODO: how about implement this instead? https://github.com/ReneNyffenegger/cpp-base64/blob/master/base64.cpp
    namespace internal {
        #include "base64.h"
    }

    static std::string encode(const std::string& data) {
        return internal::macaron::Base64::Encode(data);
    }

    static int decode(const std::string& input, std::string& out) {
        return internal::macaron::Base64::Decode(input, out);
    }
};

namespace Base64=rfc4648;
