#ifndef HELPERFUNCTIONS_HPP
#define HELPERFUNCTIONS_HPP

#include <string>
#include <type_traits>

namespace redd {

namespace detail {

template<typename T>
struct IsStrOrPtr_IMPL : std::false_type {};
template<>
struct IsStrOrPtr_IMPL<std::string> : std::true_type {};
template<>
struct IsStrOrPtr_IMPL<const char*> : std::true_type {};
template<>
struct IsStrOrPtr_IMPL<char*> : std::true_type {};

template<typename T>
constexpr bool IsStrOrPtr = IsStrOrPtr_IMPL<
                                typename std::remove_reference<
                                    typename std::decay<T>::type
                                >::type
                            >::value;

/*
 * Function will assign the value to output only if
 *  the object_key is not null and it does exists
*/
template<typename O, typename J, typename K, typename D>
constexpr auto setIfNotNull(O&& output, const J& json_obj, K&& key_name, D&& default_value)
-> decltype(json_obj.value(key_name, default_value), json_obj.find(key_name), void()) {
    auto n = json_obj.find(key_name);
    if (n != json_obj.end()) {
        if (!n->is_null()) {
            output = json_obj.value(std::forward<K>(key_name), std::forward<D>(default_value));
        }
        else {
            output = default_value;
        }
    }
    else {
        output = default_value;
    }
}
/*
template<typename T>
constexpr auto isNotNull(const T& obj) noexcept(noexcept(std::declval<T>().is_null()))
-> decltype(std::declval<T>().is_null(), bool()) {
    return obj.is_null();
}
*/

} //! detail namespace

} //! redd namespace




#endif // HELPERFUNCTIONS_HPP
