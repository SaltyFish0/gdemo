//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#include "CommonAPI.h"
#include "LessonX.h"
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////////////////
//
// 主函数入口
//
//////////////////////////////////////////////////////////////////////////////////////////
//屏幕边界
float g_fScreenLeft = 0.f; // 屏幕左边界值
float g_fScreenRight = 0.f; // 右
float g_fScreenTop = 0.f; // 上
float g_fScreenBottom = 0.f; // 下


float g_fSpeedLeft = 0.f; // 左方向速度
float g_fSpeedRight = 0.f; // 右
float g_fSpeedTop = 0.f; // 上
float g_fSpeedBottom = 0.f; // 下

bool y_loadMapflag = false; // 切换地图
bool y_musicPower = true; // 音乐开关

int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR     lpCmdLine,
                   int       nCmdShow)


{
	// 初始化游戏引擎
	if( !dInitGameEngine( hInstance, lpCmdLine ) )
		return 0;

    g_fScreenLeft = dGetScreenLeft();
    g_fScreenRight = dGetScreenRight();
    g_fScreenTop = dGetScreenTop();
    g_fScreenBottom = dGetScreenBottom();
    dSetSpriteWorldLimit("role", WORLD_LIMIT_NULL, g_fScreenLeft, g_fScreenTop, g_fScreenRight, g_fScreenBottom);

	// To do : 在此使用API更改窗口标题
	dSetWindowTitle("Lesson");
	// 加载音乐
	mciSendString(TEXT("open ../SourceCode/resources/music.wav Alias music"),NULL,NULL, NULL);
	mciSendString(TEXT("play music"),NULL,NULL, NULL);
    // 音乐按钮旋转
    dSetSpriteAutoRot("musicPower", 360);
    dResizeWindow(1280, 1024);
	// 引擎主循环，处理屏幕图像刷新等工作
	while( dEngineMainLoop() )
	{
		// 获取两次调用之间的时间差，传递给游戏逻辑处理
		float	fTimeDelta	=	dGetTimeDelta();
		// 执行游戏主循环
		GameMainLoop( fTimeDelta );

        // 切换地图
        if(y_loadMapflag){
            dLoadMap("main.t2d");
        }

	};

	// 关闭游戏引擎
	dShutdownGameEngine();
	return 0;
}

//==========================================================================
//
// 引擎捕捉鼠标移动消息后，将调用到本函数
// 参数 fMouseX, fMouseY：为鼠标当前坐标
//
void dOnMouseMove( const float fMouseX, const float fMouseY )
{
	// 可以在此添加游戏需要的响应函数
	OnMouseMove(fMouseX, fMouseY );
}
//==========================================================================
//
// 引擎捕捉鼠标点击消息后，将调用到本函数
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
//
void dOnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
    // 界面开始开始游戏
    if(iMouseType == 0 && dIsPointInSprite("begin",fMouseX,fMouseY))
    {
        dSetSpriteLinearVelocity("role",20,0);
        printf("Hello World!\n");
    }
    // 音乐按钮 控制播放音乐
    if(iMouseType == 0 && dIsPointInSprite("musicPower",fMouseX,fMouseY))
    {
        if(y_musicPower)
        {
            // 停止旋转,暂停音乐
            dSetSpriteAutoRot("musicPower", 0);
            mciSendString(TEXT("pause music"),NULL,NULL, NULL);
        }else{
            // 旋转... 继续音乐
            dSetSpriteAutoRot("musicPower", 360);
            mciSendString(TEXT("resume music"),NULL,NULL, NULL);
        }
        y_musicPower = !y_musicPower;

    }

    if(iMouseType == 0 && dIsPointInSprite("sf",fMouseX,fMouseY))
    {
        dLoadMap("untitled.t2d");
    }

	// 可以在此添加游戏需要的响应函数
	OnMouseClick(iMouseType, fMouseX, fMouseY);

}
//==========================================================================
//
// 引擎捕捉鼠标弹起消息后，将调用到本函数
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
//
void dOnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{
	// 可以在此添加游戏需要的响应函数
	OnMouseUp(iMouseType, fMouseX, fMouseY);
}
//==========================================================================
//
// 引擎捕捉键盘按下消息后，将调用到本函数
// 参数 iKey：被按下的键，值见 enum KeyCodes 宏定义
// 参数 iAltPress, iShiftPress，iCtrlPress：键盘上的功能键Alt，Ctrl，Shift当前是否也处于按下状态(0未按下，1按下)
//
void dOnKeyDown( const int iKey, const int iAltPress, const int iShiftPress, const int iCtrlPress )
{
	// 可以在此添加游戏需要的响应函数

	OnKeyDown(iKey, iAltPress, iShiftPress, iCtrlPress);
}
//==========================================================================
//
// 引擎捕捉键盘弹起消息后，将调用到本函数
// 参数 iKey：弹起的键，值见 enum KeyCodes 宏定义
//
void dOnKeyUp( const int iKey )
{
	// 可以在此添加游戏需要的响应函数
	OnKeyUp(iKey);
}

//===========================================================================
//
// 引擎捕捉到精灵与精灵碰撞之后，调用此函数
// 精灵之间要产生碰撞，必须在编辑器或者代码里设置精灵发送及接受碰撞
// 参数 szSrcName：发起碰撞的精灵名字
// 参数 szTarName：被碰撞的精灵名字
//
void dOnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
	// 可以在此添加游戏需要的响应函数
	OnSpriteColSprite(szSrcName, szTarName);
}

//===========================================================================
//
// 引擎捕捉到精灵与世界边界碰撞之后，调用此函数.
// 精灵之间要产生碰撞，必须在编辑器或者代码里设置精灵的世界边界限制
// 参数 szName：碰撞到边界的精灵名字
// 参数 iColSide：碰撞到的边界 0 左边，1 右边，2 上边，3 下边
//
void dOnSpriteColWorldLimit( const char *szName, const int iColSide )
{
	// 可以在此添加游戏需要的响应函数
	OnSpriteColWorldLimit(szName, iColSide);

	//判断是否到达世界边界
	if (!strcmp(szName, "role"))
    {
        y_loadMapflag = true;
    }

}

