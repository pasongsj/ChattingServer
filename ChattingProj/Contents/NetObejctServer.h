#pragma once
#include "NetObject.h"

// 설명 : 서버 오브젝트
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
	void Start() override;

	void Update(float DeltaTime) override;

	void Release() override
	{
		for (std::pair<int, SOCKET> _User : Users)
		{
			if (!(INVALID_SOCKET == _User.second))
			{
				closesocket(_User.second);
			}
		}
		Users.clear();
		NetObject::Release();
	}

private:
	static int ClientObjectID;

	bool BindPort(SOCKADDR_IN Add);
	bool Listen();
	void Accept();

	bool m_IsAccept = false;



};

