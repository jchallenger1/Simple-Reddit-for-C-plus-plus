#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "src/Reddit.hpp"
using namespace redd;

// Example of MethodListing::hot, new, top, controversial and rising
// Function uses the interface of /[/r/subreddit]/new, [/r/subreddit]/hot ...
// Example will :
// Get 80 new posts from /r/pics

// Alternatively, you can set MethodListing::Inputs::limit to 80
// (max of 100 per page) for the same effect.

int main() {
    // Get the user token, expires in 1 hr
    RedditUser user("Username","Password","clientID","clientSecret");
    RedditSimpleClient client;
    try {
        user.setToken(client.requestToken(user));
    } catch(RedditError& err) {
        std::cerr << err << std::endl;
    }

    MethodListing listing;
    MethodListing::Inputs& inputs = listing.inputs(); // <- note the reference.
    std::string after;
    std::vector<MethodListing::Link> list;

    while (list.size() < 80) {
        inputs.after = after; // set the posting to the 'next page'
        MethodListing::T3Listing item = listing._new(user, "pics");
        if (list.size() == 0) {
            list.assign(item.links.begin(), item.links.end());
            after = item.after; // set the after id.
        }
        else {
            std::copy(item.links.begin(), item.links.end(), std::back_inserter(list));
            after = item.after;
        }
    }

    for (MethodListing::Link& n : list) { // print out the urls
        std::cout << n.url << std::endl;
    }

    return 0;
}
