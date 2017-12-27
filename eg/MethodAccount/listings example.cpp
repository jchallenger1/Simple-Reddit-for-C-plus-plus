#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "src/Reddit.hpp"

#include "RedditUser.hpp"
#include "RedditError.hpp"
#include "MethodListing.hpp"
#include "ThingTypes.hpp"

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
	MethodListing listing;
    try {
        user.setToken(listing.requestToken(user));
    } catch(RedditError& err) {
        std::cerr << err << std::endl;
    }

    
    MethodListing::Inputs& inputs = listing.inputs(); // <- note the reference.
    std::string after;
    std::vector<ThingTypes::Link> list;

    while (list.size() < 80) {
        inputs.after = after; // set the posting to the 'next page'
        ThingTypes::T3Listing item = listing._new(user, "pics");
        if (list.size() == 0) {
            list.assign(item.links.begin(), item.links.end());
            after = item.after; // set the after id.
        }
        else {
            std::copy(item.links.begin(), item.links.end(), std::back_inserter(list));
            after = item.after;
        }
    }

    for (ThingTypes::Link& n : list) { // print out the urls
        std::cout << n.url << std::endl;
    }

    return 0;
}
