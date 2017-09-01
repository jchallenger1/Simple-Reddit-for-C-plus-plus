#ifndef REDDIT
#define REDDIT

/* TODO
 * Add an interface to simple non authorization requests
 * Add comments to explain
 * Implement RedditMedia, RedditSub, RedditComment
 * Add classes or implementations to represent interior and exterior(on subreddit) posts
 * Hide implementation classes and functions.
 */

#include <curl/curl.h>
#include "Curl.hpp"
#include "HelperFunctions.hpp"
#include "RedditSimpleClient.hpp"
#include "RedditComment.hpp"
#include "RedditMedia.hpp"
#include "RedditSub.hpp"
#include "RedditUrl.hpp"
#include "RedditUser.hpp"

namespace redd {}


#endif
