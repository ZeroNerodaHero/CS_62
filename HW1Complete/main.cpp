#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include "User.h"
#include "Network.h"
using namespace std;

void readMessage(Network &n){
    string fin = "posts";

    ifstream in(fin);
    if(in.fail()){return;}

    string tmp;
    getline(in,tmp);
    int nPost = stoi(tmp);

    for(int i = 0; i < nPost; i++){
        vector<string> v(5,"");
        for(int i = 0; i < 5; i++){
            getline(in,v[i]);
        }
        int id,uid,likes,tid=-1;
        stringstream s1(v[0]);s1>>id;
        stringstream s2(v[2]);s2>>uid;
        stringstream s3(v[3]);s3>>likes;

        User from = n.get_user(uid);
        if(from.getFname() != "Not Set"){
            string fromName = from.getFname()+" "+from.getLname();
            if(v[4] != ""){
                getline(in,tmp);
                stringstream s4(tmp);s4>>tid;
                User to= n.get_user(tid);
                if(to.getFname() != "Not Set"){
                    string toName = to.getFname()+" "+to.getLname();
                    n.addDM(fromName,v[1],likes,id,toName);
                }
            } else{
                n.addPost(fromName,v[1],likes,id);
            }
        }

/*
        cout << id << " " 
            << v[1] << " "
            << uid << " "
            << likes<< " "
            << tid << endl;
*/
    }
}

int main(){
    Network test;
    string file = "largeTest";
    cout << "load file > ";
    //getline(cin,file);
    if(file != ""){
        if(test.readFriends(file) == -1){
            cout << "error reading" << endl;
            return 0;
        } else{
            cout << "finish" << endl;
        }
    }
    readMessage(test);
    
    
    while(1){
        string tmp;
        cout << "> ";
        getline(cin,tmp);
        stringstream ss(tmp);
        ss >> tmp;
        if(tmp == "") break;
        int opt = stoi(tmp);
        if(opt == 1){
            string fname,lname,byear,zip;
            ss >> fname >> lname >>byear >>zip;
            test.add_user(User(test.num_users(),stoi(byear),stoi(zip),fname,lname,vector<int>()));
        } else if(opt == 2 || opt == 3 || opt == 7 || opt == 12){
            string fname1,lname1;
            string fname2,lname2;
            ss >> fname1 >> lname1;
            ss >> fname2 >> lname2;
            string user1= fname1+" "+lname1;
            string user2= fname2+" "+lname2;
            
            if(opt == 2){
                if(test.add_connection(user1, user2) == -1){
                    cout << "Error: Users not found for connection or already connected" << endl;
                } else {cout << "Success: Updated Network" << endl;}
            } 
            else if(opt == 3){
                if(test.remove_connection(user1,user2) == -1){
                    cout << "Error: Users not found for deletion or already disconnected" << endl;
                } else {cout << "Success: Updated Network" << endl;}
            } 
            else if(opt == 7){
                int id1 = test.get_id(user1);
                int id2 = test.get_id(user2);
                vector<int> res= test.shortest_path(id1,id2);
                bool isFirst = 1;
                if(res[0] != -1){
                    cout << "Depth: " <<res.size()-1<< endl;
                    for(auto it : res) {
                        User tmp = test.get_user(it);
                        cout << (isFirst ? "" : " -> ")+ tmp.getFname()+" "+tmp.getLname(); 
                        isFirst = 0;
                    }
                } else{
                    cout << "THERE IS NOT PATH BETWEEN "+user1+" and "+user2 << endl;
                }cout <<endl;
            } else if(opt == 12){
                string scnt; ss >> scnt;
                int cnt = stoi(scnt);
                cout << test.displayDM(user1,user2,cnt) << endl;
            } else{
                cout << "ERROR: WTF" << endl;
            }
        } else if(opt == 4){
            cout << "id\tname\t\t\tyear\tzip\n===========================================\n";
            for(int i = 0; i < test.num_users(); i++){
                User tmp = test.get_user(i);
                cout << tmp.getId() << '\t' <<
                    tmp.getFname() << " " << tmp.getLname() << "\t\t" <<
                    tmp.getBday() << "\t" <<
                    tmp.getZip() <<endl;
            }
            
        } else if(opt == 5 || opt== 9 || opt==11){
            string fname,lname;
            ss >> fname >> lname; 
            int userId= (test.get_id(fname+" "+lname));
            if(userId == -1){
                cout << "ERROR: User not found\n";
                continue;
            }
            if(opt == 5){
                cout << "id\tname\t\t\tyear\tzip\n===========================================\n";
                User tmp = test.get_user(userId);
                for(auto it: tmp.getConn()){
                    User fren = test.get_user(it);
                    cout << fren.getId() << '\t' <<
                        fren.getFname() << " " << fren.getLname() << "\t\t" <<
                        fren.getBday() << "\t" <<
                        fren.getZip() <<endl;
                }
            } else if(opt == 9){
                int score; 
                vector<int> frenList = test.suggest_friends(userId,score);
                cout << "The suggested friend(s) is/are:" << endl;
                if(score != -1){
                    for(auto it: frenList){
                        User frenSug = test.get_user(it);
                        cout << "\t"+frenSug.getFname()+" "+frenSug.getLname()+"\tScore: "<<score << endl;
                    }
                } else {
                    cout << "NONE" << endl;
                }
            } else if(opt == 11){
                int cnt = 0;
                string scnt; 
                ss >> scnt;
                stringstream sc(scnt);
                sc >> cnt;
                
                cout << test.displayPosts(fname+" "+lname,cnt) << endl;
            }
        } else if(opt == 6){
            string outfile;
            ss >> outfile;
            test.write_friends(outfile);
        } else if(opt == 8){
            vector<vector<int> > sets = test.groups();
            for(int i = 0; i < sets.size(); i++){
                cout << "Set "<<i+1 << " => ";
                bool flag =1;
                    
                for(auto it: sets[i]){
                    User tmp = test.get_user(it);
                    cout <<(flag?"":", ")<<tmp.getFname() << " "<<tmp.getLname();
                    flag= 0;
                } cout << endl;
            }
        } else if(opt == 10){
            string fname,lname;
            ss >> fname >> lname; 
            string read_dist;
            ss >> read_dist;
            int dist = stoi(read_dist);
            int userId;
            vector<int> path = test.distance_user(test.get_id(fname+" "+lname),userId,dist);
            if(userId != -1){
                User fUser= test.get_user(userId);
                
                cout << "PATH of "<<dist <<" from "<<fname+" "+lname<<" to "
                        << fUser.getFname()+" "+fUser.getLname() << endl;
                bool isFirst = 1;
                for(auto it:path){
                    User tmp = test.get_user(it);
                    cout << (isFirst?"":"->")<<tmp.getFname()+" "+tmp.getLname();
                    isFirst = 0;
                } cout << endl;
            } else {
                cout << "No path that long exists from user" << endl;
            }
        } else{
            cout << "Exiting" << endl;
            break;
        }
        cout << "\t\t\t ... \n";
    }
}
