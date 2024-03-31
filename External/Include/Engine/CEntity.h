#pragma once

class CEntity
{
private:
	static UINT g_iNextID;

private:
	wstring		m_strName;
	const UINT	m_iID;
	bool		m_isActive;

public:
	void SetActive(bool _active) { m_isActive = _active; }
	bool IsActive() { return m_isActive; }
	void SetName(const wstring& _strName) {  m_strName = _strName; }
	const wstring& GetName() { return m_strName; }
	UINT GetID() { return m_iID; }

public:
	virtual CEntity* Clone() = 0;

public:
	CEntity();
	CEntity(const CEntity& _other);
	virtual ~CEntity();
};

