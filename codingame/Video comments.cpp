#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct Comment {
    string name;
    string time;
    int likes;
    string priority;
    int originalIndex;
    bool isReply;
    vector<Comment> replies;
    string fullLine;
};

Comment parseComment(const string& line, int index) {
    Comment comment;
    comment.originalIndex = index;
    comment.fullLine = line;
    comment.isReply = (line.substr(0, 4) == "    ");
    
    string data = comment.isReply ? line.substr(4) : line;
    
    stringstream ss(data);
    string token;
    
    getline(ss, token, '|');
    comment.name = token;
    
    getline(ss, token, '|');
    comment.time = token;
    
    getline(ss, token, '|');
    comment.likes = stoi(token);
    
    getline(ss, token, '|');
    comment.priority = token;
    
    return comment;
}

bool compareComments(const Comment& a, const Comment& b) {
    if (a.priority == "Pinned" && b.priority != "Pinned") return true;
    if (a.priority != "Pinned" && b.priority == "Pinned") return false;
    
    if (a.priority == "Followed" && b.priority != "Followed") return true;
    if (a.priority != "Followed" && b.priority == "Followed") return false;
    
    if (a.priority == "Followed" && b.priority == "Followed") {
        if (a.likes != b.likes) return a.likes > b.likes;
        if (a.time != b.time) return a.time > b.time;
        return a.originalIndex < b.originalIndex;
    }
    
    if (a.likes != b.likes) return a.likes > b.likes;
    if (a.time != b.time) return a.time > b.time;
    return a.originalIndex < b.originalIndex;
}

int main() {
    int n;
    cin >> n;
    cin.ignore();
    
    vector<Comment> mainComments;
    
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        
        Comment comment = parseComment(line, i);
        
        if (comment.isReply) {
            if (!mainComments.empty()) {
                mainComments.back().replies.push_back(comment);
            }
        } else {
            mainComments.push_back(comment);
        }
    }
    
    for (auto& comment : mainComments) {
        if (!comment.replies.empty()) {
            sort(comment.replies.begin(), comment.replies.end(), compareComments);
        }
    }
    
    sort(mainComments.begin(), mainComments.end(), compareComments);
    
    for (const auto& comment : mainComments) {
        cout << comment.fullLine << endl;
        for (const auto& reply : comment.replies) {
            cout << reply.fullLine << endl;
        }
    }
    
    return 0;
}
