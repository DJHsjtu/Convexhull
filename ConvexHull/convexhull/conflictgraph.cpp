#include "conflictgraph.h"

conflictgraph::conflictgraph(DrawableDcel* dcel, std::vector<Pointd>verVect)
{

 this->dcel=dcel;
 this->verVect=verVect;
}

void conflictgraph::inizialize(){

    Eigen::Matrix4d matrix;


    for (Dcel::FaceIterator fit = dcel->faceBegin(); fit != dcel->faceEnd(); ++fit){

        Dcel::Face* f = *fit;
        Dcel::HalfEdge * halfEdge=f->getOuterHalfEdge();


        for(unsigned int i=0;i<3;i++){

            Pointd point= halfEdge->getFromVertex()->getCoordinate();

              matrix(i,0) = point.x();
              matrix(i,1) = point.y();
              matrix(i,2) = point.z();
              matrix(i,3) = 1;


              halfEdge = halfEdge->getNext();
        }

        for(unsigned int i=4; i<verVect.size(); i++){

            Pointd p=verVect[i];

            matrix(3,0) = p.x();
            matrix(3,1) = p.y();
            matrix(3,2) = p.z();
            matrix(3,3) = 1;

            if(!(matrix.determinant() > std::numeric_limits<double>::epsilon())){

               addFConflict_v(verVect[i],f);
               addVConflict_f(f,verVect[i]);

            }
        }
    }
}

    bool conflictgraph::isVisible(Pointd point, Dcel::Face* face){

        int index=0;
        Eigen::Matrix4Xd matrix;

        for(Dcel::Face::IncidentVertexIterator vit=face->incidentVertexBegin();vit!=face->incidentVertexEnd();++vit){

            Dcel::Vertex* vert =*vit;
            Pointd point= vert->getCoordinate();

            matrix(index,0) = point.x();
            matrix(index,1) = point.y();
            matrix(index,2) = point.z();
            matrix(index,3) = 1;

            index++;

        }


        matrix(3,0) = point.x();
        matrix(3,1) = point.y();
        matrix(3,2) = point.z();
        matrix(3,3) = 1;

        return !(matrix.determinant() > std::numeric_limits<double>::epsilon());

    }

    void conflictgraph::addFConflict_v(Pointd point , Dcel::Face* face){

        if(this->f_graph[point]==nullptr){

             this->f_graph[point]=new std::set<Dcel::Face*>;
        }

        this->f_graph.at(point)->insert(face);
    }
    void conflictgraph::addVConflict_f(Dcel::Face* face, Pointd point){

        if(this->v_graph[face]==nullptr){

             this->v_graph[face]=new std::set<Pointd>;
        }

        this->v_graph.at(face)->insert(point);
    }
