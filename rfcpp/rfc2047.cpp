#include "rfc2045.h"
#include "rfc2047.h"
#include "rfc4648.h"

#include <sstream>

/* A function to decode rfc 2047 encoded strings
 * See https://datatracker.ietf.org/doc/html/rfc2047
 */

/*
 *     auto c = in.peek();
    if (c != '=') {
        // this is not encoded, but a normal ASCII string
#if 0
        std::ostringstream sstr;
        sstr << in.rdbuf();
        return sstr.str();
#else
        std::string str(std::istreambuf_iterator<char>{in}, {});
        return str;
#endif
    }

 */


namespace  {

enum class ParseState{
    begin,
    charset_prefix1,
    charset_prefix2,
    charset,
    encoding_prefix,
    encoding,
    text_prefix,
    reading_text,
    suffix_1,
    suffix_2,
    end,
};

// https://datatracker.ietf.org/doc/html/rfc2047#section-2
//    encoded-word = "=?" charset "?" encoding "?" encoded-text "?="
static auto decode_impl(std::istream &in) -> std::string {
    auto decoded_string = std::string();
    auto state = ParseState::begin;

    // consume original string
    auto charset = std::string();
    auto encoding = std::string();
    auto text = std::string();

    char c = in.get();
    while (c != EOF) {
        switch (state) {
        case ParseState::begin:
            if (c != '=') {
                // this is not encoded, but a normal ASCII string
                // std::string str(std::istreambuf_iterator<char>{in}, {});
                return {};
            }
            state = ParseState::charset_prefix1;
            break;
        case ParseState::charset_prefix1:
            // this is an invalid state, just bail out.
            if (c != '?') {
                return {};
            }
            state = ParseState::charset_prefix2;
            break;
        case ParseState::charset_prefix2:
            // char set cannot be empty, at least a single char is needed. this will be
            // a broken charset... but... OK..
            if (c == '?') {
                return {};
            }
            charset += c;
            state = ParseState::charset;
            break;
        case ParseState::charset:
            if (c == '?') {
                state = ParseState::encoding_prefix;
                break;
            }
            charset += c;
            break;
        case ParseState::encoding_prefix:
            // encoding cannot be empty
            if (c == '?') {
                return {};
            }
            encoding += c;
            state = ParseState::encoding;
            break;
        case ParseState::encoding:
            if (c == '?') {
                state = ParseState::text_prefix;
                break;
            }
            encoding += c;
            break;
        case ParseState::text_prefix:
            // empty text? this this valid?
            if (c == '?') {
                return {};
            }
            state = ParseState::reading_text;
            text += c;
            break;
        case ParseState::reading_text:
            // empty text? this this valid?
            if (c == '?') {
                state = ParseState::suffix_1;
                continue;
            }
            text += c;
            break;
        case ParseState::suffix_1:
            if (c != '?') {
                return {};
            }
            state = ParseState::suffix_2;
            break;
        case ParseState::suffix_2:
            if (c != '=') {
                return {};
            }
            state = ParseState::end;
            break;
        case ParseState::end:
            // Nothing is supported after this step
//            return {};
            break;
        }

        if (state == ParseState::end) {
            break;
        }
        c = in.get();
    }

    if (encoding == "B") {
        rfc4648::decode(text, decoded_string);
    } else if (encoding == "Q") {
        decoded_string = rfc2045::decode(text);
    }


    // TODO - convert from charset to utf8
    // This magically works now for utf8 and ascii
    return decoded_string;
}


}

auto rfc2047::decode(std::istream &in) -> std::string {
    auto out = std::string();
    while (in.peek() != EOF) {
        auto s = decode_impl(in);
        out += s;
    }
    return out;
}

auto rfc2047::decode(const std::string &in) -> std::string {
    std::stringstream ss;
    ss << in;
    auto s = rfc2047::decode(ss);
    return s .empty() ? in : s;
}

auto rfc2047::decode(const std::string_view in) -> std::string {
    std::stringstream ss;
    ss << in;
    auto s = rfc2047::decode(ss);
    return s .empty() ? std::string(in) : s;
}
