#ifndef __DUMMY_H__
#define __DUMMY_H__

#include "Module.h"
#include "Globals.h"

class ModuleDummy : public Module
{
	bool Init()
	{
		LOG("\nDummy Init!");
		return true;
	}

	update_status PreUpdate()
	{
		LOG("\nDummy PreUpdate!");
		return update_status::UPDATE_CONTINUE;
	}

	update_status Update()
	{
		LOG("\nDummy Update!");
		return update_status::UPDATE_CONTINUE;
	}

	update_status PostUpdate()
	{
		LOG("\nDummy PostUpdate!");
		return update_status::UPDATE_CONTINUE;
	}

	bool CleanUp()
	{
		LOG("\nDummy CleanUp!");
		return true;
	}
};

#endif // __DUMMY_H__