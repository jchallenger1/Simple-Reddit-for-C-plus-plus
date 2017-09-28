#include <memory>
#include <string>

#include "MethodListing.hpp"

namespace redd {

MethodListing::MethodListing(const MethodListing& other)
    : extraInputs(std::make_unique<Inputs>(*other.extraInputs)) {
    this->curl = other.curl;

}

MethodListing& MethodListing::operator =(const MethodListing& other) {
    *this->extraInputs = *other.extraInputs;
    this->curl = other.curl;
    return *this;
}

/*void MethodListing::setInputs(const Inputs& inputs) {
    extraInputs = inputs;
}

MethodListing::Inputs MethodListing::inputs() const {
    return extraInputs;
}

MethodListing::Hot MethodListing::hot(const RedditUser&,const std::string& s) {

}*/


} //! redd namsepace
