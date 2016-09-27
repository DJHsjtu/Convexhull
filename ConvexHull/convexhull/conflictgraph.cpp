#include "conflictgraph.h"

ConflictGraph::ConflictGraph(DrawableDcel* dcel, std::vector<Pointd>&verVect)
{

    this->dcel=dcel;
    this->verVect=verVect;
}

ConflictGraph::~ConflictGraph(){

    std::cout<<"Object conflictGraph is being deleted";

}

void ConflictGraph::inizialize(){

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

bool ConflictGraph::isVisible(Pointd point, Dcel::Face* face){

    int index=0;
    Eigen::Matrix4d mat;

    for(Dcel::Face::IncidentVertexIterator vit=face->incidentVertexBegin();vit!=face->incidentVertexEnd();++vit,index++

){

        Dcel::Vertex* vert =*vit;
        Pointd point= vert->getCoordinate();

        mat(index,0) = point.x();
        mat(index,1) = point.y();
        mat(index,2) = point.z();
        mat(index,3) = 1;


    }


    mat(3,0) = point.x();
    mat(3,1) = point.y();
    mat(3,2) = point.z();
    mat(3,3) = 1;

    return !(mat.determinant() > std::numeric_limits<double>::epsilon());

}

void ConflictGraph::addFConflict_v(Pointd point , Dcel::Face* face){

    if(this->f_graph[point]==nullptr){

        this->f_graph[point]=new std::set<Dcel::Face*>;
    }

    this->f_graph.at(point)->insert(face);
}

void ConflictGraph::addVConflict_f(Dcel::Face* face, Pointd point){

    if(this->v_graph[face]==nullptr){

        this->v_graph[face]=new std::set<Pointd>;
    }

    this->v_graph.at(face)->insert(point);
}

std::set<Dcel::Face*>* ConflictGraph::getFacesVisible(Pointd &vertex){

    std::set<Dcel::Face*>* faceList=this->f_graph[vertex];

    if(faceList==nullptr){

        faceList=new std::set<Dcel::Face*>;

        this->f_graph[vertex]=faceList;
    }

    return new std::set<Dcel::Face*>(*faceList);
}


std::set<Pointd>* ConflictGraph::getVerticesVisible(Dcel::Face* face){

    std::set<Pointd>* vectList=this->v_graph[face];

    if(vectList==nullptr){

        vectList=new std::set<Pointd>;

        this->v_graph[face]=vectList;
    }

    return new std::set<Pointd>(*vectList);
}

void ConflictGraph::deleteFaces(std::set<Dcel::Face *> *faces){
    // per ogni faccia elimino i vertici visibili dalla faccia da f_graph
    for(std::set<Dcel::Face*>::iterator fit = faces->begin(); fit != faces->end(); ++fit){
        Dcel::Face* currentFace=*fit;
        std::set<Pointd>* vertexFromRemoveFace = getVerticesVisible(currentFace);

        for(std::set<Pointd>::iterator vit=vertexFromRemoveFace->begin();vit!=vertexFromRemoveFace->end();++vit){

            Pointd currentPoint=*vit;
            f_graph.at(currentPoint)->erase(currentFace);
        }
        //elimino la faccia da v_graph
        v_graph.erase(currentFace);
    }
}

void ConflictGraph::deletePoint(Pointd &vertex){
    // per ogni vertice elimino le facce visibili dal vertice da v_graph

        std::set<Dcel::Face*>* faceFromRemoveVertex = getFacesVisible(vertex);

        for(std::set<Dcel::Face*>::iterator fit=faceFromRemoveVertex->begin();fit!=faceFromRemoveVertex->end();++fit){

            Dcel::Face* currentFace=*fit;
            v_graph.at(currentFace)->erase(vertex);
        }
        //elimino il vertice da f_graph
        f_graph.erase(vertex);
    }

void ConflictGraph::updateConflictGraph(Dcel::Face *face, std::set<Pointd> *vertices){


    for(std::set<Pointd>::iterator pit = vertices->begin(); pit != vertices->end(); ++pit){
            if(isVisible(*pit, face)){
                addFConflict_v(*pit, face);
                addVConflict_f(face, *pit);
            }
        }

}

