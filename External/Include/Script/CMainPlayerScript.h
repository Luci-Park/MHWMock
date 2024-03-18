#pragma once
#include "Engine\CScript.h"
#include "Engine\CGameObject.h"
#include "Engine\CKeyMgr.h"
#include <string>

#include <vector>
#include <map>


enum class Event
{
    IDLE,
    MOVE,
    MOVE_FORWARD,
    ATTACK,
    HIT,
    END,
};

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
    virtual void Enter(CGameObject* player,PlayerStateMachine* StateMachine);
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine);
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine);
};

class PlayerStateMachine
{
private:
    std::map<std::wstring,State*> _States;
    State* _curState;
    CGameObject* _player;
    
public:


    PlayerStateMachine();
    PlayerStateMachine(CGameObject* player);
    ~PlayerStateMachine();
public:
    void CreateState();
    void ChangeState(std::wstring newState);
    void Tick();
};

class ST_PLAYER_IDLE : public State
{
private:
public:
    ST_PLAYER_IDLE();
    ~ST_PLAYER_IDLE() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_MOVE : public State
{
private:
public:
    ST_PLAYER_MOVE();
    ~ST_PLAYER_MOVE() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_MOVE_FORWARD : public State
{
private:
public:
    ST_PLAYER_MOVE_FORWARD();
    ~ST_PLAYER_MOVE_FORWARD() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};