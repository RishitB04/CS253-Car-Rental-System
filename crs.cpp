#include <bits/stdc++.h>

using namespace std;

class User;
class Customer;
class Employee;
class Manager;

class Car
{
public:
    string model;
    string brand;
    string availability;
    string borrower;
    string borrower_id;
    string due_date;
    void store(string m, string b, string a, string cus, string id, string dd)
    {
        model = m;
        brand = b;
        availability = a;
        borrower = cus;
        borrower_id = id;
        due_date = dd;
    }
};

class User
{
protected:
    string password;

public:
    string id;
    string name;
    bool valid(string u, string p)
    {
        if (password.length() != p.size())
            return false;
        return (id == u && password == p) ? true : false;
    }
    void n_pwd(string p)
    {
        password = p;
    }
    virtual void store(string n, string i, string p)
    {
        name = n;
        id = i;
        password = p;
    }
};

class Customer : public User
{
public:
    string customer_r;
    int Fine;
    unordered_map<string, Car> car_r;
    void store(string u, string i, string pwd, string cr, string f)
    {
        name = u;
        id = i;
        password = pwd;
        customer_r = cr;
        Fine = stoi(f);
    }
    void carlist();
    void cus();
};

class Employee : public User
{
public:
    string employee_r;
    int Fine;
    unordered_map<string, Car> car_r;
    void store(string u, string i, string pwd, string cr, string f)
    {
        name = u;
        id = i;
        password = pwd;
        employee_r = cr;
        Fine = stoi(f);
    }
    void emp();
    void carlist2();
};

class Manager : public User
{
public:
    void man();
};

void logout();
void Select_role();

unordered_map<string, Employee> empm;
unordered_map<string, Customer> cusm;
unordered_map<string, Car> carm;
vector<Car> cara;
const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
Manager l;

vector<vector<string>> vecc;
vector<vector<string>> veccu;
vector<vector<string>> vece;

string duedate(string str, int period)
{
    int d, m, y, dd, mm, yy;
    string date, month;
    d = stoi(str.substr(0, 2));
    m = stoi(str.substr(3, 2));
    y = stoi(str.substr(6, 2));
    mm = m;
    yy = y;
    dd = d + period;
    while (dd > monthDays[mm - 1])
    {
        dd -= monthDays[m - 1];
        mm++;
        if (mm > 12)
        {
            mm = 1;
            yy++;
        }
    }
    date = to_string(dd);
    if (date.length() == 1)
    {
        date = "0" + date;
    }
    month = to_string(mm);
    if (month.length() == 1)
    {
        month = "0" + month;
    }
    return date + "/" + month + "/" + to_string(yy);
}

vector<vector<string>> opencar()
{
    vector<vector<string>> v;
    string line, word;
    ifstream f("car.txt");
    if (f.is_open())
    {
        while (getline(f, line))
        {
            stringstream ss(line);
            vector<string> s;
            while (ss >> word)
            {
                s.push_back(word);
            }
            v.push_back(s);
        }
        f.close();
    }
    return v;
}

vector<vector<string>> opencustomer()
{
    vector<vector<string>> v;
    string line, word;
    ifstream f("customer.txt");
    if (f.is_open())
    {
        while (getline(f, line))
        {
            stringstream ss(line);
            vector<string> s;
            while (ss >> word)
            {
                s.push_back(word);
            }
            v.push_back(s);
        }
        f.close();
    }
    return v;
}

vector<vector<string>> openemployee()
{
    vector<vector<string>> v;
    string line, word;
    ifstream f("employee.txt");
    if (f.is_open())
    {
        while (getline(f, line))
        {
            stringstream ss(line);
            vector<string> s;
            while (ss >> word)
            {
                s.push_back(word);
            }
            v.push_back(s);
        }
        f.close();
    }
    return v;
}

void carvec()
{
    Car obj;
    int i;
    carm.clear();
    for (i = 0; i < vecc.size(); i++)
    {
        obj.store(vecc[i][0], vecc[i][1], vecc[i][2], vecc[i][3], vecc[i][4], vecc[i][5]);
        carm[vecc[i][0]] = obj;
        if (vecc[i][2] == "0")
        {
            if (cusm.find(vecc[i][4]) != cusm.end())
            {
                (cusm[vecc[i][4]].car_r)[vecc[i][0]] = obj;
            }
            else
            {
                (empm[vecc[i][4]].car_r)[vecc[i][0]] = obj;
            }
        }
    }
    return;
}

