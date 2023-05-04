#ifndef LOGGEDFORM_H
#define LOGGEDFORM_H

#include <QWidget>
#include <QTableWidget>
#include <vector>
using namespace std;

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

    void populatePage(vector<int> t);
    void populateTable(QTableWidget *t, vector<int> data);

private:
    Ui::loggedForm *ui;

};

#endif // LOGGEDFORM_H
