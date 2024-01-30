#pragma once
#include "CRenderComponent.h"

#include "ptr.h"
#include "CParticleUpdateShader.h"

class CStructuredBuffer;

class CParticleSystem :
    public CRenderComponent
{
private:
    CStructuredBuffer*          m_ParticleBuffer;
    CStructuredBuffer*          m_RWBuffer;
    CStructuredBuffer*          m_ModuleDataBuffer;
    
    tParticleModule             m_ModuleData;
    Ptr<CParticleUpdateShader>  m_UpdateCS;
    Ptr<CTexture>               m_ParticleTexture;
   
    float                       m_AccTime;

public:
    void ActiveModule(PARTICLE_MODULE _ModuleType) { m_ModuleData.ModuleCheck[(UINT)_ModuleType] = true; }
    void DeactivateModule(PARTICLE_MODULE _ModuleType) { m_ModuleData.ModuleCheck[(UINT)_ModuleType] = false; }


    // 초당 생성 개수 설정
    void SetSpawnRate(int _SpawnRate) { m_ModuleData.SpawnRate = _SpawnRate; }

    // 생성 시 초기 색상 설정
    void SetSpawnInitialColor(Vec3 _vInitialColor) { m_ModuleData.vSpawnColor = _vInitialColor; }

    void SetModuleData(tParticleModule _Module) { m_ModuleData = _Module; }
    tParticleModule GetModuleData() { return m_ModuleData; }
    
    void SetParticleMaterial(Ptr<CTexture> _Texture) { m_ParticleTexture = _Texture; }
    Ptr<CTexture> GetParticleMaterial() { return m_ParticleTexture; }


public:
    virtual void finaltick() override;
    virtual void render() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CParticleSystem);
public:
    CParticleSystem();
    ~CParticleSystem();
};

