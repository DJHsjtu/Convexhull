#include "conflictgraph.h"

/**

  La classe ConflictGraph si preoccupa di tenere traccia di punti visibili da una faccia della dcel e facce visibili da un punto,
  gestendo opportunamente l'aggiornamento e la cancellazione durante gli step di creazione del convexhull.
  Le conflict list sono formate da :
  mappa di set di punti e singola faccia (p_graph),
  mappa di set di facce e singolo punto (f_graph).
  Sono stati usati set al posto di list o vector perchè vengono fatte molte operazioni di modifica delle conflict list,
  e std::set è più efficiente in questo degli altri. Inoltre vengono usati i puntatori a set per efficienza

 */
/**
 * @brief ConflictGraph::ConflictGraph costruttore della classe ConflictGraph, prende in ingresso la dcel e il vettore dei punti
 * @param Dcel dcel da manipolare
 * @param verVect vettore dei punti
 */
ConflictGraph::ConflictGraph(DrawableDcel* dcel, const std::vector<Pointd> &vectPoint)
{

    this->dcel=dcel;
    this->vectPoint=vectPoint;

}

ConflictGraph::~ConflictGraph(){


}

/**
 * @brief ConflictGraph::inizialize inizializza le conflict list del conflictGraph checkando la visiblità di ogni faccia del tetraedro
 * con i vertici rimanenti della dcel
 */
void ConflictGraph::inizialize(){


    //per ogni faccia del tetraedro
    for(auto fit=this->dcel->faceBegin();fit!=this->dcel->faceEnd();++fit){

        Dcel::Face* currFace=*fit;

        //per ogni vertice della dcel rimanente
        for(unsigned int i=4;i<vectPoint.size();i++){

            //se il punto vede la faccia corrente inizializzo le conflict list
            if(faceVisibleFromPoint(vectPoint[i],currFace)){

                addFConflict_p(vectPoint[i],currFace);
                addPConflict_f(currFace,vectPoint[i]);
            }

        }
    }
}



/**
 * @brief ConflictGraph::addFConflict_p inserisce la faccia nella conflict list dei punti
 * @param point punto che serve per modificare la sua conflict list
 * @param face faccia da aggiungere alla conflict list
 */
void ConflictGraph::addFConflict_p(Pointd point , Dcel::Face* face){

    //se non ha elementi la inizializzo con un set vuoto
    if(this->f_graph[point]==nullptr){

        this->f_graph[point]=new std::set<Dcel::Face*>;
    }
    //inserisco la faccia
    this->f_graph.at(point)->insert(face);
}


/**
 * @brief ConflictGraph::addPConflict_f inserisce il punto nella conflict list delle facce
 * @param point da aggiungere
 * @param face faccia per modificare la sua conflict list
 */

void ConflictGraph::addPConflict_f(Dcel::Face* face, Pointd point){

    //se non ha elementi la inizializzo con un set vuoto
    if(this->p_graph[face]==nullptr){

        this->p_graph[face]=new std::set<Pointd>;
    }
    // inserisco il punto
    this->p_graph.at(face)->insert(point);
}


/**
 * @brief ConflictGraph::findVisibleFaces restituisce le facce visibili da un punto
 * @param punto point
 * @return set di facce visibili dal punto
 */
std::set<Dcel::Face*>* ConflictGraph::findVisibleFaces(Pointd &point){

    std::set<Dcel::Face*> *faces=this->f_graph[point];

    // se non ha trovato elementi, inizializzo un nuovo set
    if(faces==nullptr){

        faces=new std::set<Dcel::Face*>;

        //inserisco il set di facce nella conflict list dei punti
        this->f_graph[point]=faces;
    }

    return new std::set<Dcel::Face*>(*faces);
}

/**
 * @brief ConflictGraph::findVisiblePoints restituisce i punti visibili da una faccia
 * @param face faccia
 * @return set di punti visibili dalla faccia
 */

std::set<Pointd>* ConflictGraph::findVisiblePoints(Dcel::Face* face){

    std::set<Pointd> *points=this->p_graph[face];

    // se non ha trovato elementi, inizializzo un nuovo set
    if(points==nullptr){

        points=new std::set<Pointd>;

        //inserisco il set di punti nella conflict list delle facce
        this->p_graph[face]=points;
    }

    return new std::set<Pointd>(*points);
}
/**
 * @brief ConflictGraph::mergeVerticesVisible restituisce una mappa che contiene, per ogni half edge dell'orizzonte,
 * un set di punti visibili da una faccia
 * @param lista degli half edge dell'orizzonte
 * @return mappa che associa i punti visibili a un half edge
 */

