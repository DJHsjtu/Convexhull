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
#include "GUI/mainwindow.h"

class convexhullbuilder
{
public:
    convexhullbuilder(DrawableDcel* dcel);
    void build();
   void build(MainWindow * mainWindow);

private:

    DrawableDcel * dcel;
    std::vector<Pointd> vect;

    void getVertices();
    void permuteVertices();
    void buildTetrahedron();
    void addOtherFaceTetrahedron(Dcel::Vertex* otherVertex, Dcel::HalfEdge* existingHe);
    bool checkOrientationToNormal();

};


#endif // CONVEXHULLBUILDER_H
