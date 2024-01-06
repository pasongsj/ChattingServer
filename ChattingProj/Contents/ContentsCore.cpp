#include "ContentsCore.h"
#include <EnginePlatform/EngineGUI.h>
#include "CoreWindow.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}



void ContentsCore::ContentsStart()
{

#ifdef _DEBUG
	EngineGUI::GUIWindowCreate<CoreWindow>("CoreWindow");
#endif

}

void ContentsCore::ContentsEnd()
{

}
