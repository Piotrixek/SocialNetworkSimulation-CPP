#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Comment {
public:
    std::string username;
    std::string text;

    Comment(const std::string& user, const std::string& comment) : username(user), text(comment) {}
};

class User {
public:
    std::string username;
    std::vector<std::string> posts;
    std::vector<Comment> comments;
    std::unordered_set<std::string> friends;

    User(const std::string& name) : username(name) {}

    void post(const std::string& message) {
        posts.push_back(message);
    }

    void addFriend(const std::string& friendName) {
        friends.insert(friendName);
    }

    void commentOnPost(const std::string& comment) {
        comments.emplace_back(username, comment);
    }
};

class SocialNetwork {
private:
    std::unordered_map<std::string, User> users;

public:
    void addUser(const std::string& username) {
        if (users.find(username) == users.end()) {
            User newUser(username);
            users.insert({username, newUser});
            std::cout << "User '" << username << "' has been added to the social network." << std::endl;
        } else {
            std::cout << "User '" << username << "' already exists in the social network." << std::endl;
        }
    }

    void postMessage(const std::string& username, const std::string& message) {
        auto userIt = users.find(username);
        if (userIt != users.end()) {
            userIt->second.post(message);
            std::cout << "Message posted by '" << username << "': " << message << std::endl;
        } else {
            std::cout << "User '" << username << "' does not exist in the social network." << std::endl;
        }
    }

    void printUserPosts(const std::string& username) {
        auto userIt = users.find(username);
        if (userIt != users.end()) {
            std::cout << "Posts by user '" << username << "':" << std::endl;
            for (const auto& post : userIt->second.posts) {
                std::cout << "- " << post << std::endl;
            }
        } else {
            std::cout << "User '" << username << "' does not exist in the social network." << std::endl;
        }
    }

    void addFriendship(const std::string& username, const std::string& friendName) {
        auto userIt = users.find(username);
        auto friendIt = users.find(friendName);
        if (userIt != users.end() && friendIt != users.end()) {
            userIt->second.addFriend(friendName);
            friendIt->second.addFriend(username);
            std::cout << "'" << username << "' and '" << friendName << "' are now friends." << std::endl;
        } else {
            std::cout << "Invalid usernames for adding friendship." << std::endl;
        }
    }

    void commentOnPost(const std::string& username, const std::string& targetUsername, const std::string& comment) {
        auto userIt = users.find(username);
        auto targetIt = users.find(targetUsername);
        if (userIt != users.end() && targetIt != users.end()) {
            if (targetIt->second.posts.size() > 0) {
                targetIt->second.commentOnPost(comment);
                std::cout << "Comment posted by '" << username << "' on '" << targetUsername << "' post: " << comment << std::endl;
            } else {
                std::cout << "User '" << targetUsername << "' has no posts to comment on." << std::endl;
            }
        } else {
            std::cout << "Invalid usernames for posting a comment." << std::endl;
        }
    }

    void printUserFriends(const std::string& username) {
        auto userIt = users.find(username);
        if (userIt != users.end()) {
            std::cout << "Friends of user '" << username << "':" << std::endl;
            for (const auto& friendName : userIt->second.friends) {
                std::cout << "- " << friendName << std::endl;
            }
        } else {
            std::cout << "User '" << username << "' does not exist in the social network." << std::endl;
        }
    }
};

int main() {
    SocialNetwork socialNetwork;

    socialNetwork.addUser("Alice");
    socialNetwork.addUser("Bob");
    socialNetwork.addUser("Charlie");

    socialNetwork.postMessage("Alice", "Hello, everyone!");
    socialNetwork.postMessage("Bob", "Hey there!");

    socialNetwork.addFriendship("Alice", "Bob");
    socialNetwork.addFriendship("Alice", "Charlie");

    socialNetwork.commentOnPost("Bob", "Alice", "Nice post!");
    socialNetwork.commentOnPost("Charlie", "Alice", "I agree!");

    socialNetwork.printUserFriends("Alice");

    return 0;
}
