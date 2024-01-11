#include "PrecompiledHeader.h"
#include "NetObejctServer.h"

int NetObejctServer::ClientObjectID = 1;

NetObejctServer::NetObejctServer() 
{
}

NetObejctServer::~NetObejctServer() 
{
}

void NetObejctServer::Start()
{
    m_IsServer = true;
    
    SOCKADDR_IN Add;
    if (false == CreateSocket(Add))
    {
        return;
    }
    if (false == BindPort(Add))
    {
        return;
    }
    if (false == Listen())
    {
        return;
    }
    Accept();
    int a = 0;
}


bool NetObejctServer::BindPort(SOCKADDR_IN Add)
{
    // 포트번호 바인딩
    if (SOCKET_ERROR == bind(m_Socket, (const sockaddr*)&Add, sizeof(SOCKADDR_IN)))
    {
        return false;
    }
    return true;
}

bool NetObejctServer::Listen()
{
    // 수신대기
    if (SOCKET_ERROR == listen(m_Socket, BackLog))
    {
        return false;
    }
    return true;
}

void NetObejctServer::Accept()
{
    int AddressLen = sizeof(SOCKADDR_IN);

    SOCKADDR_IN ClientAdd;

    memset(&ClientAdd, 0, sizeof(ClientAdd));

    SOCKET ClientSocket = accept(m_Socket, (struct sockaddr*)&ClientAdd, &AddressLen);

    if (SOCKET_ERROR == ClientSocket || INVALID_SOCKET == ClientSocket)
    {
        return;
    }

    if (true == Users.contains(ClientObjectID))
    {
        MsgAssert("이미 존재하는 유저가 또 존재할수는 없습니다 ID 오류 입니다.");
        return;
    }
    Client = ClientSocket;
    Users[ClientObjectID++] = ClientSocket;
    m_IsAccept = true;
}

void NetObejctServer::Update(float DeltaTime)
{
    //for (const std::pair<int, SOCKET>& _Cli : Users)
    //{
    //   Read(_Cli.second,
    //}

    int a = 0;

}