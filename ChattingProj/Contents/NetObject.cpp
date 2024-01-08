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
    // ���� ����
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
    Add.sin_family = AF_INET; // ip4�ּ� ü�踦 ���ڴ�.
    Add.sin_port = htons(Port); // ��Ʈ��ũ ��ſ� ��ȿ�� ����� ������� ������ش�.
    if (SOCKET_ERROR == inet_pton(AF_INET, IP.c_str(), &Add.sin_addr))
    {
        return false;
    }
    return true;
}
