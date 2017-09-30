#include <memory>
#include <string>

#include "MethodListing.hpp"

namespace redd {

MethodListing::MethodListing(const detail::Method& m) {
    setDependencyOn(m);
}

void MethodListing::setInputs(const Inputs& inputs) {
    *extraInputs = inputs;
}

MethodListing::Inputs& MethodListing::inputs() const {
    return *extraInputs;
}

MethodListing::Hot MethodListing::hot(const RedditUser&, const std::string& s) {
    return Hot();
}


} //! redd namsepace
