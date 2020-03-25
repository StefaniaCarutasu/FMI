#include <iostream>
#include <vector>
#include <string>
using namespace std;
class student
{
    string nume, prenume, id_std;
    vector<string>specializari;
    float medie_bac;
    static int nr_std;
public:
    student(string, string, float, vector<string>);
    bool esteInscris(string);
    string getId();
};
student::student(string n, string p, float m, vector<string>s) :nume(n), prenume(p), medie_bac(m), specializari(s)
{
    nr_std++;
    this->id_std = "FMI_" + to_string(nr_std);
}

int student::nr_std = 0;
bool student::esteInscris(string spec)
{
    for (string s : this->specializari)
    {
        if (s == spec)
            return true;
    }
    return false;
}
class App {
    vector<student>v;
public:
    void add(student);
    void afisareSpecializare(string);
    void eliminareStudent(string);
};
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