std::map<Dcel::HalfEdge*, std::set<Pointd>*> ConflictGraph::mergeVerticesVisible(std::list<Dcel::HalfEdge*> horizon){

    std::map<Dcel::HalfEdge *, std::set<Pointd>*> mapResult;

    //scorro l'orizzionte, e prendo i vertici in conflitto con le facce incidenti agli half edge dell'orizzonte e ai twin di quegli half edge
    //e li metto nella mappa relativa al singolo half edge considerato
    for(auto hit = horizon.begin(); hit != horizon.end(); ++hit){

        Dcel::HalfEdge* currentHalfEdge = *hit;

        std::set<Pointd>* allVertices= new std::set<Pointd>;

        Dcel::Face* halfEdgeFace =currentHalfEdge->getFace();
        Dcel::Face* twinFace= currentHalfEdge->getTwin()->getFace();

        //cerco i punti visibili a partire dalle facce degli halfEdge dell'orizzonte e dei loro twin
        std::set<Pointd> * VFromFaceHorizon=findVisiblePoints(halfEdgeFace);
        std::set<Pointd> * VFromFaceTwinHorizon=findVisiblePoints(twinFace);

        //unisco i punti visibili dalla faccia incidente all'halfEdge dell'orizzionte e al suo twin
        allVertices->insert(VFromFaceHorizon->begin(),VFromFaceHorizon->end());
        allVertices->insert(VFromFaceTwinHorizon->begin(),VFromFaceTwinHorizon->end());

        mapResult[currentHalfEdge]=allVertices;

    }

    return mapResult;

}

/**
 * @brief ConflictGraph::deleteFaces cancella le facce nel set dato in ingresso dal conflict graph
 * @param faces set delle facce da modificare
 */

void ConflictGraph::deleteFaces(std::set<Dcel::Face *> *faces)
{
    // per ogni faccia
    for(auto fit = faces->begin(); fit != faces->end(); ++fit)
    {

        Dcel::Face* currentFace=*fit;
        //recupero i punti visibili dalla faccia da p_graph
        std::set<Pointd>* pointVisibleFromFace = findVisiblePoints(currentFace);

        //elimino la faccia da p_graph
        p_graph.erase(currentFace);

        //per ogni punto visibile dalla faccia
        for(auto pit=pointVisibleFromFace->begin();pit!=pointVisibleFromFace->end();++pit)
        {
            //elimino il riferimento da f_graph
            Pointd currentPoint=*pit;
            f_graph.at(currentPoint)->erase(currentFace);
        }

    }
}

/**
 * @brief ConflictGraph::deletePoint cancella il punto dal conflict graph
 * @param point punto da eliminare
 */

void ConflictGraph::deletePoint(Pointd &point)
{
    // recupero le facce visibili dal punto da f_graph
    std::set<Dcel::Face*>* faceVisibleFromPoint = findVisibleFaces(point);

    //elimino il punto da f_graph
    f_graph.erase(point);

    //per ogni faccia visibile
    for(auto fit=faceVisibleFromPoint->begin();fit!=faceVisibleFromPoint->end();++fit)
    {
        //elimino il riferimento del punto da p_graph
        Dcel::Face* currentFace=*fit;
        p_graph.at(currentFace)->erase(point);
    }
}

/**
 * @brief ConflictGraph::updateConflictGraph aggiorna il conflict graph.
 * Controlla la faccia visibile dal punto passato in ingresso
 * @param face faccia per fare il check
 * @param point punto che potrebbe vedere la faccia
 */
void ConflictGraph::updateConflictGraph(Dcel::Face *face, const Pointd point)
{

    //se il punto vede la faccia, aggiorno le conflict list
    if(faceVisibleFromPoint(point, face)){

        addFConflict_p(point, face);
        addPConflict_f(face, point);
    }
}

/**
 * @brief ConflictGraph::faceVisibleFromPoint controlla se il punto vede la faccia
 * @return Vero se il vertice vede la faccia, falso altrimenti
 */

bool ConflictGraph::faceVisibleFromPoint(const Pointd point, Dcel::Face* face)
{

    int index=0;
    Eigen::Matrix4d mat;

    for(auto vit=face->incidentVertexBegin();vit!=face->incidentVertexEnd();++vit)
    {

        Dcel::Vertex* vert =*vit;
        Pointd point= vert->getCoordinate();

        mat(index,0) = point.x();
        mat(index,1) = point.y();
        mat(index,2) = point.z();
        mat(index,3) = 1;

        index++;
    }

    mat(3,0) = point.x();
    mat(3,1) = point.y();
    mat(3,2) = point.z();
    mat(3,3) = 1;

    double det=mat.determinant();

    return (det < -std::numeric_limits<double>::epsilon());

}
