#ifndef CONVEXHULLBUILDER_H
#define CONVEXHULLBUILDER_H

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
#include "conflictgraph.h"
#include "GUI/mainwindow.h"

class Convexhullbuilder
{
public:
    Convexhullbuilder(DrawableDcel* dcel,bool isChecked);
    ~Convexhullbuilder();
    void build(MainWindow * mainWindow);

private:

    DrawableDcel * dcel;
    std::vector<Pointd> vect;
    ConflictGraph *conflictGraph;
    bool isChecked;
    void getVertices();
    void permuteVertices();
    void buildTetrahedron();
    void addOtherFaceTetrahedron(Dcel::Vertex* otherVertex, Dcel::HalfEdge* existingHe);
    Dcel::Face* addNewFaces(Dcel::Vertex* otherVertex, Dcel::HalfEdge* existingHe);
    void setTwins(std::vector<Dcel::Face*> &faceList);
    bool checkOrientationToNormal();
    std::list<Dcel::HalfEdge*> getHorizon(std::set<Dcel::Face*> *facesVisibleFromVertex);
    std::map<Dcel::HalfEdge *, std::set<Pointd> *> getVertexMapFromHorizon(std::list<Dcel::HalfEdge*> horizon);
    void removeVisibleFaces(std::set<Dcel::Face*>* faces);

};


#endif // CONVEXHULLBUILDER_H
