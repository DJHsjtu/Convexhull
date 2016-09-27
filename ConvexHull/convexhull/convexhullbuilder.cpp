#include "convexhullbuilder.h"


Convexhullbuilder::Convexhullbuilder(DrawableDcel * dcel, bool isChecked)
{
    this->dcel = dcel;
    this->vect = std::vector<Pointd>();
    this->isChecked=isChecked;

}
Convexhullbuilder::~Convexhullbuilder(){

    std::cout<<"Object CHbuilder is being deleted";

}

void Convexhullbuilder::build(MainWindow* mainWindow){

    getVertices();
    dcel->reset();
    permuteVertices();
    buildTetrahedron();

    conflictGraph=new ConflictGraph(this->dcel,this->vect);
    conflictGraph->inizialize();


    for(unsigned int i=4;i<vect.size();i++){

        Pointd currentVertex=vect[i];

        std::set<Dcel::Face*>* facesToRemoveVertex=conflictGraph->getFacesVisible(currentVertex);


        if(facesToRemoveVertex->size()>0){

            Dcel::Vertex* newVertex=dcel->addVertex(currentVertex);

            std::list<Dcel::HalfEdge*> horizon=getHorizon(facesToRemoveVertex);

            std::map<Dcel::HalfEdge*, std::set<Pointd>*> vertexMapfromHorizon=getVertexMapFromHorizon(horizon);

            conflictGraph->deleteFaces(facesToRemoveVertex);
            removeVisibleFaces(facesToRemoveVertex);
            if(isChecked){
                usleep(400);

                dcel->update();
                mainWindow->updateGlCanvas();
            }

            std::vector<Dcel::Face*> newFacestoBuild;

            for(std::list<Dcel::HalfEdge*>::iterator hit = horizon.begin(); hit != horizon.end(); ++hit){
                Dcel::HalfEdge* halfEdge = *hit;

                //crea nuova faccia da aggiungere al vettore
                Dcel::Face* newFace = addNewFaces(newVertex, halfEdge);
                newFacestoBuild.push_back(newFace);

                //aggiorno il conflict graph
                conflictGraph->updateConflictGraph(newFace, vertexMapfromHorizon[halfEdge]);
            }
            setTwins(newFacestoBuild);


        }
        if(isChecked){
            usleep(400);

            dcel->update();
            mainWindow->updateGlCanvas();
        }

        conflictGraph->deletePoint(vect[i]);

    }


}


void::Convexhullbuilder::getVertices(){

    for (Dcel::VertexIterator vit = this->dcel->vertexBegin(); vit != this->dcel->vertexEnd(); ++vit){

        Dcel::Vertex* v = *vit;
        this->vect.push_back(v->getCoordinate());

    }

}

void Convexhullbuilder::permuteVertices(){

    Eigen::Matrix4d mat;
    double det;
    bool coplanar=false;

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

        //finchè det <0 prendo altri punti dalla dcel
        if(det < std::numeric_limits<double>::epsilon() && det > -std::numeric_limits<double>::epsilon()){


            coplanar=true;
        }


        if(coplanar){

            std::cout<< "rimescolo";
            std::shuffle(this->vect.begin(),this->vect.end(), g);
        }
    }while(coplanar);

}

