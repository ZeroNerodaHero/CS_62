#ifndef DIRECTMESSAGE_H
#define DIRECTMESSAGE_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include "Post.h"
using namespace std;
class DirectMessage:public Post{
    public:
        DirectMessage();
        DirectMessage(int id,int author,int to,int likes,string message);
        string displayPost();

        int getRecip();
    private:
        int to;
};
#endif
