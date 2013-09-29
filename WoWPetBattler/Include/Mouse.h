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

#ifndef ROBOT_MOUSE_H
#define ROBOT_MOUSE_H

#include "Global.h"
namespace Robot {



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

enum Button
{
	ButtonLeft			= 0x01,			// VK_LBUTTON  (N/A)
	ButtonMiddle		= 0x04,			// VK_MBUTTON  (N/A)
	ButtonRight			= 0x02,			// VK_RBUTTON  (N/A)
	ButtonX1			= 0x05,			// VK_XBUTTON1 (N/A)
	ButtonX2			= 0x06,			// VK_XBUTTON2 (N/A)
};

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>
/// <copying> Atomic </copying>

class ROBOT_EXPORT Mouse
{
public:
	// Constructors
	Mouse								(void);

public:
	// Functions
	void				Click			(Button button) const;
	void				Press			(Button button) const;
	void				Release			(Button button) const;

	void				ScrollH			(int32 amount) const;
	void				ScrollV			(int32 amount) const;

	Point				GetPos			(void) const;
	void				SetPos			(const Point& point) const;
	void				SetPos			(uint32 x, uint32 y) const;

	// TODO: Button state

public:
	// Properties
	Range				AutoDelay;		// Auto delay range
};

} // namespace Robot
#endif // ROBOT_MOUSE_H
