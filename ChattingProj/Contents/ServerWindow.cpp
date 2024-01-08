#include "PrecompiledHeader.h"
#include "ServerWindow.h"


int ServerWindow::UserID = 1;

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
            IsServer = true;
        }

        if (ImGui::Button("Access Client"))
        {
            Connect();
            SelectAccess = true;
        }
    }
    else
    {
        if(true == IsServer)
        {
            Accept();
        }
    }
}

void ServerWindow::Accept()
{
    int AddressLen = sizeof(SOCKADDR_IN);
    while (true)
    {
        SOCKADDR_IN ClientAdd;

        memset(&ClientAdd, 0, sizeof(ClientAdd));

        SOCKET ClientSocket = accept(MySocket, (struct sockaddr*)&ClientAdd, &AddressLen);

        if (SOCKET_ERROR == ClientSocket || INVALID_SOCKET == ClientSocket)
        {
            return;
        }

        if (true == Users.contains(UserID))
        {
            MsgAssert("이미 존재하는 유저가 또 존재할수는 없습니다 ID 오류 입니다.");
            return;
        }

        Users[UserID++] = ClientSocket;
        break;
	}
    int a = 0;

}


bool ServerWindow::Connect()
{
    // 내 프로그램이 네트워크를 사용할래요.
    WSAData WsaData;

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
    return true;
}
//
void ServerWindow::OpenServer()
{
    // 소켓 생성
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

    // 포트번호 바인딩
    if (SOCKET_ERROR == bind(MySocket, (const sockaddr*)&Add, sizeof(SOCKADDR_IN)))
    {
        return;
    }

    // 수신대기
    if (SOCKET_ERROR == listen(MySocket, BackLog))
    {
        return;
    }


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

void ServerWindow::Release()
{
    for (std::pair<int, SOCKET> User : Users)
    {
        closesocket(User.second);
    }
    if (!(INVALID_SOCKET == MySocket))
    {
		closesocket(MySocket);
    }
    
}
