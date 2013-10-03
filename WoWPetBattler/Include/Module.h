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

#ifndef ROBOT_MODULE_H
#define ROBOT_MODULE_H

#include "Common.h"
#include "Process.h"
#include <string>
namespace Robot {



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class ROBOT_EXPORT Module
{
	friend class Process;

public:
	// Constructors
	Module							(void);

private:
	Module							(Process process,
									 uintptr address);

public:
	// Functions
	std::string		GetName			(void) const;
	std::string		GetPath			(void) const;
	uintptr			GetSize			(void) const;

	uintptr			GetEntry		(void) const;
	Process			GetProcess		(void) const;
	uintptr			GetAddress		(void) const;

public:
	// Operators
	bool			operator ==		(const Module& module) const;
	bool			operator !=		(const Module& module) const;

private:
	// Fields
	Process			mProcess;		// Parent process
	uintptr			mAddress;		// Module address
};

} // namespace Robot
#endif // ROBOT_MODULE_H
