#include <iostream>
#include <string>
#include <vector>
#include "src/Reddit.hpp"
using namespace redd;

// Example of MethodListing::duplicates
// Function uses the interface of /duplicates/article
// Example will :
// Get the top from 10 posts from /r/funny
// Return any duplicates from the one post.

int main() {
    // Get the user token, expires in 1 hr
    RedditUser user("Username","Password","clientID","clientSecret");
    RedditSimpleClient client;
    try {
        user.setToken(client.requestToken(user));
    } catch(RedditError& err) {
        std::cout << err << std::endl;
    }

    std::string id;
    std::string title;
    // Set time period to all, and only acquire 10 posts.
    MethodListing::Inputs inputs;
    inputs.limit = 10;
    inputs.t = "all";
    MethodListing listing;
    listing.setInputs(inputs);
    // get the top post from funny
    MethodListing::T3Listing pair = listing.top(user, "funny");
    if (!pair.links.empty()) {
        id = pair.links[0].id;
        title = pair.links[0].title;
    }

    // get duplicates
    std::vector<MethodListing::Link> duplicates = listing.duplicates(user, id);
    std::cout << title << " has " << duplicates.size() - 1 << " duplicate posts" << std::endl;
    return 0;
}
