#ifndef LOGGEDFORM_H
#define LOGGEDFORM_H

#include <QWidget>
#include <QTableWidget>
#include <vector>
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
            vector<pair<int, QString> > suggest);
    void updatePath(QString path);
signals:
    void emitUserChange(int id);
    void friendSearch(string name);
    void addFriend(int id);

private:
    Ui::loggedForm *ui;
    void populateTable(QTableWidget *t, vector<pair<int, QString> > data);

    vector<QString> genFriends();

    vector<int> frenList;
    vector<int> suggestFriends;
};

#endif // LOGGEDFORM_H
