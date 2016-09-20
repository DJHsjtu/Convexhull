#ifndef CONFLICTGRAPH_H
#define CONFLICTGRAPH_H

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/LU>
#include "GUI/managers/dcelmanager.h"
#include "lib/dcel/drawable_dcel.h"
#include "lib/common/point.h"
#include "stdlib.h"
#include <random>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
#include "GUI/mainwindow.h"

class conflictgraph
{
public:

    conflictgraph(DrawableDcel* dcel, std::vector<Pointd>verVect);
    void inizialize();
    bool isVisible(Pointd point, Dcel::Face * face);

private:

    DrawableDcel * dcel;
    std::vector<Pointd> verVect;
    std::map<Dcel::Face*, std::set<Pointd>*> v_graph;
    std::map<Pointd ,std::set<Dcel::Face*>*> f_graph;

    void addFConflict_v(Pointd point, Dcel::Face* face);
    void addVConflict_f(Dcel::Face* face, Pointd point);
};

#endif // CONFLICTGRAPH_H
