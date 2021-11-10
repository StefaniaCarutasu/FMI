#include "student.h"
#include<vector>
#include<string>
student::student( string n, string p, float m, vector<string>s):nume(n), prenume(p), medie_bac(m), specializari(s)
{
    nr_std++;
    this->id_std="FMI_"+to_string(nr_std);
}

int student::nr_std=0;
