// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices
void makeModels() {
	//// M1 : Cube

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices components (3 * number of vertices)
	M1_vertices.resize(3 * 8);

	// first vertex of M1
	M1_vertices[0] = -1.0;
	M1_vertices[1] = -1.0;
	M1_vertices[2] = -1.0;

	// second vertex of M1
	M1_vertices[3] = 1.0;
	M1_vertices[4] = -1.0;
	M1_vertices[5] = -1.0;

	// third vertex of M1
	M1_vertices[6] = 1.0;
	M1_vertices[7] = 1.0;
	M1_vertices[8] = -1.0;

	// fourth vertex of M1
	M1_vertices[9] = -1.0;
	M1_vertices[10] = 1.0;
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

	int NSlices = 36;
	float radius = 1;
	// The height is the distance from the center, it's half of the normal figure height
	float height = 1;
	// Center of the cylinder figure
	float center_x = 0, center_y = 0, center_z = -3;

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices components (3 * number of vertices)
	// The circle has NSlices+1 vertices because we consider 1 unique slice for each triangle and 1 vertex for the center of the circle
	M2_vertices.resize((NSlices + 1) * 3 * 2);

	// Vertices definitions of the Upper circle center
	M2_vertices[0] = center_x;
	M2_vertices[1] = center_y + height;
	M2_vertices[2] = center_z;
	// --- Upper circle ---
	for (int i = 0; i < NSlices; i++) {
		//x for the vertex
		M2_vertices[(i + 1) * 3 + 0] = center_x + radius * cos((float)i / NSlices * 2.0 * M_PI);
		//y for the vertex
		M2_vertices[(i + 1) * 3 + 1] = center_y + height;
		//z for the vertex
		M2_vertices[(i + 1) * 3 + 2] = center_z + radius * sin((float)i / NSlices * 2.0 * M_PI);
	}

	// Vertices definitions of the Lower circle center
	M2_vertices[(NSlices + 1) * 3 + 0] = center_x;
	M2_vertices[(NSlices + 1) * 3 + 1] = center_y - height;
	M2_vertices[(NSlices + 1) * 3 + 2] = center_z;
	// --- Lower circle---
	for (int i = (NSlices + 1); i < 2 * NSlices + 1; i++) {
		//x for the vertex
		M2_vertices[(i + 1) * 3 + 0] = center_x + radius * cos((float)(i - NSlices - 1) / NSlices * 2.0 * M_PI);
		//y for the vertex
		M2_vertices[(i + 1) * 3 + 1] = center_y - height;
		//z for the vertex
		M2_vertices[(i + 1) * 3 + 2] = center_z + radius * sin((float)(i - NSlices - 1) / NSlices * 2.0 * M_PI);
	}

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M2_indices.resize(3 * NSlices * 4);

	// Indices to connect Upper circle vertices to circle center
	for (int i = 0; i < NSlices; i++) {
		M2_indices[i * 3 + 0] = 0;
		M2_indices[i * 3 + 1] = i + 1;
		// With "i + 2" when we arrive at the last vertex it will go one above, whit this formula at the last vortex we came back to "1"
		// So we used "(i + 1) % NSlices + 1"
		M2_indices[i * 3 + 2] = (i + 1) % NSlices + 1;
	}

	// Indices to connect Lower circle vertices to circle center
	for (int i = NSlices; i < 2 * NSlices; i++) {
		M2_indices[i * 3 + 0] = NSlices + 1;
		M2_indices[i * 3 + 1] = i + 2;
		// With "i + 3" when we arrive at the last vertex it will go one above
		// So we used "((i + 1) % NSlices) + NSlices + 2"
		M2_indices[i * 3 + 2] = ((i + 1) % NSlices) + NSlices + 2;
	}

	// Lateral Cylinder part, Half triangle for each face
	for (int i = 0; i < NSlices; i++) {
		M2_indices[(2 * NSlices + i) * 3 + 0] = i + 1;
		M2_indices[(2 * NSlices + i) * 3 + 1] = (i + 1) % NSlices + 1;
		M2_indices[(2 * NSlices + i) * 3 + 2] = NSlices + i + 2;
	}

	// Lateral Cylinder part, the missing half triangle for each face
	for (int i = 0; i < NSlices; i++) {
		M2_indices[(3 * NSlices + i) * 3 + 0] = NSlices + i + 2;
		M2_indices[(3 * NSlices + i) * 3 + 1] = ((i + 1) % NSlices) + NSlices + 2;
		M2_indices[(3 * NSlices + i) * 3 + 2] = (i + 1) % NSlices + 1;
	}







	//// M3 : Sphere
	// Replace the code below, that creates a simple triangle, with the one to create a sphere.

	float xCircle, yCircle, zCircle, xyCircle;
	float radiusCircle = 2.0f;
	// Differnt dimension circles that makes the sphere
	float stackCount = 36.0f;
	// Same dimension circles
	float sectorCount = 12.0f;
	float sectorStep = 2 * M_PI / sectorCount;
	float stackStep = M_PI / stackCount;
	float sectorAngle, stackAngle;
	int valueOfArrayCircle = 0;
	int valueOfSecondArrayCircle = 0;
	int k1Circle, k2Circle;

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices components (3 * number of vertices)
	M3_vertices.resize(3 * stackCount * sectorCount * 2);

	// Vertices definitions
	for (int i = 0; i <= stackCount; i++) {
		stackAngle = M_PI / 2 - i * stackStep;
		xyCircle = radiusCircle * cos(stackAngle);
		zCircle = radiusCircle * sin(stackAngle);

		for (int j = 0; j <= sectorCount; j++) {
			sectorAngle = j * sectorStep;

			xCircle = xyCircle * cos(sectorAngle);
			yCircle = xyCircle * sin(sectorAngle);
			M3_vertices[(valueOfArrayCircle * 3) + 0] = xCircle;
			M3_vertices[(valueOfArrayCircle * 3) + 1] = yCircle;
			M3_vertices[(valueOfArrayCircle * 3) + 2] = zCircle;
			valueOfArrayCircle++;
		}
	}


	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M3_indices.resize(3 * stackCount * sectorCount * 2);

	// indices definitions
	for (int i = 0; i < stackCount; i++) {
		k1Circle = i * (sectorCount + 1);
		k2Circle = k1Circle + sectorCount + 1;

		for (int j = 0; j < sectorCount; j++, k1Circle++, k2Circle++) {
			if (i != 0) {
				M3_indices[valueOfSecondArrayCircle] = k1Circle;
				valueOfSecondArrayCircle++;
				M3_indices[valueOfSecondArrayCircle] = k2Circle;
				valueOfSecondArrayCircle++;
				M3_indices[valueOfSecondArrayCircle] = k1Circle + 1;
				valueOfSecondArrayCircle++;
			}

			if (i != stackCount - 1) {
				M3_indices[valueOfSecondArrayCircle] = k1Circle + 1;
				valueOfSecondArrayCircle++;
				M3_indices[valueOfSecondArrayCircle] = k2Circle;
				valueOfSecondArrayCircle++;
				M3_indices[valueOfSecondArrayCircle] = k2Circle + 1;
				valueOfSecondArrayCircle++;
			}
		}
	}










	//// M4 : Spring

	// How much smooth the "faces" of the cylinders that compose the spring
	int nSSlices = 12;
	// How many cylinders we can use
	float steps = 500;
	// Cylinder radius
	float r = 0.5; 
	// Distance from the center of cylinder from center of the spring
	float R = 4; 
	float t = 0.f;
	// Number of rounds - spring height
	int n = 20; 
	// Distance between rounds
	float d = 2; 

	float sCx = 0, sCy = 0, sCz = 0;

	// vertices components (3 * number of vertices)
	M4_vertices.resize(3 * (steps * nSSlices));

	// Vertices definitions
	for (int i = 0; i < steps; i++) {
		t = (float)i / steps * n * 2.0 * M_PI;
		// Center of circle "i"
		sCx = R * cos(t);
		sCy = (d * t) / M_PI;
		sCz = R * sin(t);
		for (int j = 0; j < nSSlices; j++) {
			//x for the vertex
			M4_vertices[j * 3 + i * nSSlices * 3 + 0] = sCx + r * cos((float)j / nSSlices * 2.0 * M_PI) * cos(t);
			//y for the vertex
			M4_vertices[j * 3 + i * nSSlices * 3 + 1] = sCy + r * sin((float)j / nSSlices * 2.0 * M_PI); 
			// z for the vertex
			M4_vertices[j * 3 + i * nSSlices * 3 + 2] = sCz + r * cos((float)j / nSSlices * 2.0 * M_PI) * sin(t); 
		}
	}


	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M4_indices.resize(3 * (steps * nSSlices) * 2);

	// indices definitions
	int lastVal = 0;

	for (int i = 0; i < steps - 1; i++) {
		for (int j = 0; j < nSSlices; j++) {
			M4_indices[j * 3 + i * nSSlices * 3 + 0] = j + i * nSSlices;
			M4_indices[j * 3 + i * nSSlices * 3 + 1] = j + i * nSSlices + nSSlices;
			M4_indices[j * 3 + i * nSSlices * 3 + 2] = ((j + 1) % nSSlices) + nSSlices * i;
		}
		lastVal = i * nSSlices * 3;
	}

	for (int i = 0; i < steps - 1; i++) {
		for (int j = 0; j < nSSlices; j++) {
			M4_indices[j * 3 + (steps + i) * nSSlices * 3 + 0] = j + i * nSSlices + nSSlices;
			M4_indices[j * 3 + (steps + i) * nSSlices * 3 + 1] = ((j + 1) % nSSlices) + nSSlices * i + nSSlices;
			M4_indices[j * 3 + (steps + i) * nSSlices * 3 + 2] = ((j + 1) % nSSlices) + nSSlices * i;
		}
	}

}