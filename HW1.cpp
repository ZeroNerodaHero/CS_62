#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

/*
Notes:
-users are assigned numbers sequentially rather than randomly because if not, i don't think it is possible.
*/

class User{
    public:
        User(){
            id = rand();
            bday = zip = -1;
            f_name = l_name = "Not Set"; 
        } 
        User(int id, int bday, int zip, string f_name, string l_name, vector<int> conn){
            this->id = id;
            this->bday = bday;
            this->zip = zip;
            this->f_name = f_name;
            this->l_name = l_name;
            this->conn = conn; 
        }
        void add_friend(int f_id){
            conn.push_back(f_id);
        }
        void delete_friend(int f_id){
            auto it = find(conn.begin(),conn.end(),f_id);
            if(it != conn.end())
                conn.erase(it);
        }
        int getId(){return id;}
        int getBday(){return bday;}
        int getZip(){return zip;}
        string getFname(){return f_name;}
        string getLname(){return l_name;}
        vector<int> getConn(){return conn;}
        int getConn(int it){return conn[it];}
    private:
        int id;
        int bday, zip;        
        string f_name, l_name;
        vector<int> conn;
};
class Network{
    public:
        Network(){}; 
        void add_user(User u){
            conn.push_back(u);
        }
        int write_friends(string fout){
            ofstream out(fout);
            if(out.fail()){return -1;}
            out << num_users() << endl; 
            for(auto it : conn){
                out << it.getId() << endl;
                out << "\t" << it.getFname() << " " << it.getLname() << endl 
                    << "\t" << it.getBday() << endl
                    << "\t" << it.getZip() << endl;
                out << "\t";
                for(auto f : it.getConn()){
                    out << f << " ";
                } out << endl;
            }
            return 0;
        }
        int readFriends(string fin){
            //overwrite everything?
            conn.clear();

            ifstream in(fin);
            if(in.fail()){return -1;}

            string tmp;
            getline(in,tmp);
            int nUser = stoi(tmp);

            for(int i = 0; i < nUser; i++){
                string id,byear,zip;
                string name, fstring;
                
                getline(in,id);
                getline(in,name);
                getline(in,byear);
                getline(in,zip);
                getline(in,fstring);

                stringstream sn(name);
                string fname,lname;
                sn >> fname >> lname;
                stringstream sf(fstring);

                vector<int> v;
                int tmp;
                while(sf >> tmp){
                    v.push_back(tmp);
                }
                add_user(User(
                    stoi(id),stoi(byear),stoi(zip),fname,lname,v
                ));
            }
            return 0;
        }
        int add_connection(string s1, string s2){
            int u1 = get_id(s1);
            int u2 = get_id(s2);
            if(u1 == -1 || u2 == -1) return -1;

            conn[u1].add_friend(u2);
            conn[u2].add_friend(u1);
            return 0;
        }
        int remove_connection(string s1, string s2){
            int u1 = get_id(s1);
            int u2 = get_id(s2);
            if(u1 == -1 || u2 == -1) return -1;

            conn[u1].delete_friend(u2);
            conn[u2].delete_friend(u1);
            return 0;
        }
        int get_id(string name){
            for(auto it : conn){
                if(it.getFname()+" "+it.getLname() == name){
                    return it.getId();
                }
            }
            return -1;
        }
        int num_users(){return conn.size();}

        User get_user(int id){
            for(auto it : conn){
                if(it.getId()== id){
                    return it;
                }
            }
            return User();
        }
    private:
        vector<User> conn;
};
int main(){
    Network test;
    string file;
    cout << "load file > ";
    getline(cin,file);
    if(file != ""){
        if(test.readFriends(file) == -1){
            cout << "error reading" << endl;
            return 0;
        } else{
            cout << "finish" << endl;
        }
    }
    
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
        } else if(opt == 2 || opt == 3){
            string fname1,lname1;
            string fname2,lname2;
            ss >> fname1 >> lname1;
            ss >> fname2 >> lname2;
            
            if(opt == 2){
                if(test.add_connection(fname1+" "+lname1, fname2+" "+lname2) == -1){
                    cout << "Error: Users not found for connection" << endl;
                } else {cout << "Success: Updated Network" << endl;}
            } 
            else {
                if(test.remove_connection(fname1+" "+lname1, fname2+" "+lname2) == -1){
                    cout << "Error: Users not found for deletion" << endl;
                } else {cout << "Success: Updated Network" << endl;}
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
            
        } else if(opt == 5){
            cout << "id\tname\t\t\tyear\tzip\n===========================================\n";
            string fname,lname;
            ss >> fname >> lname; 
            User tmp = test.get_user(test.get_id(fname+" "+lname));
            for(auto it: tmp.getConn()){
                User fren = test.get_user(it);
                cout << fren.getId() << '\t' <<
                    fren.getFname() << " " << fren.getLname() << "\t\t" <<
                    fren.getBday() << "\t" <<
                    fren.getZip() <<endl;
            }
        } else if(opt == 6){
            string outfile;
            ss >> outfile;
            test.write_friends(outfile);
        } else{
            break;
        }
        cout << "\t\t\t ... \n";
    }
}
