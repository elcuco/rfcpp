# rfcppp - a C++ implementation of rfc protocols in C++

This library wants to be a set of implementation of various RFC protocols
in pure C++.

Code is sometimes ported from C code, and sometimes the intreface available uses
internally other embeded libraries.

Code should be re-usable/consumable as a CMake library (and should be eventually
available in conan).

## Usage:

Example how to embed (inside your CMakeLists.txt):
``` CMake

# using CPM
CPMAddPackage("gh:elcuco/rfcpp#master")

# using git sub-modules
add_subdirectory(rfcpp)

# or using fetch conetent directly
```

Example for API usage:
``` C++
rfc4648::decode("TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu", s);
assert(s == "Many hands make light work.");

Base64::decode("TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu", s);
assert(s == "Many hands make light work.");
```


## License

This project is licensed under the 3 clause BSD. 
