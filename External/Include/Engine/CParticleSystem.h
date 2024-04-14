#pragma once
#include "CRenderComponent.h"
#include "CParticleUpdateShader.h"

class CStructuredBuffer;

class CParticleSystem :
    public CRenderComponent
{
private:
    struct AnimeFrame
    {
        Vec2 vFrames;
        Vec2 vSize;
        Vec2 vLeftTop;
        float fDuration;
    };

    Vec2                        m_AnimeXY;
    vector<AnimeFrame>          m_Frames;

    CStructuredBuffer*          m_ParticleBuffer;
    CStructuredBuffer*          m_RWBuffer;
    CStructuredBuffer*          m_ModuleDataBuffer;
    CStructuredBuffer*          m_AnimeDataBuffer;
    
    tParticleModule             m_ModuleData;
    tParticleAnime              m_AnimeData;
    Ptr<CParticleUpdateShader>  m_UpdateCS;
    Ptr<CTexture>               m_ParticleTexture;
   
    float                       m_AccTime;
    float                       m_AnimeTime;
    float                       m_ActiveTime;
    float                       m_DeadTime;
    int                         m_AnimeIdx;
    bool                        m_IsAnime;
public:
    void ActiveModule(PARTICLE_MODULE _ModuleType) { m_ModuleData.ModuleCheck[(UINT)_ModuleType] = true; }
    void DeactivateModule(PARTICLE_MODULE _ModuleType) { m_ModuleData.ModuleCheck[(UINT)_ModuleType] = false; }


    // 초당 생성 개수 설정
    void SetSpawnRate(int _SpawnRate) { m_ModuleData.SpawnRate = _SpawnRate; }

    // 생성 시 초기 색상 설정
    void SetSpawnInitialColor(Vec3 _vInitialColor) { m_ModuleData.vSpawnColor = _vInitialColor; }
    void SetSpawnInitialSpeed(float _Speed) { m_ModuleData.Speed = _Speed; }
    void SetSpawnInitialStartScale(float _Scale) { m_ModuleData.StartScale = _Scale; }
    void SetSpawnInitialEndScale(float _Scale) { m_ModuleData.EndScale = _Scale; }
    void SetSpawnInitialRate(float rate) { m_ModuleData.SpawnRate = rate; }

    void SetModuleData(tParticleModule _Module) { m_ModuleData = _Module; }
    tParticleModule GetModuleData() { return m_ModuleData; }
    
    void SetParticleTexture(Ptr<CTexture> _Texture) { m_ParticleTexture = _Texture; }
    Ptr<CTexture> GetParticleTexture() { return m_ParticleTexture; }

    void IsAnime(bool isanime) { m_IsAnime = isanime; }
    bool IsAnime(void) { return m_IsAnime; }

    void AnimeXY(Vec2 XY) { m_AnimeXY = XY; }
    Vec2 AnimeXY(void) { return m_AnimeXY; }

    void DeadTime(float time) { m_DeadTime = time; }
    float DeadTime(void) { return m_DeadTime; }
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

