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

#ifndef ROBOT_PROCESS_H
#define ROBOT_PROCESS_H

#include "Global.h"
#include <memory>
#include <string>
namespace Robot {

	class Memory;
	class Module;
	class Window;



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>
/// <copying> Shared </copying>

class ROBOT_EXPORT Process
{
public:
	// Constructors
	explicit Process				(int32 pid = 0);

public:
	// Functions
	bool			IsValid			(void) const;

	int32			GetID			(void) const;
	void*			GetHandle		(void) const;
	Memory			GetMemory		(void) const;

	std::string		GetName			(void) const;
	std::string		GetPath			(void) const;

	void			Exit			(void);
	void			Kill			(void);
	bool			HasExited		(void) const;

	bool			IsWoW64			(void) const;

	uint32			GetModules		(const char* name,
									 Module* results,
									 uint32 length) const;

	uint32			GetWindows		(Window* results,
									 uint32 length) const;

	static uint32	Find			(const char* name,
									 Process* results,
									 uint32 length);

	static Process	Create			(const Args& args);
	static Process	GetCurrent		(void);

public:
	// Operators
	bool			operator ==		(int32 pid);
	bool			operator !=		(int32 pid);

	bool			operator ==		(const Process& process);
	bool			operator !=		(const Process& process);

private:
	// Fields
	class Data;
	std::shared_ptr<Data> mData;	// Shared process data
};

} // namespace Robot
#endif // ROBOT_PROCESS_H
