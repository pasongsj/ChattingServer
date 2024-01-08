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
            MsgAssert("�̹� �����ϴ� ������ �� �����Ҽ��� �����ϴ� ID ���� �Դϴ�.");
            return;
        }

        Users[UserID++] = ClientSocket;
        break;
	}
    int a = 0;

}


bool ServerWindow::Connect()
{
    // �� ���α׷��� ��Ʈ��ũ�� ����ҷ���.
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

    // ����ȣ��Ʈ ip ����ǻ�Ϳ� ���� �����ϰڴ�.

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
    return true;
}
//
void ServerWindow::OpenServer()
{
    // ���� ����
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

    // ��Ʈ��ȣ ���ε�
    if (SOCKET_ERROR == bind(MySocket, (const sockaddr*)&Add, sizeof(SOCKADDR_IN)))
    {
        return;
    }

    // ���Ŵ��
    if (SOCKET_ERROR == listen(MySocket, BackLog))
    {
        return;
    }


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
