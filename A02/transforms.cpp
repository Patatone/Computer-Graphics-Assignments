#include <cmath>

	// Translate of +2 on the x axis, and -1 on the y axis
	const float MT1[] =  {
			   1.0,		0.0,		0.0,		2.0,
			   0.0,		1.0,		0.0,		-1.0,
			   0.0,		0.0,		1.0,		0.0,
			   0.0,		0.0,		0.0,		1.0};
			
	float pi = 3.14;
	//Rotate of 45 degrees on the x axis
	//Rotation, angles have to be espressed in radians
	const float MT2[] = {
		   1.0,		0.0,			0.0,		0.0,
		   0.0,		cos(pi/4),	-sin(pi/4),		0.0,
		   0.0,		sin(pi/4),	cos(pi/4),		0.0,
		   0.0,		0.0,			0.0,		1.0 };


	// Make the object 2 times smaller
	//Scaling
	const float MT3[] =  {
			   0.5,		0.0,		0.0,		0.0,
			   0.0,		0.5,		0.0,		0.0,
			   0.0,		0.0,		0.5,		0.0,
			   0.0,		0.0,		0.0,		1.0};
			   
	// Make the object 2 times longer on the z axis, and half on the other axis
	//Scaling
	const float MT4[] =  {
			   0.5,		0.0,		0.0,		0.0,
			   0.0,		0.5,		0.0,		0.0,
			   0.0,		0.0,		2.0,		0.0,
			   0.0,		0.0,		0.0,		1.0};

	// Mirror over the z axis
	//Scaling - axial mirroring, obtained using negative scaling factor
	//Assign -1 to all the scaling factors but the one of the axis
	const float MT5[] =  {
			   -1.0,	0.0,		0.0,		0.0,
			   0.0,		-1.0,		0.0,		0.0,
			   0.0,		0.0,		1.0,		0.0,
			   0.0,		0.0,		0.0,		1.0};
			   
	// Flatten over the z axis
	//Set the z scaling factor to zero
	const float MT6[] =  {
			   1.0,		0.0,		0.0,		0.0,
			   0.0,		1.0,		0.0,		0.0,
			   0.0,		0.0,		0.0,		0.0,
			   0.0,		0.0,		0.0,		1.0};

	// Make a shear along the Y axis, with a factor of 1 along the x axis
	const float MT7[] =  {
			   1.0,		1.0,		0.0,		0.0,
			   0.0,		1.0,		0.0,		0.0,
			   0.0,		0.0,		1.0,		0.0,
			   0.0,		0.0,		0.0,		1.0};
