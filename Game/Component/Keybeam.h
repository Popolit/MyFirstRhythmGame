#pragma once
class Keybeam
{
private:
	Rendering::Animation::Component KB;
public:
	Keybeam();
	void SetLane(UINT const & lane);
	void Reset();
	void Pressing();
	void Draw(float const& location);
};

