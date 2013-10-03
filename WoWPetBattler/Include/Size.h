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

#ifndef ROBOT_SIZE_H
#define ROBOT_SIZE_H

#include "Global.h"
namespace Robot {
	class Point;



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class ROBOT_EXPORT Size
{
public:
	// Constructors
	Size						(int32  value  =  0);
	Size						(int32  w, int32  h);
	Size						(const Point& point);

public:
	// Operators
	Size&		operator +=		(const Size& size);
	Size&		operator -=		(const Size& size);

	Size		operator +		(const Size& size) const;
	Size		operator -		(const Size& size) const;

	bool		operator ==		(const Size& size) const;
	bool		operator !=		(const Size& size) const;

public:
	// Properties
	int32		W;				// Width  of the size
	int32		H;				// Height of the size
};

} // namespace Robot
#endif // ROBOT_SIZE_H
