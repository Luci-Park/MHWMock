#include "pch.h"

int tAnimationChannel::Save(FILE* _FILE)
{
    try
    {
        int preState = (int)ePreState;
        int postState = (int)ePostState;
        fwrite(&preState, sizeof(int), 1, _FILE);
        fwrite(&postState, sizeof(int), 1, _FILE);

        int keyNum = vecPositionKeys.size();
        fwrite(&keyNum, sizeof(int), 1, _FILE);
        for (size_t i = 0; i < keyNum; i++)
        {
            fwrite(&vecPositionKeys[i].time, sizeof(double), 1, _FILE);
            fwrite(&vecPositionKeys[i].value, sizeof(Vec3), 1, _FILE);
        }

        keyNum = vecScaleKeys.size();
        fwrite(&keyNum, sizeof(int), 1, _FILE);
        for (size_t i = 0; i < keyNum; i++)
        {
            fwrite(&vecScaleKeys[i].time, sizeof(double), 1, _FILE);
            fwrite(&vecScaleKeys[i].value, sizeof(Vec3), 1, _FILE);
        }

        keyNum = vecRotationKeys.size();
        fwrite(&keyNum, sizeof(int), 1, _FILE);
        for (size_t i = 0; i < keyNum; i++)
        {
            fwrite(&vecRotationKeys[i].time, sizeof(double), 1, _FILE);
            fwrite(&vecRotationKeys[i].value, sizeof(Quaternion), 1, _FILE);
        }

        return S_OK;
    }
    catch (const std::exception&)
    {
        return E_FAIL;
    }
}

int tAnimationChannel::Load(FILE* _FILE)
{
    int preState, postState;
    fread(& preState, sizeof(int), 1, _FILE);
    fread(&postState, sizeof(int), 1, _FILE);

    ePreState = (AnimBehaviour)preState;
    ePostState = (AnimBehaviour)postState;

    int keyNum;

    fread(&keyNum, sizeof(int), 1, _FILE);
    vecPositionKeys.resize(keyNum);
    for (size_t i = 0; i < keyNum; i++)
    {
        fread(&vecPositionKeys[i].time, sizeof(double), 1, _FILE);
        fread(&vecPositionKeys[i].value, sizeof(Vec3), 1, _FILE);
    }

    fread(&keyNum, sizeof(int), 1, _FILE);
    vecScaleKeys.resize(keyNum);
    for (size_t i = 0; i < keyNum; i++)
    {
        fread(&vecScaleKeys[i].time, sizeof(double), 1, _FILE);
        fread(&vecScaleKeys[i].value, sizeof(Vec3), 1, _FILE);
    }

    fread(&keyNum, sizeof(int), 1, _FILE);
    vecRotationKeys.resize(keyNum);
    for (size_t i = 0; i < keyNum; i++)
    {
        fread(&vecRotationKeys[i].time, sizeof(double), 1, _FILE);
        fread(&vecRotationKeys[i].value, sizeof(Quaternion), 1, _FILE);
    }

    return S_OK;
}
