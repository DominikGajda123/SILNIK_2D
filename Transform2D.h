/** \file Transform2D.h
 * \brief Plik projektu SILNIK 2D - SFML 3.1.
 */
#pragma once
#include "Point2D.h"
#include <cmath>
namespace Transform2D {
inline Point2D translate(Point2D p,float dx,float dy){return {p.getX()+dx,p.getY()+dy};}
inline Point2D rotate(Point2D p,float degrees,Point2D center={}) {
 float a=degrees*3.14159265358979323846f/180.f;
 float x=p.getX()-center.getX(),y=p.getY()-center.getY();
 return {center.getX()+x*std::cos(a)-y*std::sin(a),center.getY()+x*std::sin(a)+y*std::cos(a)};
}
inline Point2D scale(Point2D p,float sx,float sy,Point2D center={}){
 return {center.getX()+(p.getX()-center.getX())*sx,center.getY()+(p.getY()-center.getY())*sy};
}
}
