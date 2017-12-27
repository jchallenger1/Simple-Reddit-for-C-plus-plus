#include <iostream>
#include <string>
#include <vector>
#include "src/Reddit.hpp"

#include "RedditUser.hpp"
#include "RedditError.hpp"
#include "MethodListing.hpp"
#include "ThingTypes.hpp"

using namespace redd;

// Example of MethodListing::commentTree member function
// Funciton uses the interface of [/r/subreddit]/comments/article reddit api method
// Example will :
// get the top comments from the top post of /r/all
// output all 10 comments from the post.

int main() {
    // Get the user token, expires in 1 hr
    RedditUser user("Username","Password","clientID","clientSecret");
	MethodListing listings;
    try {
        user.setToken(listings.requestToken(user));
    } catch(RedditError& err) {
        std::cerr << err << std::endl;
    }

    // set the total time frame to all time.
    // only include 10 posts
    MethodListing::Inputs& input = listings.inputs(); // <- note the reference.
    input.t = "all";
    input.limit = 10;

    // Get the id of the post
    std::string id;
    std::string subreddit = "all";
    ThingTypes::T3Listing list = listings.top(user, subreddit);
    id = list.links[0].id;


    // Get the comments from the post.
    ThingTypes::PostCommentPair pair = listings.commentTree(user, subreddit, id);

    // stdout comments without children
    for (ThingTypes::Comment com : pair.comments) {
        std::cout << com.body << std::endl;
    }
    return 0;
}
