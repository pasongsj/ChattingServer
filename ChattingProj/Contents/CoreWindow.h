#pragma once
#include <EnginePlatform/EngineGUI.h>

// Ό³Έν :
class CoreWindow : public EngineGUIWindow
{
public:
	// constrcuter destructer
	CoreWindow();
	~CoreWindow();

	// delete Function
	CoreWindow(const CoreWindow& _Other) = delete;
	CoreWindow(CoreWindow&& _Other) noexcept = delete;
	CoreWindow& operator=(const CoreWindow& _Other) = delete;
	CoreWindow& operator=(CoreWindow&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void OnGUI(float _DeltaTime) override;

private:

};

