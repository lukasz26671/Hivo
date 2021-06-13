#pragma once
#include <iostream>
#include <type_traits>
#pragma warning(disable:26812)

#define TokenTypeCast(val) static_cast<TokenType>(val);
#define AstTypeCast(val) static_cast<AstType>(val);

template <typename Enumeration>
constexpr std::enable_if_t<std::is_enum<Enumeration>::value,
    std::underlying_type_t<Enumeration>> as_number(const Enumeration value)
{
    return static_cast<std::underlying_type_t<Enumeration>>(value);
}
