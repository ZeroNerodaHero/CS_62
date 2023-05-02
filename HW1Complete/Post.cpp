#include "Post.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
Post::Post(){
    this->id=-1;
    this->author=-1;
    this->likes=0;
    this->message="ERROR";
}
Post::Post(int id,int author,int likes,string message){
    this->id=id;
    this->author=author;
    this->likes=likes;
    this->message=message;
}

string Post::displayPost(){
    return message + "\nLiked by "+to_string(likes)+" people";
}
int Post::getId(){
    return id;
}
int Post::getAuthor(){
    return author;
}
int Post::getLikes(){
    return likes;
}
