#include "pch.h"
#include "AnimatorGraphStructures.h"

int Node::PinNum = 0;
Node::Node()
{
	inputPin = PinNum++;
	outputPin = PinNum++;
}
