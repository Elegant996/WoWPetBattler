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

#ifndef ROBOT_SCREEN_H
#define ROBOT_SCREEN_H

#include "Global.h"
namespace Robot {
	class Window;



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>
/// <copying> Static </copying>

class ROBOT_EXPORT Screen
{
private:
	// Hidden
	 Screen							(void);
	~Screen							(void);
	 Screen							(const Screen& screen);
	 Screen&		operator =		(const Screen& screen);

public:
	// Functions
	static Size		GetResolution	(void);
	static void		EnableAero		(bool state);

	static Color	GrabPixel		(Window window, const Point& point);
	static Color	GrabPixel		(Window window, uint16 x, uint16 y);

	static bool		GrabScreen		(Window window, Image* image,
									 const Bounds& bounds);

	static bool		GrabScreen		(Window window, Image* image,
									 int32 x =  0, int32 y =  0,
									 int32 w = -1, int32 h = -1);
};

} // namespace Robot
#endif // ROBOT_SCREEN_H
