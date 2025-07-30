//
// CScriptFile
//
// This class encapsulates a FILE pointer in a reference counted class for
// use within AngelScript.
//

#ifndef SCRIPTFILE_H
#define SCRIPTFILE_H

#include "scriptstring.h"

//---------------------------
// Compilation settings
//

// Set this flag to turn on/off write support
//  0 = off
//  1 = on

#ifndef AS_WRITE_OPS
#define AS_WRITE_OPS 1
#endif




//---------------------------
// Declaration
//

#ifndef ANGELSCRIPT_H 
// Avoid having to inform include path if header is already include before
#include "angelscript.h"
#endif

#include <string>
#include <stdio.h>

BEGIN_AS_NAMESPACE

class CScriptFile
{
public:
	CScriptFile();

	virtual void AddRef() const;
	virtual void Release() const;

	// TODO: Implement the "r+", "w+" and "a+" modes
	// mode = "r" -> open the file for reading
	//        "w" -> open the file for writing (overwrites existing file)
	//        "a" -> open the file for appending
	virtual int  Open(const std::string &filename, const std::string &mode);
	virtual int  Close();
	virtual int  GetSize() const;
	virtual bool IsEOF() const;

	// Reading
	virtual int			ReadString(unsigned int length, ScriptString& str);
	virtual int			ReadLine(ScriptString& str);
	virtual asINT64     ReadInt(asUINT bytes);
	virtual asQWORD     ReadUInt(asUINT bytes);
	virtual float       ReadFloat();
	virtual double      ReadDouble();

	// Writing
	virtual int WriteString(const std::string &str);
	virtual int WriteInt(asINT64 v, asUINT bytes);
	virtual int WriteUInt(asQWORD v, asUINT bytes);
	virtual int WriteFloat(float v);
	virtual int WriteDouble(double v);

	// Cursor
	virtual int GetPos() const;
	virtual int SetPos(int pos);
	virtual int MovePos(int delta);

	// Big-endian = most significant byte first
	bool mostSignificantByteFirst;

protected:
	virtual ~CScriptFile();

	mutable int refCount;
	FILE       *file;
};

#ifndef FONLINE_DLL
// This function will determine the configuration of the engine
// and use one of the two functions below to register the file type
void RegisterScriptFile(asIScriptEngine *engine);

// Call this function to register the file type
// using native calling conventions
void RegisterScriptFile_Native(asIScriptEngine *engine);

// Use this one instead if native calling conventions
// are not supported on the target platform
void RegisterScriptFile_Generic(asIScriptEngine *engine);
#endif

END_AS_NAMESPACE

#endif
