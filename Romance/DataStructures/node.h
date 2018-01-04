//
//  node.h
//  Romance
//
//  Created by Evan Putnam on 12/14/17.
//  Copyright © 2017 Evan Putnam. All rights reserved.
//

#ifndef node_h
#define node_h

#include <stdio.h>


typedef struct Nodes{
    double data;
}Node;

int getIntData(Node* node);

double getDoubleData(Node* node);

#endif /* node_h */
