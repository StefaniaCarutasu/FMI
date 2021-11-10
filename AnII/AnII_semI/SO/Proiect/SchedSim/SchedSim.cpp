#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
using namespace std;

const int TimeSlice = 10;

struct proces
{
    int timpExecutie;
    int momentStart;
    int momentFinish;
    int durataTotala;
    int timpRamas;
};

vector<pair<int, proces>> procese;
vector<pair<int, proces>> proceseCopy;
vector<pair<int, proces>> rezultateRoundRobin;
vector<pair<int, proces>> rezultateFCFS;

void citire()
{
    ifstream f("procese.in.txt");
    int nrProcese;
    int prioritate;
    proces p;
    f >> nrProcese;
    for (int i = 0; i < nrProcese; i++)
    {
        f >> prioritate >> p.timpExecutie;
        p.timpRamas = p.timpExecutie;
        procese.push_back(make_pair(prioritate, p));
        proceseCopy.push_back(make_pair(prioritate, p));
    }

    f.close();
}

bool sortare(pair<int, proces> p1, pair<int, proces> p2)
{
    return p1.first > p2.first;
}

void roundRobin()
{
    sort(procese.begin(), procese.end(), sortare);
    int moment = 0; //momentul curent
    unsigned int i = 0;
    while (i < procese.size())
    {

        if (procese[i].second.timpExecutie == procese[i].second.timpRamas)
        {
            procese[i].second.momentStart = moment;
        }
        if (procese[i].second.timpRamas <= TimeSlice)
        {
            moment += procese[i].second.timpRamas;
            procese[i].second.momentFinish = moment;
            procese[i].second.timpRamas = 0;
            procese[i].second.durataTotala = procese[i].second.momentFinish - procese[i].second.momentStart;
            rezultateRoundRobin.push_back(procese[i]);
            procese.erase(procese.begin() + i);
            i = 0;
        }
        else
        {
            procese[i].second.timpRamas -= TimeSlice;
            moment += TimeSlice;
            if (i != procese.size())
            {
                if ((i != 0 && procese[i].first == procese[i + 1].first) || i == 0)
                    i++;
                else i = 0;
            }
            else i = 0;

        }

    }
}

void FCFS()
{
    sort(proceseCopy.begin(), proceseCopy.end(), sortare);
    int moment = 0;
    for (auto i : proceseCopy)
    {
        i.second.momentStart = moment;
        moment += i.second.timpExecutie;
        i.second.momentFinish = moment;
        i.second.durataTotala = i.second.timpExecutie;
        i.second.timpRamas = 0;
        rezultateFCFS.push_back(i);
    }
}

void afisareStatistici()
{
    cout << "Statistici scheduler round-robin:\n";
    for (auto i : rezultateRoundRobin)
    {
        cout << "Prioritate: " << i.first << "       Timp executie: " << i.second.timpExecutie << "      Moment start: " << i.second.momentStart << "      Moment finish: " << i.second.momentFinish << '\n';

    }
    cout << "\nStatistici scheduler first come first served:\n";
    for (auto i : rezultateFCFS)
    {
        cout << "Prioritate: " << i.first << "       Timp executie: " << i.second.timpExecutie << "      Moment start: " << i.second.momentStart << "      Moment finish: " << i.second.momentFinish << '\n';

    }

    float throughputFCFS, avgWaitFCFS = 0, avgCmpFCFS = 0, throughputRR, avgWaitRR = 0, avgCmpRR = 0;
    throughputFCFS = ((float)rezultateFCFS.size() / (float)rezultateFCFS[rezultateFCFS.size() - 1].second.momentFinish);
    for (auto i : rezultateFCFS)
    {
        avgWaitFCFS += i.second.momentStart;
        avgCmpFCFS += i.second.momentFinish;
    }
    avgWaitFCFS = avgWaitFCFS / rezultateFCFS.size();
    avgCmpFCFS = avgCmpFCFS / rezultateFCFS.size();

    throughputRR = throughputFCFS;
    for (auto i : rezultateRoundRobin)
    {
        avgWaitRR += i.second.momentStart;
        avgCmpRR += i.second.momentFinish;
    }
    avgWaitRR = avgWaitRR / rezultateRoundRobin.size();
    avgCmpRR = avgCmpRR / rezultateRoundRobin.size();

    cout << '\n' << '\n' << "                                Compararea celor doi algoritmi de scheduling\n";
    cout << "\n                                          THROUGHPUT              AVG WAIT TIME               AVG COMPLETION TIME\n";
    cout << "\nRount-Robin                               " << throughputRR << "                   " << avgWaitRR << "                       " << avgCmpRR << '\n';
    cout << "First come first serve                    " << throughputFCFS << "                   " << avgWaitFCFS << "                       " << avgCmpFCFS << '\n';
}


int main()
{
    citire();
    roundRobin();
    FCFS();
    afisareStatistici();
    return 0;
}