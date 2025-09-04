// Wc.h
#ifndef _wc_h_
#define _wc_h_

#include "Command.h"

// A command to count words or characters in a text
class Wc : public Command
{
public:
	Wc();
	virtual ~Wc();

	virtual void execute() override;
	void validate() override;
};

#endif