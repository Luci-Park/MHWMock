#include "pch.h"
#include "AssimpTest.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void TestAssimp()
{
	Assimp::Importer importer;
	string filename = "C:\\Users\\user\\Documents\\_Quve17\\Luci\\Coding\\AssortRock\\MHWMock\\anjanath\\mod\\em100_00.fbx";
	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		// Error handling: Unable to load the model
		int i = 0;
		return;
	}
	int j = 0;
}
