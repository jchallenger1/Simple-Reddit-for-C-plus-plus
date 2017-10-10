#include <iostream>
#include <string>
#include <vector>
#include "src/Reddit.hpp"
using namespace redd;

// Example of MethodListing::commentTree member function
// Funciton uses the interface of [/r/subreddit]/comments/article reddit api method
// Example will :
// get the top comments from the top post of /r/all
// output all 10 comments from the post.

int main() {
    // Get the user token, expires in 1 hr
    RedditUser user("Username","Password","clientID","clientSecret");
    RedditSimpleClient client;
    try {
        user.setToken(client.requestToken(user));
    } catch(RedditError& err) {
        std::cerr << err << std::endl;
    }

    MethodListing listings;

    // set the total time frame to all time.
    // only include 10 posts
    MethodListing::Inputs& input = listings.inputs(); // <- note the reference.
    input.t = "all";
    input.limit = 10;

    // Get the id of the post
    std::string id;
    std::string subreddit = "all";
    MethodListing::T3Listing list = listings.top(user, subreddit);
    id = list.links[0].id;


    // Get the comments from the post.
    MethodListing::PostCommentPair pair = listings.commentTree(user, subreddit, id);

    // stdout comments without children
    for (MethodListing::Comment com : pair.comments) {
        std::cout << com.body << std::endl;
    }
    return 0;
}
