#pragma once
#include <math.h>

class _Vec2 {
public:
	GLfloat x;
	GLfloat y;
};

class _Vec3 {
public:
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

class _VecInt3 {
public:
	GLint x;
	GLint y;
	GLint z;
};

class loaderNfg {

	struct vertex {
		_Vec3 pos, norm, binorm, tgt;
		_Vec2 uv;
	};

	struct pattern {
		_VecInt3 pos;
	};

public:
	struct vertex jumVertex[512];
	struct pattern jumTampilan[718];
	GLint totalNrVertex, totalNFG;

private:
	FILE* loadModel;

	float px, py, pz, nx, ny, nz, bx, by, bz, tx, ty, tz, u, v;
	int x, y, z;
	char junk[200];

	bool loadFile() {
		fopen_s(&loadModel, "C:/Users/Alfriyanis/Desktop/Github/GRAFKOM_TR_H_672016125/GRAFKOM_TR_H_672016125/Woman1.nfg", "r");
		if (!loadModel) {
			return false;
		}
		return true;
	}

	void loadNrVertex() {
		// Mendapatkan total node
		fscanf_s(this->loadModel, "NrVertices : %d", &totalNrVertex);
	}

	void loadCoordinate() {
		for (int i = 0; i < totalNrVertex; i++) {
			// Membaca nilai pada setiap baris 
			fscanf_s(loadModel, "%*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];", &px, &py, &pz, &nx, &ny, &nz, &bx, &by, &bz, &tx, &ty, &tz, &u, &v);

			this->jumVertex[i].pos.x = px;
			this->jumVertex[i].pos.y = py;
			this->jumVertex[i].pos.z = pz;

			this->jumVertex[i].norm.x = nx;
			this->jumVertex[i].norm.y = ny;
			this->jumVertex[i].norm.z = nz;

			this->jumVertex[i].binorm.x = bx;
			this->jumVertex[i].binorm.y = by;
			this->jumVertex[i].binorm.z = bz;

			this->jumVertex[i].tgt.x = tx;
			this->jumVertex[i].tgt.y = ty;
			this->jumVertex[i].tgt.z = tz;

			this->jumVertex[i].uv.x = u;
			this->jumVertex[i].uv.y = v;
		}
	}

	void loadNrIndices() {
		fscanf_s(this->loadModel, "\nNrIndices:%d", &totalNFG);
	}

	void trianglePattern() {

		int jumTampilan = totalNFG / 3;

		fscanf_s(this->loadModel, "\n");

		for (int i = 0; i < jumTampilan; i++) {
			fscanf_s(this->loadModel, "%*d. %d, %d, %d", &x, &y, &z);
			this->jumTampilan[i].pos.x = x;
			this->jumTampilan[i].pos.y = y;
			this->jumTampilan[i].pos.z = z;
		}

	}

	void closeFile() {
		fclose(loadModel);
	}

public:
	void readfile() {
		if (this->loadFile()) {
			this->loadNrVertex();
			this->loadCoordinate();
			this->loadNrIndices();
			this->trianglePattern();
			this->closeFile();
		}
		else {
			printf("File cannot proccessed");
		}
	}
};