#pragma once
#include <EnginePlatform/EngineGUI.h>

// ���� :
class ServerWindow : public EngineGUIWindow
{
public:

	static class NetObject* NetInst;

	// constrcuter destructer
	ServerWindow();
	~ServerWindow();

	// delete Function
	ServerWindow(const ServerWindow& _Other) = delete;
	ServerWindow(ServerWindow&& _Other) noexcept = delete;
	ServerWindow& operator=(const ServerWindow& _Other) = delete;
	ServerWindow& operator=(ServerWindow&& _Other) noexcept = delete;

protected:
	void Start() override;
	void OnGUI(float _DeltaTime) override;
	void Release() override;

private:
	static int UserID;
	//std::string InputBlank = std::string(81,' ');
	char InputBlank[1024] = { 0 };

	char RevData[1024] = { 0 };
	bool SelectAccess = false;
	bool IsServer;
	std::string IP = "127.0.0.1";
	int Port = 30000;
	int BackLog = 512;
	//SOCKET MySocket;

	void Send(const char* Data, unsigned int _Size, int _IgnoreID);

	//void Accept();


};

