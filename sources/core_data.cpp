#include "core_data.h"

CoreData::CoreData()
{
	this->window = NULL;
	this->windowWidth = 800;
	this->windowHeight = 600;
	this->isWireFrameModeOn = false;
}

CoreData::CoreData(const CoreData& other)
{
	this->window = other.window;
	this->windowWidth = other.windowWidth;
	this->windowHeight = other.windowHeight;
	this->isWireFrameModeOn = other.isWireFrameModeOn;
}

CoreData::~CoreData()
{
}

CoreData& CoreData::operator= (const CoreData& other)
{
	if (&other == this)
		return *this;

	// This will not create a new window, rather two objects will reference the same one.
	// So I dont know why would I even need this.
	this->window = other.window;
	this->windowWidth = other.windowWidth;
	this->windowHeight = other.windowHeight;
	this->isWireFrameModeOn = other.isWireFrameModeOn;
	return *this;
}
