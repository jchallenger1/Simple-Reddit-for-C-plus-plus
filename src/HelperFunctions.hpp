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
    constexpr bool IsStrOrPtr = IsStrOrPtr_IMPL<
                                    typename std::remove_reference<
                                        typename std::decay<T>::type
                                    >::type
                                >::value;

    template<typename T, typename G, typename ...Args>
    constexpr auto setIfNotNull(T&& object_member, const G& object_key, Args&&... args)
    noexcept(noexcept(std::declval<G>().is_null())) ->
    decltype(std::declval<G>().is_null(), std::declval<G>().value(0,0), void()) {
        static_assert(sizeof...(args) >= 2, "Member function \"value\" must have atleast 2 arguments");
        if (!object_key.is_null()) {
            object_member = object_key.value(std::forward<Args>(args)...);
        }
    }
    /*
    template<typename T>
    constexpr auto isNotNull(const T& obj) noexcept(noexcept(std::declval<T>().is_null()))
    -> decltype(std::declval<T>().is_null(), bool()) {
        return obj.is_null();
    }
    */
}




#endif // HELPERFUNCTIONS_HPP
