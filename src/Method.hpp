#ifndef METHOD_HPP
#define METHOD_HPP

#include <memory>

#include "Curl.hpp"
#include "json.hpp"

namespace redd {

namespace detail {

class Method {
public:
    explicit Method() : curl(std::make_shared<detail::Curl>()), wkptr(curl) {}
    Method(Method& m);
    virtual ~Method() = 0;

    void setDependencyOn(const Method& method) &;

    void createNewHandle() &;

protected:
    std::shared_ptr<detail::Curl> curl;
    std::weak_ptr<detail::Curl> wkptr;

    void checkJsonErrors(const nlohmann::json& json) const;
    void strToJson(const std::string& src, nlohmann::json& json) const;
};




}//! detail namespace

}//! redd namespace

#endif // METHOD_HPP
