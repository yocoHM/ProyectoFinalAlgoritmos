#ifndef NODODOSTRES
#define NODODOSTRES

#include <QPainter>
#include <QDebug>
#include <QGraphicsItem>
#include <iostream>
#include "edge.h"

template <class T>
class NodoDosTres: public QGraphicsItem {
  bool hasSmall = false;
  bool hasHigh = false;
  bool full = false;
  T* menor = nullptr;
  T* mayor = nullptr;
  T* tempCentro = nullptr;
  NodoDosTres<T>* padre = nullptr;
  NodoDosTres<T>* izquierdo = nullptr;
  NodoDosTres<T>* centro = nullptr;
  NodoDosTres<T>* derecho = nullptr;
  NodoDosTres<T>* temp = nullptr;


  Edge<T> * edgeDerecha = nullptr;
  Edge<T> * edgeIzquierda = nullptr;
  bool pressed;
  int index;
  double x,y;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        pressed = true;
        update();
        std::cout << "Se pico el nodo " << menor << std::endl;
        std::cout << "(" << x << "," << y << ")" << std::endl;
        if(padre != nullptr){
            std::cout << "Padre  " << padre->getMenor() << std::endl;

        }

        QGraphicsItem::mousePressEvent(event);
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
    {
        pressed = false;
        update();
        QGraphicsItem::mouseReleaseEvent(event);
    }

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE
    {
        switch (change) {
        case ItemPositionHasChanged:
            if(edgeIzquierda)
                edgeIzquierda->adjust();
            if(edgeDerecha)
                edgeDerecha->adjust();
    //        edgeIzquierda->adjust();
    //        edgeDerecha->adjust();
    //        foreach (Edge<T> *edge, edgeList)
    //            edge->adjust();
            //graph->itemMoved();
            break;
        default:
            break;
        };

        return QGraphicsItem::itemChange(change, value);
    }

public:
  void setCoordinates(int x,int y){
      this->x = x;
      this->y = y;
      setPos(x,y);
  }

  void setX(int x){
      this->x = x;
  }

  void setY(int y){
      this->y = y;
  }

  int getX(){
      return x;
  }

  int getY(){
      return y;
  }

  void addEdgeDerecha(Edge<T> *edge){
      this->edgeIzquierda = edge;
      edge->adjust();
  }

  void addEdgeIzquierda(Edge<T> *edge){
      this->edgeDerecha = edge;
      edge->adjust();
  }

  void setIndex(int index){
      this->index = index;
  }

  int getIndex(){
      return index;
  }

  QRectF boundingRect() const
  {
      return QRectF(-15.5, -15.5, 34, 34);
  }

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
  {

      QString disp = QString::number(*menor);
      QRectF chan = QRectF(-15.5, -15.5, 34, 34);

      painter->setRenderHint(QPainter::Antialiasing);
      painter->setRenderHint(QPainter::HighQualityAntialiasing);
      painter->setPen(Qt::black);
      painter->setBrush(QBrush(Qt::white));
      painter->drawEllipse(-15, -15, 45, 30);

      if(this->mayor != nullptr){
          QString disp2 = QString::number(*mayor);
          QString juntos = disp + "|" + disp2;
          painter->drawText(QRectF(-12, -10.5, 40, 24),Qt::AlignCenter, juntos);
      }
      else {
          painter->drawText(QRectF(-12, -10.5, 40, 24),Qt::AlignCenter, disp);
      }


  }

  void borrar(QGraphicsScene *scene) {
      scene->removeItem(this);
      //borrarEdges(scene);
      delete this;
  }


  //- - - - - Constructores - - - - -
  NodoDosTres<T>() : izquierdo(nullptr), centro(nullptr), derecho(nullptr), padre(nullptr), menor(nullptr), mayor(nullptr), tempCentro(nullptr),temp(nullptr) { }

  NodoDosTres(T _menor)
  {
    menor = new T(_menor);
    hasSmall = true;
    pressed = false;
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
  }

  //- - - - - Destructor - - - - -
  virtual ~NodoDosTres()
  {
    izquierdo = centro = derecho = padre = temp = nullptr;
    menor = mayor = nullptr;
  }

