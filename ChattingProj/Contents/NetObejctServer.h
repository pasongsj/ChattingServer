#pragma once
#include "NetObject.h"

// Ό³Έν :
class NetObejctServer : public NetObject
{
public:
	// constrcuter destructer
	NetObejctServer();
	~NetObejctServer();

	// delete Function
	NetObejctServer(const NetObejctServer& _Other) = delete;
	NetObejctServer(NetObejctServer&& _Other) noexcept = delete;
	NetObejctServer& operator=(const NetObejctServer& _Other) = delete;
	NetObejctServer& operator=(NetObejctServer&& _Other) noexcept = delete;

protected:

private:

};

