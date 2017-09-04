#ifndef REDDITCLIENT_HPP
#define REDDITCLIENT_HPP
/* A class representing the whole api usability.
 * The class must have a communication with all API methods
 * Each will be done through classes
 * Eg,
 * class Client {
 *  class account
 *  class captcha
 *  class flair
 *  class redditgold
 *  ....
 * }
 * They will each be separated by classes, and with each subclass will contain
 * multiple structs and functions to read, write and manipulate data.
 */


namespace redd {

    class RedditClient;

}


#endif // REDDITCLIENT_HPP
