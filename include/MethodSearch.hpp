#ifndef METHODSEARCH_HPP
#define METHODSEARCH_HPP

#include <memory>
#include <string>
#include <vector>

#include "Method.hpp"
#include "ThingTypes.hpp"
#include "RedditUser.hpp"

namespace redd {

class MethodSearch : public detail::Method {
public:
    struct Inputs;

    MethodSearch() :extra_inputs(std::make_unique<Inputs>()) {}

    void setInputs(const Inputs&);
    void resetInputs();
    Inputs& inputs();

    std::vector<Link> search(const RedditUser& user, const std::string& s);

private:
    std::unique_ptr<Inputs> extra_inputs;

    std::string inputsToString() const;
};


struct MethodSearch::Inputs {
    std::string after;
    std::string before;
    std::string q;
    std::string show;
    std::string sort;
    std::string syntax;
    std::string t;
    std::string type;
    unsigned count;
    unsigned limit;
    bool restrict_sr;
    bool sr_detail;
};


}//! redd namespace



#endif // METHODSEARCH_HPP
