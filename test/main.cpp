#include <iostream>
#include <string>
#include <curl/curl.h>
#include "../src/Reddit.hpp"
using namespace redd;

int main() {
    RedditUser x("throw12away323459","123321");
    x.setID(std::string("mkLIyes5Rt5PEg"));
    x.setSecret("QY7K4654Td_9KX3K4eWNQ4z4zL0");

    RedditSimpleClient client;
    x.setToken(client.requestToken(x));
    std::cout << x.token() << std::endl;
    return 0;
}
