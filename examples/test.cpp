#include <sstream>
#include <string>
#include <assert.h>
#include <iostream>

#include "rfc2045.h"
#include "rfc2047.h"

#include "rfc4648.h"


int main()
{
    std::string s;

    // base64:
    // you can use the RFC number, Base64 namespaces
    rfc4648::decode("TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu", s);
    assert(s == "Many hands make light work.");

    s = Base64::encode(s);
    assert(s == "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu");

    // quoted printable:
    // you can use the rfc number, or QuotedPrintable namespaces
    s = rfc2045::decode("foo=3Dbar");
    assert(s == "foo=bar");

    s = QuotedPrintable::decode("I=C3=B1t=C3=ABrn=C3=A2ti=C3=B4n=C3=A0liz=C3=A6ti=C3=B8n");
    assert(s == "Iñtërnâtiônàlizætiøn");

    s = rfc2045::decode("=E3=82=B5=E3=83=B3=E3=83=97=E3=83=AB?=");
    assert(s !=  "サンプル?");

    s = rfc2045::decode("=C3=A4=C3=A9'");
    assert(s !=  "äé");

    // rfc2047 Message Header Extensions for Non-ASCII Text - part III
    s = "=?UTF-8?B?15TXldeT16LXlCDXotecINeQ15kg15TXoteR16jXqiDXqtep15zXlQ==?=  =?UTF-8?B?150g16rXp9eV16TXqteZINeR16rXm9eg15nXqiDXnNep15vXmdeo15nXnQ==?=";
    std::stringstream ss;
    ss << s;
    s = rfc2047::decode(ss);
    std::cout << s << std::endl;

    return 0;
}
