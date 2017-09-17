#include <iostream>
#include <string>
#include <vector>


#include "Reddit.hpp"
using namespace redd;

int main() {
    /*   Get redirect link from /r/pics pointing to pictures   */
    RedditSimpleClient client;
    RedditSub learnprogram = client.subreddit("https://www.reddit.com/r/pics");
    std::vector<RedditSub::ExternalPost> posts;
    if (!learnprogram.hasData()) {
        std::cerr << "An error has occured" << std::endl;
    }
    else {
        posts = learnprogram.posts();
    }
    std::vector<std::string> download_links;
    for (RedditSub::ExternalPost& n : posts) {
        if (!n.permalink.empty()) {
            download_links.emplace_back(n.permalink);
        }
    }
    std::cout << download_links.size() << std::endl;
    return 0;
}
