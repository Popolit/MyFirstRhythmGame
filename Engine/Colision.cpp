#define _USE_MATH_DEFINES
#include "Collision.h"

namespace Collision
{
	inline Matrix<2, 2> Rotation(float const & angle)
	{
		float constexpr radian = static_cast<float>(M_PI) / 180.0f;
		float const r_angle = radian * angle;
		return	Matrix<2, 2>	{+cos(r_angle), -sin(r_angle),
								+sin(r_angle), +cos(r_angle)};
	}

	//점 & 원
	bool Collide(Point const& LHS, Circle const& RHS)
	{
		return Length(LHS.Location - RHS.Location) <= RHS.Diameter / 2;
	}
	bool Collide(Circle const& LHS, Point const& RHS) { return Collide(RHS, LHS); }


	//점 & 사각형
	bool Collide(Point const& LHS, RectAngle const& RHS)
	{
		if (RHS.Angle == 0)
		{
			Vector<2> const min = RHS.Location - RHS.Length / 2;
			Vector<2> const max = RHS.Location + RHS.Length / 2;
			return	min[0] <= LHS.Location[0] && LHS.Location[0] <= max[0] &&
				min[1] <= LHS.Location[1] && LHS.Location[1] <= max[1];
		}
		else
		{
			return Collide(	Point{ LHS.Location * Rotation(-RHS.Angle) },
							RectAngle{ RHS.Length, 0, RHS.Location * Rotation(-RHS.Angle) });
		}
	}
	bool Collide(RectAngle const& LHS, Point const& RHS) { return Collide(RHS, LHS); }
	

	//원 & 원
	bool Collide(Circle const& LHS, Circle& RHS)
	{
		return Length(LHS.Location - RHS.Location) <= (LHS.Diameter + RHS.Diameter) / 2;
	}

	//원 & 사각형
	bool Collide(Circle const& LHS, RectAngle const& RHS)
	{
		if (RHS.Angle == 0)
		{
			Vector<2> const min = RHS.Location - RHS.Length / 2;
			Vector<2> const max = RHS.Location + RHS.Length / 2;

			//사각형의 변 영역에 충돌
			if ((min[0] <= LHS.Location[0] && LHS.Location[0] <= max[0]) ||
				(min[1] <= LHS.Location[1] && LHS.Location[1] <= max[1]))
			{
				return Collide(Point{ LHS.Location }, RectAngle{ RHS.Length + LHS.Diameter, RHS.Angle, RHS.Location });
			}
			//사각형의 모서리 영역에 충돌
			else
			{
				Point const vertex{ Vector<2> {RHS.Location[0] - LHS.Location[0] < 0 ? max[0] : min[0],
											   RHS.Location[1] - LHS.Location[1] < 0 ? max[1] : min[1]} };
				return Collide(LHS, vertex);
			}
		}
		else
		{
			return Collide(	Circle{ LHS.Diameter, LHS.Location * Rotation(-RHS.Angle) },
							RectAngle{ RHS.Length, 0, RHS.Location * Rotation(-RHS.Angle) });
		}
	}
	bool Collide(RectAngle const& LHS, Circle const& RHS) { return Collide(RHS, LHS); }


	bool Collide(RectAngle const& LHS, RectAngle const& RHS)
	{
		//AABB 충돌검사
		if (LHS.Angle == RHS.Angle)
		{
			Vector<2> L_Location = LHS.Location;
			Vector<2> R_Location = RHS.Location;

			//0 < Angle일때
			if (LHS.Angle)
			{
				L_Location *= Rotation(-LHS.Angle);
				R_Location *= Rotation(-RHS.Angle);
			}

			Vector<2> const LS = L_Location - LHS.Length / 2;
			Vector<2> const LB = L_Location + LHS.Length / 2;
			Vector<2> const RS = R_Location - RHS.Length / 2;
			Vector<2> const RB = R_Location + RHS.Length / 2;

			return LS[0] < RB[0] && LS[1] < RB[1] && RS[0] < LB[0] && RS[1] < LB[1];
		}
		//OBB 충돌검사
		else
		{
			Vector<2> const distance = LHS.Location - RHS.Location;
			if ((Length(LHS.Length) + Length(RHS.Length)) / 2 < Length(distance)) return false;

			Vector<2> const axes[4]
			{
				Vector<2>(1,0) * Rotation(LHS.Angle),
				Vector<2>(0,1) * Rotation(LHS.Angle),
				Vector<2>(1, 0) * Rotation(RHS.Angle),
				Vector<2>(0,1) * Rotation(RHS.Angle)
			};

			Vector<2> const vectors[4]
			{
				axes[0] * (LHS.Length[0] / 2),
				axes[1] * (LHS.Length[1] / 2),
				axes[2] * (RHS.Length[0] / 2),
				axes[3] * (RHS.Length[1] / 2)
			};

			for (unsigned i = 0; i < 4; i++)
			{
				float sum = 0;

				for (unsigned j = 0; j < 4; j++)
					sum += abs(Dot(axes[i], vectors[j]));

				if (abs(Dot(axes[i], distance)))
					return false;
			}
			return true;
		}
	}
}