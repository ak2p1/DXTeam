#pragma once

class CBase
{
	virtual int Update(float _fTime = 0.0f) = 0;
	virtual void Render() = 0;
};
