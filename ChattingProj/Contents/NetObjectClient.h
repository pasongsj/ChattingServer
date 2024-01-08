#pragma once
#include "NetObject.h"
// Ό³Έν :
class NetObjectClient : public NetObject
{
public:
	// constrcuter destructer
	NetObjectClient();
	~NetObjectClient();

	// delete Function
	NetObjectClient(const NetObjectClient& _Other) = delete;
	NetObjectClient(NetObjectClient&& _Other) noexcept = delete;
	NetObjectClient& operator=(const NetObjectClient& _Other) = delete;
	NetObjectClient& operator=(NetObjectClient&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float DeltTime) override;

private:

	bool Connect(SOCKADDR_IN _ClientAdd);

};

