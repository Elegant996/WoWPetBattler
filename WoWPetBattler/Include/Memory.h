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

#include "Global.h"
#include "Process.h"
namespace Robot {



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>
/// <copying> Atomic </copying>

class ROBOT_EXPORT Memory
{
	friend class Process;

public:
	// Functions
	Process			GetProcess		(void) const;

	uint64			Read			(const void* address,
									 void* result,
									 uint64 length) const;

	uint64			Read			(const void* address,
									 uint8 indirection,
									 const void** offsets,
									 void* result,
									 uint64 length) const;

	uint64			Write			(const void* address,
									 const void* data,
									 uint64 length) const;

	uint64			Write			(const void* address,
									 uint8 indirection,
									 const void** offsets,
									 const void* data,
									 uint64 length) const;

	bool			IsReadable		(const void* address) const;
	bool			IsWritable		(const void* address) const;
	bool			IsGuarded		(const void* address) const;

	bool			IsReadable		(const void* address,
									 uint8 indirection,
									 const void** offsets) const;

	bool			IsWritable		(const void* address,
									 uint8 indirection,
									 const void** offsets) const;

	bool			IsGuarded		(const void* address,
									 uint8 indirection,
									 const void** offsets) const;

private:
	// Fields
	Process			mProcess;		// Selected process
};

} // namespace Robot
#endif // ROBOT_MEMORY_H
