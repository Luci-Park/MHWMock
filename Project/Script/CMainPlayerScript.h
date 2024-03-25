#pragma once
#include <string>
#include <map>
#include "pch.h"
#include "Engine\CScript.h"
#include "Engine\CGameObject.h"
#include "Engine\CKeyMgr.h"
#include "Engine\CTransform.h"
#include "Engine\CAnimationStateMachine.h"


#define A_TRUE (AnimParamUnion)true
#define A_FALSE (AnimParamUnion)false

#define A_FORWARD (AnimParamUnion)0
#define A_LEFT (AnimParamUnion)1
#define A_BACKWARD (AnimParamUnion)2
#define A_RIGHT (AnimParamUnion)3

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

class PlayerStateMachine
{
private:
    State*_curState;
    CGameObject* _player;
    CAnimationStateMachine* _ASTM;
    std::map<std::wstring,State*> _States;
    
public:
    PlayerStateMachine();
    PlayerStateMachine(CGameObject* player);
    ~PlayerStateMachine();
public:
    void Begin();
    void CreateState();
    void CreateStateParam();
    void ChangeState(std::wstring newState);
    void Tick();
public:
    void setPlayer(CGameObject* player);
    void SetASTMParam(std::wstring paramId, AnimParamType type, AnimParamUnion param);
    double GetStateDuration();
};

class State
{
private:
    struct StateParam
    {
        AnimParamUnion _uStateparam;
        AnimParamType _eStateparam;
    };
protected:
    static std::map<std::wstring, StateParam> _StateParam;
public:
    State();
    virtual ~State();
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine);
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine);
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine);
public:
    void AddParam(std::wstring paramId, AnimParamUnion Stateparamunion, AnimParamType Stateparamtype);
    StateParam SetParam(std::wstring paramId,AnimParamUnion param);
    void ChangeASTMParam(PlayerStateMachine* PSM, std::wstring paramId, AnimParamUnion param);
    AnimParamUnion GetParam(std::wstring paramId);
    double GetStateDuration(PlayerStateMachine* PSM);
};

class ST_PLAYER_N_IDLE : public State
{
private:
public:
    ST_PLAYER_N_IDLE();
    ~ST_PLAYER_N_IDLE() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

#pragma region N_MOVE class
class ST_PLAYER_N_MOVE : public State
{
private:
public:
    ST_PLAYER_N_MOVE();
    ~ST_PLAYER_N_MOVE() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_N_MOVE_FORWARD : public State
{
private:
public:
    ST_PLAYER_N_MOVE_FORWARD();
    ~ST_PLAYER_N_MOVE_FORWARD() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_N_MOVE_LEFT : public State
{
private:
public:
    ST_PLAYER_N_MOVE_LEFT();
    ~ST_PLAYER_N_MOVE_LEFT() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_N_MOVE_Backward : public State
{
private:
public:
    ST_PLAYER_N_MOVE_Backward();
    ~ST_PLAYER_N_MOVE_Backward() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_N_MOVE_Right : public State
{
private:
public:
    ST_PLAYER_N_MOVE_Right();
    ~ST_PLAYER_N_MOVE_Right() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

#pragma endregion

#pragma region N_HIT class
class ST_PLAYER_N_HIT : public State
{
public:
    ST_PLAYER_N_HIT();
    ~ST_PLAYER_N_HIT() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_N_HIT_F : public State
{
public:
    ST_PLAYER_N_HIT_F();
    ~ST_PLAYER_N_HIT_F() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_N_HIT_L : public State
{
public:
    ST_PLAYER_N_HIT_L();
    ~ST_PLAYER_N_HIT_L() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_N_HIT_B : public State
{
public:
    ST_PLAYER_N_HIT_B();
    ~ST_PLAYER_N_HIT_B() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_N_HIT_R : public State
{
public:
    ST_PLAYER_N_HIT_R();
    ~ST_PLAYER_N_HIT_R() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};
#pragma endregion

class ST_PLAYER_N_ROLLING : public State
{
public:
    ST_PLAYER_N_ROLLING();
    ~ST_PLAYER_N_ROLLING() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

