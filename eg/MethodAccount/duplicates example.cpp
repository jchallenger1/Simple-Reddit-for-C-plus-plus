#include <iostream>
#include <string>
#include <vector>

#include "RedditUser.hpp"
#include "RedditError.hpp"
#include "MethodListing.hpp"
#include "ThingTypes.hpp"


using namespace redd;

// Example of MethodListing::duplicates
// Function uses the interface of /duplicates/article
// Example will :
// Get the top from 10 posts from /r/funny
// Return any duplicates from the one post.

int main() {
    // Get the user token, expires in 1 hr
    RedditUser user("Username","Password","clientID","clientSecret");
    MethodListing listing;
    try {
        user.setToken(listing.requestToken(user));
    } catch(RedditError& err) {
        std::cerr << err << std::endl;
    }

    std::string id;
    std::string title;
    // Set time period to all, and only acquire 10 posts.
    MethodListing::Inputs inputs;
    inputs.limit = 10;
    inputs.t = "all";
    listing.setInputs(inputs);
    // get the top post from funny
    ThingTypes::T3Listing pair = listing.top(user, "funny");
    if (!pair.links.empty()) {
        id = pair.links[0].id;
        title = pair.links[0].title;
    }

    // get duplicates
    std::vector<ThingTypes::Link> duplicates = listing.duplicates(user, id);
    std::cout << title << " has " << duplicates.size() - 1 << " duplicate posts" << std::endl;
    return 0;
}
