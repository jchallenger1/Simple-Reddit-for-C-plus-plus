#ifndef MethodObserver_HPP
#define MethodObserver_HPP

#include <type_traits>
#include <map>
#include <functional>

#include "Method.hpp"
#include "HelperFunctions.hpp"
#include "RedditError.hpp"

namespace redd {

/*
 * Acts as a method manager, uses parts of the observer pattern by delegating
 * the networking part of the class to this object.
 * Needed if the user wants to use multiple methods in a class or in their
 * general program or mostly to use less resources by reducing the instances of Curl objects.
*/
class MethodObserver final : private detail::Method {
public:
    MethodObserver() = default;
    ~MethodObserver() {
        while (!observers.empty()) {
            removeMethod(observers.begin()->second.get());
        }
    }

    template<typename T>
    void registerMethod(T& method);

    template<typename T, typename ...Meths>
    void registerMethod(T& method, Meths&... methods);

    void removeMethod(Method& method) {
        if (!isRegistered(method)) { throw RedditError("Method was not found.");}
        auto x = observers.find(addressOf(method));
        x->second.get().createNewHandle();
        observers.erase(x);
    }

    bool isRegistered(Method& method) const {
        return observers.find(addressOf(method)) != observers.end();
    }

    size_t methodCount() const noexcept {
        return observers.size();
    }

private:
    using Method = detail::Method;
    std::map<size_t, std::reference_wrapper<Method>> observers;
    size_t addressOf(const Method& m) const noexcept {
        return reinterpret_cast<size_t>(&m);
    }
};

template<typename T>
void MethodObserver::registerMethod(T& method) {
    static_assert(std::is_base_of<Method, T>::value,
                  "Function's parameters must be all reddit methods.");
    if (!isRegistered(method)) {
        method.setDependencyOn(*this);
        observers.emplace(std::make_pair(addressOf(method), std::ref(method)));
    }

}

template<typename T, typename ...Meths>
void MethodObserver::registerMethod(T& method, Meths&... methods) {
    constexpr bool isAllMethods = std::is_base_of<Method, T>::value &&
            detail::is_all_base_of<Method, Meths...>::value;
    static_assert(isAllMethods, "Function's parameters must be all methods.");
    registerMethod(method);
    if (sizeof...(methods) > 0) {
        registerMethod(methods...);
    }
}

}//! redd namespace


#endif // MethodObserver_HPP
