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
	dPlaySound("../resources/music.wav", 1, 1);

	// ������ѭ����������Ļͼ��ˢ�µȹ���
	while( dEngineMainLoop() )
	{
		// ��ȡ���ε���֮���ʱ�����ݸ���Ϸ�߼�����
		float	fTimeDelta	=	dGetTimeDelta();
		// ִ����Ϸ��ѭ��
		GameMainLoop( fTimeDelta );
        float a = dGetSpritePositionX("role");
        if(a > 1)
        {
          //dLoadMap("untitled.t2d");
          dSetSpriteFlipX("role", 1);
          dSetSpriteLinearVelocity("role", -20, 0);
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
    if(iMouseType==0 && dIsPointInSprite("begin",fMouseX,fMouseY))
    {
        dSetSpriteLinearVelocity("role",20,0);
        float a = dGetSpritePositionX("role");
        dSetSpriteFlipX("role", 0);
        printf("ff=%lf=\n",a);
        printf("Hello World!\n");

        //dGetSpritePosit
        //dLoadMap("untitled.t2d");
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
     if(strcmp(szName, "role") == 0){
                dSetSpriteLinearVelocity(szName,0,0);
                return;
    }
	// �����ڴ������Ϸ��Ҫ����Ӧ����
	OnSpriteColWorldLimit(szName, iColSide);
}

