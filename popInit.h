/*
 * File:   popInit.h
 * Author: MAN
 *
 * Created on September 7, 2013, 7:01 AM
 */

#ifndef _POPINIT_H
#define	_POPINIT_H

#include <eot.h>
#include "routeSet.h"
#include "inputData.h"
#include <stdlib.h>

void popInit(eoPop< RouteSet<double> >& _pop, int popSize, int routeSetSize, eoEvalFunc< RouteSet<double> >& _eval)
{
    ifstream fin(INITIAL_ROUTE_SET);
    RouteSet<double> initRs;
    vector< Route<double> > initV;
    for (int iroute = 0; iroute < routeSetSize; iroute++)
    {
        Route<double> initR;
        vector<int> initNodeList(VERTICES_NO, 0);

        list<int> initL;
        int node;
        fin >> node;
        while (node != -1)
        {
            initL.push_back(node);
            initNodeList[node] = 1;
            fin >> node;
        }
        initR.setR(initL);
        initR.setNodeList(initNodeList);
        initR.fitness(1.0 / DS[initL.front()][initL.back()]); //fitness 1/ds
        initV.push_back(initR);
    }
    initRs.setRs(initV);
    _eval(initRs);

    //std::cout<<initRs<<std::endl; //comment after test
    RouteSet<double> initRs1;
    vector< Route<double> > initV1;
    for (int iroute = 0; iroute < routeSetSize; iroute++)
    {
        Route<double> initR;
        vector<int> initNodeList(VERTICES_NO, 0);

        list<int> initL;
        int node;
        fin >> node;
        while (node != -1)
        {
            initL.push_back(node);
            initNodeList[node] = 1;
            fin >> node;
        }
        initR.setR(initL);
        initR.setNodeList(initNodeList);
        initR.fitness(1.0 / DS[initL.front()][initL.back()]); //fitness 1/ds
        initV1.push_back(initR);
    }
    initRs1.setRs(initV1);
    _eval(initRs1);

    RouteSet<double> initRs2;
    vector< Route<double> > initV2;
    for (int iroute = 0; iroute < routeSetSize; iroute++)
    {
        Route<double> initR;
        vector<int> initNodeList(VERTICES_NO, 0);

        list<int> initL;
        int node;
        fin >> node;
        while (node != -1)
        {
            initL.push_back(node);
            initNodeList[node] = 1;
            fin >> node;
        }
        initR.setR(initL);
        initR.setNodeList(initNodeList);
        initR.fitness(1.0 / DS[initL.front()][initL.back()]); //fitness 1/ds
        initV2.push_back(initR);
    }
    initRs2.setRs(initV2);
    _eval(initRs2);

    for (int igeno = 0; igeno < popSize; igeno++)
    {
        if(igeno%(1+rand()%3)==0)
            _pop.push_back(initRs);
        else if(igeno%(1+rand()%3)==1)
            _pop.push_back(initRs1);
        else
             _pop.push_back(initRs2);

    }
}

#endif	/* _POPINIT_H */

