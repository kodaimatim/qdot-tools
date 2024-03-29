// $Id: Sphere.h,v 1.2 2004/04/22 20:09:44 jshumwa Exp $
/*
    Copyright (C) 2004 John B. Shumway, Jr.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
#ifndef __Sphere_h_
#define __Sphere_h_
#include "Structure.h"

class Material;

/** Representation for a spherical quantum dot structure.
    @author John Shumway */
class Sphere : public Structure {
public:
  /** Constructor.  Provide the x,y,z coordinates for the center
      of the sphere and the radius.  All coords are in 
      eight-atom cell lattice units. */
  Sphere(const double x, const double y, const double z, 
         const double radius, const Material* material);

  /** Is a given point inside the sphere? */
  bool isPointInStruct(const Vec3& pt) const;

protected:
  /** The x-coordinate of the center of the sphere, measured in eight 
      atom lattice units. */
  const double x;
  /** The y-coordinate of the center of the sphere, measured in eight 
      atom lattice units. */
  const double y;
  /** The z-coordinate of the center of the sphere, measured in eight 
      atom lattice units. */
  const double z;
  /** The radius of the sphere, measured in eight atom lattice units. */
  const double radius;
  /** The radius squared, used for determining the surface. */
  const double r2;
};
#endif
