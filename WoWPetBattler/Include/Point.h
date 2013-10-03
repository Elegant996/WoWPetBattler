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

#ifndef ROBOT_POINT_H
#define ROBOT_POINT_H

#include "Global.h"
namespace Robot {
	class Size;



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class ROBOT_EXPORT Point
{
public:
	// Constructors
	Point						(int32 value  = 0);
	Point						(int32 x, int32 y);
	Point						(const Size& size);

public:
	// Operators
	Point&		operator +=		(const Point& point);
	Point&		operator -=		(const Point& point);

	Point		operator +		(const Point& point) const;
	Point		operator -		(const Point& point) const;

	bool		operator ==		(const Point& point) const;
	bool		operator !=		(const Point& point) const;

	Point		operator -		(void) const;

public:
	// Properties
	int32		X;				// Point X coordinate
	int32		Y;				// Point Y coordinate
};

} // namespace Robot
#endif // ROBOT_POINT_H
