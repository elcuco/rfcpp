#include "rfc2045.h"

namespace  {

static bool is_hex(const char c) {
    return std::string("0123456789ABCDEF").find(c) !=  std::string::npos;
}

/* hexval -- return value of a hexadecimal digit (0-9A-F) */
static auto hexval(int c)
{
    if ('0' <= c && c <= '9')
        return c - '0';
    return 10 + c - 'A';
}

static auto decode_char(const char c1, const char c2) -> auto {
    // assert(c1 == '=');
    return 16 * hexval(c1) + hexval(c2);
}


}
/*
 * encode_quoted_printable -- print a string encoded as quoted-printable
 *
 * Ported from: https://www.w3.org/Tools/Mail-Transcode/mail-transcode.c
 */

auto rfc2045::encode(const std::string &s) ->  std::string {
    std::string out;

    for (int n = 0, k=0; k < s.length(); k++) {
        auto c = s[k];
        if (n >= 73 && c != 10 && c != 13) {
            char cc[128];
            snprintf(cc, 128, "=\r\n");
            n = 0;
            out += std::string(cc);
        }

        if (c == 10 || c == 13) {
            out += c;
            n = 0;
        } else if (c<32 || c==61 || c>126) {
            char cc[128];
            n += snprintf(cc, 128, "=%02X", (unsigned char)c);
            out += std::string(cc);
        } else if (c != 32 || (s[k+1]) != 10 && (s[k+1] != 13)) {
            out += c;
            n++;
        }
        else {
            char cc[128];
            n += snprintf(cc, 128, "=20");
            out += std::string(cc);
        }
    }
    return out;
}


/*
 * decode_quoted_printable -- decode and print a quoted-printable string
 *
 *
 * Ported from: https://www.w3.org/Tools/Mail-Transcode/mail-transcode.c
 */
auto rfc2045::decode(const std::string &s) -> std::string
{
    auto l = s.length();
    auto out = std::string();

    for (int i=0; i<l; ) {
        auto c = s[i];
        auto next = s[i+1];
        auto next_next = s[i+2];
        if (c != '=')  {
            out += c;
            i++;
        } else if (next == '\r' && next_next == '\n')  {
            i += 3;
        } else if (next == '\n') {
            i += 2;
        } else if (!is_hex(next)) {
            out += next;
            i++;
        }
        else if (!is_hex(next_next))  {
            out += next;
            i++;
        } else {
            auto cc = decode_char(next, next_next);
            out += cc;
            i += 3;
        }
    }
    return out;
}