  //- - - - - Setters - - - - -
  void setIzquierdo(NodoDosTres<T> * info)
  {
    izquierdo = info;
  }

  void setDerecho(NodoDosTres<T> * info)
  {
    derecho = info;
  }

  void setCentro(NodoDosTres<T> * info)
  {
    centro = info;
  }

  void setPadre(NodoDosTres<T> * info)
  {
    padre = info;
  }

  void setTemp(NodoDosTres<T>* nodo)
  {
    temp = nodo;
  }

  void setTempCentro(T _info)
  {
    if(tempCentro == nullptr)
    {
      tempCentro = new T(_info);
    }
    else
    {
      *tempCentro = _info;
    }
  }

  void setMenor(T _info)
  {
    if(menor!=nullptr)
    {
      *menor = _info;
    }
    else
    {
      menor = new T(_info);
    }
  }

  void setMayor(T _info)
  {
    if(mayor!=nullptr)
    {
      *mayor = _info;
    }
    else
    {
      mayor = new T(_info);
    }
  }

  void setInfo(T _info)
  {
    if(!menor) {
      menor = new T(_info);
    }
    else {

      if(_info >= *menor) {
        if(!mayor) {
          mayor = new T(_info);
        }
      }
      else if(_info < *menor) {
        mayor = new T(*menor);
        *menor = _info;
      }

    }
  }

  void setInfoCentro(T _info)
  {
    if(mayor && menor)
    {
      if(!tempCentro)
      {
        tempCentro = new T(_info);
        if(_info < *menor)
        {
          *tempCentro = *menor;
          *menor = _info;
        }
        else if(_info >= *menor && _info <= *mayor)
        {
          *tempCentro = _info;
        }
        else
        {
          *tempCentro = *mayor;
          *mayor = _info;
        }
      }
      else
      {
        if(_info < *menor)
        {
          *tempCentro = *menor;
          *menor = _info;
        }
        else if(_info >= *menor && _info <= *mayor)
        {
          *tempCentro = _info;
        }
        else
        {
          *tempCentro = *mayor;
          *mayor = _info;
        }
      }
    }
  }

  //- - - - - Getters - - - - -
  NodoDosTres<T>* getTemp()
  {
    return temp;
  }

  NodoDosTres<T> * getIzquierdo() const
  {
    return izquierdo;
  }

  NodoDosTres<T> * getDerecho() const
  {
    return derecho;
  }

  NodoDosTres<T> * getCentro() const
  {
    return centro;
  }

  NodoDosTres<T> * getPadre() const
  {
    return padre;
  }

  T getTempCentro()
  {
    return *tempCentro;
  }

  T getMenor()
  {
    return *menor;
  }

  T getMayor()
  {
    return *mayor;
  }

  //- - - - - Voids - - - - -
  void borrarTempCentro()
  {
    if(tempCentro) {
      tempCentro = nullptr;
    }
  }

  void borrarLlaves()
  {
    if(menor)
      menor = nullptr;
    if(mayor)
      mayor = nullptr;
  }

  void borrarMayor()
  {
    if(mayor)
    {
      mayor = nullptr;
    }
  }

  void borrarMenor()
  {
    if(menor)
      menor = nullptr;
  }

  void cambioMayorAMenor()
  {
    if(!menor)
      menor = new T(*mayor);
    else
      *menor = *mayor;
    mayor = nullptr;
  }

  //- - - - - Bools - - - - -
  bool tieneTempCentro()
  {
    if(tempCentro) {
      return true;
    }
    else {
      return false;
    }
  }

  bool isFull()
  {
    if(mayor && menor)
      return true;
    return false;
  }

  bool tieneTresLlaves()
  {
    return mayor && menor && tempCentro;
  }

  bool hasLower(){
    if(menor == nullptr)
      return false;
    else
      return true;
  }

  bool hasHigher(){
    if(mayor==nullptr)
      return false;
    else
      return true;
  }

  bool sinLlaves()
  {
    return !menor && !mayor;
  }

//  bool esCentro()
//  {
//      if(this->centro->padre != nullptr){
//          if (this == padre->centro->centro){
//              return true;
//          }
//          else {
//              return false;
//          }
//      }
//      else{
//          return false;
//      }
//  }

};

#endif // NODODOSTRES

