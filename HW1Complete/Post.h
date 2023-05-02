#ifndef POST_H
#define POST_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
class Post{
    public:
        Post();
        Post(int id,int author,int likes,string message);

        virtual string displayPost();
        
        int getId();
        int getAuthor();
        int getLikes();
    private:
        int id,author,likes;
        string message;
};
#endif
