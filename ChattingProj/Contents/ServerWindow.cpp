#include "PrecompiledHeader.h"
#include "ServerWindow.h"
//#include <WS2tcpip.h> // inet_pton �Լ��� ����ϱ� ���� ���
//#include <WinSock2.h> // window.h���� ������ ���ʿ� �־�� �Ѵ�.

//#ifndef _WINSOCK2API_
//#include <WS2tcpip.h>
//#include <WINSOCK2.H>
//#include <windows.h>
//#endif
#pragma comment (lib, "ws2_32") // <= ������ ���� ����� ���� ���̺귯��

ServerWindow::ServerWindow()
{
}

ServerWindow::~ServerWindow()
{
}

void ServerWindow::Start()
{
}

void ServerWindow::OnGUI(float _DeltaTime)
{
    if(false == SelectAccess)
    {
        if (ImGui::Button("Server Host"))
        {
            OpenServer();
            SelectAccess = true;
        }

        if (ImGui::Button("Access Client"))
        {
            Connect();
            SelectAccess = true;
        }
    }
    else
    {
        Accept();
    }
}

void ServerWindow::Accept()
{

}


bool ServerWindow::Connect()
{
    // �� ���α׷��� ��Ʈ��ũ�� ����ҷ���.
    WSAData WsaData;

    // �� ���α׷��� �����쿡�� ������ ����ϰڴٰ� �˷��ִ� �̴ϴ�.
    int errorCode = WSAStartup(MAKEWORD(2, 2), &WsaData);
    if (SOCKET_ERROR == errorCode)
    {
        MsgAssert("socket Error");
        return false;
    }

    MySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (INVALID_SOCKET == MySocket)
    {
        return false;
    }

    SOCKADDR_IN ClientAdd;

    ClientAdd.sin_family = AF_INET;
    ClientAdd.sin_port = htons(Port);

    // ����ȣ��Ʈ ip ����ǻ�Ϳ� ���� �����ϰڴ�.
    //std::string IP = _IP;

    if (SOCKET_ERROR == inet_pton(AF_INET, IP.c_str(), &ClientAdd.sin_addr))
    {
        return false;
    }

    int Len = sizeof(SOCKADDR_IN);

    // ���� �ð��� �ʰ��߽��ϴ�.
    if (SOCKET_ERROR == connect(MySocket, (const sockaddr*)&ClientAdd, Len))
    {
        MsgAssert("Ŀ��Ʈ�� �����߽��ϴ�.");
        return false;
    }

    //RecvThread.Start("Client Recv Thread", std::bind(&GameEngineNet::RecvThreadFunction, ClientSocket, this));

    return true;
}
//
void ServerWindow::OpenServer()
{
    WSAData WsaData;

    int errorCode = WSAStartup(MAKEWORD(2, 2), &WsaData);
    if (SOCKET_ERROR == errorCode)
    {
        MsgAssert("socket Error");
        return;
    }

    SOCKADDR_IN Add;
    Add.sin_family = AF_INET; // ip4�ּ� ü�踦 ���ڴ�.
    Add.sin_port = htons(Port); // ��Ʈ��ũ ��ſ� ��ȿ�� ����� ������� ������ش�.
    if (SOCKET_ERROR == inet_pton(AF_INET, "0.0.0.0", &Add.sin_addr))
    {
        return;
    }

    MySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (INVALID_SOCKET == MySocket)
    {
        return;
    }

    if (SOCKET_ERROR == bind(MySocket, (const sockaddr*)&Add, sizeof(SOCKADDR_IN)))
    {
        return;
    }


    if (SOCKET_ERROR == listen(MySocket, BackLog))
    {
        return;
    }

    //AccpetThread.Start("AcceptFunction", std::bind(GameEngineNetServer::AcceptThread, AcceptSocket, this));

}

void ServerWindow::Send(const char* Data, unsigned int _Size, int _IgnoreID)
{
 /*   if (nullptr == Data)
    {
        MsgAssert("�ƹ��� �����͵� ���� �����͸� �������� �߽��ϴ�.");
    }

    if (0 >= _Size)
    {
        MsgAssert("ũ�Ⱑ ���� �����͸� �������� �մϴ�.");
    }

    if(true == IsServer)
    {
        for (std::pair<const int, SOCKET> UserPair : Users)
        {
            if (_IgnoreID == UserPair.first)
            {
                continue;
            }
            send(UserPair.second, Data, _Size, 0);
        }
    }
    else
    {
		::send(MySocket, Data, _Size, 0);
    }*/
}