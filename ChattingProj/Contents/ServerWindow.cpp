#include "PrecompiledHeader.h"
#include "ServerWindow.h"
#include "NetObject.h"
#include "NetObejctServer.h"
#include "NetObjectClient.h"
#define _CRT_SECURE_NO_WARNINGS

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
            IsServer = true;

            SelectAccess = true;
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
        if(false == NetInst->GetIsServer()) // client
        {
            ImGui::Text("This is Client");
			ImGui::InputText("##TestMessage", &InputBlank[0], 1024);
            ImGui::SameLine();
            if (ImGui::Button("Send"))
            {
                NetInst->Send(reinterpret_cast<char*> (&InputBlank), 1024);
            }
        }
        else // server
        {
            ImGui::Text("This is Server");
            NetInst->Update(_DeltaTime);
            if (true == NetInst->Read(RevData))
            {
                memcpy_s(InputBlank,1024, &RevData[0], 1024);
            }
            ImGui::Text("##RevMessage %s", InputBlank);
            // 변경사항 적용
        }
    }

}

void ServerWindow::Release()
{
    if (nullptr != NetInst)
    {
        NetInst->Release();
        delete NetInst;
        NetInst = nullptr;
    }

}
