// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices

struct Vertex {
	glm::vec3 pos;
	glm::vec3 norm;
};

std::vector<Vertex> M1_vertices;
std::vector<Vertex> M2_vertices;
std::vector<Vertex> M3_vertices;
std::vector<Vertex> M4_vertices;

// Normal vector will be used by smooth shading techniques
// - Gouraud shading	 (per-vertex)
// - Phong shading		 (per-pixel)
// If all the faces that share the same vertex have a different
// normal vector direction, the edges appear to be sharp

// Normal vector direction is a property of the triangle
// Here 3 vortex will have 3 differet normal vector direction

void makeModels() {
	//// M1 : Cube

	// vertices components (3 * number of vertices)
	M1_vertices.resize(3 * 8);

	// first vertex of M1 (left bottom front)
	M1_vertices[0].pos = glm::vec3(-1.0, -1.0, -1.0);

	M1_vertices[0].norm = glm::vec3(0.0, 0.0, -1.0);

	// second vertex of M1 (right bottom front)
	M1_vertices[1].pos = glm::vec3(1.0, -1.0, -1.0);
	M1_vertices[1].norm = glm::vec3(0.0, 0.0, -1.0);

	// third vertex of M1 (right top front)
	M1_vertices[2].pos = glm::vec3(1.0, 1.0, -1.0);
	M1_vertices[2].norm = glm::vec3(0.0, 0.0, -1.0);

	// fourth vertex of M1 (left top front)
	M1_vertices[3].pos = glm::vec3(-1.0, 1.0, -1.0);
	M1_vertices[3].norm = glm::vec3(0.0, 0.0, -1.0);

	//---------------------------------
	M1_vertices[4].pos = glm::vec3(1.0, -1.0, -1.0);
	M1_vertices[4].norm = glm::vec3(1.0, 0.0, 0.0);


	M1_vertices[5].pos = glm::vec3(1.0, -1.0, 1.0);
	M1_vertices[5].norm = glm::vec3(1.0, 0.0, 0.0);


	M1_vertices[6].pos = glm::vec3(1.0, 1.0, 1.0);
	M1_vertices[6].norm = glm::vec3(1.0, 0.0, 0.0);


	M1_vertices[7].pos = glm::vec3(1.0, 1.0, -1.0);
	M1_vertices[7].norm = glm::vec3(1.0, 0.0, 0.0);

	//---------------------------------
	M1_vertices[8].pos = glm::vec3(1.0, -1.0, 1.0);
	M1_vertices[8].norm = glm::vec3(0.0, 0.0, 1.0);


	M1_vertices[9].pos = glm::vec3(-1.0, -1.0, 1.0);
	M1_vertices[9].norm = glm::vec3(0.0, 0.0, 1.0);


	M1_vertices[10].pos = glm::vec3(-1.0, 1.0, 1.0);
	M1_vertices[10].norm = glm::vec3(0.0, 0.0, 1.0);


	M1_vertices[11].pos = glm::vec3(1.0, 1.0, 1.0);
	M1_vertices[11].norm = glm::vec3(0.0, 0.0, 1.0);


	//---------------------------------
	M1_vertices[12].pos = glm::vec3(-1.0, -1.0, 1.0);
	M1_vertices[12].norm = glm::vec3(-1.0, 0.0, 0.0);


	M1_vertices[13].pos = glm::vec3(-1.0, -1.0, -1.0);
	M1_vertices[13].norm = glm::vec3(-1.0, 0.0, 0.0);


	M1_vertices[14].pos = glm::vec3(-1.0, 1.0, -1.0);
	M1_vertices[14].norm = glm::vec3(-1.0, 0.0, 0.0);


	M1_vertices[15].pos = glm::vec3(-1.0, 1.0, 1.0);
	M1_vertices[15].norm = glm::vec3(-1.0, 0.0, 0.0);


	//---------------------------------
	M1_vertices[16].pos = glm::vec3(-1.0, 1.0, 1.0);
	M1_vertices[16].norm = glm::vec3(0.0, 1.0, 0.0);


	M1_vertices[17].pos = glm::vec3(1.0, 1.0, 1.0);
	M1_vertices[17].norm = glm::vec3(0.0, 1.0, 0.0);


	M1_vertices[18].pos = glm::vec3(1.0, 1.0, -1.0);
	M1_vertices[18].norm = glm::vec3(0.0, 1.0, 0.0);


	M1_vertices[19].pos = glm::vec3(-1.0, 1.0, -1.0);
	M1_vertices[19].norm = glm::vec3(0.0, 1.0, 0.0);


	//---------------------------------
	M1_vertices[20].pos = glm::vec3(-1.0, -1.0, 1.0);
	M1_vertices[20].norm = glm::vec3(0.0, -1.0, 0.0);


	M1_vertices[21].pos = glm::vec3(1.0, -1.0, 1.0);
	M1_vertices[21].norm = glm::vec3(0.0, -1.0, 0.0);


	M1_vertices[22].pos = glm::vec3(1.0, -1.0, -1.0);
	M1_vertices[22].norm = glm::vec3(0.0, -1.0, 0.0);


	M1_vertices[23].pos = glm::vec3(-1.0, -1.0, -1.0);
	M1_vertices[23].norm = glm::vec3(0.0, -1.0, 0.0);

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	// number of triangles = 2 * cube faces = 12
	M1_indices.resize(3 * 12);

	// first triangle
	M1_indices[0] = 0;
	M1_indices[1] = 1;
	M1_indices[2] = 2;

	// second triangle
	M1_indices[3] = 2;
	M1_indices[4] = 3;
	M1_indices[5] = 0;

	// -------------------
	M1_indices[6] = 4;
	M1_indices[7] = 5;
	M1_indices[8] = 6;

	M1_indices[9] = 6;
	M1_indices[10] = 7;
	M1_indices[11] = 4;

	// -------------------
	M1_indices[12] = 8;
	M1_indices[13] = 9;
	M1_indices[14] = 11;

	M1_indices[15] = 11;
	M1_indices[16] = 10;
	M1_indices[17] = 9;

	// -------------------
	M1_indices[18] = 12;
	M1_indices[19] = 13;
	M1_indices[20] = 14;

	M1_indices[21] = 14;
	M1_indices[22] = 15;
	M1_indices[23] = 12;

	// -------------------
	M1_indices[24] = 16;
	M1_indices[25] = 17;
	M1_indices[26] = 18;

	M1_indices[27] = 18;
	M1_indices[28] = 19;
	M1_indices[29] = 16;

	// -------------------
	M1_indices[30] = 20;
	M1_indices[31] = 21;
	M1_indices[32] = 22;

	M1_indices[33] = 22;
	M1_indices[34] = 23;
	M1_indices[35] = 20;





	//// M2 : Cylinder

	int NSlices = 36;
	float radius = 1;
	// The real cyliner height is two times this value
	float height = 1;
	float cx = 0, cy = 0, cz = 0;

	int baseIndex = 0;


	// NSlices for the top cap, NSlices for the bottom cap, NSlices*2 for side
	// 1 bottom cap center, 1 top cap center
	M2_vertices.resize(NSlices * 4 + 2);

	// --- Upper circle ---
	// Vertices definitions of the Upper circle center
	M2_vertices[baseIndex].pos = glm::vec3(cx, cy + height, cz);
	// The vertices on the ring belonging to the cap, will have normal
	// oriented along the y - axis.
	M2_vertices[baseIndex].norm = glm::vec3(0, 1, 0);

	baseIndex = 1;


	for (int i = 0; i < NSlices; i++) {
		//x for the vertex
		float x = cx + radius * cos((float)i / NSlices * 2.0 * M_PI);
		//y for the vertex
		float y = cy + height;
		//z for the vertex
		float z = cz + radius * sin((float)i / NSlices * 2.0 * M_PI);

		M2_vertices[baseIndex + i].pos = glm::vec3(x, y, z);
		M2_vertices[baseIndex + i].norm = glm::vec3(0, 1, 0);
	}

	baseIndex = NSlices + 1;

	// --- Lower circle ---
	// Vertices definitions of the Lower circle center
	M2_vertices[baseIndex].pos = glm::vec3(cx, cy - height, cz);
	M2_vertices[baseIndex].norm = glm::vec3(0, -1, 0);

	baseIndex = NSlices + 2;

	for (int i = 0; i < NSlices; i++) {
		//x for the vertex
		float x = cx + radius * cos((float)i / NSlices * 2.0 * M_PI);
		//y for the vertex
		float y = cy - height;
		//z for the vertex
		float z = cz + radius * sin((float)i / NSlices * 2.0 * M_PI);

		M2_vertices[baseIndex + i].pos = glm::vec3(x, y, z);
		M2_vertices[baseIndex + i].norm = glm::vec3(0, -1, 0);
	}

	// --- Lateral Vertices definitions ---
	baseIndex = 2 * NSlices + 2;


	for (int i = 0; i < NSlices; i++) {
		float x = cx + radius * cos((float)i / NSlices * 2.0 * M_PI);
		float y = cy + height;
		float z = cz + radius * sin((float)i / NSlices * 2.0 * M_PI);

		float nx = cos((float)i / NSlices * 2.0 * M_PI);
		float nz = sin((float)i / NSlices * 2.0 * M_PI);

		M2_vertices[baseIndex + i].pos = glm::vec3(x, y, z);
		// The vertices on the ring belonging to the side, will be directed
		// outside, along the radius of the cap
		M2_vertices[baseIndex + i].norm = glm::vec3(nx, 0, nz);
	}

	// --- Lateral Vertices definitions ---
	baseIndex = 3 * NSlices + 2;

	for (int i = 0; i < NSlices; i++) {
		float x = cx + radius * cos((float)i / NSlices * 2.0 * M_PI);
		float y = cy - height;
		float z = cz + radius * sin((float)i / NSlices * 2.0 * M_PI);

		float nx = cos((float)i / NSlices * 2.0 * M_PI);
		float nz = sin((float)i / NSlices * 2.0 * M_PI);

		M2_vertices[baseIndex + i].pos = glm::vec3(x, y, z);
		// The vertices on the ring belonging to the side, will be directed
		// outside, along the radius of the cap
		M2_vertices[baseIndex + i].norm = glm::vec3(nx, 0, nz);
	}


	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M2_indices.resize(3 * (NSlices * 4));

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
		M2_indices[(2 * NSlices + i) * 3 + 0] = 2 * NSlices + 2 + i;
		M2_indices[(2 * NSlices + i) * 3 + 1] = ((i + 1) % NSlices) + 2 * NSlices + 2;
		M2_indices[(2 * NSlices + i) * 3 + 2] = 3 * NSlices + 2 + i;
	}

	// Lateral Cylinder part, the missing half triangle for each face
	for (int i = 0; i < NSlices; i++) {
		M2_indices[(3 * NSlices + i) * 3 + 0] = 3 * NSlices + 2 + i;
		M2_indices[(3 * NSlices + i) * 3 + 1] = ((i + 1) % NSlices) + 3 * NSlices + 2;
		M2_indices[(3 * NSlices + i) * 3 + 2] = ((i + 1) % NSlices) + 2 * NSlices + 2;
	}


	//// M3 : Sphere

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

	// vertices components (number of vertices)
	M3_vertices.resize(stackCount * sectorCount * 2);


	for (int i = 0; i <= stackCount; i++) {
		stackAngle = M_PI / 2 - i * stackStep;
		xyCircle = radiusCircle * cos(stackAngle);
		zCircle = radiusCircle * sin(stackAngle);

		for (int j = 0; j <= sectorCount; j++) {
			sectorAngle = j * sectorStep;

			xCircle = xyCircle * cos(sectorAngle);
			yCircle = xyCircle * sin(sectorAngle);

			M3_vertices[valueOfArrayCircle].pos = glm::vec3(xCircle, yCircle, zCircle);
			M3_vertices[valueOfArrayCircle].norm = glm::vec3(xCircle, yCircle, zCircle);
			valueOfArrayCircle++;
		}
	}

	// indices (3 * number of triangles)
	M3_indices.resize(3 * stackCount * sectorCount * 2);

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


	// vertices components (number of vertices)
	M4_vertices.resize(steps * nSSlices);

	// Vertices definitions
	for (int i = 0; i < steps; i++) {
		t = (float)i / steps * n * 2.0 * M_PI;
		// Center of circle "i"
		sCx = R * cos(t);
		sCy = (d * t) / M_PI;
		sCz = R * sin(t);
		for (int j = 0; j < nSSlices; j++) {
			float x = sCx + r * cos((float)j / nSSlices * 2.0 * M_PI) * cos(t);
			float y = sCy + r * sin((float)j / nSSlices * 2.0 * M_PI);
			float z = sCz + r * cos((float)j / nSSlices * 2.0 * M_PI) * sin(t);

			float nx = cos((float)j / nSSlices * 2.0 * M_PI) * cos(t);
			float ny = sin((float)j / nSSlices * 2.0 * M_PI);
			float nz = cos((float)j / nSSlices * 2.0 * M_PI) * sin(t);

			M4_vertices[j + i * nSSlices].pos = glm::vec3(x, y, z);
			M4_vertices[j + i * nSSlices].norm = glm::vec3(nx, ny, nz);

		}
	}

	// indices (3 * number of triangles)
	M4_indices.resize(3 * (steps * nSSlices) * 2);

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