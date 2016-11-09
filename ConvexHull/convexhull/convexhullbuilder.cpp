#include "convexhullbuilder.h"

/** La classe ConvexhullBuilder è la classe principale per la creazione del convexhull. Si segue passo passo l'algoritmo visto,a partire
 * dalla creazione del tetraedro dai primi 4 vertici non coplanari della dcel fino all'eliminazione del punto corrente dal conflictGraph,
 * passando dalla creazione degli halfEdge dell'orizzonte. Il metodo principale è buildConvexhull(). La gestione del conflictGraph è affidata
 * a un'altra classe.
**/

/**
 * @brief ConvexhullBuilder::ConvexhullBuilder costruttore della classe ConvexhullBuilder
 * @param dcel dcel iniziale
 * @param mainWindow finestra principale dell'UI
 * @param isChecked flag per aggiornamento della visualizzazione della dcel
 */
ConvexhullBuilder::ConvexhullBuilder(DrawableDcel* dcel, MainWindow* mainWindow, bool isChecked)
{

    this->dcel=dcel;
    this->mainWindow=mainWindow;
    this->isChecked=isChecked;

}

ConvexhullBuilder::~ConvexhullBuilder(){


}
/**
*@brief ConvexhullBuilder::getVertices copia i vertici della dcel in un vettore di punti
*
*/
void ConvexhullBuilder::getVertices(){

    for(auto viter=this->dcel->vertexBegin();viter!=this->dcel->vertexEnd();++viter){

        Dcel::Vertex* v=*viter;
        this->vectPoint.push_back(v->getCoordinate());
    }
}
/**
*@brief ConvexhullBuilder::validPermutation cerca i primi 4 punti da usare per costruire il tetraedro
*@return true se i vertici trovati non sono coplanari, false altrimenti
*/

bool ConvexhullBuilder::validPermutation(){

    Eigen::Matrix4d mat;
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(this->vectPoint.begin(),this->vectPoint.end(), g);

    for(unsigned int i=0;i<4;i++){
        mat(i,0)=this->vectPoint[i].x();
        mat(i,1)=this->vectPoint[i].y();
        mat(i,2)=this->vectPoint[i].z();
        mat(i,3)=1;
    }
    double det=mat.determinant();
    //false se sono coplanari, true altrimenti
    return !(det < std::numeric_limits<double>::epsilon() && det > -std::numeric_limits<double>::epsilon());
}

/**
 * @brief ConvexhullBuilder::buildTetrahedon costruisce il tetraedro usando i primi 4 punti della dcel
 *
 */
