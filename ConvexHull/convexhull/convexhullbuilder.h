#ifndef CONVEXHULLBUILDER_H
#define CONVEXHULLBUILDER_H


#include "lib/dcel/drawable_dcel.h"
#include <stdlib.h>
#include "GUI/mainwindow.h"
#include <vector>
#include <algorithm>
#include <random>
#include <eigen3/Eigen/Dense>
#include "conflictgraph.h"


class ConvexhullBuilder
{
public:
    ConvexhullBuilder(DrawableDcel* dcel, MainWindow* mainwindow, bool isChecked);
    ~ConvexhullBuilder();
    void buildConvexHull();
    void stepUpdate();
    void getVertices();
    bool validPermutation();
    void buildTetrahedon();
    void removeVisibleFaces(std::set<Dcel::Face*> *visibleFaces);
    std::vector<Dcel::Face*> createNewFaces(Dcel::Vertex* inputVertex,std::list<Dcel::HalfEdge*> horizon);
    std::list<Dcel::HalfEdge*> buildHorizon(std::set<Dcel::Face*> *visibleFaces);

private:
    DrawableDcel *dcel;
    std::vector<Pointd> vectPoint;
    ConflictGraph* conflictGraph;
    MainWindow* mainWindow;
    bool isChecked;  
};

#endif // CONVEXHULLBUILDER_H
