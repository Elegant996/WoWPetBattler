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

#ifndef ROBOT_TASKBAR_H
#define ROBOT_TASKBAR_H

#include "Global.h"
namespace Robot {



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>
/// <copying> Atomic </copying>

class ROBOT_EXPORT Taskbar
{
public:
	////////////////////////////////////////////////////////////////////////////////
	/// <summary> </summary>

	enum Location { Left, Top, Right, Bottom };

public:
	// Constructors
	Taskbar						(void);

public:
	// Functions
	bool		Synchronize		(void);

	Bounds		GetBounds		(void) const;
	Size		GetSize			(void) const;
	Point		GetPosition		(void) const;

	Location	GetLocation		(void) const;
	bool		IsTopMost		(void) const;
	bool		IsAutoHide		(void) const;

private:
	// Fields
	Bounds		mBounds;		// Position and size
	Location	mLocation;		// Taskbar location
	bool		mTopMost;		// Is always on top
	bool		mAutoHide;		// Is auto hiding
};

} // namespace Robot
#endif // ROBOT_TASKBAR_H
