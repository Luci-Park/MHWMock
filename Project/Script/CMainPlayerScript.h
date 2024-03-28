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
#define A_NONE (AnimParamUnion)4

#define A_F 0
#define A_L 1
#define A_B 2
#define A_R 3

#define A_0 (AnimParamUnion)0
#define A_1 (AnimParamUnion)1
#define A_2 (AnimParamUnion)2
#define A_3 (AnimParamUnion)3
#define A_4 (AnimParamUnion)4

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
    CGameObject* _Camera;
    bool _bCamera;
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void OnCollisionEnter(CCollider3D* _Other) override;

    virtual void OnAnimationBegin(IAnimationState* _pState) override;
    virtual void OnAnimationEndStart(IAnimationState* _pState) override;
    virtual void OnAnimationEndFinished(IAnimationState* _pState) override;
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
    CGameObject* _Camera;
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
    void setCamera(CGameObject* camera);
    void SetASTMParam(std::wstring paramId, AnimParamType type, AnimParamUnion param);
    void ChangeASTMParam(std::wstring paramId, AnimParamUnion param);
public:
    void OnAnimationBegin(IAnimationState* _pState);
    void OnAnimationEndStart(IAnimationState* _pState);
    void OnAnimationEndFinished(IAnimationState* _pState);
    
public:
    double GetStateDuration();
    AnimParamUnion GetASTMParam(std::wstring paramId);
    CGameObject* GetCamera();
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
    bool    m_IsAnimationEnd;
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
    AnimParamUnion GetParam(std::wstring paramId , PlayerStateMachine* PSM);
    double GetStateDuration(PlayerStateMachine* PSM);
    int CalculateDir(float dot, float cross);
    void ReSet() { m_IsAnimationEnd = false; }
public:
    virtual void OnAnimationBegin(IAnimationState* _pState, PlayerStateMachine* StateMachine) {}
    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) {}
    virtual void OnAnimationEndFinished(IAnimationState* _pState, PlayerStateMachine* StateMachine) {}
};


#pragma region Idle State

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

