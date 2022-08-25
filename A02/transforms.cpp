
// -> Translate of +2 on the x axis, and -1 on the y axis
// The translation matrix can be obtained by putting "dx", "dy" and "dz"
// on the last column of an identity matrix.
const float MT1[] = {
		   1.0,		0.0,		0.0,		2.0,
		   0.0,		1.0,		0.0,		-1.0,
		   0.0,		0.0,		1.0,		0.0,
		   0.0,		0.0,		0.0,		1.0 };

// -> Rotate of 45 degrees on the x axis
// Rotation, angles have to be espressed in radians
const float MT2[] = {
	   1.0,		0.0,			0.0,		0.0,
	   0.0,		cos(M_PI / 4),	-sin(M_PI / 4),		0.0,
	   0.0,		sin(M_PI / 4),	cos(M_PI / 4),		0.0,
	   0.0,		0.0,			0.0,		1.0 };


// -> Make the object 2 times smaller
// Scaling can be obtained multiplying the three coordinates 
// of the points with a factor "s"
const float MT3[] = {
		   0.5,		0.0,		0.0,		0.0,
		   0.0,		0.5,		0.0,		0.0,
		   0.0,		0.0,		0.5,		0.0,
		   0.0,		0.0,		0.0,		1.0 };

// -> Make the object 2 times longer on the z axis, and half on the other axis
// Scaling
const float MT4[] = {
		   0.5,		0.0,		0.0,		0.0,
		   0.0,		0.5,		0.0,		0.0,
		   0.0,		0.0,		2.0,		0.0,
		   0.0,		0.0,		0.0,		1.0 };

// -> Mirror over the z axis
// Scaling - axial mirroring, obtained using negative scaling factor
// Assign -1 to all the scaling factors but the one of the axis
const float MT5[] = {
		   -1.0,	0.0,		0.0,		0.0,
		   0.0,		-1.0,		0.0,		0.0,
		   0.0,		0.0,		1.0,		0.0,
		   0.0,		0.0,		0.0,		1.0 };

// -> Flatten over the z axis
// Set the z scaling factor to zero
const float MT6[] = {
		   1.0,		0.0,		0.0,		0.0,
		   0.0,		1.0,		0.0,		0.0,
		   0.0,		0.0,		0.0,		0.0,
		   0.0,		0.0,		0.0,		1.0 };

// -> Make a shear along the Y axis, with a factor of 1 along the x axis
// The shear transform bends an object in one direction
// We edit the first and the third element of the second column with the x and z factor
const float MT7[] = {
		   1.0,		1.0,		0.0,		0.0,
		   0.0,		1.0,		0.0,		0.0,
		   0.0,		0.0,		1.0,		0.0,
		   0.0,		0.0,		0.0,		1.0 };
