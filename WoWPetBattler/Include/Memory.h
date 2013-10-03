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

#ifndef ROBOT_MEMORY_H
#define ROBOT_MEMORY_H

#include "Common.h"
#include "Process.h"
namespace Robot {



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class ROBOT_EXPORT Memory
{
	friend class Process;

public:
	// Functions
	Process			GetProcess		(void) const;

	bool			IsReadable		(uintptr address) const;
	bool			IsWritable		(uintptr address) const;
	bool			IsGuarded		(uintptr address) const;

	uintptr			ReadData		(uintptr address,
									 void* result,
									 uintptr length) const;

	uintptr			WriteData		(uintptr address,
									 const void* data,
									 uintptr length) const;

	uint32			ProtectRegion	(uintptr address,
									 uint32 protect) const;

public:
	// Operators
	bool			operator ==		(const Memory& memory) const;
	bool			operator !=		(const Memory& memory) const;

private:
	// Fields
	Process			mProcess;		// Selected process
};

} // namespace Robot
#endif // ROBOT_MEMORY_H
