#ifndef ENUM_CAST_HPP
#define ENUM_CAST_HPP

#include <iostream>

template <typename Enumeration>
auto as_integer(Enumeration const value) -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

#endif
