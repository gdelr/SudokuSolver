#ifndef ORDEREDPAIR_H
#define ORDEREDPAIR_H

class OrderedPair {
public:
  int x,y=0;
  int value=0;
  OrderedPair(int a,int b){
    x=a;
    y=b;
  }
  OrderedPair(int a,int b,int c){x=a;y=b;value=c;}
  OrderedPair(const OrderedPair &op){
    x=op.x;y=op.y;value=op.value;
  }

  int getX(){return x;}
  int getY(){return y;}
  int getValue(){return value;}
  void setValue(int newValue){value=newValue;}
  
  
  
  };

#endif 
