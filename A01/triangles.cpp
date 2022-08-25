/**************
 Function Triangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b)

 draws a triangle connecting points (x1,y1)  (x2, y2) and (x3, y3), colored with the (r,g,b) specified color.
 vertex are expressed in Normalized screen coordinates, (i.e. in range [-1,+1]), following the Vulkan convention.
 The red, green and blue (r,g,b) values are in the range [0,1].
***************/

// Right upper corner	(1,-1)
// Left upper corner	(-1,-1)
// Center of the screen	(0,0)
// Right lower corner	(1,1)
// Left lower corner	(-1,1)

// Roof
Triangle(-0.03, 0.18, 0.35, -0.45, 0.72, 0.18, 1, 0, 0);

// House body
Triangle(0.08, 0.18, 0.08, 0.8, 0.64, 0.18, 0, 0, 1);
Triangle(0.64, 0.8, 0.08, 0.8, 0.64, 0.18, 0, 0, 1);

// Left window
Triangle(0.14, 0.28, 0.28, 0.28, 0.14, 0.42, 1, 1, 0);
Triangle(0.28, 0.42, 0.28, 0.28, 0.14, 0.42, 1, 1, 0);

// Right window
Triangle(0.45, 0.28, 0.57, 0.28, 0.45, 0.42, 1, 1, 0);
Triangle(0.57, 0.42, 0.57, 0.28, 0.45, 0.42, 1, 1, 0);

// Door
Triangle(0.28, 0.50, 0.40, 0.50, 0.28, 0.82, 1, 1, 0);
Triangle(0.40, 0.80, 0.40, 0.50, 0.28, 0.82, 1, 1, 0);

// Grass
Triangle(-1, 0.8, 1, 0.8, -1, 1, 0, 1, 0);
Triangle(1, 1, 1, 0.8, -1, 1, 0, 1, 0);

// Sun
for (int i = 0; i < 32; i++) {
	Triangle(0.00 + 0.05 * cos(6.28 / 32 * (i - 0.5)), -0.80 + 0.05 * sin(6.28 / 32 * (i - 0.5)),
		0.00 + 0.10 * cos(6.28 / 32 * i), -0.80 + 0.10 * sin(6.28 / 32 * i),
		0.00 + 0.05 * cos(6.28 / 32 * (i + 0.5)), -0.80 + 0.05 * sin(6.28 / 32 * (i + 0.5)),
		1, 1, 0);
}
