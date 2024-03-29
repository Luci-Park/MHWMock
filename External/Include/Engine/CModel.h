#pragma once
#include "CRes.h"
#include "CMaterial.h"
#include "CMesh.h"
#include "CGameObject.h"

class aiScene;
class aiNode;
struct tModelNode;

class CModel :
	public CRes
{
private:
    vector<Ptr<CMesh>>      m_vecMeshes;
    vector<Ptr<CMaterial>>  m_vecMaterials;
    vector<wstring>         m_vecAnimNames;
    set<wstring>            m_setBoneNames;
    tModelNode*             m_pRootNode;;

public:
    static Ptr<CModel> LoadFromFbx(const wstring& _strRelativePath);
    Ptr<CMesh> GetMesh(UINT _idx) { return _idx < m_vecMeshes.size() ? m_vecMeshes[_idx] : nullptr; }
    Ptr<CMaterial> GetMaterial(int _idx){ return _idx < m_vecMaterials.size() ? m_vecMaterials[_idx] : nullptr; }
    tModelNode* GetRootNode() { return m_pRootNode; }
    CGameObject* CreateGameObjectFromModel();
    void AddBoneName(wstring _strName) { m_setBoneNames.insert(_strName); }

    virtual int Save(const wstring& _strRelativePath) override;
private:
    virtual int Load(const wstring& _strRelativePath) override;

    virtual void UpdateData() {}
public:
    CModel();
    ~CModel();
};

struct tModelNode
{
    tModelNode() 
        : vPos(0, 0, 0)
        , qRot(Quaternion::Identity)
        , vScale(1, 1, 1)
        , vecChildren(0)
        , pMesh(nullptr)
        , pMaterial(nullptr)
    {

    }
    ~tModelNode();
    wstring strName;
    Vec3 vPos;
    Quaternion qRot;
    Vec3 vScale;
    vector<tModelNode*> vecChildren;
    Ptr<CMesh> pMesh;
    Ptr<CMaterial> pMaterial;

    int Save(FILE* _File);
    int Load(FILE* _File);

    static tModelNode* CreateFromAssimp(const aiScene* _aiScene, aiNode* _aiNode, Ptr<CModel> _pModel);
    CGameObject* CreateGameObjectFromNode();
    CGameObject* SpawnGameObjectFromNode();
    tModelNode* FindNode(wstring _strName);
};