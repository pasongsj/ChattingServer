#include "PrecompiledHeader.h"

#include "ContentsCore.h"
#include <EnginePlatform/EngineGUI.h>
#include "CoreWindow.h"
#include "ServerWindow.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}



void ContentsCore::ContentsStart()
{

#ifdef _DEBUG
	//EngineGUI::GUIWindowCreate<CoreWindow>("CoreWindow");
#endif
	EngineGUI::GUIWindowCreate<ServerWindow>("ServerWindow");

}

void ContentsCore::ContentsEnd()
{

}
