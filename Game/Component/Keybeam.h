#pragma once

//Å°ºö Å¬·¡½º
class Keybeam
{
private:
	Rendering::Animation::Component KB;
public:
	Keybeam();
	void SetLane(UINT const & lane);
	void Update();
	void Pressing();
	void Draw(float const& location);
};

