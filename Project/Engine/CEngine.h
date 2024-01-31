#pragma once

class CEngine
	: public CSingleton<CEngine>
{
private:
	HWND	m_hWnd;

	// ������ �ػ�
	Vec2	m_vResolution;
	bool	_UsingGUI;
	

public:
	Vec2 GetWindowResolution() { return m_vResolution; }
	HWND GetMainWnd() { return m_hWnd ; }
	void SetUsingGUI(bool usingGui) { _UsingGUI = usingGui; }
public:
	int init(HWND _hWnd, UINT _iWidth, UINT _iHeight);
	void progress();

private:
	void tick();
	void render();


public:
	CEngine();
	~CEngine();
};
