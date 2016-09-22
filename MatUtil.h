#pragma once
namespace MatUtil
{
	static int clamp(int _value, int _min, int _max) { return (_min >= _value) ? _min : ((_max <= _value) ? _max : _value); }
}