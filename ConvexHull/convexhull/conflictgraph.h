#ifndef CONFLICTGRAPH_H
#define CONFLICTGRAPH_H

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/LU>
#include "lib/dcel/drawable_dcel.h"
#include "stdlib.h"


class ConflictGraph
{
public:

    ConflictGraph(DrawableDcel* dcel, std::vector<Pointd>&verVect);
    ~ConflictGraph();
    void inizialize();
    bool isVisible(Pointd point, Dcel::Face * face);
    std::set<Dcel::Face*>* getFacesVisible(Pointd &vertex);
    std::set<Pointd>* getVerticesVisible(Dcel::Face* face);
    void deleteFaces(std::set<Dcel::Face *> *faces);
    void deletePoint(Pointd &vertex);
    void updateConflictGraph(Dcel::Face * face, std::set<Pointd> * candidateVertices);



private:

    DrawableDcel * dcel;
    std::vector<Pointd> verVect;
    std::map<Dcel::Face*, std::set<Pointd>*> v_graph;
    std::map<Pointd ,std::set<Dcel::Face*>*> f_graph;

    void addFConflict_v(Pointd point, Dcel::Face* face);
    void addVConflict_f(Dcel::Face* face, Pointd point);



};

#endif // CONFLICTGRAPH_H