void customervec()
{
    Customer obj;
    int i;
    cusm.clear();
    for (i = 0; i < veccu.size(); i++)
    {
        obj.store(veccu[i][0], veccu[i][1], veccu[i][2], veccu[i][3], veccu[i][4]);
        cusm[veccu[i][1]] = obj;
    }
    return;
}

void employeevec()
{
    Employee obj;
    int i;
    empm.clear();
    for (i = 0; i < vece.size(); i++)
    {
        obj.store(vece[i][0], vece[i][1], vece[i][2], vece[i][3], vece[i][4]);
        empm[vece[i][1]] = obj;
    }
    return;
}

int calc_fine(string date, string str1, int a)
{
    int fine = 0, dur = 0;
    string str = date;
    int d, m, y, d2, m2, y2;
    d = stoi(str.substr(0, 2));
    m = stoi(str.substr(3, 2));
    y = stoi(str.substr(6, 2));
    d2 = stoi(str1.substr(0, 2));
    m2 = stoi(str1.substr(3, 2));
    y2 = stoi(str1.substr(6, 2));
    if (y == y2)
    {
        if (m == m2)
        {
            if (d2 <= d)
            {
                return 0;
            }
            else
            {
                return ((d2 - d) * a);
            }
        }
        else if (m2 > m)
        {
            dur = d2 + monthDays[m - 1] - d;
            for (int j = m + 1; j < m2; j++)
            {
                dur = dur + monthDays[j - 1];
            }
            return (a * (dur));
        }
    }
    else if (y2 > y)
    {
        dur = d2 + monthDays[m - 1] - d;
        for (int j = m + 1; j != m2; j++)
        {
            dur = dur + monthDays[j - 1];
            if (j == 12)
            {
                j = 0;
            }
        }
        if (m2 > m)
        {
            dur += (y2 - y) * 365;
        }
        return (a * (dur));
    }
}

template <typename T>
void clear_fine(T *obj, string date)
{
    int i;
    cout << "\nYou have successfully paid " << (*obj).Fine << " fine.\n";
    (*obj).Fine = 0;
    ofstream f;
    f.open("temp.txt", ios::app);
    for (i = 0; i < vecc.size(); i++)
    {
        if (vecc[i][4] == (*obj).id)
        {
            vecc[i][5] = date;
        }
        f << vecc[i][0] << " " << vecc[i][1] << " " << vecc[i][2] << " " << vecc[i][3] << " " << vecc[i][4] << " " << vecc[i][5] << endl;
    }
    f.close();
    unordered_map<string, Car>::iterator it;
    for (it = (*obj).car_r.begin(); it != (*obj).car_r.end(); it++)
    {
        (it->second).due_date = date;
        carm[(it->second).model].due_date = date;
    }
    remove("car.txt");
    rename("temp.txt", "car.txt");
}

template <typename T>
void rent(T *obj, int z)
{
    int available, j;
    string line, word;
    string id, date;
    int i = 0;
    cout << "\nEnter today's date (dd/mm/yy): ";
    cin >> date;
    carm[cara[z - 1].model].availability = "0";
    carm[cara[z - 1].model].borrower = (*obj).name;
    carm[cara[z - 1].model].borrower_id = (*obj).id;
    carm[cara[z - 1].model].due_date = duedate(date, 28);
    (*obj).car_r[cara[z - 1].model] = carm[cara[z - 1].model];

    ofstream f;
    f.open("temp.txt", ios::app);
    for (i = 0; i < vecc.size(); i++)
    {
        if (vecc[i][0] == cara[z - 1].model)
        {
            vecc[i][2] = "0";
            vecc[i][3] = (*obj).name;
            vecc[i][4] = (*obj).id;
            vecc[i][5] = carm[cara[z - 1].model].due_date;
        }
        f << vecc[i][0] << " " << vecc[i][1] << " " << vecc[i][2] << " " << vecc[i][3] << " " << vecc[i][4] << " " << vecc[i][5] << endl;
    }
    f.close();

    remove("car.txt");
    rename("temp.txt", "car.txt");
    cout << "\n\t\tRented Successfully !!\n"
         << endl;
}

