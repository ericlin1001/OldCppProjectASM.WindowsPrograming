class AFX_EXT_CLASS CMouseHook:public CObject
{
public:
	CMouseHook();
	~CMouseHook();
	BOOL StartHook(HWND hWnd);
	BOOL StopHook();
};