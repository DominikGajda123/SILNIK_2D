/** \file LineSegment.cpp
 * \brief Plik projektu SILNIK 2D - SFML 3.1.
 */
#include "LineSegment.h"
#include "PrimitiveRenderer.h"
LineSegment::LineSegment(Point2D start, Point2D end) : start(start), end(end) {}
Point2D LineSegment::getStart() const { return start; }
Point2D LineSegment::getEnd() const { return end; }
void LineSegment::setStart(Point2D point) { start = point; }
void LineSegment::setEnd(Point2D point) { end = point; }
void LineSegment::draw(PrimitiveRenderer& renderer, sf::Color color, bool incremental) const {
    if (incremental) renderer.drawIncrementalLine(start, end, color);
    else renderer.drawLine(start, end, color);
}

void LineSegment::translate(float dx,float dy){start.translate(dx,dy);end.translate(dx,dy);}
void LineSegment::rotate(float a,Point2D c){start.rotate(a,c);end.rotate(a,c);}
void LineSegment::scale(float sx,float sy,Point2D c){start.scale(sx,sy,c);end.scale(sx,sy,c);}
