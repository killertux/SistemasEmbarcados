#include "Bezier.h"
#include "math.h"

float _getPt( float n1 , float n2 , float perc )
{
    float diff = n2 - n1;
    return n1 + ( diff * perc );
}

void draw_bezier_curve(Display *display, float displacement, uint32_t color, float x1, float y1, float x2, float y2, float x3, float y3) {
	float i, xa, xb, ya, yb, x, y;
	for (i = 0 ; i < 1 ; i += 0.01)
		{
				xa = _getPt( x1 , x2 , i );
				ya = _getPt( y1 , y2 , i );
				xb = _getPt( x2 , x3 , i );
				yb = _getPt( y2 , y3 , i );

				x = _getPt( xa , xb , i );
				y = _getPt( ya , yb , i );

				display->back_buffer[(int)(x + displacement)][(int)y] = color;
		}
}

float bezier_curve_car(float displacement, float x1, float y1, float x2, float y2, float x3, float y3, float car_y) {
	float i, xa, xb, ya, yb, x, y;
	for (i = 0 ; i < 1 ; i += 0.01)
		{
				xa = _getPt( x1 , x2 , i );
				ya = _getPt( y1 , y2 , i );
				xb = _getPt( x2 , x3 , i );
				yb = _getPt( y2 , y3 , i );

				x = _getPt( xa , xb , i );
				y = _getPt( ya , yb , i );
				
				if (y <= car_y)
					return x + displacement;
		}
	return x3;
}
