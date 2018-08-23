// Channel.h

#ifndef _CHANNEL_h
#define _CHANNEL_h
#include "Engine.h"


class Channel
{
public:
	Channel() :_type(EDIT_CHANNEL_MASTER) {}
	Channel(edit_channel type) :_type(type) {}
	
protected:

private:
	edit_channel _type;
};


#endif

