#ifndef HELPERFUNCTIONS_HPP
#define HELPERFUNCTIONS_HPP

#include <string>
#include <type_traits>

namespace redd {
    template<typename T>
    struct IsStrOrPtr_IMPL : std::false_type {};
    template<>
    struct IsStrOrPtr_IMPL<std::string> : std::true_type {};
    template<>
    struct IsStrOrPtr_IMPL<const char*> : std::true_type {};

    template<typename T>
    constexpr bool IsStrOrPtr = IsStrOrPtr_IMPL<typename std::remove_reference< typename std::decay<T>::type >::type >::value;

}




#endif // HELPERFUNCTIONS_HPP