void Customer::carlist()
{
    int j = 1;
    int z;
    cara.clear();
    if (carm.size() != 0)
    {
        cout << "\nCars Available :-\n\n";
        unordered_map<string, Car>::iterator it;
        for (it = carm.begin(); it != carm.end(); it++)
        {
            if ((it->second).availability == "1")
            {
                cout << j << ". " << (it->second).brand << " " << (it->second).model << endl;
                cara.push_back(it->second);
                j++;
            }
        }
    }
    if (j == 1)
    {
        cout << "\nNo Car Available To Rent\n\n";
    }
    else
    {
        cout << "If you want to rent a car please enter the choice from above list else enter 0 : ";
        cin >> z;
        if (z != 0)
        {
            rent(this, z);
        }
    }
}

void Employee::carlist2()
{
    int j = 1;
    int z;
    cara.clear();
    if (carm.size() != 0)
    {
        cout << "\nCars Available :-\n\n";
        unordered_map<string, Car>::iterator it;
        for (it = carm.begin(); it != carm.end(); it++)
        {
            if ((it->second).availability == "1")
            {
                cout << j << ". " << (it->second).brand << " " << (it->second).model << endl;
                cara.push_back(it->second);
                j++;
            }
        }
    }
    if (j == 1)
    {
        cout << "\nNo Car Available To Rent\n\n";
    }
    else
    {
        cout << "If you want to rent a car please enter the choice from above list else enter 0 : ";
        cin >> z;
        if (z != 0)
        {
            rent(this, z);
        }
    }
}

template <typename T>
void rtrn(T *obj, string j)
{
    int k;
    string date1, str1;
    cout << "\nEnter today's date (dd/mm/yy) : ";
    cin >> str1;
    cout << "\nIs the car damaged?(enter 1 for yes and 0 for no) : ";
    cin >> k;
    ofstream f;
    f.open("temp.txt", ios::app);
    for (int i = 0; i < vecc.size(); i++)
    {
        if (vecc[i][0] == j)
        {
            date1 = vecc[i][5];
            vecc[i][2] = "1";
            vecc[i][3] = "0";
            vecc[i][4] = "0";
            vecc[i][5] = "0";
        }
        f << vecc[i][0] << " " << vecc[i][1] << " " << vecc[i][2] << " " << vecc[i][3] << " " << vecc[i][4] << " " << vecc[i][5] << endl;
    }
    f.close();
    remove("car.txt");
    rename("temp.txt", "car.txt");
    cout << "\n\t\tCar returned successfully!!\n";
    carm[j].availability = "1";
    carm[j].borrower = "0";
    carm[j].borrower_id = "0";
    carm[j].due_date = "0";
    ((*obj).car_r).erase(j);
    (*obj).Fine = (*obj).Fine + calc_fine(date1, str1, 3000);
}

