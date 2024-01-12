#pragma once
class aiMesh;
class aiTexture;
class aiMaterial;
void TestAssimp();
void ExportMesh(aiMesh* _aiMesh);
void ExportTexture(aiTexture* _aiTexture);
void ExportMaterial(aiMaterial* _aiMaterial);