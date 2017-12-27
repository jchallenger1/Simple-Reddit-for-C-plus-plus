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
struct IsStrOrPtr_IMPL<const char* const> : std::true_type {};
template<>
struct IsStrOrPtr_IMPL<char*> : std::true_type {};

// Returns a bool if T is of type std::string, const char* or char*.
template<typename T>
constexpr bool IsStrOrPtr = IsStrOrPtr_IMPL<
                                    typename std::decay<T>::type
                            >::value;

// Returns a bool if T is of type std::string.
template<typename T>
constexpr bool IsStr = std::is_same<
                            typename std::remove_const<
                                typename std::decay<T>::type
                            >::type,
                        std::string>::value;

template<typename ...Conds>
struct all_ : std::true_type { };

template<typename Cond, typename ...Conds>
struct all_<Cond, Conds...> :
std::conditional<Cond::value, all_<Conds...>, std::false_type>::type { };

template<typename T, typename ...Args>
using is_all_same = all_<std::is_same<T, Args>...>;

template<typename T, typename ...Args>
using is_all_base_of = all_<std::is_base_of<T, Args>...>;


/*
 * Get value from json_obj(of type nhloman::basic_json) and writes to output;
 * writes default_value to output if errors.
 * Function acts as an exception safe
 * wrapper for nhloman::basic_json::value function.
*/
template<typename O, typename J, typename K, typename D>
auto setIfNotNull(O&& output, const J& json_obj, K&& key_name, D&& default_value)
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

} //! detail namespace

} //! redd namespace




#endif // HELPERFUNCTIONS_HPP
