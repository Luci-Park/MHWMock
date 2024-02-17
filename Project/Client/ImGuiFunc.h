#pragma once
#include "ImGui/imgui.h"

ImVec4 Convert255To1(int r, int g, int b, int a = 255)
{
	const float div = 1.f / 255.f;
	return ImVec4(r * div, g * div, b * div, a * div);
}