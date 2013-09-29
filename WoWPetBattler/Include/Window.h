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

#include "Global.h"
#include <string>
namespace Robot {
	class Process;



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>
/// <copying> Atomic </copying>

class ROBOT_EXPORT Window
{
public:
	// Constructors
	Window							(void* handle = NULL);

public:
	// Functions
	bool			IsTopMost		(void) const;
	bool			IsBorderless	(void) const;
	bool			IsMinimized		(void) const;
	bool			IsMaximized		(void) const;

	void			SetTopMost		(bool state);
	void			SetBorderless	(bool state);

	void*			GetHandle		(void) const;
	Process			GetProcess		(void) const;

	std::string		GetTitle		(void) const;
	void			SetTitle		(const char* title);

	Bounds			GetBounds		(void) const;
	void			SetBounds		(const Bounds& bounds);

	Point			MapToWindow		(const Point& point);
	Point			MapToScreen		(const Point& point);

	Bounds			MapToWindow		(const Bounds& bounds);
	Bounds			MapToScreen		(const Bounds& bounds);

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
	bool			operator ==		(void* handle);
	bool			operator !=		(void* handle);

	bool			operator ==		(const Window& window);
	bool			operator !=		(const Window& window);

private:
	// Fields
	void*			mHandle;		// Handle to the window
};

} // namespace Robot
#endif // ROBOT_WINDOW_H
