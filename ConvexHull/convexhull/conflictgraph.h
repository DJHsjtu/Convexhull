#ifndef CONFLICTGRAPH_H
#define CONFLICTGRAPH_H

#include "lib/dcel/drawable_dcel.h"
#include <stdlib.h>
#include "GUI/mainwindow.h"
#include <algorithm>
#include <random>
#include <eigen3/Eigen/Dense>

class ConflictGraph
{
public:
    ConflictGraph(DrawableDcel* dcel, const std::vector<Pointd> &vectPoint);
    ~ConflictGraph();
    void inizialize();
    bool faceVisibleFromPoint(const Pointd point, Dcel::Face * face);
    std::set<Dcel::Face*>* findVisibleFaces(const Pointd &point);
    std::set<Pointd>* findVisiblePoints(Dcel::Face* face);
    std::map<Dcel::HalfEdge*, std::set<Pointd>*>mergeVerticesVisible(const std::list<Dcel::HalfEdge*> &horizon);
    void deleteFaces(std::set<Dcel::Face *> *faces);
    void deletePoint(Pointd &point);
    void updateConflictGraph(Dcel::Face * face, const Pointd point);


  private:

      DrawableDcel* dcel;
      std::vector<Pointd> vectPoint;
      std::map<Dcel::Face*, std::set<Pointd>*> p_graph;
      std::map<Pointd ,std::set<Dcel::Face*>*> f_graph;

      void addFConflict_p(const Pointd &point, Dcel::Face* face);
      void addPConflict_f(Dcel::Face* face, const Pointd &point);



  };
#endif // CONFLICTGRAPH_H
