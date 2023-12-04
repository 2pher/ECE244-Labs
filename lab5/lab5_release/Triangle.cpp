//
//  Triangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class Rectangle here

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

#include "Shape.h"
#include "Triangle.h"

// Build a Circle object
Triangle::Triangle(string n, float x1, float y1, float x2, float y2, float x3, float y3):Shape(n, (x1+x2+x3)/3, (y1+y2+y3)/3) {
    X1 = x1;
    Y1 = y2;
    X2 = x2;
    Y2 = y2;
    X3 = x3;
    Y3 = y3;
}

Triangle::~Triangle() {
    // Nothing to do
}

void Triangle::draw() const {
    // Set floating point printing to fixed point with 2 decimals
    cout << std::fixed;
    cout << std::setprecision(2);
    
    // Print the information
    cout << "triangle: " << name << " "
         << x_centre << " " << y_centre
         << " " << X1 << " " << Y1 
         << " " << X2 << " " << Y2 
         << " " << X3 << " " << Y3
         << " " << computeArea()
         << endl;
}

float Triangle::computeArea() const {
    return (0.5*(abs((x1*(y2-y3))+(x2*(y3-y1))+(x3*(y1-y2)))));
}

Shape* Triangle::clone() const {
    return (new Triangle(*this));
}