class ST_PLAYER_WP_IDLE : public State
{
private:
public:
    ST_PLAYER_WP_IDLE();
    ~ST_PLAYER_WP_IDLE() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_AXE_IDLE : public State
{
public:
    ST_PLAYER_AXE_IDLE();
    ~ST_PLAYER_AXE_IDLE() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

#pragma endregion

#pragma region Move State

#pragma region N State

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

#pragma region Wp State
class ST_PLAYER_WP_MOVE : public State
{
private:
public:
    ST_PLAYER_WP_MOVE();
    ~ST_PLAYER_WP_MOVE() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_WP_MOVE_Forward : public State
{
private:
public:
    ST_PLAYER_WP_MOVE_Forward();
    ~ST_PLAYER_WP_MOVE_Forward() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_WP_MOVE_Right : public State
{
private:
public:
    ST_PLAYER_WP_MOVE_Right();
    ~ST_PLAYER_WP_MOVE_Right() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_WP_MOVE_Left : public State
{
private:
public:
    ST_PLAYER_WP_MOVE_Left();
    ~ST_PLAYER_WP_MOVE_Left() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_WP_MOVE_Backward : public State
{
private:
public:
    ST_PLAYER_WP_MOVE_Backward();
    ~ST_PLAYER_WP_MOVE_Backward() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

#pragma endregion

#pragma region Wp Axe State

class ST_PLAYER_AXE_MOVE : public State
{
public:
    ST_PLAYER_AXE_MOVE();
    ~ST_PLAYER_AXE_MOVE() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_AXE_MOVE_FORWARD : public State
{
public:
    ST_PLAYER_AXE_MOVE_FORWARD();
    ~ST_PLAYER_AXE_MOVE_FORWARD() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;

};

class ST_PLAYER_AXE_MOVE_LEFT : public State
{
public:
    ST_PLAYER_AXE_MOVE_LEFT();
    ~ST_PLAYER_AXE_MOVE_LEFT() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;

};

class ST_PLAYER_AXE_MOVE_RIGHT : public State
{
public:
    ST_PLAYER_AXE_MOVE_RIGHT();
    ~ST_PLAYER_AXE_MOVE_RIGHT() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;

};

class ST_PLAYER_AXE_MOVE_BACKWARD : public State
{
public:
    ST_PLAYER_AXE_MOVE_BACKWARD();
    ~ST_PLAYER_AXE_MOVE_BACKWARD() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;

};

#pragma endregion

#pragma endregion

#pragma region Hit State

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

    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
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

    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
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

    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
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

    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_WP_HIT : public State
{
public:
    ST_PLAYER_WP_HIT();
    ~ST_PLAYER_WP_HIT() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_WP_HIT_F : public State
{
public:
    ST_PLAYER_WP_HIT_F();
    ~ST_PLAYER_WP_HIT_F() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;

    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_WP_HIT_L : public State
{
public:
    ST_PLAYER_WP_HIT_L();
    ~ST_PLAYER_WP_HIT_L() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;

    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_WP_HIT_B : public State
{
public:
    ST_PLAYER_WP_HIT_B();
    ~ST_PLAYER_WP_HIT_B() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;

    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_WP_HIT_R : public State
{
public:
    ST_PLAYER_WP_HIT_R();
    ~ST_PLAYER_WP_HIT_R() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;

    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};
class ST_PLAYER_WP_AXE_HIT : public State
{
public:
    ST_PLAYER_WP_AXE_HIT();
    ~ST_PLAYER_WP_AXE_HIT() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_WP_AXE_HIT_F : public State
{
public:
    ST_PLAYER_WP_AXE_HIT_F();
    ~ST_PLAYER_WP_AXE_HIT_F() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;

    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_WP_AXE_HIT_L : public State
{
public:
    ST_PLAYER_WP_AXE_HIT_L();
    ~ST_PLAYER_WP_AXE_HIT_L() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;

    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_WP_AXE_HIT_B : public State
{
public:
    ST_PLAYER_WP_AXE_HIT_B();
    ~ST_PLAYER_WP_AXE_HIT_B() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;

    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_WP_AXE_HIT_R : public State
{
public:
    ST_PLAYER_WP_AXE_HIT_R();
    ~ST_PLAYER_WP_AXE_HIT_R() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;

    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};

#pragma endregion

#pragma region Rolling

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
class ST_PLAYER_WP_ROLLING : public State
{
public:
    ST_PLAYER_WP_ROLLING();
    ~ST_PLAYER_WP_ROLLING() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_WP_AXE_ROLLING : public State
{
public:
    ST_PLAYER_WP_AXE_ROLLING();
    ~ST_PLAYER_WP_AXE_ROLLING() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

#pragma endregion

#pragma region Wp_Attack

class ST_PLAYER_WP_ATTACK : public State
{
public:
    ST_PLAYER_WP_ATTACK();
    ~ST_PLAYER_WP_ATTACK() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

#pragma region Wp_Sheld_Attack

class ST_PLAYER_WP_SHELD_ATTACK : public State
{
public:
    ST_PLAYER_WP_SHELD_ATTACK();
    ~ST_PLAYER_WP_SHELD_ATTACK() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};


#pragma endregion

#pragma region Wp_Dash_Attack

class ST_PLAYER_WP_DASH_ATTACK : public State
{
public:
    ST_PLAYER_WP_DASH_ATTACK();
    ~ST_PLAYER_WP_DASH_ATTACK() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};

#pragma endregion




class ST_PLAYER_WP_ATTACK_COMBOSLASH_01 : public State
{
public:
    ST_PLAYER_WP_ATTACK_COMBOSLASH_01();
    ~ST_PLAYER_WP_ATTACK_COMBOSLASH_01() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;

};

class ST_PLAYER_WP_ATTACK_COMBOSLASH_02 : public State
{
public:
    ST_PLAYER_WP_ATTACK_COMBOSLASH_02();
    ~ST_PLAYER_WP_ATTACK_COMBOSLASH_02() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};


class ST_PLAYER_WP_ATTACK_COMBOSLASH_03 : public State
{
public:
    ST_PLAYER_WP_ATTACK_COMBOSLASH_03();
    ~ST_PLAYER_WP_ATTACK_COMBOSLASH_03() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_WP_BOTTLE_CHARGE : public State
{
public:
    ST_PLAYER_WP_BOTTLE_CHARGE();
    ~ST_PLAYER_WP_BOTTLE_CHARGE() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};

//charge enchent knife
class ST_PLAYER_WP_CHARGE_K_ENCHENT : public State
{
public:
    ST_PLAYER_WP_CHARGE_K_ENCHENT();
    ~ST_PLAYER_WP_CHARGE_K_ENCHENT() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};
//enchent knife attack
class ST_PLAYER_WP_K_ENCHENT_ATTACK : public State
{
public:
    ST_PLAYER_WP_K_ENCHENT_ATTACK();
    ~ST_PLAYER_WP_K_ENCHENT_ATTACK() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};

//charge
class ST_PLAYER_WP_CHARGE : public State
{
public:
    ST_PLAYER_WP_CHARGE();
    ~ST_PLAYER_WP_CHARGE() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};

//double slash
class ST_PLAYER_WP_DOUBLE_SLASH : public State
{
public:
    ST_PLAYER_WP_DOUBLE_SLASH();
    ~ST_PLAYER_WP_DOUBLE_SLASH() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};

//upper slash
class ST_PLAYER_WP_UPPER_SLASH : public State
{
public:
    ST_PLAYER_WP_UPPER_SLASH();
    ~ST_PLAYER_WP_UPPER_SLASH() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};

//sliding attck_f
class ST_PLAYER_WP_SLIDING_ATTACK_F : public State
{
public:
    ST_PLAYER_WP_SLIDING_ATTACK_F();
    ~ST_PLAYER_WP_SLIDING_ATTACK_F() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};

//sliding attck_l
class ST_PLAYER_WP_SLIDING_ATTACK_L : public State
{
public:
    ST_PLAYER_WP_SLIDING_ATTACK_L();
    ~ST_PLAYER_WP_SLIDING_ATTACK_L() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};
//sliding attck_r
class ST_PLAYER_WP_SLIDING_ATTACK_R : public State
{
public:
    ST_PLAYER_WP_SLIDING_ATTACK_R();
    ~ST_PLAYER_WP_SLIDING_ATTACK_R() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};

//sliding attck_b
class ST_PLAYER_WP_SLIDING_ATTACK_B : public State
{
public:
    ST_PLAYER_WP_SLIDING_ATTACK_B();
    ~ST_PLAYER_WP_SLIDING_ATTACK_B() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};

//super bust attack
class ST_PLAYER_SUPER_BUST_ATTACK : public State
{
public:
    ST_PLAYER_SUPER_BUST_ATTACK();
    ~ST_PLAYER_SUPER_BUST_ATTACK() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};

//bust attck
class ST_PLAYER_BUST_ATTACK : public State
{
public:
    ST_PLAYER_BUST_ATTACK();
    ~ST_PLAYER_BUST_ATTACK() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;
};


#pragma endregion

#pragma region Wp_Axe_Attack

class ST_PLAYER_WP_AXE_ATTACK : public State
{
public:
    ST_PLAYER_WP_AXE_ATTACK();
    ~ST_PLAYER_WP_AXE_ATTACK() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

#pragma endregion

#pragma region Wp_Switch

class ST_PLAYER_WP_SWITCH : public State
{
public:
    ST_PLAYER_WP_SWITCH();
    ~ST_PLAYER_WP_SWITCH() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
};

class ST_PLAYER_WP_SWITCH_KNIFE_TO_AXE : public State
{
public:
    ST_PLAYER_WP_SWITCH_KNIFE_TO_AXE();
    ~ST_PLAYER_WP_SWITCH_KNIFE_TO_AXE() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;

};

class ST_PLAYER_WP_SWITCH_AXE_TO_KNIFE: public State
{
public:
    ST_PLAYER_WP_SWITCH_AXE_TO_KNIFE();
    ~ST_PLAYER_WP_SWITCH_AXE_TO_KNIFE() override;
public:
    virtual void Enter(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Tick(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void Exit(CGameObject* player, PlayerStateMachine* StateMachine) override;
    virtual void OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine) override;

};
#pragma endregion