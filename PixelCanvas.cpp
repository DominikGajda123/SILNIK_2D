/** \file PixelCanvas.cpp
 * \brief Plik projektu SILNIK 2D - SFML 3.1.
 */
#include "PixelCanvas.h"
#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>
PixelCanvas::PixelCanvas(unsigned w,unsigned h):width(w),height(h),pixels(w*h,sf::Color::White),texture(sf::Vector2u{w,h}){}
void PixelCanvas::clear(sf::Color c){std::fill(pixels.begin(),pixels.end(),c);dirty=true;}
sf::Color PixelCanvas::get(int x,int y)const{return inside(x,y)?pixels[size_t(y)*width+x]:sf::Color::Transparent;}
void PixelCanvas::set(int x,int y,sf::Color c){if(inside(x,y)){pixels[size_t(y)*width+x]=c;dirty=true;}}
void PixelCanvas::brush(int x,int y,int r,sf::Color c){r=std::max(0,r);for(int j=-r;j<=r;++j)for(int i=-r;i<=r;++i)if(i*i+j*j<=r*r)set(x+i,y+j,c);}
void PixelCanvas::line(int x0,int y0,int x1,int y1,sf::Color c,int t){
 int dx=std::abs(x1-x0),sx=x0<x1?1:-1,dy=-std::abs(y1-y0),sy=y0<y1?1:-1,err=dx+dy;
 for(;;){brush(x0,y0,std::max(0,t/2),c);if(x0==x1&&y0==y1)break;int e=2*err;if(e>=dy){err+=dy;x0+=sx;}if(e<=dx){err+=dx;y0+=sy;}}
}
void PixelCanvas::rectangle(int x0,int y0,int x1,int y1,sf::Color c,bool filled){
 int l=std::max(0,std::min(x0,x1)),r=std::min(int(width)-1,std::max(x0,x1));
 int t=std::max(0,std::min(y0,y1)),b=std::min(int(height)-1,std::max(y0,y1));
 if(filled){for(int y=t;y<=b;++y)for(int x=l;x<=r;++x)set(x,y,c);}
 else {line(x0,y0,x1,y0,c);line(x1,y0,x1,y1,c);line(x1,y1,x0,y1,c);line(x0,y1,x0,y0,c);}
}
void PixelCanvas::ellipse(int cx,int cy,int rx,int ry,sf::Color c,bool filled){
 rx=std::abs(rx);ry=std::abs(ry);if(rx==0||ry==0)return;
 if(filled){for(int y=-ry;y<=ry;++y){float z=float(y)/ry;int xx=int(rx*std::sqrt(std::max(0.f,1.f-z*z)));for(int x=-xx;x<=xx;++x)set(cx+x,cy+y,c);}}
 else {int steps=std::max(80,6*std::max(rx,ry));for(int i=0;i<=steps;++i){float a=6.28318530718f*i/steps;set(cx+int(std::round(rx*std::cos(a))),cy+int(std::round(ry*std::sin(a))),c);}}
}
void PixelCanvas::polygon(const std::vector<sf::Vector2i>& pts,sf::Color c,bool filled){
 if(pts.size()<3)return;
 if(filled){int miny=int(height)-1,maxy=0;for(auto p:pts){miny=std::min(miny,p.y);maxy=std::max(maxy,p.y);}
 for(int y=std::max(0,miny);y<=std::min(int(height)-1,maxy);++y){std::vector<float> xs;
 for(size_t i=0;i<pts.size();++i){auto a=pts[i],b=pts[(i+1)%pts.size()];if((a.y<=y&&b.y>y)||(b.y<=y&&a.y>y))xs.push_back(a.x+float(y-a.y)*(b.x-a.x)/float(b.y-a.y));}
 std::sort(xs.begin(),xs.end());for(size_t i=1;i<xs.size();i+=2)for(int x=std::max(0,int(std::ceil(xs[i-1])));x<=std::min(int(width)-1,int(std::floor(xs[i])));++x)set(x,y,c);
 }}
 for(size_t i=0;i<pts.size();++i){auto a=pts[i],b=pts[(i+1)%pts.size()];line(a.x,a.y,b.x,b.y,c);}
}
void PixelCanvas::floodFill(int x,int y,sf::Color fill,bool eight){
 if(!inside(x,y))return;sf::Color target=get(x,y);if(target==fill)return;
 std::queue<sf::Vector2i> q;q.push({x,y});set(x,y,fill);
 const int dx[]={1,-1,0,0,1,1,-1,-1},dy[]={0,0,1,-1,1,-1,1,-1};
 while(!q.empty()){auto p=q.front();q.pop();for(int i=0;i<(eight?8:4);++i){int nx=p.x+dx[i],ny=p.y+dy[i];if(inside(nx,ny)&&get(nx,ny)==target){set(nx,ny,fill);q.push({nx,ny});}}}
}
void PixelCanvas::boundaryFill(int x,int y,sf::Color boundary,sf::Color fill){
 if(!inside(x,y)||boundary==fill)return;std::queue<sf::Vector2i> q;q.push({x,y});
 const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};
 while(!q.empty()){auto p=q.front();q.pop();if(!inside(p.x,p.y))continue;auto c=get(p.x,p.y);if(c==boundary||c==fill)continue;set(p.x,p.y,fill);
 for(int i=0;i<4;++i)q.push({p.x+dx[i],p.y+dy[i]});}
}
// Wykrywa kolor zamknietego obrysu na podstawie czterech kierunkow.
// Nie wypelnia, jezeli granica nie jest zamknieta lub ma rozne kolory.
void PixelCanvas::boundaryFillAuto(int x,int y,sf::Color fill){
 if(!inside(x,y))return;
 const sf::Color background=get(x,y);
 if(background==fill)return;
 const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};
 sf::Color border=sf::Color::Transparent;
 for(int d=0;d<4;++d){
  int px=x,py=y;
  while(inside(px,py)&&get(px,py)==background){px+=dx[d];py+=dy[d];}
  if(!inside(px,py))return; // Brak obrysu w tym kierunku.
  sf::Color found=get(px,py);
  if(d==0)border=found;
  else if(found!=border)return; // Granice o roznych kolorach.
 }
 if(border==fill||border==background)return;
 // Najpierw sprawdzamy obszar, zeby nie zalac calego plotna.
 std::queue<sf::Vector2i> q;
 std::vector<unsigned char> seen(pixels.size(),0);
 std::vector<sf::Vector2i> region;
 q.push({x,y});seen[size_t(y)*width+x]=1;
 while(!q.empty()){
  auto p=q.front();q.pop();
  if(p.x==0||p.y==0||p.x==int(width)-1||p.y==int(height)-1)return;
  region.push_back(p);
  for(int d=0;d<4;++d){
   int nx=p.x+dx[d],ny=p.y+dy[d];
   if(!inside(nx,ny))return;
   size_t index=size_t(ny)*width+nx;
   if(seen[index])continue;
   seen[index]=1;
   if(get(nx,ny)!=border)q.push({nx,ny});
  }
 }
 for(const auto& p:region)set(p.x,p.y,fill);
}
void PixelCanvas::render(sf::RenderWindow& window){
 if(dirty){sf::Image img({width,height},sf::Color::White);for(unsigned y=0;y<height;++y)for(unsigned x=0;x<width;++x)img.setPixel({x,y},pixels[size_t(y)*width+x]);texture.update(img);dirty=false;}
 sf::Sprite sprite(texture);window.draw(sprite);
}
bool PixelCanvas::save(const std::string& path)const{
 sf::Image img({width,height},sf::Color::White);for(unsigned y=0;y<height;++y)for(unsigned x=0;x<width;++x)img.setPixel({x,y},pixels[size_t(y)*width+x]);return img.saveToFile(path);
}
