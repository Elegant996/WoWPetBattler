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

#ifndef ROBOT_WINDOW_H
#define ROBOT_WINDOW_H

#include "Common.h"
#include <string>
namespace Robot {
	class Process;



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class ROBOT_EXPORT Window
{
public:
	// Constructors
	Window							(uintptr handle = 0);

public:
	// Functions
	bool			IsTopMost		(void) const;
	bool			IsBorderless	(void) const;
	bool			IsMinimized		(void) const;
	bool			IsMaximized		(void) const;

	void			SetTopMost		(bool state);
	void			SetBorderless	(bool state);

	uintptr			GetHandle		(void) const;
	Process			GetProcess		(void) const;

	std::string		GetTitle		(void) const;
	void			SetTitle		(const char* title);

	Bounds			GetBounds		(void) const;
	void			SetBounds		(const Bounds& bounds);

	Point			MapToWindow		(const Point& point) const;
	Point			MapToScreen		(const Point& point) const;

	Bounds			MapToWindow		(const Bounds& bounds) const;
	Bounds			MapToScreen		(const Bounds& bounds) const;

	void			Close			(void) const;
	void			Minimize		(void) const;
	void			Restore			(void) const;
	void			Maximize		(void) const;

	static uint32	Find			(const char* title,
									 Window* results,
									 uint32 length);

	static Window	GetActive		(void);
	static void		SetActive		(const Window& window);

public:
	// Operators
	bool			operator ==		(uintptr handle) const;
	bool			operator !=		(uintptr handle) const;

	bool			operator ==		(const Window& window) const;
	bool			operator !=		(const Window& window) const;

private:
	// Fields
	uintptr			mHandle;		// Handle to the window
};

} // namespace Robot
#endif // ROBOT_WINDOW_H
