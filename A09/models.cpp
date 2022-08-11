// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices
void makeModels() {
//// M1 : Cube
// Replace the code below, that creates a simple square, with the one to create a cube.

// Resizes the vertices array. Repalce the values with the correct number of
// vertices components (3 * number of vertices)
M1_vertices.resize(3 * 8);

// first vertex of M1
M1_vertices[0] = -1.0;
M1_vertices[1] = -1.0;
M1_vertices[2] = -1.0;

// second vertex of M1
M1_vertices[3] =  1.0;
M1_vertices[4] = -1.0;
M1_vertices[5] = -1.0;

// third vertex of M1
M1_vertices[6] =  1.0;
M1_vertices[7] =  1.0;
M1_vertices[8] = -1.0;

// fourth vertex of M1
M1_vertices[9] = -1.0;
M1_vertices[10] =  1.0;
M1_vertices[11] = -1.0;

// Now the other side of the cube, it differs only for the z-axis
// 5 vertex of M1
M1_vertices[12] = -1.0;
M1_vertices[13] = -1.0;
M1_vertices[14] = 1.0;

// 6 vertex of M1
M1_vertices[15] = 1.0;
M1_vertices[16] = -1.0;
M1_vertices[17] = 1.0;

// 7 vertex of M1
M1_vertices[18] = 1.0;
M1_vertices[19] = 1.0;
M1_vertices[20] = 1.0;

// 8 vertex of M1
M1_vertices[21] = -1.0;
M1_vertices[22] = 1.0;
M1_vertices[23] = 1.0;

// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)
// number of triangles = 2 * cube faces = 12
M1_indices.resize(3 * 12);
M1_indices = { 0,1,2, 2,3,0, 0,3,4, 4,3,7, 5,6,7, 7,4,5, 1,6,5, 1,2,6, 7,6,2, 3,2,7, 4,5,0, 1,0,5 };

//// M2 : Cylinder
// Replace the code below, that creates a simple rotated square, with the one to create a cylinder.

int NSlices = 36;
float radius = 1;
//The height is the distance from the center, it's half of the normal figure height
float height = 1;
//Center of the cylinder figure
float center_x = 0, center_y = 0, center_z = -3;

// Resizes the vertices array. Repalce the values with the correct number of
// vertices components (3 * number of vertices)
// The circle has NSlices+1 vertices because we consider 1 unique slice for each triangle and 1 vertex for the center of the circle
M2_vertices.resize((NSlices+1)*3*2);

// Vertices definitions of the Upper circle center
M2_vertices[0]  = center_x;
M2_vertices[1]  = center_y + height;
M2_vertices[2]  = center_z;
//Upper circle
for (int i = 0; i < NSlices; i++) {
	M2_vertices[(i + 1) * 3 + 0] = center_x + radius * cos((float)i / NSlices * 2.0 * M_PI);
	M2_vertices[(i + 1) * 3 + 1] = center_y + height;
	M2_vertices[(i + 1) * 3 + 2] = center_z + radius * sin((float)i / NSlices * 2.0 * M_PI);
}

// Vertices definitions of the Lower circle center
M2_vertices[(NSlices + 1) * 3 + 0] = center_x;
M2_vertices[(NSlices + 1) * 3 + 1] = center_y - height;
M2_vertices[(NSlices + 1) * 3 + 2] = center_z;
//Lower circle
for (int i =(NSlices + 1); i < 2*NSlices; i++) {
	M2_vertices[(i + 1) * 3 + 0] = center_x + radius * cos((float)(i - NSlices - 1) / NSlices * 2.0 * M_PI);
	M2_vertices[(i + 1) * 3 + 1] = center_y - height;
	M2_vertices[(i + 1) * 3 + 2] = center_z + radius * sin((float)(i - NSlices - 1) / NSlices * 2.0 * M_PI);
}

// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)
M2_indices.resize(3 * NSlices * 2);

// Indices to connect Upper circle vertices to circle center
for (int i = 0; i < NSlices; i++) {
	M2_indices[i * 3 + 0] = 0;
	M2_indices[i * 3 + 1] = i + 1;
	// With "i + 2" when we arrive at the last vertex it will go one above
	// So we used "(i + 1) % NSlices + 1"
	M2_indices[i * 3 + 2] = (i + 1) % NSlices + 1;
}

// Indices to connect Lower circle vertices to circle center
for (int i = NSlices; i < 2 * NSlices; i++) {
	M2_indices[i * 3 + 0] = NSlices + 1;
	M2_indices[i * 3 + 1] = i + 2;
	// With "i + 2" when we arrive at the last vertex it will go one above
	// So we used "(i + 1) % NSlices + 1"
	M2_indices[i * 3 + 2] = ((i + 1) % NSlices) + NSlices + 2;
}









//// M3 : Sphere
// Replace the code below, that creates a simple triangle, with the one to create a sphere.

// Resizes the vertices array. Repalce the values with the correct number of
// vertices components (3 * number of vertices)
M3_vertices.resize(9);

// Vertices definitions
M3_vertices[0]  =  0.0;
M3_vertices[1]  =  1.0;
M3_vertices[2]  = -1.2;
M3_vertices[3]  = -0.866;
M3_vertices[4]  = -0.5;
M3_vertices[5]  = -1.2;
M3_vertices[6]  =  0.866;
M3_vertices[7]  = -0.5;
M3_vertices[8]  = -1.2;


// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)
M3_indices.resize(3);

// indices definitions
M3_indices[0] = 0;
M3_indices[1] = 1;
M3_indices[2] = 2;









//// M4 : Spring
// Replace the code below, that creates a simple octahedron, with the one to create a spring.
M4_vertices.resize(3 * 6);

// Vertices definitions
M4_vertices[0]  =  0.0;
M4_vertices[1]  =  1.414;
M4_vertices[2]  = -1.0;
M4_vertices[3]  =  0.0;
M4_vertices[4]  = -1.414;
M4_vertices[5]  = -1.0;
M4_vertices[6]  = -1.0;
M4_vertices[7]  =  0.0;
M4_vertices[8]  = -2.0;
M4_vertices[9]  = -1.0;
M4_vertices[10] =  0.0;
M4_vertices[11] =  0.0;
M4_vertices[12] =  1.0;
M4_vertices[13] =  0.0;
M4_vertices[14] =  0.0;
M4_vertices[15] =  1.0;
M4_vertices[16] =  0.0;
M4_vertices[17] = -2.0;


// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)
M4_indices.resize(3 * 8);

// indices definitions
M4_indices[0]  = 0;
M4_indices[1]  = 2;
M4_indices[2]  = 3;
M4_indices[3]  = 1;
M4_indices[4]  = 3;
M4_indices[5]  = 2;
M4_indices[6]  = 0;
M4_indices[7]  = 3;
M4_indices[8]  = 4;
M4_indices[9]  = 1;
M4_indices[10] = 4;
M4_indices[11] = 3;
M4_indices[12] = 0;
M4_indices[13] = 4;
M4_indices[14] = 5;
M4_indices[15] = 1;
M4_indices[16] = 5;
M4_indices[17] = 4;
M4_indices[18] = 0;
M4_indices[19] = 5;
M4_indices[20] = 2;
M4_indices[21] = 1;
M4_indices[22] = 2;
M4_indices[23] = 5;
}