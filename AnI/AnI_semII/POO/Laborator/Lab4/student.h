#ifndef STUDENT_H
#define STUDENT_H
#include<vector>

class student
{   string nume, prenume, id_std;
    vector<string>specializari;
    float medie_bac;
    static int nr_std;
    public:
        student(string, string, float, vector<string>);
        bool esteInscris(string);
        string getId();
};

#endif // STUDENT_H