void ConvexhullBuilder::buildTetrahedon(){

    Eigen::Matrix4d mat;
    //reupero i primi 4 punti del vettore
    for(unsigned int i=0; i<4; i++){
        mat(i, 0) = this->vectPoint[i].x();
        mat(i, 1) = this->vectPoint[i].y();
        mat(i, 2) = this->vectPoint[i].z();
        mat(i, 3) = 1;
    }

    double det = mat.determinant();

    Dcel::Vertex* v1;
    Dcel::Vertex* v2;
    Dcel::Vertex* v3;
    Dcel::Vertex* v4;

    //controllo l'orientamento dei vertici per settare la prima faccia opportunamente
    if(det < -std::numeric_limits<double>::epsilon()){

        v1=this->dcel->addVertex(this->vectPoint[2]);
        v2=this->dcel->addVertex(this->vectPoint[1]);
        v3=this->dcel->addVertex(this->vectPoint[0]);
        v4=this->dcel->addVertex(this->vectPoint[3]);
    }
    else{

        v1=this->dcel->addVertex(this->vectPoint[0]);
        v2=this->dcel->addVertex(this->vectPoint[1]);
        v3=this->dcel->addVertex(this->vectPoint[2]);
        v4=this->dcel->addVertex(this->vectPoint[3]);
    }

    //ogni faccia ha tre halfEdge, tre vertici e una faccia
    Dcel::HalfEdge* he1=this->dcel->addHalfEdge();
    Dcel::HalfEdge* he2=this->dcel->addHalfEdge();
    Dcel::HalfEdge* he3=this->dcel->addHalfEdge();

    Dcel::Face* face=this->dcel->addFace();

    //settaggio opportuno dei parametri
    face->setOuterHalfEdge(he1);

    he1->setFace(face);
    he1->setFromVertex(v1);
    he1->setToVertex(v2);
    he1->setNext(he2);
    he1->setPrev(he3);
    v1->setIncidentHalfEdge(he1);

    he2->setFace(face);
    he2->setFromVertex(v2);
    he2->setToVertex(v3);
    he2->setNext(he3);
    he2->setPrev(he1);
    v2->setIncidentHalfEdge(he2);


    he3->setFace(face);
    he3->setFromVertex(v3);
    he3->setToVertex(v1);
    he3->setNext(he1);
    he3->setPrev(he2);
    v3->setIncidentHalfEdge(he3);

    v1->setCardinality(2);
    v2->setCardinality(2);
    v3->setCardinality(2);

    //costruisco la lista di halfEdge da passare alla funzione di creazione delle facce
    std::list<Dcel::HalfEdge*> heList;
    heList.push_back(he1);
    heList.push_back(he2);
    heList.push_back(he3);

    createNewFaces(v4,heList);
}
/**
 * @brief ConvexhullBuilder::buildConvexHull è il metodo principale per la costruzione del convexhull.
 */
void ConvexhullBuilder::buildConvexHull(){
    //recupero i vertici dalla dcel e li copio in un vettore di punti
    getVertices();

    //reset della dcel
    this->dcel->reset();

    //mi assicuro che i primi 4 vertici non siano coplanari
    bool isValid=false;
    do{
        isValid=validPermutation();
    }
    while(!isValid);

    //costruisco tetraedro iniziale
    buildTetrahedon();

    //inizializzo conflictGraph
    conflictGraph=new ConflictGraph(this->dcel,this->vectPoint);
    conflictGraph->inizialize();

    //a partire dal 5 punto del vettore di punti
    for(unsigned int i=4;i<vectPoint.size();i++){

        Pointd point=this->vectPoint[i];
        //prendo le facce visibili dal nuovo punto
        std::set<Dcel::Face*>*facesVisible=conflictGraph->findVisibleFaces(point);

        if(facesVisible->size() >0){

            //aggiungo come vertice alla dcel il punto corrente
            Dcel::Vertex* newVertex=this->dcel->addVertex(point);

            std::list<Dcel::HalfEdge*> horizon;

            //costruisco l'orizzonte a partire dalle facce visibili
            horizon=buildHorizon(facesVisible);

            //per ogni halfEdge dell'orizzonte, ho un set di punti visibili dalla faccia di qull'halfEdge e del suo twin,serve
            //per l'aggiornamento più veloce del conflictGraph
            std::map<Dcel::HalfEdge*, std::set<Pointd>*> verticesVisible=conflictGraph->mergeVerticesVisible(horizon);

            //elimino facce visibili dal conflict graph e dalla dcel
            removeVisibleFaces(facesVisible);

            //creo nuove facce,a partire dal nuovo vertice e gli halfEdge dell'orizzonte
            std::vector<Dcel::Face*> faces=createNewFaces(newVertex,horizon);

            //per ogni halhEdge dell'orizzonte
            for(auto heit=horizon.begin();heit!=horizon.end();++heit){

                Dcel::HalfEdge* halfEdge=*heit;

                //recupero i punti che potrebbero essere visibili dall'halfEdge dell'orizzonte e dal suo twin
                std::set<Pointd> *points=verticesVisible[halfEdge];

                //per ogni faccia creata
                unsigned int j=0;
                for(j=0;j<faces.size();j++){

                    //per ogni punto che potrebbe vedere la faccia
                    for(auto pit=points->begin();pit!=points->end();++pit){

                        //aggiorno il conflictGraph
                        conflictGraph->updateConflictGraph(faces[j],*pit);

                    }

                }
            }
        }
        //se il checkbox sulla visualizzazione incrementale dell'algoritmo è settato, aggiorno la visualizzazione della dcel
        if(isChecked){

            stepUpdate();
        }

        //elimino il punto corrente dal conflictGraph
        conflictGraph->deletePoint(this->vectPoint[i]);

    }
}

