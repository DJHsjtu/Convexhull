#include "convexhullbuilder.h"


convexhullbuilder::convexhullbuilder(DrawableDcel * dcel)
{
    this->dcel = dcel;
    this->vect = std::vector<Pointd>();

}

void convexhullbuilder::build(MainWindow* mainWindow){

    getVertices();
    dcel->reset();
    permuteVertices();
    buildTetrahedron();

            }
void convexhullbuilder::build(){

    getVertices();
    dcel->reset();
    permuteVertices();
    buildTetrahedron();

            }


void::convexhullbuilder::getVertices(){

    for (Dcel::VertexIterator vit = this->dcel->vertexBegin(); vit != this->dcel->vertexEnd(); ++vit){

        Dcel::Vertex* v = *vit;
        this->vect.push_back(v->getCoordinate());

    }

    std::cout << "n vertices: " << vect.size();


}

void convexhullbuilder::permuteVertices(){

    Eigen::Matrix4d mat;
    double det;
    bool coplanar=true;

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(this->vect.begin(),this->vect.end(), g);

    do{
       for(unsigned int i=0;i<4;i++){

            mat(i,0)=this->vect[i].x();
            mat(i,1)=this->vect[i].y();
            mat(i,2)=this->vect[i].z();
            mat(i,3)=1;

        }

       det=mat.determinant();
       std::cout << "\ndeterminante : " << det;

        //finchè det <0 prendo altri punti dalla dcel

        coplanar= det < std::numeric_limits<double>::epsilon() && det > -std::numeric_limits<double>::epsilon();

         std::cout << "\ncomplanari? : " << coplanar;

         if(coplanar){

              std::cout<< "rimescolo";
              std::shuffle(this->vect.begin(),this->vect.end(), g);
         }
       }while(coplanar);

}

void convexhullbuilder::buildTetrahedron(){

       Dcel::Vertex* a = this->dcel->addVertex(this->vect[0]);
       Dcel::Vertex* b = this->dcel->addVertex(this->vect[1]);
       Dcel::Vertex* c = this->dcel->addVertex(this->vect[2]);
       Dcel::Vertex* d = this->dcel->addVertex(this->vect[3]);

       Dcel::HalfEdge* he1In = this->dcel->addHalfEdge();
       Dcel::HalfEdge* he2In = this->dcel->addHalfEdge();
       Dcel::HalfEdge* he3In = this->dcel->addHalfEdge();

       //check the orientation of the 4th point wrt the others
       //to determine the base face orientation

       if (checkOrientationToNormal()){

           he1In->setFromVertex(b);
           he1In->setToVertex(a);
           he1In->setNext(he3In);
           he1In->setPrev(he2In);

           he2In->setFromVertex(c);
           he2In->setToVertex(b);
           he2In->setNext(he1In);
           he2In->setPrev(he3In);

           he3In->setFromVertex(a);
           he3In->setToVertex(c);
           he3In->setNext(he2In);
           he3In->setPrev(he1In);

       } else {

           he1In->setFromVertex(a);
           he1In->setToVertex(b);
           he1In->setNext(he2In);
           he1In->setPrev(he3In);

           he2In->setFromVertex(b);
           he2In->setToVertex(c);
           he2In->setNext(he3In);
           he2In->setPrev(he1In);

           he3In->setFromVertex(c);
           he3In->setToVertex(a);
           he3In->setNext(he1In);
           he3In->setPrev(he2In);
       }

       a->setCardinality(2);
       b->setCardinality(2);
       c->setCardinality(2);

       Dcel::Face* face1 = this->dcel->addFace();
       face1->setOuterHalfEdge(he1In);
       he1In->setFace(face1);
       he2In->setFace(face1);
       he3In->setFace(face1);

       //add new faces connecting each half edge to the fourth vertex
       addOtherFaceTetrahedron(d, he1In);
       addOtherFaceTetrahedron(d, he2In);
       addOtherFaceTetrahedron(d, he3In);

}


void convexhullbuilder::addOtherFaceTetrahedron(Dcel::Vertex* otherVertex, Dcel::HalfEdge* existingHe){


      Dcel::HalfEdge* he1 = this->dcel->addHalfEdge();
      Dcel::HalfEdge* he2 = this->dcel->addHalfEdge();
      Dcel::HalfEdge* he3 = this->dcel->addHalfEdge();

      Dcel::Vertex* startVertex = existingHe->getFromVertex();
      Dcel::Vertex* endVertex = existingHe->getToVertex();

      he1->setFromVertex(endVertex);
      endVertex->setIncidentHalfEdge(he1);
      he1->setToVertex(startVertex);
      he1->setNext(he2);
      he1->setPrev(he3);
      he1->setTwin(existingHe);
      existingHe->setTwin(he1);
      endVertex->incrementCardinality();
      startVertex->incrementCardinality();

      he2->setFromVertex(startVertex);
      startVertex->setIncidentHalfEdge(he2);
      he2->setToVertex(otherVertex);
      he2->setNext(he3);
      he2->setPrev(he1);
      startVertex->incrementCardinality();
      otherVertex->incrementCardinality();

      //set the twin following the structure of the DCEL.
      //firstly they can be null but they will be all set when all the faces are created
      if(existingHe->getPrev()->getTwin() != nullptr){
          Dcel::HalfEdge* twin = existingHe->getPrev()->getTwin()->getPrev();
          he2->setTwin(twin);
          twin->setTwin(he2);
      }


      he3->setFromVertex(otherVertex);
      otherVertex->setIncidentHalfEdge(he3);
      he3->setToVertex(endVertex);
      he3->setNext(he1);
      he3->setPrev(he2);
      endVertex->incrementCardinality();
      otherVertex->incrementCardinality();

      //set the twin following the structure of the DCEL.
      //firstly they can be null but they will be all set when all the faces are created
      if(existingHe->getNext()->getTwin() != nullptr){
          Dcel::HalfEdge* twin = existingHe->getNext()->getTwin()->getNext();
          he3->setTwin(twin);
          twin->setTwin(he3);
      }


      Dcel::Face* face = this->dcel->addFace();
      face->setOuterHalfEdge(he1);
      he1->setFace(face);
      he2->setFace(face);
      he3->setFace(face);

}

bool convexhullbuilder::checkOrientationToNormal(){

    Eigen::Matrix4d matrix;

    for(unsigned int i=0; i<4; i++){
        matrix(i, 0) = this->vect[i].x();
        matrix(i, 1) = this->vect[i].y();
        matrix(i, 2) = this->vect[i].z();
        matrix(i, 3) = 1;
    }

    double det = matrix.determinant();

    if(det < -std::numeric_limits<double>::epsilon()){

        return true;

    }
    else {
        return false;
    }


}



