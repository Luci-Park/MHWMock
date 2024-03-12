#pragma once
#include "CEntity.h"


class CComponent;
class CTransform;
class CMeshRender;
class CSkinnedMeshRender;
class CParticleSystem;
class CCollider3D;
class CAnimator2D;
class CAnimator3D;
class CLight2D;
class CLight3D;
class CCamera;
class CRenderComponent;
class CSkyBox;
class CTileMap;
class CDecal;
class CLandScape;
class CScript;
class CBoneHolder;
class CCanvas;

#define GET_COMPONENT(Type, TYPE) C##Type* Type() const { return (C##Type*)m_arrCom[(UINT)COMPONENT_TYPE::TYPE]; }

class CGameObject :
    public CEntity
{
private:
    CComponent*             m_arrCom[(UINT)COMPONENT_TYPE::END];
    CRenderComponent*       m_RenderCom;
    vector<CScript*>        m_vecScript;

    CGameObject*            m_Parent;
    vector<CGameObject*>    m_vecChildren;
    vector<CGameObject*>    m_vecAllChildren;

    int                     m_iSiblingIdx;
    int                     m_iLayerIdx;
    bool                    m_bDead;
    float                   m_LifeTime;
    float                   m_CurLifeTime;
    bool                    m_bLifeSpan;

public:
    void begin();       

    void tick();        
    virtual void finaltick();
    void finaltick_module();
    void render();
    void render_shadowmap();
    void Release();

public:
    void AddComponent(CComponent* _Component);
    void AddChild(CGameObject* _Object);
    void SetParent(CGameObject* _Object);
    int GetSiblingIdx() { return m_iSiblingIdx; }

    void AddCollider3D(SHAPE_TYPE _type, ACTOR_TYPE _actorType);

    int DeleteComponent(COMPONENT_TYPE _type);

    CComponent* GetComponent(COMPONENT_TYPE _ComType) { return m_arrCom[(UINT)_ComType]; }
    const vector<CGameObject*>& GetChildren() { return m_vecChildren; }
    const vector<CGameObject*>& GetAllChildren();
    void PushChildObj(CGameObject* _Obj);

    CGameObject* GetParent() const { return m_Parent; }
    CGameObject* GetRoot() const;
    CGameObject* FindChildByName(wstring _strName);

    GET_COMPONENT(Transform, TRANSFORM);
    GET_COMPONENT(MeshRender, MESHRENDER);
    GET_COMPONENT(SkinnedMeshRender, SKINNEDMESHRENDER);
    GET_COMPONENT(ParticleSystem, PARTICLESYSTEM);
    GET_COMPONENT(Camera, CAMERA);
    GET_COMPONENT(Collider3D, COLLIDER3D);
    GET_COMPONENT(Light2D, LIGHT2D);
    GET_COMPONENT(TileMap, TILEMAP);
    GET_COMPONENT(Animator2D, ANIMATOR2D);
    GET_COMPONENT(Animator3D, ANIMATOR3D);
    GET_COMPONENT(Light3D, LIGHT3D);  
    GET_COMPONENT(SkyBox, SKYBOX);
    GET_COMPONENT(Decal, DECAL);
    GET_COMPONENT(LandScape, LANDSCAPE);
    GET_COMPONENT(BoneHolder, BONEHOLDER); 
    GET_COMPONENT(Canvas, CANVAS);

    CComponent* GetComponentInParent(COMPONENT_TYPE _CType);

    CRenderComponent* GetRenderComponent() const {  return m_RenderCom; }

    void SetLayerIndex(int _Idx) { m_iLayerIdx = _Idx; }
    int GetLayerIndex() { return m_iLayerIdx; }

    template<typename T>
    T* GetScript();

    const vector<CScript*>& GetScripts() { return m_vecScript; }

    void SetLifeSpan(float _fTime)
    {
        if (m_bLifeSpan)
            return;

        m_LifeTime = _fTime;
        m_bLifeSpan = true;
    }

    bool IsDead() { return m_bDead; }
    bool IsAncestor(CGameObject* _Target);


private:
    void DisconnectFromParent();
    void ChangeToChildType();
    void AddParentList();

    void SetSiblingIdx(int _idx);


    CLONE(CGameObject)    
public:
    CGameObject();
    CGameObject(const CGameObject& _Other);
    ~CGameObject();

    friend class CLayer;
    friend class CEventMgr;
};

template<typename T>
inline T* CGameObject::GetScript()
{
    for (size_t i = 0; i < m_vecScript.size(); ++i)
    {
        T* pScript = dynamic_cast<T*> (m_vecScript[i]);
        if (nullptr != pScript)
            return pScript;
    }

    return nullptr;
}