/**
 * @brief ConvexhullBuilder::createNewFaces aggiunge nuove facce alla dcel, tante quanti sono gli halfEdge passati in input
 * @param inputVertex vertice corrente
 * @param horizon lista di halfEdge
 * @return vettore di facce appena create
 */
std::vector<Dcel::Face*> ConvexhullBuilder::createNewFaces(Dcel::Vertex *inputVertex, std::list<Dcel::HalfEdge*> horizon) {

    std::vector<Dcel::Face*> faces;

    //scorro sulla lista di halfEdge
    for(auto heit=horizon.begin();heit!=horizon.end();++heit){

        Dcel::HalfEdge* currHe= *heit;
        //uso i due vertici dell'halfedge considerato come due vertici per costruirmi la nuova faccia
        Dcel::Vertex* v1=currHe->getToVertex();
        Dcel::Vertex* v2=currHe->getFromVertex();

        Dcel::HalfEdge* he1=this->dcel->addHalfEdge();
        Dcel::HalfEdge* he2=this->dcel->addHalfEdge();
        Dcel::HalfEdge* he3=this->dcel->addHalfEdge();

        Dcel::Face* face=this->dcel->addFace();

        //settaggio opportuno dei parametri
        face->setOuterHalfEdge(he1);

        he1->setFace(face);
        he1->setTwin(currHe);
        currHe->setTwin(he1);
        he1->setFromVertex(v1);
        he1->setToVertex(v2);
        he1->setNext(he2);
        he1->setPrev(he3);
        v1->setIncidentHalfEdge(he1);
        v1->incrementCardinality();
        v2->incrementCardinality();

        he2->setFace(face);
        he2->setFromVertex(v2);
        he2->setToVertex(inputVertex);
        he2->setNext(he3);
        he2->setPrev(he1);
        v2->setIncidentHalfEdge(he2);
        v2->incrementCardinality();
        inputVertex->incrementCardinality();

        he3->setFace(face);
        he3->setFromVertex(inputVertex);
        he3->setToVertex(v1);
        he3->setNext(he1);
        he3->setPrev(he2);
        inputVertex->setIncidentHalfEdge(he3);
        inputVertex->incrementCardinality();
        v1->incrementCardinality();

        faces.push_back(face);


    }

    //setto i twin secondo la regola: il secondo half edge della faccia corrente
    //ha come twin il terzo half edge della faccia precedente
    for(unsigned int i=1;i<=faces.size();i++){

        //uso il modulo per ritornare alla faccia iniziale
        Dcel::HalfEdge* nextOfOuter=faces[i% faces.size()]->getOuterHalfEdge()->getNext();
        Dcel::HalfEdge* prevOfOuterPrevFace=faces[i-1]->getOuterHalfEdge()->getPrev();

        nextOfOuter->setTwin(prevOfOuterPrevFace);
        prevOfOuterPrevFace->setTwin(nextOfOuter);
    }

    return faces;
}

/**
 * @brief ConvexhullBuilder::buildHorizon costruisce gli half edge dell'orizzonte e ne restituisce la lista ordinata.
 * @param visibleFaces la lista di facce visibili
 * @return lista di halfEdge ordinata
 */
