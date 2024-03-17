#pragma once
#include "Engine\CScript.h"
#include "Engine\CGameObject.h"

class State;
class PlayerStateMachine;
class ST_PLAYER_IDLE;
class CMainPlayerScript :
    public CScript
{
public:
    enum class OBJPARAMNAME
    {
        End,
    };
private:
    bool _Gravity;
    PlayerStateMachine* _stateMachine;
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void OnCollisionEnter(CCollider3D* _Other) override;

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;
    CLONE(CMainPlayerScript);
public:
    CMainPlayerScript();
    ~CMainPlayerScript();
};

class State
{
private:

public:
    State();
    virtual ~State();
public:
    virtual void Enter(CGameObject* player);
    virtual void Tick(CGameObject* player);
    virtual void Exit(CGameObject* player);
};

class PlayerStateMachine
{
private:
    State* _curState;
    CGameObject* _player;
public:
    PlayerStateMachine();
    PlayerStateMachine(CGameObject* player);
    ~PlayerStateMachine();
public:
    void ChangeState(State* newState);
    void Tick();
};

class ST_PLAYER_IDLE : public State
{
private:
public:
    ST_PLAYER_IDLE();
    ~ST_PLAYER_IDLE() override;
public:
    virtual void Enter(CGameObject* player) override;
    virtual void Tick(CGameObject* player) override;
    virtual void Exit(CGameObject* player) override;
};