void Convexhullbuilder::buildTetrahedron(){

    Dcel::Vertex* v1 = this->dcel->addVertex(this->vect[0]);
    Dcel::Vertex* v2 = this->dcel->addVertex(this->vect[1]);
    Dcel::Vertex* v3 = this->dcel->addVertex(this->vect[2]);
    Dcel::Vertex* v4 = this->dcel->addVertex(this->vect[3]);

    Dcel::HalfEdge* halfEdge1 = this->dcel->addHalfEdge();
    Dcel::HalfEdge* halfEdge2 = this->dcel->addHalfEdge();
    Dcel::HalfEdge* halfEdge3 = this->dcel->addHalfEdge();

    //controllo l'orientamento del quarto punto rispetto agli altri per vedere il verso della faccia
    if (checkOrientationToNormal()){

        halfEdge1->setFromVertex(v2);
        halfEdge1->setToVertex(v1);
        halfEdge1->setNext(halfEdge3);
        halfEdge1->setPrev(halfEdge2);

        halfEdge2->setFromVertex(v3);
        halfEdge2->setToVertex(v2);
        halfEdge2->setNext(halfEdge1);
        halfEdge2->setPrev(halfEdge3);

        halfEdge3->setFromVertex(v1);
        halfEdge3->setToVertex(v3);
        halfEdge3->setNext(halfEdge2);
        halfEdge3->setPrev(halfEdge1);

    } else {

        halfEdge1->setFromVertex(v1);
        halfEdge1->setToVertex(v2);
        halfEdge1->setNext(halfEdge2);
        halfEdge1->setPrev(halfEdge3);

        halfEdge2->setFromVertex(v2);
        halfEdge2->setToVertex(v3);
        halfEdge2->setNext(halfEdge3);
        halfEdge2->setPrev(halfEdge1);

        halfEdge3->setFromVertex(v3);
        halfEdge3->setToVertex(v1);
        halfEdge3->setNext(halfEdge1);
        halfEdge3->setPrev(halfEdge2);
    }

    Dcel::Face* face1 = this->dcel->addFace();
    face1->setOuterHalfEdge(halfEdge1);
    halfEdge1->setFace(face1);
    halfEdge2->setFace(face1);
    halfEdge3->setFace(face1);

    v1->setCardinality(2);
    v2->setCardinality(2);
    v3->setCardinality(2);

    addOtherFaceTetrahedron(v4, halfEdge1);
    addOtherFaceTetrahedron(v4, halfEdge2);
    addOtherFaceTetrahedron(v4, halfEdge3);

}


void Convexhullbuilder::addOtherFaceTetrahedron(Dcel::Vertex* inputVertex, Dcel::HalfEdge* existingHe){


    Dcel::HalfEdge* halfEdge1 = this->dcel->addHalfEdge();
    Dcel::HalfEdge* halfEdge2 = this->dcel->addHalfEdge();
    Dcel::HalfEdge* halfEdge3 = this->dcel->addHalfEdge();

    Dcel::Vertex* startVertex = existingHe->getFromVertex();
    Dcel::Vertex* endVertex = existingHe->getToVertex();

    halfEdge1->setFromVertex(endVertex);
    endVertex->setIncidentHalfEdge(halfEdge1);
    halfEdge1->setToVertex(startVertex);
    halfEdge1->setNext(halfEdge2);
    halfEdge1->setPrev(halfEdge3);
    halfEdge1->setTwin(existingHe);
    existingHe->setTwin(halfEdge1);
    endVertex->incrementCardinality();
    startVertex->incrementCardinality();

    halfEdge2->setFromVertex(startVertex);
    startVertex->setIncidentHalfEdge(halfEdge2);
    halfEdge2->setToVertex(inputVertex);
    halfEdge2->setNext(halfEdge3);
    halfEdge2->setPrev(halfEdge1);
    startVertex->incrementCardinality();
    inputVertex->incrementCardinality();

    //seguendo la dcel setto i twin
    if(existingHe->getPrev()->getTwin() != nullptr){
        Dcel::HalfEdge* twin = existingHe->getPrev()->getTwin()->getPrev();
        halfEdge2->setTwin(twin);
        twin->setTwin(halfEdge2);
    }


    halfEdge3->setFromVertex(inputVertex);
    inputVertex->setIncidentHalfEdge(halfEdge3);
    halfEdge3->setToVertex(endVertex);
    halfEdge3->setNext(halfEdge1);
    halfEdge3->setPrev(halfEdge2);
    endVertex->incrementCardinality();
    inputVertex->incrementCardinality();

    if(existingHe->getNext()->getTwin() != nullptr){
        Dcel::HalfEdge* twin = existingHe->getNext()->getTwin()->getNext();
        halfEdge3->setTwin(twin);
        twin->setTwin(halfEdge3);
    }


    Dcel::Face* face = this->dcel->addFace();
    face->setOuterHalfEdge(halfEdge1);
    halfEdge1->setFace(face);
    halfEdge2->setFace(face);
    halfEdge3->setFace(face);

}

