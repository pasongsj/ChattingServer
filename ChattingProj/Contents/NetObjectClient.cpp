#include "PrecompiledHeader.h"
#include "NetObjectClient.h"

NetObjectClient::NetObjectClient() 
{
}

NetObjectClient::~NetObjectClient() 
{
}

void NetObjectClient::Start()
{
    SOCKADDR_IN Add;
    if (false == CreateSocket(Add))
    {
        return;
    }
    if (false == Connect(Add))
    {
        return;
    }
    int a = 0;
}

void NetObjectClient::Update(float DeltaTime)
{

}

bool NetObjectClient::Connect(SOCKADDR_IN _ClientAdd)
{
    int Len = sizeof(SOCKADDR_IN);
    // 접속 시간을 초과했습니다.
    if (SOCKET_ERROR == connect(m_Socket, (const sockaddr*)&_ClientAdd, Len))
    {
        MsgAssert("커넥트에 실패했습니다.");
        return false;
    }
    return true;
}
