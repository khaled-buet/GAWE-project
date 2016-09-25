/*
 * File:   inputData.h
 * Author: MAN
 *
 * Created on September 5, 2013, 8:58 PM
 */

#ifndef _INPUTDATA_H
#define	_INPUTDATA_H

#include <climits>
//#include <map>
//#include <cstdlib>
//#include <list>

#define DEMAND_FILE "MandlOriginDestination.txt"
#define TRAVEL_TIME_FILE "MandlDistances.txt"
#define INITIAL_ROUTE_SET "initRouteSet"
#define VERTICES_NO 15
#undef INFINITY
#define INFINITY INT_MAX
#define TRANSFER_PENALTY 5

using namespace std;

int d[VERTICES_NO][VERTICES_NO];
int tr[VERTICES_NO][VERTICES_NO];
int sDist[VERTICES_NO][VERTICES_NO];
int DS[VERTICES_NO][VERTICES_NO];
list <int> sPath[VERTICES_NO][VERTICES_NO];
vector <int> AdjList[VERTICES_NO];
map<string, float> parameters;

void readParam()
{
    ifstream fin("param");
    string name;
    float value;
    while (!fin.eof())
    {
        fin >> name >> value;
        cout << name << ":" << value << ",";
        parameters[name] = value;
        //        cout<<parameters[name]<<endl;
    }
    fin.close();

}

void readData()
{
    FILE * file = fopen(DEMAND_FILE, "r");
    FILE * file1 = fopen(TRAVEL_TIME_FILE, "r");
    for (int i = 0; i < VERTICES_NO; i++)
    {
        tr[i][i] = 0;
        for (int j = i + 1; j < VERTICES_NO; j++)
        {
            tr[j][i] = tr[i][j] = INFINITY;
        }
    }

    for (int i = 0; i < VERTICES_NO; i++)
    {
        for (int j = 0; j < VERTICES_NO; j++)
        {
            fscanf(file, "%d", &d[i][j]);
            fscanf(file1, "%d", &tr[i][j]);
            if (tr[i][j] != 0 && tr[i][j] != INFINITY)
            {
                AdjList[i].push_back(j);
            }
        }
    }
    fclose(file);
    fclose(file1);
}

list <int> findPath(int next[][VERTICES_NO], int i, int j) //called by floydWarshallWithPath()
{
    list <int> path;
    if (sPath[i][j].size() != 0)
    {
        return sPath[i][j];
    }
    if (sDist[i][j] == INFINITY)
    {
        cout << "No path between " << i << " and " << j;
        exit(0);
    }
    if (tr[i][j] != INFINITY)
    {
        path.push_back(i);
        path.push_back(j);
        return path;
    }
    else
    {
        int k = next[i][j];
        path = findPath(next, i, k);
        list <int> kj = findPath(next, k, j);
        path.pop_back();
        path.insert(path.end(), kj.begin(), kj.end());
        return path;
    }

}

void floydWarshallWithPath()
{

    int next[VERTICES_NO][VERTICES_NO];
    for (int i = 0; i < VERTICES_NO; i++)
    {
        sDist[i][i] = 0;
        for (int j = i + 1; j < VERTICES_NO; j++)
        {
            sDist[j][i] = sDist[i][j] = tr[i][j];
        }
    }

    for (int k = 0; k < VERTICES_NO; k++)
    {
        for (int i = 0; i < VERTICES_NO; i++)
        {
            for (int j = i + 1; j < VERTICES_NO; j++)
            {
                if (sDist[i][k] == INFINITY || sDist[k][j] == INFINITY)
                {
                    continue;
                }
                if ((sDist[i][k] + sDist[k][j]) < sDist[i][j])
                {
                    sDist[j][i] = sDist[i][j] = sDist[i][k] + sDist[k][j];
                    next[j][i] = next[i][j] = k;
                }
            }
        }
    }

    for (int i = 0; i < VERTICES_NO; i++)
    {
        for (int j = i + 1; j < VERTICES_NO; j++)
        {
            sPath[j][i] = sPath[i][j] = findPath(next, i, j);
            sPath[j][i].reverse();
        }
    }
    float ATT = 0, totalDemand = 0;
    for (int i = 0; i < VERTICES_NO; i++)
    {
        for (int j = i + 1; j < VERTICES_NO; j++)
        {
            totalDemand += d[i][j];
            ATT += d[i][j] * sDist[i][j];
        }
    }
    parameters["OptimalATT"] = ATT / totalDemand;
    cout<< " OpATT"<<parameters["OptimalATT"]<<endl;
}

void findDS()
{
    for (int i = 0; i < VERTICES_NO; i++)
    {
        DS[i][i] = 0;
        for (int j = i + 1; j < VERTICES_NO; j++)
        {
            int sum = 0;
            list<int>::iterator outer = sPath[i][j].end();
            for (outer--; outer != sPath[i][j].begin(); outer--)
            {
                list<int>::iterator inner;
                for (inner = sPath[i][j].begin(); inner != outer; inner++)
                {
                    sum += d[*inner][*outer];
                }
            }
            DS[i][j] = DS[j][i] = sum;
        }
    }
}

void gatherAllInfo()
{
    readParam();
    readData();
    floydWarshallWithPath();
    findDS();
}

#endif	/* _INPUTDATA_H */

