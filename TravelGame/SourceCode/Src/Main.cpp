//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#include "CommonAPI.h"
#include "LessonX.h"

///////////////////////////////////////////////////////////////////////////////////////////
//
// ���������
//
//////////////////////////////////////////////////////////////////////////////////////////
int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR     lpCmdLine,
                   int       nCmdShow)
float g_fSpeedLeft = 0.f; // �����ٶ�
float g_fSpeedRight = 0.f; // ��
float g_fSpeedTop = 0.f; // ��
float g_fSpeedBottom = 0.f; // ��
{
	// ��ʼ����Ϸ����
	if( !dInitGameEngine( hInstance, lpCmdLine ) )
		return 0;
    dSetSpriteWorldLimit("role", WORLD_LIMIT_NULL, g_fScreenLeft, g_fScreenTop, g_fScreenRight, g_fScreenBottom);



	// To do : �ڴ�ʹ��API���Ĵ��ڱ���
	dSetWindowTitle("Lesson");

	// ������ѭ����������Ļͼ��ˢ�µȹ���
	while( dEngineMainLoop() )
	{
		// ��ȡ���ε���֮���ʱ�����ݸ���Ϸ�߼�����
		float	fTimeDelta	=	dGetTimeDelta();

		// ִ����Ϸ��ѭ��
		GameMainLoop( fTimeDelta );
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
	switch(iKey)
    {
        case KEY_W:
            g_fSpeedTop = -40.f;
            break;
        case KEY_A:
            g_fSpeedLeft = -60.f;
            break;
        case KEY_S:
            g_fSpeedBottom = 40.f;
            break;
        case KEY_D:
            g_fSpeedRight = 60.f;
            break;
        default:
            break;

    }
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
}

