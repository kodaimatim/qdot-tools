// $Id: LatticeIndexingH5.h,v 1.4 2007/03/14 19:47:50 jshumwa Exp $
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
#ifndef __LatticeIndexingH5_h_
#define __LatticeIndexingH5_h_

#include <string>
#include <valarray>
#include <blitz/tinyvec.h>
#include "StructH5.h"

/** Mapping of actual geometry to an ideal lattice.

    Layout in the H5 file:
    \begin{itemize}
    \item latticeIndexing \begin{itemize}
      \item a (attribute, real[3]) - Lattice constant in atomic units.
      \item a1 (attribute, integer[3]) 
                             - 1st primative cell lattice vector in units of a.
      \item a2 (attribute, integer[3])
                             - 2nd primative cell lattice vector in units of a.
      \item a3 (attribute, integer[3]) 
                             - 3rd primative cell lattice vector in units of a.
      \item nAtomsPerPrimCell (attribute, integer) 
                             - Number of atoms in primative cell.
      \item primativeAtomOffsets (dataset, real[nBase,4])
                             - Positions of atoms in the primative cell in 
                               units of a (cartesian coordinate).
      \item index (dataset, integer[nAtom,4]) - Position of each atom 
                               in ideal lattice, (icell[1:3],ipos).
      \item n1 (attribute, integer[3])
                              - 1st supercell vector, in primative cell coords.
      \item n2 (attribute, integer[3]) 
                              - 2nd supercell vector, in primative cell coords.
      \item n3 (attribute, integer[3])
                              - 3rd supercell vector, in primative cell coords.
    \end{itemize}\end{itemize}

    @author John Shumway */
class LatticeIndexingH5 : public StructH5 {
public:
#ifdef ENABLE_FLOAT
  typedef blitz::TinyVector<float,3> Vec3;
#else
  typedef blitz::TinyVector<double,3> Vec3;
#endif
  typedef blitz::TinyVector<int,3> IVec3;
  /** Index structure (i,j,k,ipos). */
  struct indices {
    int i,j,k,ipos;
  };
  /** Constructor */
  LatticeIndexingH5(const double a, 
    const Vec3& a1, const Vec3& a2, const Vec3& a3, 
    const std::valarray<Vec3>& offset,
    const int natoms, const IVec3 n1, const IVec3 n2, const IVec3 n3);

  /** Write the supercell to a struct.h5 file. */
  void h5Write(const std::string& filename, const int mode=APPEND) const;
  /** Get the number of atoms in the primative cell. */
  int getNAtomPerPrimCell() const;
  /** Get the offset of the ith atom in the primative cell. */
  const Vec3& getPrimAtomOffset(const int i) const;
  /** Get the ideal position of the ith atom in the supercell. */
  const Vec3 getIdealPosition(const int i) const;
  /** Get the ideal position of the ith atom in the supercell,
      divided by the lattice constant. */
  const Vec3 getIdealPositionOverA(const int i) const;
  /** Get the primative cell index of the ith atom in the supercell. */
  int getIPos(const int i) const;
  /** Indexing. */
  mutable std::valarray<indices> index;
  /** Lattice constant in atomic units. */
  const double a;
  /** 1st primative cell lattice vector in units of a. */
  const Vec3 a1;
  /** 2nd primative cell lattice vector in units of a. */
  const Vec3 a2;
  /** 3rd primative cell lattice vector in units of a. */
  const Vec3 a3;
  /** Number of atoms in the primative cell. */
  const int nAtomPerPrimCell;
  /** Offsets of atoms in the primative cell. */
  mutable std::valarray<Vec3> offset;
  /** 1st supercell vector, in primative basis coordinates. */
  const IVec3 n1;
  /** 2nd supercell vector, in primative basis coordinates. */
  const IVec3 n2;
  /** 3rd supercell vector, in primative basis coordinates. */
  const IVec3 n3;
protected:
};
#endif
