#ifndef METHOD_HPP
#define METHOD_HPP

#include <memory>

#include "Curl.hpp"

namespace redd {

namespace detail {

class Method {
public:
    explicit Method() : curl(std::make_shared<detail::Curl>()), wkptr(curl) {}
    Method(Method& m) { setDependencyOn(m); }
    virtual ~Method() = default;

    void setDependencyOn(const Method& method) & {
        auto ptr = method.wkptr.lock();
        if (ptr) {
            curl = method.curl;
            wkptr = method.curl;
        }
        else {
            throw std::runtime_error("Method type's curl pointer does not exist.");
        }
    }
    void createNewHandle() & {
        curl = std::make_shared<detail::Curl>();
        wkptr = curl;
    }
protected:
    std::shared_ptr<detail::Curl> curl;
    std::weak_ptr<detail::Curl> wkptr;
};

}//! detail namespace

}//! redd namespace

#endif // METHOD_HPP