std::list<Dcel::HalfEdge*> ConvexhullBuilder::buildHorizon(std::set<Dcel::Face *> *visibleFaces){

    std::vector<Dcel::HalfEdge*> horizon_unordered;
    std::list<Dcel::HalfEdge*> horizon_ordered;

    //scorro tra le facce visibili
    for(auto fit=visibleFaces->begin();fit!=visibleFaces->end();++fit){

        Dcel::Face* currFace=*fit;
        //per ogni halfEdge della faccia, controllo se il suo twin appartiene a una faccia non visibile,in caso affermativo il twin
        //fa parte dell'orizzonte
        for(auto heit=currFace->incidentHalfEdgeBegin();heit!=currFace->incidentHalfEdgeEnd();++heit){

            Dcel::HalfEdge* currHe=*heit;

            if(currHe->getTwin()!=nullptr){

                if(visibleFaces->count(currHe->getTwin()->getFace())==0){

                    horizon_unordered.push_back(currHe->getTwin());

                }

            }
        }
    }

    int index=0;
    int i=0;
    int size=horizon_unordered.size();


    for(int count=0;count<size;count++){

        //controllo ogni halfEdge dell'orizzonte disordinato con il suo successivo, facendo il check su fromVertex() del successivo
        //e toVertex() di quello corrente.
        if(index==0){

            Dcel::HalfEdge* currHe=horizon_unordered[i%size];

            for(int count=0;count<size;count++){

                if(currHe->getToVertex()==horizon_unordered[(count+1)%size]->getFromVertex()){
                    //appena lo trovo lo inserisco nell'orizzonte ordinato
                    horizon_ordered.push_back(horizon_unordered[(count+1)%size]);

                    index++;
                }
            }
            i++;
        }
        else{

            //appena ne trovo uno controllo fromVertex() e toVertex() tra ultimo halfEdge inserito nell'orizzonte ordinato e tutti quelli
            // di quello non ordinato
            Dcel::HalfEdge* currHe=horizon_ordered.back();

            for(int count=0;count<size;count++){

                if(currHe->getToVertex()==horizon_unordered[(count+1)%size]->getFromVertex()){
                    //appena lo trovo lo inserisco nell'orizzonte ordinato
                    horizon_ordered.push_back(horizon_unordered[(count+1)%size]);

                    index++;
                }
            }

        }

    }


    return horizon_ordered;
}

/**
 * @brief ConvexHullBuilder::stepUpdate aggiorna la visualizzazione della dcel. Viene richiamato solo se è selezonato
 * "Show phases" nella UI
 */

void ConvexhullBuilder::stepUpdate(){


    usleep(500);
    dcel->update();
    this->mainWindow->updateGlCanvas();
}
/**
 * @brief ConvexhullBuilder::removeVisibleFaces rimuove le facce visibili dalla dcel e dal conflictGraph
 * @param visibleFaces set di facce da rimuovere
 */
void ConvexhullBuilder::removeVisibleFaces(std::set<Dcel::Face *> *visibleFaces){

    //elimino le facce visibili dal conflictGraph
    conflictGraph->deleteFaces(visibleFaces);

    //per ogni faccia visibile
    for(auto it = visibleFaces->begin(); it != visibleFaces->end(); ++it){

        Dcel::Face* face = *it;

        //per ogni halfEdge della faccia
        for(auto heit = face->incidentHalfEdgeBegin(); heit != face->incidentHalfEdgeEnd(); ++heit){

            Dcel::HalfEdge* halfEdge = *heit;
            //prendo fromVertex e toVertex dell'halfEdge corrente
            Dcel::Vertex* v1 = halfEdge->getFromVertex();
            Dcel::Vertex* v2 = halfEdge->getToVertex();

            //elimino halfEdge corrente
            this->dcel->deleteHalfEdge(halfEdge);

            //decremento cardinalità vertici legati all'halfedge appena elimiato
            v1->decrementCardinality();
            v2->decrementCardinality();

            //se la cardinalità == 0 rimuovo il vertice dalla dcel
            if(v1->getCardinality() == 0){
                this->dcel->deleteVertex(v1);
            }
            if(v2->getCardinality() == 0){
                this->dcel->deleteVertex(v2);
            }
        }

        //infine rimuovo la faccia
        this->dcel->deleteFace(face);
    }
}
