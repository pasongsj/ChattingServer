#include "ContentsCore.h"
#include <EnginePlatform/EngineGUI.h>

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}



void ContentsCore::ContentsStart()
{

#ifdef _DEBUG
	//EngineGUI::GUIWindowCreate<GameEngineCoreWindow>("CoreWindow");	
#endif

	//EngineGUI::GUIWindowCreate<class TestGUIWindow>("TestGUIWindow");
	//GameEngineGUI::GUIWindowCreate<ServerWindow>("ServerWindow");
	//GameEngineGUI::GUIWindowCreate<MapEditorWindow>("MapEditorWindow");
	//GameEngineGUI::GUIWindowCreate<BossFrogWindow>("BossFrogWindow");
	//GameEngineGUI::GUIWindowCreate<PlayerInfoWindow>("PlayerInfoWindow");
	//

	////InstallFont();

	//GameEngineCore::CreateLevel<CenterLevel>();
	////GameEngineCore::CreateLevel<TestLevel>();
	////GameEngineCore::CreateLevel<ServerTestLevel>();
	//GameEngineCore::CreateLevel<MapEditorLevel>();
	//GameEngineCore::CreateLevel<PhysXTestLevel>();
	//GameEngineCore::CreateLevel<StartLevel>();
	//GameEngineCore::CreateLevel<UITestLevel>();
	//GameEngineCore::CreateLevel<MapTestLevel>();
	//GameEngineCore::CreateLevel<OfficeLevel>();
	//GameEngineCore::CreateLevel<FortressLevel>();
	//GameEngineCore::CreateLevel<BossFrogLevel>();
	//GameEngineCore::CreateLevel<OldCrowLevel>();
	//GameEngineCore::CreateLevel<PlayerTestLevel>();
	//GameEngineCore::CreateLevel<BossTestLevel>();
	//GameEngineCore::CreateLevel<ExplainLevel>();

	//GameEngineCore::ChangeLevel("StartLevel");
}

void ContentsCore::ContentsEnd()
{
	//MapEditorWindow::EditorGUI->ReleaseMapEditor();
	//RemoveFont();
}
//
//
//void ContentsCore::InstallFont()
//{
//	GameEngineDirectory Dir;
//	Dir.MoveParentToDirectory("ContentResources");
//	Dir.Move("ContentResources");
//	Dir.Move("Text");
//	std::vector<GameEngineFile> FontFiles = Dir.GetAllFile({ ".otf", ".ttf" });
//	for (GameEngineFile& File : FontFiles)
//	{
//		if (0 == AddFontResourceA(File.GetFullPath().c_str()))
//		{
//			MsgAssert("폰트 설치에 실패했습니다.");
//			return;
//		}
//
//		SendMessage(GameEngineWindow::GetHWnd(), WM_FONTCHANGE, NULL, NULL);
//	}
//}
//
//void ContentsCore::RemoveFont()
//{
//	GameEngineDirectory Dir;
//	Dir.MoveParentToDirectory("ContentResources");
//	Dir.Move("ContentResources");
//	Dir.Move("Text");
//	std::vector<GameEngineFile> FontFiles = Dir.GetAllFile({ ".otf", ".ttf" });
//	for (GameEngineFile& File : FontFiles)
//	{
//		if (0 == RemoveFontResourceA(File.GetFullPath().data()))
//		{
//			MsgAssert("폰트 삭제에 실패했습니다.");
//			return;
//		}
//
//		SendMessage(GameEngineWindow::GetHWnd(), WM_FONTCHANGE, NULL, NULL);
//	}
//}
