#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void TestAssimp();
void ExportMesh(aiMesh* _aiMesh);
void ExportTexture(aiTexture* _aiTexture);
void ExportMaterial(aiMaterial* _aiMaterial);
void ExportAnimation(aiAnimation* _aiAnimation);

void ProcessBone(aiBone* _aiBone);
void ProcessSkeleton(aiSkeleton* _aiSkeleton);
