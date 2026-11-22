/** \file PrimitiveRenderer.cpp
 * \brief Plik projektu SILNIK 2D - SFML 3.1.
 */
#include "PrimitiveRenderer.h"
#include <algorithm>
#include <cmath>

PrimitiveRenderer::PrimitiveRenderer(sf::RenderWindow& window) : window(window) {}
void PrimitiveRenderer::drawPoint(const Point2D& point, sf::Color color) {
    sf::RectangleShape pixel({1.f, 1.f});
    pixel.setPosition(point.position());
    pixel.setFillColor(color);
    window.draw(pixel);
}
void PrimitiveRenderer::drawLine(const Point2D& a, const Point2D& b, sf::Color color) {
    sf::Vertex vertices[] = {sf::Vertex(a.position(), color), sf::Vertex(b.position(), color)};
    window.draw(vertices, 2, sf::PrimitiveType::Lines);
}
void PrimitiveRenderer::drawIncrementalLine(const Point2D& a, const Point2D& b, sf::Color color) {
    // Algorytm przyrostowy (DDA), dziala tez dla pionowych i stromych odcinkow.
    float dx = b.getX() - a.getX();
    float dy = b.getY() - a.getY();
    int steps = static_cast<int>(std::ceil(std::max(std::abs(dx), std::abs(dy))));
    if (steps == 0) { drawPoint(a, color); return; }
    float x = a.getX(), y = a.getY();
    float stepX = dx / steps, stepY = dy / steps;
    sf::VertexArray pixels(sf::PrimitiveType::Points);
    for (int i = 0; i <= steps; ++i) {
        pixels.append(sf::Vertex({std::round(x), std::round(y)}, color));
        x += stepX;
        y += stepY;
    }
    window.draw(pixels);
}
void PrimitiveRenderer::drawRectangle(float x, float y, float width, float height, sf::Color color, bool filled) {
    sf::RectangleShape shape({width, height});
    shape.setPosition({x, y});
    if (filled) shape.setFillColor(color);
    else { shape.setFillColor(sf::Color::Transparent); shape.setOutlineThickness(2.f); shape.setOutlineColor(color); }
    window.draw(shape);
}
void PrimitiveRenderer::drawCircle(float x, float y, float radius, sf::Color color, bool filled) {
    sf::CircleShape shape(radius);
    shape.setPosition({x, y});
    if (filled) shape.setFillColor(color);
    else { shape.setFillColor(sf::Color::Transparent); shape.setOutlineThickness(2.f); shape.setOutlineColor(color); }
    window.draw(shape);
}
void PrimitiveRenderer::drawTriangle(const Point2D& a, const Point2D& b, const Point2D& c, sf::Color color) {
    sf::ConvexShape shape(3);
    shape.setPoint(0, a.position()); shape.setPoint(1, b.position()); shape.setPoint(2, c.position());
    shape.setFillColor(color); window.draw(shape);
}
void PrimitiveRenderer::drawPolyline(const std::vector<Point2D>& points, sf::Color color, bool closed, bool incremental) {
    if (points.size() < 2) return;
    for (size_t i = 1; i < points.size(); ++i) {
        if (incremental) drawIncrementalLine(points[i - 1], points[i], color);
        else drawLine(points[i - 1], points[i], color);
    }
    if (closed) {
        if (incremental) drawIncrementalLine(points.back(), points.front(), color);
        else drawLine(points.back(), points.front(), color);
    }
}

void PrimitiveRenderer::drawAlgorithmCircle(Point2D c,int r,sf::Color color) {
 if(r<0)return;
 sf::VertexArray v(sf::PrimitiveType::Points);
 for(int x=0;x<=r;++x){int y=static_cast<int>(std::round(std::sqrt(float(r*r-x*x))));
  for(auto q:std::vector<sf::Vector2i>{{x,y},{-x,y},{x,-y},{-x,-y},{y,x},{-y,x},{y,-x},{-y,-x}})
   v.append(sf::Vertex({c.getX()+float(q.x),c.getY()+float(q.y)},color));
 }
 window.draw(v);
}
void PrimitiveRenderer::drawAlgorithmEllipse(Point2D c,int rx,int ry,sf::Color color){
 if(rx<1||ry<1)return;
 sf::VertexArray v(sf::PrimitiveType::Points);
 for(int x=0;x<=rx;++x){float t=float(x)/rx;int y=int(std::round(ry*std::sqrt(std::max(0.f,1.f-t*t))));
  for(auto q:std::vector<sf::Vector2i>{{x,y},{-x,y},{x,-y},{-x,-y}})
   v.append(sf::Vertex({c.getX()+float(q.x),c.getY()+float(q.y)},color));
 }
 for(int y=0;y<=ry;++y){float t=float(y)/ry;int x=int(std::round(rx*std::sqrt(std::max(0.f,1.f-t*t))));
  for(auto q:std::vector<sf::Vector2i>{{x,y},{-x,y},{x,-y},{-x,-y}})
   v.append(sf::Vertex({c.getX()+float(q.x),c.getY()+float(q.y)},color));
 }
 window.draw(v);
}
namespace {
float orient(const Point2D& a,const Point2D& b,const Point2D& c){return (b.getX()-a.getX())*(c.getY()-a.getY())-(b.getY()-a.getY())*(c.getX()-a.getX());}
bool onSegment(const Point2D& a,const Point2D& b,const Point2D& c){return b.getX()>=std::min(a.getX(),c.getX())&&b.getX()<=std::max(a.getX(),c.getX())&&b.getY()>=std::min(a.getY(),c.getY())&&b.getY()<=std::max(a.getY(),c.getY());}
bool intersects(const Point2D& a,const Point2D& b,const Point2D& c,const Point2D& d){
 float p=orient(a,b,c),q=orient(a,b,d),r=orient(c,d,a),s=orient(c,d,b);
 if(((p>0&&q<0)||(p<0&&q>0))&&((r>0&&s<0)||(r<0&&s>0)))return true;
 constexpr float e=0.0001f;
 return (std::abs(p)<e&&onSegment(a,c,b))||(std::abs(q)<e&&onSegment(a,d,b))||(std::abs(r)<e&&onSegment(c,a,d))||(std::abs(s)<e&&onSegment(c,b,d));
}
}
bool PrimitiveRenderer::drawPolygon(const std::vector<Point2D>& points,sf::Color color){
 const size_t n=points.size();if(n<3)return false;
 for(size_t i=0;i<n;i++)for(size_t j=i+1;j<n;j++){
  if(j==i+1||(i==0&&j==n-1))continue;
  if(intersects(points[i],points[(i+1)%n],points[j],points[(j+1)%n]))return false;
 }
 drawPolyline(points,color,true);return true;
}
