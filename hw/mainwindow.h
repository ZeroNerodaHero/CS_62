#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loggedform.h"
#include "loginpage.h"
#include "/home/school/Downloads/CS_62/HW1Complete/Network.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void onEmitLogin(QString str);
    void onEmitUserClick(int id);
private:
    Ui::MainWindow *ui;
    loggedForm *loggedInWidget;
    loginPage *loginWidget;

    Network net;
    User current_user,loggedUser;

    vector<pair<int,QString> > genFrens();
    vector<pair<int,QString> > genSuggest();
};
#endif // MAINWINDOW_H