Dcel::Face* Convexhullbuilder::addNewFaces(Dcel::Vertex* inputVertex, Dcel::HalfEdge* existingHe){

    Dcel::HalfEdge* halfEdge1 = this->dcel->addHalfEdge();
    Dcel::HalfEdge* halfEdge2 = this->dcel->addHalfEdge();
    Dcel::HalfEdge* halfEdge3 = this->dcel->addHalfEdge();

    Dcel::Vertex* startVertex = existingHe->getFromVertex();
    Dcel::Vertex* endVertex = existingHe->getToVertex();

    halfEdge1->setFromVertex(endVertex);
    endVertex->setIncidentHalfEdge(halfEdge1);
    halfEdge1->setToVertex(startVertex);
    halfEdge1->setNext(halfEdge2);
    halfEdge1->setPrev(halfEdge3);
    halfEdge1->setTwin(existingHe);
    existingHe->setTwin(halfEdge1);
    endVertex->incrementCardinality();
    startVertex->incrementCardinality();

    halfEdge2->setFromVertex(startVertex);
    startVertex->setIncidentHalfEdge(halfEdge2);
    halfEdge2->setToVertex(inputVertex);
    halfEdge2->setNext(halfEdge3);
    halfEdge2->setPrev(halfEdge1);
    startVertex->incrementCardinality();
    inputVertex->incrementCardinality();

    halfEdge3->setFromVertex(inputVertex);
    inputVertex->setIncidentHalfEdge(halfEdge3);
    halfEdge3->setToVertex(endVertex);
    halfEdge3->setNext(halfEdge1);
    halfEdge3->setPrev(halfEdge2);
    endVertex->incrementCardinality();
    inputVertex->incrementCardinality();

    Dcel::Face* face = this->dcel->addFace();
    face->setOuterHalfEdge(halfEdge1);
    halfEdge1->setFace(face);
    halfEdge2->setFace(face);
    halfEdge3->setFace(face);


    return face;

}


bool Convexhullbuilder::checkOrientationToNormal(){

    Eigen::Matrix4d mat;

    for(unsigned int i=0; i<4; i++){
        mat(i, 0) = this->vect[i].x();
        mat(i, 1) = this->vect[i].y();
        mat(i, 2) = this->vect[i].z();
        mat(i, 3) = 1;
    }

    double det = mat.determinant();

    if(det < -std::numeric_limits<double>::epsilon()){

        return true;

    }
    else {
        return false;
    }


}

std::list<Dcel::HalfEdge*> Convexhullbuilder::getHorizon(std::set<Dcel::Face*>* facesVisibleFromVertex){


    std::list<Dcel::HalfEdge*> horizon;
    Dcel::HalfEdge * firstHorizonHe;

    bool found=false;

    //scorro le facce visibili eprendo gli incident half edge
    for(std::set<Dcel::Face*>::iterator fit=facesVisibleFromVertex->begin();fit!=facesVisibleFromVertex->end();++fit){

        Dcel::Face *faceVisible=*fit;


        for(Dcel::Face::IncidentHalfEdgeIterator iheit=faceVisible->incidentHalfEdgeBegin();iheit!=faceVisible->incidentHalfEdgeEnd();++iheit){

            Dcel::HalfEdge * firstVisibleHe= *iheit;
            if(firstVisibleHe->getTwin() != nullptr){
                //se il twin di un half edge visibile ha la faccia incidente nell'insieme di facce non visibili, è parte dell'orizzionte
                if(facesVisibleFromVertex->count(firstVisibleHe->getTwin()->getFace())==0){

                    firstHorizonHe=firstVisibleHe->getTwin();
                    found=true;
                }
            }
        }
    }

    if(found){

        //dobbiamo scorrere le facce a partire dal primo half edge dell'orizzonte trovato,per trovare tutto l'orizzonte
        Dcel::Face *incidentFace;

        Dcel::HalfEdge *currentHe;
        Dcel::HalfEdge *nextHe;
        Dcel::HalfEdge *twinOfNextHe;


        currentHe=firstHorizonHe;
        horizon.push_front(firstHorizonHe);
        //ciclo fino a che non torno al he di partenza dell'orizzonte

        do{

            nextHe=currentHe->getNext();
            twinOfNextHe=nextHe->getTwin();
            incidentFace=twinOfNextHe->getFace();
            //se la faccia incidente del twin del next he è visibile, fa parte dell'orizzonte
            if(facesVisibleFromVertex->count(incidentFace)==1){

                horizon.push_back(nextHe);
                currentHe=nextHe;
            }
            else{
                currentHe=twinOfNextHe;
            }
        }
        while(currentHe!=firstHorizonHe && firstHorizonHe!= currentHe->getNext());
    }

    return horizon;

}