void modifyuser(int i)
{
    int j;
    cout << "\n\nChoose one of the following options:-\n1.Add\n2.Delete\n3.Update\n4.Go Back\nEnter one choice : ";
    cin >> j;
    switch (i)
    {
    case 1:
    {
        switch (j)
        {
        case 1:
        {
            string u, p, _id;
            cout << "\nEnter Name : ";
            cin >> u;
            cout << "\nEnter Password : ";
            cin >> p;
            cout << "\nEnter Unique ID : ";
            cin >> _id;
            while (cusm.find(_id) != cusm.end() || empm.find(_id) != empm.end())
            {
                cout << "\nPlease enter a unique ID : ";
                cin >> _id;
            }
            cusm[_id].store(u, _id, p, "5", "0");
            vector<string> n{u, _id, p, "5", "0"};
            veccu.push_back(n);
            ofstream f;
            f.open("temp.txt", ios::app);
            for (i = 0; i < veccu.size(); i++)
            {
                f << veccu[i][0] << " " << veccu[i][1] << " " << veccu[i][2] << " " << veccu[i][3] << " " << veccu[i][4] << endl;
            }
            f.close();

            remove("customer.txt");
            rename("temp.txt", "customer.txt");
            cout << "\n\t\tCustomer Added Successfully !!\n"
                 << endl;
            break;
        }
        case 2:
        {
            string _id;
            cout << "\nEnter ID : ";
            cin >> _id;
            while (cusm.find(_id) == cusm.end())
            {
                cout << "\nPlease enter a existing ID : ";
                cin >> _id;
            }
            unordered_map<string, Car>::iterator it = cusm[_id].car_r.begin();
            while (it != cusm[_id].car_r.end())
            {
                ofstream f;
                f.open("temp.txt", ios::app);
                for (int i = 0; i < vecc.size(); i++)
                {
                    if (vecc[i][0] == it->first)
                    {
                        vecc[i][2] = "1";
                        vecc[i][3] = "0";
                        vecc[i][4] = "0";
                        vecc[i][5] = "0";
                    }
                    f << vecc[i][0] << " " << vecc[i][1] << " " << vecc[i][2] << " " << vecc[i][3] << " " << vecc[i][4] << " " << vecc[i][5] << endl;
                }
                f.close();
                remove("car.txt");
                rename("temp.txt", "car.txt");
                carm[it->first].availability = "1";
                carm[it->first].borrower = "0";
                carm[it->first].borrower_id = "0";
                carm[it->first].due_date = "0";
                cara.push_back(carm[it->first]);
                it++;
            }
            cusm.erase(_id);

            ofstream f;
            f.open("temp.txt", ios::app);
            for (i = 0; i < veccu.size(); i++)
            {
                if (veccu[i][1] == _id)
                {
                    veccu.erase(veccu.begin() + i);
                    i--;
                    continue;
                }
                f << veccu[i][0] << " " << veccu[i][1] << " " << veccu[i][2] << " " << veccu[i][3] << " " << veccu[i][4] << endl;
            }
            f.close();

            remove("customer.txt");
            rename("temp.txt", "customer.txt");
            cout << "\n\t\tCustomer Deleted Successfully !!\n"
                 << endl;
            break;
        }
        case 3:
        {
            string _id;
            cout << "\nEnter ID : ";
            cin >> _id;
            while (cusm.find(_id) == cusm.end())
            {
                cout << "\nPlease enter a existing ID : ";
                cin >> _id;
            }
            string p;
            cout << "\nEnter New Password : ";
            cin >> p;
            cusm[_id].n_pwd(p);
            cout << "\n\t\tNew Password Has Been Set Successfully !!\n";
            ofstream f;
            f.open("temp.txt", ios::app);
            for (i = 0; i < veccu.size(); i++)
            {
                if (veccu[i][1] == _id)
                {
                    veccu[i][2] = p;
                }
                f << veccu[i][0] << " " << veccu[i][1] << " " << veccu[i][2] << " " << veccu[i][3] << " " << veccu[i][4] << endl;
            }
            f.close();

            remove("customer.txt");
            rename("temp.txt", "customer.txt");
            break;
        }

        default:
            break;
        }
        break;
    }
    case 2:
    {
        switch (j)
        {
        case 1:
        {
            string u, p, _id;
            cout << "\nEnter Name : ";
            cin >> u;
            cout << "\nEnter Password : ";
            cin >> p;
            cout << "\nEnter Unique ID : ";
            cin >> _id;
            while (cusm.find(_id) != cusm.end() || empm.find(_id) != empm.end())
            {
                cout << "\nPlease enter a unique ID : ";
                cin >> _id;
            }
            empm[_id].store(u, _id, p, "5", "0");
            vector<string> n{u, _id, p, "5", "0"};
            vece.push_back(n);
            ofstream f;
            f.open("temp.txt", ios::app);
            for (i = 0; i < vece.size(); i++)
            {
                f << vece[i][0] << " " << vece[i][1] << " " << vece[i][2] << " " << vece[i][3] << " " << vece[i][4] << endl;
            }
            f.close();

            remove("employee.txt");
            rename("temp.txt", "employee.txt");
            cout << "\n\t\temployee Added Successfully !!\n"
                 << endl;
            break;
        }
        case 2:
        {
            string _id;
            cout << "\nEnter ID : ";
            cin >> _id;
            while (empm.find(_id) == empm.end())
            {
                cout << "\nPlease enter a existing ID : ";
                cin >> _id;
            }
            unordered_map<string, Car>::iterator it = empm[_id].car_r.begin();
            while (it != empm[_id].car_r.end())
            {
                ofstream f;
                f.open("temp.txt", ios::app);
                for (int i = 0; i < vecc.size(); i++)
                {
                    if (vecc[i][0] == it->first)
                    {
                        vecc[i][2] = "1";
                        vecc[i][3] = "0";
                        vecc[i][4] = "0";
                        vecc[i][5] = "0";
                    }
                    f << vecc[i][0] << " " << vecc[i][1] << " " << vecc[i][2] << " " << vecc[i][3] << " " << vecc[i][4] << " " << vecc[i][5] << endl;
                }
                f.close();
                remove("car.txt");
                rename("temp.txt", "car.txt");
                carm[it->first].availability = "1";
                carm[it->first].borrower = "0";
                carm[it->first].borrower_id = "0";
                carm[it->first].due_date = "0";
                it++;
            }
            empm.erase(_id);

            ofstream f;
            f.open("temp.txt", ios::app);
            for (i = 0; i < vece.size(); i++)
            {
                if (vece[i][1] == _id)
                {
                    vece.erase(vece.begin() + i);
                    i--;
                    continue;
                }
                f << vece[i][0] << " " << vece[i][1] << " " << vece[i][2] << " " << vece[i][3] << " " << vece[i][4] << endl;
            }
            f.close();

            remove("employee.txt");
            rename("temp.txt", "employee.txt");
            cout << "\n\t\temployee Deleted Successfully !!\n"
                 << endl;
            break;
        }
        case 3:
        {
            string _id;
            cout << "\nEnter ID : ";
            cin >> _id;
            while (empm.find(_id) == empm.end())
            {
                cout << "\nPlease enter a existing ID : ";
                cin >> _id;
            }
            string p;
            cout << "\nEnter New Password : ";
            cin >> p;
            empm[_id].n_pwd(p);
            cout << "\n\t\tNew Password Has Been Set Successfully !!\n";
            ofstream f;
            f.open("temp.txt", ios::app);
            for (i = 0; i < vece.size(); i++)
            {
                if (vece[i][1] == _id)
                {
                    vece[i][2] = p;
                }
                f << vece[i][0] << " " << vece[i][1] << " " << vece[i][2] << " " << vece[i][3] << " " << vece[i][4] << endl;
            }
            f.close();
            remove("employee.txt");
            rename("temp.txt", "employee.txt");
            break;
        }

        default:
            break;
        }
        break;
    }

    default:
        break;
    }
}

