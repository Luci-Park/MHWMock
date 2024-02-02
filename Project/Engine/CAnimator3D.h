#pragma once
#include "CComponent.h"

class CAnimator3D :
	public CComponent
{
public:
	CAnimator3D();
	CAnimator3D(const CAnimator3D& _origin);
	~CAnimator3D();
};

