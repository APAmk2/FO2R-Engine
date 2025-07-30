#ifndef SCRIPTANY_H
#define SCRIPTANY_H

#ifndef ANGELSCRIPT_H 
// Avoid having to inform include path if header is already include before
#include "angelscript.h"
#endif


BEGIN_AS_NAMESPACE

class CScriptAny 
{
public:
	// Constructors
	CScriptAny(asIScriptEngine *engine);
	CScriptAny(void *ref, int refTypeId, asIScriptEngine *engine);

	// Memory management
	virtual int AddRef() const;
	virtual int Release() const;

	// Copy the stored value from another any object
	CScriptAny &operator=(const CScriptAny&);
	virtual int CopyFrom(const CScriptAny *other);

	// Store the value, either as variable type, integer number, or real number
	virtual void Store(void *ref, int refTypeId);
	virtual void Store(asINT64 &value);
	virtual void Store(double &value);

	// Retrieve the stored value, either as variable type, integer number, or real number
	virtual bool Retrieve(void *ref, int refTypeId) const;
	virtual bool Retrieve(asINT64 &value) const;
	virtual bool Retrieve(double &value) const;

	// Get the type id of the stored value
	virtual int  GetTypeId() const;

	// GC methods
	virtual int  GetRefCount();
	virtual void SetFlag();
	virtual bool GetFlag();
	virtual void EnumReferences(asIScriptEngine *engine);
	virtual void ReleaseAllHandles(asIScriptEngine *engine);

protected:
	virtual ~CScriptAny();
	virtual void FreeObject();

	mutable int refCount;
	mutable bool gcFlag;
	asIScriptEngine *engine;

	// The structure for holding the values
    struct valueStruct
    {
        union
        {
            asINT64 valueInt;
            double  valueFlt;
            void   *valueObj;
        };
        int   typeId;
    };

	valueStruct value;
};

#ifndef FONLINE_DLL
void RegisterScriptAny(asIScriptEngine *engine);
void RegisterScriptAny_Native(asIScriptEngine *engine);
void RegisterScriptAny_Generic(asIScriptEngine *engine);
#endif

END_AS_NAMESPACE

#endif
