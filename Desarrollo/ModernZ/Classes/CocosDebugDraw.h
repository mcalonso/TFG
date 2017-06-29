#ifndef __DEBUG_DRAW_H__
#define __DEBUG_DRAW_H__

#include <Box2D/Box2D.h>
#include "cocos2d.h"

class	CocosDebugDraw : public	b2Draw 
{
	float32	mRatio;
	cocos2d::DrawNode	*mNode;

public:				CocosDebugDraw();
					CocosDebugDraw(float32	ratio);
					~CocosDebugDraw();

					cocos2d::Node*	GetNode();
					void	Clear();

					/// Draw a closed polygon provided in CCW order.
					virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

					/// Draw a solid closed polygon provided in CCW order.
					virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

					/// Draw a circle.
					virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);

					/// Draw a solid circle.
					virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

					/// Draw a line segment.
					virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

					/// Draw a transform. Choose your own length scale.
					virtual void DrawTransform(const b2Transform& xf);
};

#endif // __DEBUG_DRAW_H__
