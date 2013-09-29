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

#include "Global.h"
#include "Process.h"
#include <string>
namespace Robot {



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>
/// <copying> Atomic </copying>

class ROBOT_EXPORT Module
{
	friend class Process;

public:
	// Constructors
	Module							(void);

private:
	Module							(Process process,
									 void* address);

public:
	// Functions
	std::string		GetName			(void) const;
	std::string		GetPath			(void) const;
	uint32			GetSize			(void) const;

	const void*		GetEntry		(void) const;
	const void*		GetAddress		(void) const;
	Process			GetProcess		(void) const;

public:
	// Operators
	bool			operator ==		(const Module& module);
	bool			operator !=		(const Module& module);

private:
	// Fields
	void*			mAddress;		// Module address
	Process			mProcess;		// Parent process
};

} // namespace Robot
#endif // ROBOT_MODULE_H
