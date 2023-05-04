#ifndef Network_H
#define Network_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include "User.h"
#include "Post.h"
#include "DirectMessage.h"
using namespace std;

class Network{
    public:
        Network(); 
        void add_user(User u);
        int write_friends(string fout);
        int readFriends(string fin);
        int add_connection(string s1, string s2);
        int remove_connection(string s1, string s2);
        int get_id(string name);
        int num_users();
        vector<int> shortest_path(int from, int to);
        vector<vector<int> > groups();
        User get_user(int id);
        vector<int> suggest_friends(int who, int& score);
        vector<int> distance_user(int from, int& to, int distance);


        int read_posts(string fin);
        string displayPosts(string name, int cnt);
        string displayDM(string from,string to, int cnt);
        void addPost(string who,string msg, int likes, int id);
        void addDM(string who,string msg, int likes, int id,string to);
    private:
        User* getUserPointer(int id);
        vector<User> conn;
};
#endif
