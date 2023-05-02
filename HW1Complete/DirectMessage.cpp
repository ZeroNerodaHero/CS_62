#include "DirectMessage.h"
#include "Post.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
DirectMessage::DirectMessage():Post(){
    this->to = -1;
}
DirectMessage::DirectMessage(int id,int author,int to,int likes,string message):
    Post(id,author,likes,message){
        this->to = to;
}
string DirectMessage::displayPost(){
    return Post::displayPost() + "$"+to_string(to)+"$";
}

int DirectMessage::getRecip(){
    return to;
}
