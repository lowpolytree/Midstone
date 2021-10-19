#pragma once
#include "Game.h"

class Command
{
public:
	virtual ~Command() {}
	virtual void Execute() = 0;
};

class QuitCommand : public Command
{
public:
	virtual void Execute() override;
};

class PlayCommand : public Command
{
public:
	virtual void Execute() override;
};

class ReplayCommand : public Command 
{
public:
	virtual void Execute() override;
};