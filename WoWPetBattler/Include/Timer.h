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

#ifndef ROBOT_TIMER_H
#define ROBOT_TIMER_H

#include "Common.h"
namespace Robot {



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Measures elapsed time with micro-second accuracy. </summary>

class ROBOT_EXPORT Timer
{
public:
	// Constructors
	Timer						(void);

public:
	// Functions
	void		Start			(void);
	void		Stop			(void);
	void		Reset			(void);

	uint64		GetElapsedSec	(void) const;
	uint64		GetElapsedMil	(void) const;
	uint64		GetElapsedMic	(void) const;

	uint64		GetStartedSec	(void) const;
	uint64		GetStartedMil	(void) const;
	uint64		GetStartedMic	(void) const;

	uint64		GetStoppedSec	(void) const;
	uint64		GetStoppedMil	(void) const;
	uint64		GetStoppedMic	(void) const;

	static void	Sleep			(const Range& mil);

public:
	// Operators
	bool		operator ==		(const Timer& timer) const;
	bool		operator !=		(const Timer& timer) const;

private:
	// Fields
	uint64		mStarted;		// Time started (micro)
	uint64		mStopped;		// Time stopped (micro)
};

} // namespace Robot
#endif // ROBOT_TIMER_H
