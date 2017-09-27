#ifndef REDDIT
#define REDDIT

/* TODO
 * Add an interface to simple non authorization requests
 * Implement RedditMedia, RedditSub, RedditComment
 * Add classes or implementations to represent interior and exterior(on subreddit) posts
*/

/* Dependency Files */
#include <curl/curl.h>
#include "json.hpp"

/* Library Files */
#include "Curl.hpp"
#include "RedditError.hpp"
#include "HelperFunctions.hpp"
#include "RedditSimpleClient.hpp"
#include "RedditSub.hpp"
#include "RedditUrl.hpp"
#include "RedditUser.hpp"

#include "MethodAccount.hpp"
#include "MethodListing.hpp"

#endif
