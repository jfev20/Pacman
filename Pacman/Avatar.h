#ifndef AVATAR_H
#define AVATAR_H

#include "MovableGameEntity.h"
#include "Vector2f.h"
#include <map>
#include <vector>

class Avatar : public MovableGameEntity
{
public:
	Avatar(const Vector2f& aPosition, Graphic* aGraphic);
	~Avatar(void);

	void Update(float aTime);

private:
	void UpdateFacingDirection(Vector2f dir);

	std::map<std::list<float>, std::vector<std::string>> graphicOrientation{
		{{0,-1},{ "open_up_32.png" ,"closed_up_32.png" }},		
		{{0,1},{ "open_down_32.png" ,"closed_down_32.png" }},	
		{{-1,0},{ "open_left_32.png" ,"closed_left_32.png" }},	
		{{1,0},{ "open_right_32.png" ,"closed_right_32.png" }}
	};
	std::vector<std::string> currentDirectionGraphics;
	
};

#endif //AVATAR_H

