#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include "../src/json.hpp"
#include "../src/Reddit.hpp"
using namespace redd;

int main() {
    /*   Example get redirect link from /r/pics   */
    RedditSimpleClient client;
    RedditSub learnprogram = client.subreddit("https://www.reddit.com/r/pics");
    std::vector<RedditSub::ExternalPost> posts;
    if (!learnprogram.hasData()) {
        std::cerr << "Error!!" << std::endl;
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
