#ifndef HELPERFUNCTIONS_HPP
#define HELPERFUNCTIONS_HPP

#include <string>
#include <type_traits>

namespace redd {
    template<typename T>
    struct IsSupported_IMPL : std::false_type {};
    template<>
    struct IsSupported_IMPL<std::string> : std::true_type {};
    template<>
    struct IsSupported_IMPL<const char*> : std::true_type {};

    template<typename T>
    constexpr bool IsSupported = IsSupported_IMPL<typename std::remove_reference< typename std::decay<T>::type >::type >::value;


}




#endif // HELPERFUNCTIONS_HPP
