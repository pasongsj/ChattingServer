#pragma once
#include <EngineBase/EngineDebug.h>


// Ό³Έν :
class NetObject
{
	static int ObjectID;
	friend class ServerWindow;
public:

	// constrcuter destructer
	NetObject();
	virtual ~NetObject();

	// delete Function
	NetObject(const NetObject& _Other) = delete;
	NetObject(NetObject&& _Other) noexcept = delete;
	NetObject& operator=(const NetObject& _Other) = delete;
	NetObject& operator=(NetObject&& _Other) noexcept = delete;

	inline bool GetIsServer()
	{
		return m_IsServer;
	}

	inline void Setting(std::string_view _IP, int _Port)
	{
		IP = _IP;
		Port = _Port;
	}

protected:
	virtual void Start() {};
	virtual void Update(float DeltaTime) {};
	virtual void Release()
	{
		if (!(INVALID_SOCKET == m_Socket))
		{
			closesocket(m_Socket);
		}
	}


	bool m_IsServer;

	std::string IP;
	int Port;
	SOCKET m_Socket;

	int BackLog;

	bool CreateSocket(SOCKADDR_IN& Add);

	void Send(const char* Data, unsigned int _Size, int _IgnoreID);

private:



};