void carrec()
{
    unordered_map<string, Car>::iterator it;
    int j = 1;
    for (it = carm.begin(); it != carm.end(); it++)
    {
        cout << "\n"
             << j << ". " << (it->second).brand << " " << (it->second).model << " " << (it->second).borrower << " " << (it->second).borrower_id;
        j++;
    }
    cout << endl;
    cout << "\n\nChoose one of the following options:-\n1.Add\n2.Delete\n3.Go Back\nEnter one choice : ";
    cin >> j;
    switch (j)
    {
    case 1:
    {
        string b, m;
        cout << "\nEnter Brand Name : ";
        cin >> b;
        cout << "\nEnter Model Name : ";
        cin >> m;
        while (carm.find(m) != carm.end())
        {
            cout << "\nPlease enter a unique Model name : ";
            cin >> m;
        }
        carm[m].store(m, b, "1", "0", "0", "0");
        vector<string> n{m, b, "1", "0", "0", "0"};
        vecc.push_back(n);
        ofstream f;
        f.open("temp.txt", ios::app);
        for (int i = 0; i < vecc.size(); i++)
        {
            f << vecc[i][0] << " " << vecc[i][1] << " " << vecc[i][2] << " " << vecc[i][3] << " " << vecc[i][4] << " " << vecc[i][5] << endl;
        }
        f.close();

        remove("car.txt");
        rename("temp.txt", "car.txt");
        cout << "\n\t\tCar Added Successfully !!\n"
             << endl;
        break;
    }

    case 2:
    {
        string m;
        cout << "\nModel Name : ";
        cin >> m;
        while (carm.find(m) == carm.end())
        {
            cout << "\nPlease enter a existing Model name : ";
            cin >> m;
        }
        string _id = carm[m].borrower_id;
        if (_id != "0")
        {
            if (cusm.find(_id) != cusm.end())
            {
                cusm[_id].car_r.erase(m);
            }
            else
                empm[_id].car_r.erase(m);
        }
        else
        {
            for (int i = 0; i < cara.size(); i++)
            {
                if (cara[i].model == m)
                {
                    cara.erase(cara.begin() + i);
                    break;
                }
            }
        }
        ofstream f;
        f.open("temp.txt", ios::app);
        for (int i = 0; i < vecc.size(); i++)
        {
            if (vecc[i][0] == m)
            {
                vecc.erase(vecc.begin() + i);
                i--;
                continue;
            }
            f << vecc[i][0] << " " << vecc[i][1] << " " << vecc[i][2] << " " << vecc[i][3] << " " << vecc[i][4] << " " << vecc[i][5] << endl;
        }
        f.close();

        remove("car.txt");
        rename("temp.txt", "car.txt");
        cout << "\n\t\tCar Deleted Successfully !!\n"
             << endl;
        break;
    }

    case 3:
    {
        return;
        break;
    }

    default:
        break;
    }
}

