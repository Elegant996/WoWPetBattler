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

#include "Common.h"
namespace Robot {
	class Window;



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

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
	static void		EnableAero		(bool enable);

	static Color	GrabPixel		(const Window& window,
									 const Point& point);

	static Color	GrabPixel		(const Window& window,
									 int16  x, int16  y);

	static bool		GrabScreen		(const Window& window,
									 Image* image,
									 const Bounds& bounds);

	static bool		GrabScreen		(const Window& window,
									 Image* image,
									 int16 x =  0, int16 y =  0,
									 int16 w = -1, int16 h = -1);
};

} // namespace Robot
#endif // ROBOT_SCREEN_H
