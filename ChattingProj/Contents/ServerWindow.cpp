#include "PrecompiledHeader.h"
#include "ServerWindow.h"
#include "NetObject.h"
#include "NetObejctServer.h"
#include "NetObjectClient.h"

int ServerWindow::UserID = 1;
NetObject* ServerWindow::NetInst = nullptr;

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
    if(false == SelectAccess && nullptr == NetInst)
    {
        if (ImGui::Button("Server Host"))
        {
            NetInst =  new NetObejctServer();
            NetInst->Setting(IP, Port);
            NetInst->Start();
            SelectAccess = true;
            IsServer = true;
        }

        if (ImGui::Button("Access Client"))
        {
            NetInst = new NetObjectClient();
            NetInst->Setting(IP, Port);
            NetInst->Start();

            SelectAccess = true;
        }
    }
    else if (nullptr != NetInst)
    {
        NetInst->Update(_DeltaTime);
    }

}

void ServerWindow::Release()
{
    //for (std::pair<int, SOCKET> User : Users)
    //{
    //    closesocket(User.second);
    //}
    //if (nullptr != NetInst)
    //{
    //    NetInst->Release();
    //}
    if (!(INVALID_SOCKET == MySocket))
    {
		closesocket(MySocket);
    }

    
}
