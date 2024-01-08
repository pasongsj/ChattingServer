#pragma once
#include <EngineBase/EngineDebug.h>


// Ό³Έν :
class NetObject
{
public:
	static int UserID;
	// constrcuter destructer
	NetObject();
	~NetObject();

	// delete Function
	NetObject(const NetObject& _Other) = delete;
	NetObject(NetObject&& _Other) noexcept = delete;
	NetObject& operator=(const NetObject& _Other) = delete;
	NetObject& operator=(NetObject&& _Other) noexcept = delete;

protected:

private:
	bool m_IsServer;
	std::string IP;
	int Port;
	int BackLog;
	SOCKET m_Socket;

	void CreateSocket();

	void Send(const char* Data, unsigned int _Size, int _IgnoreID);



};

