#pragma once
#include <memory>
#include <map>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <string_view>
#include <EngineBase/EngineDebug.h>


class EngineGUIWindow :public std::enable_shared_from_this<EngineGUIWindow>
{
	friend class EngineGUI;

private:
	void Begin()
	{
		std::string_view View = GetName();

		ImGui::Begin(View.data());
	}
	void End()
	{
		ImGui::End();
	}
	std::string_view GetName() const
	{
		return NameData;
	}

	void SetName(std::string_view _Name)
	{
		NameData = _Name;
	}

public:
	virtual void Start() {}
	virtual void OnGUI(float _DeltaTime) {};
	std::string NameData;

};

// 설명 :
class EngineGUI
{
public:
	static bool IsInit;

	// constrcuter destructer
	EngineGUI();
	~EngineGUI();

	// delete Function
	EngineGUI(const EngineGUI& _Other) = delete;
	EngineGUI(EngineGUI&& _Other) noexcept = delete;
	EngineGUI& operator=(const EngineGUI& _Other) = delete;
	EngineGUI& operator=(EngineGUI&& _Other) noexcept = delete;

	static void Initialize();

	static void Render(float _DeltaTime);

	static void Release();

	template<typename WindowType>
	static std::shared_ptr<EngineGUIWindow> GUIWindowCreate(std::string_view _Name)
	{
		if (AllWindow.end() != AllWindow.find(_Name.data()))
		{
			MsgAssert("이런 이름을 가진 GUI윈도우는 이미 존재합니다." + std::string(_Name));
			return nullptr;
		}

		std::shared_ptr<EngineGUIWindow> WindowPtr = std::make_shared<WindowType>();
		AllWindow[_Name.data()] = WindowPtr ;
		WindowPtr->SetName(_Name);
		WindowPtr->Start();

		return WindowPtr;
	}

	template<typename ConvertType>
	static std::shared_ptr<ConvertType> FindGUIWindowConvert(std::string_view _Name)
	{
		std::shared_ptr<EngineGUIWindow> Window = FindGUIWindow(_Name);

		return std::dynamic_pointer_cast<ConvertType>(Window);
	}

	static std::shared_ptr<EngineGUIWindow> FindGUIWindow(std::string_view _Name)
	{
		std::map<std::string, std::shared_ptr<EngineGUIWindow>>::iterator FindIter = AllWindow.find(_Name.data());

		if (AllWindow.end() == FindIter)
		{
			return nullptr;
		}

		return FindIter->second;

	}

	
protected:

private:
	static std::map<std::string, std::shared_ptr<EngineGUIWindow>> AllWindow;
};

