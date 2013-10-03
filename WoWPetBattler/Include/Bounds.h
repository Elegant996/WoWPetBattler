////////////////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------------- //
//                                                                            //
//                        (C) 2010-2013  David Krutsko                        //
//                        See LICENSE.md for copyright                        //
//                                                                            //
// -------------------------------------------------------------------------- //
////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------//
// Prefaces                                                                   //
//----------------------------------------------------------------------------//

#ifndef ROBOT_BOUNDS_H
#define ROBOT_BOUNDS_H

#include "Global.h"
namespace Robot {
	class Size;
	class Point;



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class ROBOT_EXPORT Bounds
{
public:
	// Constructors
	Bounds						(void);

	Bounds						(int32 x, int32 y,
								 int32 w, int32 h);

	Bounds						(const Point& p,
								 const Size & s);

public:
	// Functions
	Point		GetPos			(void) const;
	Size		GetSize			(void) const;

	bool		IsEmpty			(void) const;

	int32		GetLeft			(void) const;
	int32		GetTop			(void) const;
	int32		GetBottom		(void) const;
	int32		GetRight		(void) const;

	void		SetLeft			(int32 l);
	void		SetTop			(int32 t);
	void		SetBottom		(int32 b);
	void		SetRight		(int32 r);

	void		FromLTRB		(int32 l, int32 t,
								 int32 r, int32 b);

	bool		Contains		(int32 x, int32 y) const;
	bool		Contains		(const  Point&  p) const;

	void		SetPos			(int32 x, int32 y);
	void		SetPos			(const  Point&  p);

	void		SetSize			(int32 w, int32 h);
	void		SetSize			(const  Size &  s);

public:
	// Operators
	bool		operator ==		(const Bounds& bounds) const;
	bool		operator !=		(const Bounds& bounds) const;

public:
	// Properties
	int32		X;				// Top-left X coordinate
	int32		Y;				// Top-left Y coordinate
	int32		W;				// Total bounds width
	int32		H;				// Total bounds height
};

} // namespace Robot
#endif // ROBOT_BOUNDS_H
