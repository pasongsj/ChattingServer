#pragma once
#include <EnginePlatform/EngineGUI.h>

// ���� :
class ServerWindow : public EngineGUIWindow
{
public:
	// constrcuter destructer
	ServerWindow();
	~ServerWindow();

	// delete Function
	ServerWindow(const ServerWindow& _Other) = delete;
	ServerWindow(ServerWindow&& _Other) noexcept = delete;
	ServerWindow& operator=(const ServerWindow& _Other) = delete;
	ServerWindow& operator=(ServerWindow&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void OnGUI(float _DeltaTime) override;

private:
	bool SelectAccess = false;
	bool IsServer;
	std::string IP = "127.0.0.1";
	int Port = 30000;

	int BackLog = 512;
	SOCKET MySocket;
	std::map<int, SOCKET> Users;

	void OpenServer();

	bool Connect();

	void Send(const char* Data, unsigned int _Size, int _IgnoreID);

	void Accept();

};

