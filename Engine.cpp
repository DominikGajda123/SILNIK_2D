/** \file Engine.cpp
 * \brief Plik projektu SILNIK 2D - SFML 3.1.
 */
#include "Engine.h"
#include "PrimitiveRenderer.h"
#include "PixelCanvas.h"
#include "Shapes.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
Engine::Engine(unsigned width,unsigned height,unsigned fps,bool fullscreen,bool keyboard,bool mouse)
 :keyboardEnabled(keyboard),mouseEnabled(mouse){
 try{window.create(sf::VideoMode({width,height}),"SILNIK 2D - SFML 3.1 | Lab 1-6",fullscreen?sf::State::Fullscreen:sf::State::Windowed);
 window.setFramerateLimit(fps);if(!window.isOpen())logError("Nie udalo sie otworzyc okna");}
 catch(const std::exception& e){logError(e.what());running=false;}
}
void Engine::logError(const std::string& s){std::cerr<<s<<'\n';std::ofstream f("errors.log",std::ios::app);if(f)f<<s<<'\n';}
void Engine::clear(const sf::Color& c){background=c;window.clear(c);}
sf::RenderWindow& Engine::getWindow(){return window;}
void Engine::close(){running=false;window.close();}
void Engine::run(){
 if(!window.isOpen())return;
 auto sz=window.getSize();PixelCanvas canvas(sz.x,sz.y);PrimitiveRenderer renderer(window);
 Player player({100.f,100.f});
 if (!player.loadAnimations("assets")) logError("Brak animacji w folderze assets (Walk ...png)");
 PolygonObject polygon({{560,250},{680,260},{710,350},{590,380}},sf::Color::Blue);
 sf::Clock clock;
 // Czcionka systemowa dla panelu pomocy (Windows).
 sf::Font helpFont;
 bool fontLoaded = helpFont.openFromFile("C:/Windows/Fonts/arial.ttf");
 if (!fontLoaded) logError("Nie znaleziono czcionki Arial - pomoc bedzie widoczna w tytule okna");
 float polygonAngle=0.f;
 Point2D polygonCenter(635.f,310.f);
 int tool=1,brushSize=4,colorIndex=0;bool pressed=false,erasing=false,filled=false,showDemo=true,showHelp=true;
 sf::Vector2i start{},previous{},current{},previousErase{};
 const sf::Color palette[]={sf::Color::Black,sf::Color::Red,sf::Color::Green,sf::Color::Blue,sf::Color::Magenta,sf::Color::Yellow};
 auto drawShape=[&](sf::Vector2i a,sf::Vector2i b){
  auto col=palette[colorIndex];
  if(tool==2)canvas.line(a.x,a.y,b.x,b.y,col,brushSize);
  if(tool==3)canvas.rectangle(a.x,a.y,b.x,b.y,col,filled);
  if(tool==4){int r=int(std::hypot(float(b.x-a.x),float(b.y-a.y)));canvas.ellipse(a.x,a.y,r,r,col,filled);}
  if(tool==5)canvas.ellipse(a.x,a.y,std::abs(b.x-a.x),std::abs(b.y-a.y),col,filled);
  if(tool==6){int mid=(a.x+b.x)/2;canvas.polygon({{mid,a.y},{b.x,b.y},{a.x,b.y}},col,filled);}
 };
 while(window.isOpen()&&running){
  float dt=std::min(clock.restart().asSeconds(),0.05f);
  while(const auto event=window.pollEvent()){
   if(event->is<sf::Event::Closed>())close();
   if(const auto* key=event->getIf<sf::Event::KeyPressed>()){
    using K=sf::Keyboard::Key;
    if(key->code==K::Escape)close();
    if(key->code==K::Num1)tool=1;if(key->code==K::Num2)tool=2;
    if(key->code==K::Num3)tool=3;if(key->code==K::Num4)tool=4;
    if(key->code==K::Num5)tool=5;if(key->code==K::Num6)tool=6;
    if(key->code==K::Num7)tool=7;if(key->code==K::Num8)tool=8;
    if(key->code==K::C)canvas.clear();
    if(key->code==K::F5){if(!canvas.save("rysunek.png"))logError("Nie mozna zapisac rysunek.png");else std::cout<<"Zapisano rysunek.png w katalogu roboczym\n";}
    if(key->code==K::F)filled=!filled;
    if(key->code==K::Tab || key->code==K::F1)showDemo=!showDemo;
    if(key->code==K::F2)showHelp=!showHelp;
    if(key->code==K::Add||key->code==K::Equal)brushSize=std::min(40,brushSize+2);
    if(key->code==K::Subtract||key->code==K::Hyphen)brushSize=std::max(1,brushSize-2);
    if(key->code==K::R){
     polygon.rotate(15.f,polygonCenter);
     polygonAngle+=15.f;
    }
    // Kierunek ruchu wynika z aktualnego obrotu figury.
    if(key->code==K::T||key->code==K::G){
     float radians=polygonAngle*3.14159265f/180.f;
     float step=(key->code==K::T)?10.f:-10.f;
     float dx=std::cos(radians)*step;
     float dy=std::sin(radians)*step;
     polygon.translate(dx,dy);
     polygonCenter=Transform2D::translate(polygonCenter,dx,dy);
    }
    if(key->code==K::Z)polygon.scale(1.1f,1.1f,polygonCenter);
    if(key->code==K::X)polygon.scale(0.9f,0.9f,polygonCenter);
    if(key->code==K::Q)colorIndex=(colorIndex+1)%6;
   }
   if(mouseEnabled){
    if(const auto* mouse=event->getIf<sf::Event::MouseButtonPressed>()){
     current=mouse->position;
     if(mouse->button==sf::Mouse::Button::Right){
      // Gumka dziala podczas przytrzymywania prawego przycisku.
      erasing=true;
      pressed=false;
      previousErase=current;
      canvas.brush(current.x,current.y,brushSize,sf::Color::White);
     }
     else if(mouse->button==sf::Mouse::Button::Left){
      start=previous=current;
      pressed=true;
      if(tool==7){canvas.floodFill(current.x,current.y,palette[colorIndex]);pressed=false;}
      else if(tool==8){canvas.boundaryFillAuto(current.x,current.y,palette[colorIndex]);pressed=false;}
     }
    }
    if(const auto* mouse=event->getIf<sf::Event::MouseMoved>()){
     current=mouse->position;
     if(erasing){
      canvas.line(previousErase.x,previousErase.y,current.x,current.y,sf::Color::White,brushSize);
      previousErase=current;
     }
     else if(pressed&&tool==1){canvas.line(previous.x,previous.y,current.x,current.y,palette[colorIndex],brushSize);previous=current;}
    }
    if(const auto* mouse=event->getIf<sf::Event::MouseButtonReleased>()){
     current=mouse->position;
     if(mouse->button==sf::Mouse::Button::Right)erasing=false;
     if(pressed&&mouse->button==sf::Mouse::Button::Left){if(tool>=2&&tool<=6)drawShape(start,current);pressed=false;}
    }
   }
  }
  if(!window.isOpen())break;
  if(mouseEnabled){
   current=sf::Mouse::getPosition(window);
   if(erasing){
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){
     canvas.line(previousErase.x,previousErase.y,current.x,current.y,sf::Color::White,brushSize);
     previousErase=current;
    }else erasing=false;
   }
  }
  if(keyboardEnabled)player.update(dt);
  window.clear(sf::Color::White);canvas.render(window);
  if(showDemo){
   renderer.drawLine({30,50},{230,80},sf::Color::Red);
   renderer.drawIncrementalLine({30,100},{230,170},sf::Color::Green);
   renderer.drawAlgorithmCircle({350,100},50,sf::Color::Blue);
   renderer.drawAlgorithmEllipse({500,100},80,40,sf::Color::Magenta);
   renderer.drawPolygon({{600,50},{720,70},{740,160},{620,180}},sf::Color::Black);
   polygon.draw(renderer);
  }
  // Gracz jest widoczny niezaleznie od przelacznika demonstracji F1.
  player.draw(window);
  // Podglad figury podczas przeciagania mysza.
  if(pressed&&tool>=2&&tool<=6){
   if(tool==2)renderer.drawLine({float(start.x),float(start.y)},{float(current.x),float(current.y)},sf::Color::Red);
   if(tool==3)renderer.drawRectangle(float(std::min(start.x,current.x)),float(std::min(start.y,current.y)),float(std::abs(start.x-current.x)),float(std::abs(start.y-current.y)),sf::Color::Red,false);
   if(tool==4){float r=std::hypot(float(current.x-start.x),float(current.y-start.y));renderer.drawCircle(float(start.x)-r,float(start.y)-r,r,sf::Color::Red,false);}
   if(tool==5){float rx=float(std::abs(current.x-start.x)),ry=float(std::abs(current.y-start.y));sf::CircleShape e(1.f);e.setScale({rx,ry});e.setPosition({float(start.x)-rx,float(start.y)-ry});e.setFillColor(sf::Color::Transparent);e.setOutlineColor(sf::Color::Red);e.setOutlineThickness(0.03f);window.draw(e);}
   if(tool==6){
    float mid=(float(start.x)+float(current.x))/2.f;
    // Tylko obrys podczas przeciagania mysza.
    Point2D a(mid,float(start.y));
    Point2D b(float(current.x),float(current.y));
    Point2D c(float(start.x),float(current.y));
    renderer.drawLine(a,b,sf::Color::Red);
    renderer.drawLine(b,c,sf::Color::Red);
    renderer.drawLine(c,a,sf::Color::Red);
   }
  }
  // Probka aktualnego koloru malowania w prawym gornym rogu.
  sf::RectangleShape colorPreview({44.f,44.f});
  colorPreview.setPosition({float(window.getSize().x)-60.f,16.f});
  colorPreview.setFillColor(palette[colorIndex]);
  colorPreview.setOutlineColor(sf::Color(100,100,100));
  colorPreview.setOutlineThickness(2.f);
  window.draw(colorPreview);
  // F2: panel pomocy na ekranie, F1: tylko figury demonstracyjne.
  if(showHelp && fontLoaded){
   sf::RectangleShape helpBackground({570.f,205.f});
   helpBackground.setPosition({12.f,float(window.getSize().y)-217.f});
   helpBackground.setFillColor(sf::Color(15,20,30,225));
   helpBackground.setOutlineColor(sf::Color(160,170,190));
   helpBackground.setOutlineThickness(1.f);
   window.draw(helpBackground);
   sf::Text helpText(helpFont,
      "STEROWANIE  (F2 - ukryj)\n"
      "1-8: narzedzie   Q: kolor   F: wypelnienie\n"
      "Mysz: rysowanie   PPM (trzymaj): gumka   C: czysc   F5: PNG\n"
      "WASD: gracz   R: obrot   T/G: przod/tyl\n"
      "Z/X: skala   F1: figury demo   ESC: wyjscie", 17);
   helpText.setFillColor(sf::Color::White);
   helpText.setPosition({24.f,float(window.getSize().y)-205.f});
   window.draw(helpText);
  }
  // Tytul pokazuje stan F1 i F2 nawet bez czcionki.
  if(showHelp){
   static sf::Clock titleClock;
   if(titleClock.getElapsedTime().asSeconds()>0.4f){
    const char* names[]={"", "Pedzel", "Linia", "Prostokat", "Okrag", "Elipsa", "Trojkat", "Flood", "Boundary"};
    window.setTitle(std::string("SILNIK 2D | ")+names[tool]+(showDemo?" | DEMO: ON":" | DEMO: OFF")+(showHelp?" | POMOC: ON":" | POMOC: OFF")+" | F1 demo, F2 pomoc");
    titleClock.restart();
   }
  }else window.setTitle(std::string("SILNIK 2D | F1 demo: ")+(showDemo?"ON":"OFF")+" | F2 pomoc: OFF");
  window.display(); // podwojne buforowanie SFML
 }
}
