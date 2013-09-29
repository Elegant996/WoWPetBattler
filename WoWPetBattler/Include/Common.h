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

#ifndef ROBOT_COMMON_H
#define ROBOT_COMMON_H
namespace Robot {


	
//----------------------------------------------------------------------------//
// Version                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// Defines the current robot version as a string and integer value.

#define ROBOT_VERSION 0x000000
#define ROBOT_VERSION_STR "0.0.0"

////////////////////////////////////////////////////////////////////////////////
/// Can be used as an easier method for checking the robot version.
/// An example: #if (ROBOT_VERSION >= ROBOT_VERSION_CHECK (1, 0, 2))

#define ROBOT_VERSION_CHECK( major, minor, patch ) \
			((major << 16) | (minor << 8) | (patch))



//----------------------------------------------------------------------------//
// Macros                                                                     //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// In the cases that NULL isn't defined, we will define it here.

#ifndef NULL
#define NULL 0
#endif



//----------------------------------------------------------------------------//
// Platforms                                                                  //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// Defines operating system identification macros. For every system, OS_*32 is
/// always defined while OS_*64 is only defined when building the 64-bit version.

#if defined (__linux__)

	#define ROBOT_OS_LINUX32
	#if defined (__x86_64__)
		#define ROBOT_OS_LINUX64
	#endif

#endif

#if defined (__APPLE__) && defined (__MACH__)

	#define ROBOT_OS_MAC32
	#if defined (__x86_64__)
		#define ROBOT_OS_MAC64
	#endif

#endif

#if defined (_WIN32)

	#define ROBOT_OS_WIN32
	#if defined (_WIN64)
		#define ROBOT_OS_WIN64
	#endif

#endif



//----------------------------------------------------------------------------//
// Export                                                                     //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// When building robot as a DLL, BUILDING_ROBOT_SHARED needs to be defined.
/// When building a program which uses the robot DLL, USING_ROBOT_SHARED needs
/// to be defined. When building robot either as a static library or building a
/// program which uses robot as a static library, neither BUILDING_ROBOT_SHARED
/// nor USING_ROBOT_SHARED should be defined.

#if defined (BUILDING_ROBOT_SHARED) && defined (USING_ROBOT_SHARED)
#error both BUILDING_ROBOT_SHARED and USING_ROBOT_SHARED are set - please \
	check the build configuration to ensure that at most one of these is set
#endif

#ifdef ROBOT_OS_WIN32

	#if defined (BUILDING_ROBOT_SHARED)
		#define ROBOT_EXPORT __declspec (dllexport)
	#elif defined (USING_ROBOT_SHARED)
		#define ROBOT_EXPORT __declspec (dllimport)
	#else
		#define ROBOT_EXPORT
	#endif

#elif (__GNUC__ >= 4)
	#define ROBOT_EXPORT __attribute__ ((visibility ("default")))
#else
	#define ROBOT_EXPORT
#endif



//----------------------------------------------------------------------------//
// Types                                                                      //
//----------------------------------------------------------------------------//

typedef signed char			int8;		// Signed  8-bit integer
typedef signed short		int16;		// Signed 16-bit integer
typedef signed int			int32;		// Signed 32-bit integer
typedef signed long long	int64;		// Signed 64-bit integer

typedef unsigned char		uint8;		// Unsigned  8-bit integer
typedef unsigned short		uint16;		// Unsigned 16-bit integer
typedef unsigned int		uint32;		// Unsigned 32-bit integer
typedef unsigned long long	uint64;		// Unsigned 64-bit integer

typedef float				real32;		// 32-bit real value
typedef double				real64;		// 64-bit real value

#if defined (ROBOT_OS_LINUX64) || \
	defined (ROBOT_OS_MAC64  ) || \
	defined (ROBOT_OS_WIN64  )

	typedef  int64			 intptr;	// Signed pointer integer
	typedef uint64			uintptr;	// Signed pointer integer

#else

	typedef  int32			 intptr;	// Unsigned pointer integer
	typedef uint32			uintptr;	// Unsigned pointer integer

#endif

} // namespace Robot
#endif // ROBOT_COMMON_H
