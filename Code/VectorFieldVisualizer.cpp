//
//  main.cpp
//  Vector Field Visualizer
//
//  Created by Aaron Blasdel on 12/12/11.
//  Copyright (c) 2011 Aaron Blasdel. All rights reserved.
//
//  This program simulates a vector field applying forces to weighted particles.
//  When particles leave the vector field they are replaced by a new one at a random point inside the field
//  Different vector fields are available and are cycled by using the [ and ] keys
//  Adjust the speed by using the < and > keys
//  Also to add and remove particles use the - and + keys
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "DataCanvas.h"

int main (int argc, char ** argv)
{   //create a DataCanvas object, initialize it and launch it
    DataCanvas Canvas;
    Canvas.initilize(argc, argv, "Vector Field Visualizer - Aaron Blasdel");
    Canvas.Launch();
    return 0;
}
