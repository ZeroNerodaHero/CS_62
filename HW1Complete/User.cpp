#include "User.h"
#include "Post.h"
#include "DirectMessage.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <QDebug>
using namespace std;

User::User(){
    id = rand();
    bday = zip = -1;
    f_name = l_name = "Not Set"; 
    messages = vector<Post*>();
} 
User::User(int id, int bday, int zip, string f_name, string l_name, vector<int> conn){
    this->id = id;
    this->bday = bday;
    this->zip = zip;
    this->f_name = f_name;
    this->l_name = l_name;
    this->conn = conn; 
    messages = vector<Post*>();
} 
void User::add_friend(int f_id){
    conn.push_back(f_id);
}
void User::delete_friend(int f_id){
    auto it = find(conn.begin(),conn.end(),f_id);
    if(it != conn.end())
        conn.erase(it);
}
void User::addPost(Post* p){
    if(checkPostType(p)){
        DirectMessage* DM = dynamic_cast<DirectMessage*>(p);
        addRelationDM(DM->getAuthor() == id ?
                          DM->getRecip():DM->getAuthor());
    }
    messages.push_back(p);
}
string User::displayPosts(int cnt){
    string ret = "";
    for(int i = 0,c=0; c < cnt && i<messages.size(); i++){
        if(checkPostType(messages[i])) continue;
        ret += messages[i]->displayPost() + "\n\n";
        c++;
    }
    return ret == "" ? "EMPTY" :ret;
}
string User::displayDm(int who, string name, int cnt){
    string ret = "";
    for(int i = messages.size()-1,c=0; c < cnt && i >= 0; i--){
        if(!checkPostType(messages[i])) continue;
        string tmp = messages[i]->displayPost();
//assume propert format;
        int sub = tmp.size()-2;
        while(sub > 0 && tmp[sub--] != '$'); 
        int recip = stoi(tmp.substr(sub+2,tmp.size()-sub-3));
        
        if(recip == who ){
            ret = ">"+tmp.substr(0,sub+1) + "\n\n"+ret;
            c++;
        }
        else if(messages[i]->getAuthor() == who){
            ret = "<"+tmp.substr(0,sub+1) + "\n\n"+ret;
            c++;
        }
    }
    return "From " + name + "\n"+(ret == ""?"EMPTY":ret);
}

bool User::checkPostType(Post* p){
    string tmp = p->displayPost();
    return tmp[tmp.size()-1] == '$';
}

int User::extractUserId(Post *p){
    string tmp = p->displayPost();
//assume propert format;
    int sub = tmp.size()-2;
    while(sub > 0 && tmp[sub--] != '$');
    int user = stoi(tmp.substr(sub+2,tmp.size()-sub-3));
}

void User::addRelationDM(int userId){
    qDebug() << "addRelation" << userId;
    relationDM.insert(userId);
}
bool User::hasRelationDM(int userId){
    return relationDM.find(userId) != relationDM.end();
}
unordered_set<int> User::getAllRelationDM(){
   return relationDM;
}