void userid(int i)
{
    int j = 1;
    switch (i)
    {
    case 1:
    {
        unordered_map<string, Customer>::iterator it;
        for (it = cusm.begin(); it != cusm.end(); it++)
        {
            cout << "\n"
                 << j << ". " << it->first;
            j++;
        }
        modifyuser(i);
        break;
    }
    case 2:
    {
        unordered_map<string, Employee>::iterator it;
        for (it = empm.begin(); it != empm.end(); it++)
        {
            cout << "\n"
                 << j << ". " << it->first;
            j++;
        }
        modifyuser(i);
        break;
    }

    default:
        cout << "\n\t\tPlease Choose the Correct Option :(\n";
        break;
    }
}

void Employee::emp()
{
    int i;
    cout << "\nPlease Choose One Option:\n";
    cout << "\n1.Cars Available\n2.Cars Currently Rented\n3.Fine Due\n4.Logout\n5.Close Application\n";
    cout << "\nEnter your choice : ";
    cin >> i;
    // car_rented(this);
    switch (i)
    {
    case 1:
    {
        carlist2();

        break;
    }
    case 2:
    {
        string c;
        unordered_map<string, Car>::iterator k;
        int j = 1;
        for (k = (this->car_r).begin(); k != (this->car_r).end(); k++)
        {
            cout << j << ". " << (k->second).brand << " " << (k->second).model << "   Duedate : " << (k->second).due_date << endl;
            j++;
        }
        if ((this->car_r).size() == 0)
        {
            cout << "\n\t\tNo Car Is Currently Rented\n";
        }
        else
        {
            cout << "Do you want to return a car?(1 for yes and 0 for no) : ";
            cin >> c;
            if (c == "1")
            {
                cout << "Enter the exact model of the car you want to return from the rented list : ";
                cin >> c;
                rtrn(this, c);
            }
        }
        break;
    }
    case 3:
    {
        int c;
        int fine = this->Fine;
        string s;
        cout << "\nEnter today's date (dd/mm/yy) : ";
        cin >> s;
        for (unordered_map<string, Car>::iterator k = (this->car_r).begin(); k != (this->car_r).end(); k++)
        {
            fine += calc_fine((k->second).due_date, s, 3000);
        }
        cout << "\nYour total fine is : " << fine << endl;
        cout << "\nDo you want to clear due?(1 for yes and 0 for no) : ";
        cin >> c;
        if (c == 1)
        {
            this->Fine = fine;
            clear_fine(this, s);
        }
        break;
    }
    case 4:
        logout();
        break;
    case 5:
        exit(0);
        break;
    default:
        cout << "\n\t\tPlease enter correct option :(\n";
        break;
    }
    emp();
}

