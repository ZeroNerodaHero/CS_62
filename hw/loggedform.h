#ifndef LOGGEDFORM_H
#define LOGGEDFORM_H

#include <QWidget>
#include <QTableWidget>
#include <vector>
#include "/home/school/Downloads/CS_62/HW1Complete/Network.h"
using namespace std;
#include "/home/school/Downloads/CS_62/HW1Complete/User.h"

namespace Ui {
class loggedForm;
}

class loggedForm : public QWidget
{
    Q_OBJECT
public:
    explicit loggedForm(QWidget *parent = nullptr);
    ~loggedForm();
    void hide();
    void show();

    void updateUser(
            User mainUser,
            User newUser,
           vector<pair<int, QString> > frens,
            QString posts,
            vector<pair<int, QString> > suggest,
            Network &net);
    void updatePath(QString path);

    void displayDMcomponent(Network &net);
signals:
    void emitUserChange(int id);
    void friendSearch(string name);
    void addFriend(int id);

    void updateNetwork(Network &net);

private:
    Ui::loggedForm *ui;
    void populateTable(QTableWidget *t, vector<pair<int, QString> > data);
    void refreshDMComponent(int newCur,Network &net);

    vector<QString> genFriends();

    vector<int> frenList;
    vector<int> suggestFriends;
    vector<int> DMuser;

    User store_mainUser;
    int currentDMedUser=-1;
    int currentLoadedDM=5;

    int debugCnt = 0;
};

#endif // LOGGEDFORM_H
