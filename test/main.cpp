#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include "../src/json.hpp"
#include "../src/Reddit.hpp"
using namespace redd;



int main() {
    RedditUser x("throw12away323459","123321");
    x.setID(std::string("mkLIyes5Rt5PEg"));
    x.setSecret("QY7K4654Td_9KX3K4eWNQ4z4zL0");
    RedditSimpleClient client;
    RedditSub learnprogram = client.subreddit("https://www.reddit.com/r/learnprogramming");
    std::vector<RedditSub::SimplePost> posts;
    if (!learnprogram.hasData()) {
        std::cerr << "Error!!" << std::endl;
    }
    else {
        const std::vector<RedditSub::SimplePost>& temp_posts = learnprogram.posts();
        posts = temp_posts;
    }
    std::cout << posts[0].after << std::endl;
    return 0;
}
