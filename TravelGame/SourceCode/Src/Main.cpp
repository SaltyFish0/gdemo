//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#include "CommonAPI.h"
#include "LessonX.h"
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////////////////
//
// ���������
//
//////////////////////////////////////////////////////////////////////////////////////////
//��Ļ�߽�
float g_fScreenLeft = 0.f; // ��Ļ��߽�ֵ
float g_fScreenRight = 0.f; // ��
float g_fScreenTop = 0.f; // ��
float g_fScreenBottom = 0.f; // ��


float g_fSpeedLeft = 0.f; // �����ٶ�
float g_fSpeedRight = 0.f; // ��
float g_fSpeedTop = 0.f; // ��
float g_fSpeedBottom = 0.f; // ��

bool y_loadMapflag = false; // �л���ͼ
bool y_musicPower = true; // ���ֿ���

int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR     lpCmdLine,
                   int       nCmdShow)


{
	// ��ʼ����Ϸ����
	if( !dInitGameEngine( hInstance, lpCmdLine ) )
		return 0;

    g_fScreenLeft = dGetScreenLeft();
    g_fScreenRight = dGetScreenRight();
    g_fScreenTop = dGetScreenTop();
    g_fScreenBottom = dGetScreenBottom();
    dSetSpriteWorldLimit("role", WORLD_LIMIT_NULL, g_fScreenLeft, g_fScreenTop, g_fScreenRight, g_fScreenBottom);

	// To do : �ڴ�ʹ��API���Ĵ��ڱ���
	dSetWindowTitle("Lesson");
	// ��������
	mciSendString(TEXT("open ../SourceCode/resources/music.wav Alias music"),NULL,NULL, NULL);
	mciSendString(TEXT("play music"),NULL,NULL, NULL);
    // ���ְ�ť��ת
    dSetSpriteAutoRot("musicPower", 360);
    dResizeWindow(1280, 1024);
	// ������ѭ����������Ļͼ��ˢ�µȹ���
	while( dEngineMainLoop() )
	{
		// ��ȡ���ε���֮���ʱ�����ݸ���Ϸ�߼�����
		float	fTimeDelta	=	dGetTimeDelta();
		// ִ����Ϸ��ѭ��
		GameMainLoop( fTimeDelta );

        // �л���ͼ
        if(y_loadMapflag){
            dLoadMap("main.t2d");
        }

	};

	// �ر���Ϸ����
	dShutdownGameEngine();
	return 0;
}

//==========================================================================
//
// ���沶׽����ƶ���Ϣ�󣬽����õ�������
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
//
void dOnMouseMove( const float fMouseX, const float fMouseY )
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����
	OnMouseMove(fMouseX, fMouseY );
}
//==========================================================================
//
// ���沶׽�������Ϣ�󣬽����õ�������
// ���� iMouseType����갴��ֵ���� enum MouseTypes ����
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
//
void dOnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
    // ���濪ʼ��ʼ��Ϸ
    if(iMouseType == 0 && dIsPointInSprite("begin",fMouseX,fMouseY))
    {
        dSetSpriteLinearVelocity("role",20,0);
        printf("Hello World!\n");
    }
    // ���ְ�ť ���Ʋ�������
    if(iMouseType == 0 && dIsPointInSprite("musicPower",fMouseX,fMouseY))
    {
        if(y_musicPower)
        {
            // ֹͣ��ת,��ͣ����
            dSetSpriteAutoRot("musicPower", 0);
            mciSendString(TEXT("pause music"),NULL,NULL, NULL);
        }else{
            // ��ת... ��������
            dSetSpriteAutoRot("musicPower", 360);
            mciSendString(TEXT("resume music"),NULL,NULL, NULL);
        }
        y_musicPower = !y_musicPower;

    }

    if(iMouseType == 0 && dIsPointInSprite("sf",fMouseX,fMouseY))
    {
        dLoadMap("untitled.t2d");
    }

	// �����ڴ������Ϸ��Ҫ����Ӧ����
	OnMouseClick(iMouseType, fMouseX, fMouseY);

}
//==========================================================================
//
// ���沶׽��굯����Ϣ�󣬽����õ�������
// ���� iMouseType����갴��ֵ���� enum MouseTypes ����
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
//
void dOnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����
	OnMouseUp(iMouseType, fMouseX, fMouseY);
}
//==========================================================================
//
// ���沶׽���̰�����Ϣ�󣬽����õ�������
// ���� iKey�������µļ���ֵ�� enum KeyCodes �궨��
// ���� iAltPress, iShiftPress��iCtrlPress�������ϵĹ��ܼ�Alt��Ctrl��Shift��ǰ�Ƿ�Ҳ���ڰ���״̬(0δ���£�1����)
//
void dOnKeyDown( const int iKey, const int iAltPress, const int iShiftPress, const int iCtrlPress )
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����

	OnKeyDown(iKey, iAltPress, iShiftPress, iCtrlPress);
}
//==========================================================================
//
// ���沶׽���̵�����Ϣ�󣬽����õ�������
// ���� iKey������ļ���ֵ�� enum KeyCodes �궨��
//
void dOnKeyUp( const int iKey )
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����
	OnKeyUp(iKey);
}

//===========================================================================
//
// ���沶׽�������뾫����ײ֮�󣬵��ô˺���
// ����֮��Ҫ������ײ�������ڱ༭�����ߴ��������þ��鷢�ͼ�������ײ
// ���� szSrcName��������ײ�ľ�������
// ���� szTarName������ײ�ľ�������
//
void dOnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����
	OnSpriteColSprite(szSrcName, szTarName);
}

//===========================================================================
//
// ���沶׽������������߽���ײ֮�󣬵��ô˺���.
// ����֮��Ҫ������ײ�������ڱ༭�����ߴ��������þ��������߽�����
// ���� szName����ײ���߽�ľ�������
// ���� iColSide����ײ���ı߽� 0 ��ߣ�1 �ұߣ�2 �ϱߣ�3 �±�
//
void dOnSpriteColWorldLimit( const char *szName, const int iColSide )
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����
	OnSpriteColWorldLimit(szName, iColSide);

	//�ж��Ƿ񵽴�����߽�
	if (!strcmp(szName, "role"))
    {
        y_loadMapflag = true;
    }

}

