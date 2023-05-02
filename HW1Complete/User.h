#ifndef USER_H
#define USER_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include "Post.h"
#include "DirectMessage.h"
using namespace std;
//I do not use depth and predecessor here because I feel that they are not as useful for the implementation of searching and group algorithm that I used.

class User{
    public:
        User();
        User(int id, int bday, int zip, string f_name, string l_name, vector<int> conn);
        void add_friend(int f_id);
        void delete_friend(int f_id);
        int getId(){return id;}
        int getBday(){return bday;}
        int getZip(){return zip;}
        string getFname(){return f_name;}
        string getLname(){return l_name;}
        vector<int> getConn(){return conn;}
        int getConn(int it){return conn[it];}

        void addPost(Post* p);
        string displayPosts(int cnt);
        string displayDm(int who, string name, int cnt);
    private:
        int id;
        int bday, zip;        
        int depth,predecessor;
        string f_name, l_name;
        vector<int> conn;
        vector<Post* > messages;

        bool checkPostType(Post* p);
};
#endif
