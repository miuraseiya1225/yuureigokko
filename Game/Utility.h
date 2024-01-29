#pragma once
#include<vector>
#include<iostream>
#include<string>
#include"GameMain.h"

struct Float2
{
	float mX;
	float mY;

	Float2()
		: mX(0.0f)
		, mY(0.0f)
	{

	}
};

struct Int2
{
	int mX;
	int mY;

	Int2()
		: mX(0)
		, mY(0)
	{

	}
};

struct Color3
{
	int mRed;
	int mGreen;
	int mBlue;

	Color3()
		:mRed{255}
		, mGreen{255}
		, mBlue{255}
	{

	}
};