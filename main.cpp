#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include "src/json.hpp"
#include "src/Reddit.hpp"
using namespace redd;

size_t writeToString(void *buffer, size_t size, size_t nmemb, std::string *userp) {
    userp->append(reinterpret_cast<char*>(buffer), size * nmemb);
    return size * nmemb;
}

int main() {
    RedditUser user("aosdasd","123321","5eg8ASWEt25FuQ","8jDMZngnDkzz0K51KJ2D2c2XvqQ");
    RedditSimpleClient client;
    try {
        user.setToken(client.requestToken(user));
    } catch(RedditError& err) {
        std::cout << err << std::endl;
    }
    RedditAccount me;
    me.acc_me(user);
    return 0;
}
