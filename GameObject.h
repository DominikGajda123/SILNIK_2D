/** \file GameObject.h
 * \brief Plik projektu SILNIK 2D - SFML 3.1.
 */
#pragma once
#include "Transform2D.h"
/** \brief Rysowanie prymitywow przez okno SFML i algorytmy rysowania. */
class PrimitiveRenderer;
/** \brief Klasa bazowa hierarchii obiektow. */
class GameObject { public: virtual ~GameObject()=default; };
/** \brief Interfejs aktualizacji obiektu w czasie. */
class UpdatableObject : public virtual GameObject { public: virtual void update(float dt)=0; };
/** \brief Interfejs rysowania obiektu. */
class DrawableObject : public virtual GameObject { public: virtual void draw(PrimitiveRenderer& renderer) const=0; };
/** \brief Interfejs transformacji obiektu. */
class TransformableObject : public virtual GameObject {
public: virtual void translate(float dx,float dy)=0;
 virtual void rotate(float angle,Point2D center)=0;
 virtual void scale(float sx,float sy,Point2D center)=0;
};
/** \brief Bazowy typ figur rysowalnych i transformowalnych. */
class ShapeObject : public DrawableObject, public TransformableObject {};