std::map<Dcel::HalfEdge*, std::set<Pointd>*> Convexhullbuilder::getVertexMapFromHorizon(std::list<Dcel::HalfEdge*> horizon){

    std::map<Dcel::HalfEdge *, std::set<Pointd>*> mapVertexResult;

    //scorro l'orizzionte, e prendo i vertici in conflitto con le facce incidenti agli half edge e ai twin di quegli half edge
    //e li metto nella mappa relativa al singolo half edge considerato
    for(std::list<Dcel::HalfEdge*>::iterator hit = horizon.begin(); hit != horizon.end(); ++hit){

        Dcel::HalfEdge* currentHalfEdge = *hit;



        std::set<Pointd> * VFromFaceHorizon=conflictGraph->getVerticesVisible(currentHalfEdge->getFace());
        std::set<Pointd> * VFromFaceTwinHorizon=conflictGraph->getVerticesVisible(currentHalfEdge->getTwin()->getFace());

        VFromFaceTwinHorizon->insert(VFromFaceHorizon->begin(),VFromFaceHorizon->end());
        mapVertexResult[currentHalfEdge]=VFromFaceTwinHorizon;
    }

    return mapVertexResult;
}

void Convexhullbuilder::removeVisibleFaces(std::set<Dcel::Face *> *faces){

    for(std::set<Dcel::Face*>::iterator it = faces->begin(); it != faces->end(); ++it){

        Dcel::Face* face = *it;

        //Scorro tutta la faccia
        for(Dcel::Face::IncidentHalfEdgeIterator vit = face->incidentHalfEdgeBegin(); vit != face->incidentHalfEdgeEnd(); ++vit){

            Dcel::HalfEdge* he = *vit;

            Dcel::Vertex* fromVertex = he->getFromVertex();
            Dcel::Vertex* toVertex   = he->getToVertex();

            //elimino l'half edge corrente dalla dcel
            this->dcel->deleteHalfEdge(he);

            //Decremento la cardinalità dei vertici in cui ho eliminato l'half edge
            fromVertex -> decrementCardinality();
            toVertex   -> decrementCardinality();

            //quando i vertici hanno raggiunto la cardinalità 0, vuol dire che sono più necessari alla dcel e gli inserisco nella lista
            if(fromVertex->getCardinality() == 0){
                this->dcel->deleteVertex(fromVertex);
            }
            if(toVertex->getCardinality() == 0){
                this->dcel->deleteVertex(toVertex);
            }
        }

        //elimino la faccia dalla dcel
        this -> dcel -> deleteFace(face);
    }
}

void Convexhullbuilder::setTwins(std::vector<Dcel::Face*> &faceList){

    std::vector<Dcel::HalfEdge*> he1Vector(faceList.size());
    std::vector<Dcel::HalfEdge*> he2Vector(faceList.size());
    std::vector<Dcel::HalfEdge*> he3Vector(faceList.size());

    for(unsigned int i=0; i<faceList.size(); i++){
        he1Vector[i] = faceList[i]->getOuterHalfEdge();
        he2Vector[i] = faceList[i]->getOuterHalfEdge()->getNext();
        he3Vector[i] = faceList[i]->getOuterHalfEdge()->getNext()->getNext();
    }

    for(unsigned int i=1; i<=faceList.size(); i++){
        he2Vector[i%faceList.size()]->setTwin(he3Vector[i-1]);
        he3Vector[i-1]->setTwin(he2Vector[i%faceList.size()]);
    }
}



