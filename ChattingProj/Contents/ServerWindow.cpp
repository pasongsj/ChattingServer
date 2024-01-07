#include "PrecompiledHeader.h"
#include "ServerWindow.h"
//#include <WS2tcpip.h> // inet_pton 함수를 사용하기 위한 헤더
//#include <WinSock2.h> // window.h보다 무조건 위쪽에 있어야 한다.

//#ifndef _WINSOCK2API_
//#include <WS2tcpip.h>
//#include <WINSOCK2.H>
//#include <windows.h>
//#endif
#pragma comment (lib, "ws2_32") // <= 윈도우 서버 사용을 위한 라이브러리

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
    // 내 프로그램이 네트워크를 사용할래요.
    WSAData WsaData;

    // 이 프로그램이 윈도우에게 서버를 사용하겠다고 알려주는 겁니다.
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

    // 로컬호스트 ip 내컴퓨터에 내가 접속하겠다.
    //std::string IP = _IP;

    if (SOCKET_ERROR == inet_pton(AF_INET, IP.c_str(), &ClientAdd.sin_addr))
    {
        return false;
    }

    int Len = sizeof(SOCKADDR_IN);

    // 접속 시간을 초과했습니다.
    if (SOCKET_ERROR == connect(MySocket, (const sockaddr*)&ClientAdd, Len))
    {
        MsgAssert("커넥트에 실패했습니다.");
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
    Add.sin_family = AF_INET; // ip4주소 체계를 쓰겠다.
    Add.sin_port = htons(Port); // 네트워크 통신에 유효한 에디안 방식으로 만들어준다.
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
        MsgAssert("아무런 데이터도 없는 데이터를 보내려고 했습니다.");
    }

    if (0 >= _Size)
    {
        MsgAssert("크기가 없는 데이터를 보내려고 합니다.");
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