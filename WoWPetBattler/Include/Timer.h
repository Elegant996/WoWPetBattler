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

#include "Global.h"
namespace Robot {



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Measures elapsed time with micro-second accuracy. </summary>
/// <copying> Atomic </copying>

class ROBOT_EXPORT Timer
{
public:
	// Constructors
	Timer						(void);

public:
	// Functions
	uint64		GetElapsedSec	(void) const;
	uint64		GetElapsedMil	(void) const;
	uint64		GetElapsedMic	(void) const;

	void		Start			(void);
	void		Stop			(void);
	void		Reset			(void);

	int64		GetSecsTo		(const Timer& timer) const;
	int64		GetMilsTo		(const Timer& timer) const;
	int64		GetMicsTo		(const Timer& timer) const;

	static void	Sleep			(const Range& mil);

public:
	// Operators
	bool		operator ==		(const Timer& timer) const;
	bool		operator !=		(const Timer& timer) const;

private:
	// Fields
	uint64		mT1;			// Time started (micro)
	uint64		mT2;			// Time stopped (micro)
};

} // namespace Robot
#endif // ROBOT_TIMER_H
