#include "PrecompiledHeader.h"
#include "NetObject.h"


int NetObject::ObjectID = 1;

NetObject::NetObject() 
{
}

NetObject::~NetObject() 
{
}

bool NetObject::CreateSocket(SOCKADDR_IN& Add)
{
    // 소켓 생성
    WSAData WsaData;

    int errorCode = WSAStartup(MAKEWORD(2, 2), &WsaData);
    if (SOCKET_ERROR == errorCode)
    {
        MsgAssert("socket Error");
        return false;
    }
    m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (INVALID_SOCKET == m_Socket)
    {
        return false;
    }

    //SOCKADDR_IN Add;
    Add.sin_family = AF_INET; // ip4주소 체계를 쓰겠다.
    Add.sin_port = htons(Port); // 네트워크 통신에 유효한 에디안 방식으로 만들어준다.
    if (SOCKET_ERROR == inet_pton(AF_INET, IP.c_str(), &Add.sin_addr))
    {
        return false;
    }
    return true;
}