void Customer::cus()
{
    int i;
    cout << "\nPlease Choose One Option:\n";
    cout << "\n1.Cars Available\n2.Cars Currently Rented\n3.Fine Due\n4.Logout\n5.Close Application\n";
    cout << "\nEnter your choice : ";
    cin >> i;
    switch (i)
    {
    case 1:
    {
        carlist();

        break;
    }
    case 2:
    {
        string c;
        unordered_map<string, Car>::iterator k;
        int j = 1;
        for (k = (this->car_r).begin(); k != (this->car_r).end(); k++)
        {
            cout << j << ". " << (k->second).brand << " " << (k->second).model << "   Duedate : " << (k->second).due_date << endl;
            j++;
        }
        if ((this->car_r).size() == 0)
        {
            cout << "\n\t\tNo Car Is Currently Rented\n";
        }
        else
        {
            cout << "Do you want to return a car?(1 for yes and 0 for no) : ";
            cin >> c;
            if (c == "1")
            {
                cout << "Enter the exact model of the car you want to return from the rented list : ";
                cin >> c;
                rtrn(this, c);
            }
        }
        break;
    }
    case 3:
    {
        int c;
        int fine = this->Fine;
        string s;
        cout << "\nEnter today's date (dd/mm/yy) : ";
        cin >> s;
        for (unordered_map<string, Car>::iterator k = (this->car_r).begin(); k != (this->car_r).end(); k++)
        {
            fine += calc_fine((k->second).due_date, s, 3000);
        }
        cout << "\nYour total fine is : " << fine << endl;
        cout << "\nDo you want to clear due?(1 for yes and 0 for no) : ";
        cin >> c;
        if (c == 1)
        {
            this->Fine = fine;
            clear_fine(this, s);
        }
        break;
    }
    case 4:
        logout();
        break;
    case 5:
        exit(0);
        break;
    default:
        cout << "\n\t\tPlease enter correct option :(\n";
        break;
    }
    cus();
}

void Manager ::man()
{
    int i;
    cout << "\nPlease Choose One Option:\n";
    cout << "\n1.Show User IDs\n2.Show Car Records\n3.Logout\n4.Close Application\n";
    cout << "\nEnter your choice : ";
    cin >> i;
    switch (i)
    {
    case 1:
    {
        int j;
        cout << "\nPlease choose for which role you want to see user ids.\n1.Customers\n2.Employees\nEnter your choice : ";
        cin >> j;
        userid(j);
        break;
    }
    case 2:
    {
        carrec();
        break;
    }
    case 3:
        logout();
        break;
    case 4:
        exit(0);
        break;

    default:
        cout << "\n\t\tPlease choose the correct option :(";
        break;
    }
    man();
}

void logout()
{
    Select_role();
}

void login(int i)
{
    int j = 0;
    string u, p;
    cout << "\n\nLogin Page\n";
    cout << "Enter ID : ";
    cin >> u;
    cout << "\nEnter Password : ";
    cin >> p;
    switch (i)
    {
    case 1:
    {
        if (cusm[u].valid(u, p))
        {
            cout << "\n\n\t\tSuccessfully Logged In As Customer\n\n";
            cusm[u].cus();
        }
        else
        {
            cout << "\n\n\t\tInvalid Name Or Password. Please Try Again :(\n\n";
        }
        break;
    }

    case 2:
    {
        if (empm[u].valid(u, p))
        {
            cout << "\n\n\t\tSuccessfully Logged In As Employee\n\n";
            empm[u].emp();
        }
        else
        {
            cout << "\n\n\t\tInvalid Name Or Password. Please Try Again :(\n\n";
        }
        break;
    }

    case 3:
    {
        if (l.valid(u, p))
        {
            cout << "\n\n\t\tSuccessfully Logged In As Manager\n\n";
            l.man();
        }
        else
        {
            cout << "\n\n\t\tInvalid Name Or Password. Please Try Again :(\n\n";
        }
        break;
    }

    default:
        break;
    }
}

void Select_role()
{
    int i;
    cout << "Select your role \n";
    cout << "\n1.Customer\n2.Employee\n3.Manager\n4.Close Application\n";
    cout << "Enter your choice : ";
    cin >> i;
    if (i == 1 || i == 2 || i == 3)
    {
        login(i);
    }
    else if (i == 4)
        exit(0);
    else
    {
        cout << "\n\nPlease enter correct option :(\n\n";
    }
    Select_role();
}

int main()
{
    l.store("manager", "000", "pass000");
    vecc = opencar();
    veccu = opencustomer();
    vece = openemployee();
    customervec();
    employeevec();
    carvec();
    Select_role();
}