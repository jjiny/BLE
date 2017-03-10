#include <Windows.h> 
#include <GL/GL.h> 
#include <GL/GLU.h> 
#include <GL/glut.h> 
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <math.h>

typedef GLfloat point3[3];

static float theta[3];
void Normalize(point3 &p);
void CrossProduct(point3 &a, point3 &b, point3 &c, point3 &r);
using namespace std;

vector<vector<float>> dot;
vector<vector<int>> line;
vector<vector<GLfloat>> face;
vector<vector<GLfloat>>vertexNormalIndex;

int index = 1;
bool first = true;
void CrossProduct(point3 &a, point3 &b, point3 &c, point3 &r)
{
	r[0] = (b[1] - a[1])*(c[2] - a[2]) - (b[2] - a[2])*(c[1] - a[1]);
	r[1] = (b[2] - a[2])*(c[2] - a[0]) - (b[0] - a[0])*(c[2] - a[2]);
	r[2] = (b[0] - a[0])*(c[1] - a[1]) - (b[1] - a[1])*(c[0] - a[0]);
	Normalize(r);
}
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (first) {
		gluLookAt(5, 5, 5, 0, 0, 0, 0, 5, 0);
		glScalef(2, 2, 2);
		first = false;
	}

	glColor3f(0, 0, 0);

	if (index == 1)
	{
		glBegin(GL_POINTS);
		{
			for (unsigned int i = 0; i < dot.size(); i++)
			{
				glVertex3f(dot[(GLfloat)line[i][0] - 1][0], dot[(GLfloat)line[i][0] - 1][1], dot[(GLfloat)line[i][0] - 1][2]);
				glVertex3f(dot[(GLfloat)line[i][1] - 1][0], dot[(GLfloat)line[i][1] - 1][1], dot[(GLfloat)line[i][1] - 1][2]);
				glVertex3f(dot[(GLfloat)line[i][2] - 1][0], dot[(GLfloat)line[i][2] - 1][1], dot[(GLfloat)line[i][2] - 1][2]);

				//cout << dots[i][0] << " " << dots[i][1] << " " << dots[i][2] << endl;
			}
		}
		glEnd();
	}
	else if (index == 2)
	{
		glLineWidth(0.5);
		for (unsigned int i = 0; i < line.size(); i++)
		{
			glBegin(GL_LINE_LOOP);
			glVertex3f(dot[(GLfloat)line[i][0] - 1][0], dot[(GLfloat)line[i][0] - 1][1], dot[(GLfloat)line[i][0] - 1][2]);
			glVertex3f(dot[(GLfloat)line[i][1] - 1][0], dot[(GLfloat)line[i][1] - 1][1], dot[(GLfloat)line[i][1] - 1][2]);
			glVertex3f(dot[(GLfloat)line[i][2] - 1][0], dot[(GLfloat)line[i][2] - 1][1], dot[(GLfloat)line[i][2] - 1][2]);
			//cout << dots[(GLfloat)lines[i][0] - 1][0] << " " << dots[(GLfloat)lines[i][1] - 1][0] << " " << dots[(GLfloat)lines[i][2] - 1][2] << endl;
			glEnd();
		}
	}
	else if (index == 3)
	{
		glLineWidth(0.5);
		for (unsigned int i = 0; i < line.size(); i++)
		{
			glBegin(GL_TRIANGLES);
			{
				glVertex3f(dot[(GLfloat)line[i][0] - 1][0], dot[(GLfloat)line[i][0] - 1][1], dot[(GLfloat)line[i][0] - 1][2]);
				glVertex3f(dot[(GLfloat)line[i][1] - 1][0], dot[(GLfloat)line[i][1] - 1][1], dot[(GLfloat)line[i][1] - 1][2]);
				glVertex3f(dot[(GLfloat)line[i][2] - 1][0], dot[(GLfloat)line[i][2] - 1][1], dot[(GLfloat)line[i][2] - 1][2]);
				//cout << dots[(GLfloat)lines[i][0] - 1][0] << " " << dots[(GLfloat)lines[i][1] - 1][0] << " " << dots[(GLfloat)lines[i][2] - 1][2] << endl;
			}
			glEnd();
		}
	}
	else if (index == 4)
	{
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0f, 1.0f);
		glLineWidth(0.5);
		for (unsigned int i = 0; i < line.size(); i++)
		{
			glBegin(GL_TRIANGLES);
			{
				glColor3f(0, 0, 0);
				glVertex3f(dot[(GLfloat)line[i][0] - 1][0], dot[(GLfloat)line[i][0] - 1][1], dot[(GLfloat)line[i][0] - 1][2]);
				glVertex3f(dot[(GLfloat)line[i][1] - 1][0], dot[(GLfloat)line[i][1] - 1][1], dot[(GLfloat)line[i][1] - 1][2]);
				glVertex3f(dot[(GLfloat)line[i][2] - 1][0], dot[(GLfloat)line[i][2] - 1][1], dot[(GLfloat)line[i][2] - 1][2]);
			}
			glEnd();
		}


		for (unsigned int i = 0; i < line.size(); i++)
		{
			glBegin(GL_LINE_LOOP);
			{
				glColor3f(0.5, 0.5, 0.5);
				glVertex3f(dot[(GLfloat)line[i][0] - 1][0], dot[(GLfloat)line[i][0] - 1][1], dot[(GLfloat)line[i][0] - 1][2]);
				glVertex3f(dot[(GLfloat)line[i][1] - 1][0], dot[(GLfloat)line[i][1] - 1][1], dot[(GLfloat)line[i][1] - 1][2]);
				glVertex3f(dot[(GLfloat)line[i][2] - 1][0], dot[(GLfloat)line[i][2] - 1][1], dot[(GLfloat)line[i][2] - 1][2]);
			}
			glEnd();
			//cout << line.size();
		}

		for (unsigned int i = 0; i < line.size(); i++)
		{
			point3 r;

			point3 v[3] = {
				{ dot[(GLfloat)line[i][0] - 1][0], dot[(GLfloat)line[i][0] - 1][1], dot[(GLfloat)line[i][0] - 1][2] },
				{ dot[(GLfloat)line[i][1] - 1][0], dot[(GLfloat)line[i][1] - 1][1], dot[(GLfloat)line[i][1] - 1][2] },
				{ dot[(GLfloat)line[i][2] - 1][0], dot[(GLfloat)line[i][2] - 1][1], dot[(GLfloat)line[i][2] - 1][2] },
			};

			glBegin(GL_LINES);
			{
				CrossProduct(v[0], v[1], v[2], r);

				glColor3f(0, 0, 0);
				glVertex3f(0.333* (dot[(GLfloat)line[i][0] - 1][0] + dot[(GLfloat)line[i][1] - 1][0] + dot[(GLfloat)line[i][2] - 1][0]),
					0.333* (dot[(GLfloat)line[i][0] - 1][1] + dot[(GLfloat)line[i][1] - 1][1] + dot[(GLfloat)line[i][2] - 1][1]),
					0.333*(dot[(GLfloat)line[i][0] - 1][2] + dot[(GLfloat)line[i][1] - 1][2] + dot[(GLfloat)line[i][2] - 1][2]));

				glVertex3f(0.333* (dot[(GLfloat)line[i][0] - 1][0] + dot[(GLfloat)line[i][1] - 1][0] + dot[(GLfloat)line[i][2] - 1][0]) + 0.1*r[0],
					0.333* (dot[(GLfloat)line[i][0] - 1][1] + dot[(GLfloat)line[i][1] - 1][1] + dot[(GLfloat)line[i][2] - 1][1]) + 0.1*r[1],
					0.333*(dot[(GLfloat)line[i][0] - 1][2] + dot[(GLfloat)line[i][1] - 1][2] + dot[(GLfloat)line[i][2] - 1][2]) + 0.1*r[2]);
			}
			glEnd();
		}

	}
	else if (index == 5)
	{
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0f, 1.0f);
		//glLineWidth(0.5);
		for (unsigned int i = 0; i < line.size(); i++)
		{
			glBegin(GL_TRIANGLES);
			{
				glColor3f(0, 0, 0);
				glVertex3f(dot[(GLfloat)line[i][0] - 1][0], dot[(GLfloat)line[i][0] - 1][1], dot[(GLfloat)line[i][0] - 1][2]);
				glVertex3f(dot[(GLfloat)line[i][1] - 1][0], dot[(GLfloat)line[i][1] - 1][1], dot[(GLfloat)line[i][1] - 1][2]);
				glVertex3f(dot[(GLfloat)line[i][2] - 1][0], dot[(GLfloat)line[i][2] - 1][1], dot[(GLfloat)line[i][2] - 1][2]);
			}
			glEnd();
		}


		for (unsigned int i = 0; i < line.size(); i++)
		{
			glBegin(GL_LINE_LOOP);
			{
				glColor3f(0.5, 0.5, 0.5);
				glVertex3f(dot[(GLfloat)line[i][0] - 1][0], dot[(GLfloat)line[i][0] - 1][1], dot[(GLfloat)line[i][0] - 1][2]);
				glVertex3f(dot[(GLfloat)line[i][1] - 1][0], dot[(GLfloat)line[i][1] - 1][1], dot[(GLfloat)line[i][1] - 1][2]);
				glVertex3f(dot[(GLfloat)line[i][2] - 1][0], dot[(GLfloat)line[i][2] - 1][1], dot[(GLfloat)line[i][2] - 1][2]);
			}
			glEnd();
			//cout << line.size();
		}

		for (unsigned int i = 0; i < dot.size(); i++)
		{
			//vertexNormalIndex.clear();
			for (unsigned int j = 0; j < line.size(); j++) {
				if (line[j][0] == i - 1 || line[j][1] == i - 1 || line[j][2] == i - 1) {
					point3 r;
					point3 v[3] = {
						{ dot[(GLfloat)line[j][0] - 1][0], dot[(GLfloat)line[j][0] - 1][1], dot[(GLfloat)line[j][0] - 1][2] },
						{ dot[(GLfloat)line[j][1] - 1][0], dot[(GLfloat)line[j][1] - 1][1], dot[(GLfloat)line[j][1] - 1][2] },
						{ dot[(GLfloat)line[j][2] - 1][0], dot[(GLfloat)line[j][2] - 1][1], dot[(GLfloat)line[j][2] - 1][2] },
					};
					CrossProduct(v[0], v[1], v[2], r); //v[0]~[2]삼각형 의 법선벡터

					vector<GLfloat> faceNormal;
					faceNormal.clear();

					faceNormal.push_back(r[0]);
					faceNormal.push_back(r[1]);
					faceNormal.push_back(r[2]);

					face.push_back(faceNormal);		//페이스벡터
				}

			}
			point3 vertexNormal;

			for (int k = 0; k < face.size(); k++) { //각각x,y,z좌표 face노말벡터 합 구함	
				vertexNormal[0] += face[k][0];
				vertexNormal[1] += face[k][1];
				vertexNormal[2] += face[k][2];
			}
			Normalize(vertexNormal); //합한거 normalize함
			vector<GLfloat> tempNormal;

			tempNormal.push_back(vertexNormal[0]);
			tempNormal.push_back(vertexNormal[1]);
			tempNormal.push_back(vertexNormal[2]);
			vertexNormalIndex.push_back(tempNormal);
		}
		//cout << endl << vertexNormalIndex.size();
		for (unsigned int i = 0; i < dot.size(); i++)
		{

			glBegin(GL_LINES);
			{
				glColor3f(0, 0, 0);
				glVertex3f(dot[i][0], dot[i][1], dot[i][2]);
				glVertex3f(dot[i][0] + vertexNormalIndex[i][0] * 0.3, dot[i][1] + vertexNormalIndex[i][1] * 0.3, dot[i][2] + vertexNormalIndex[i][2] * 0.3);
			}
			glEnd();
		}
	}
	glutSwapBuffers();
}

void SetupRC(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Dot()
{
	vector<float>value;
	int i = 0;

	ifstream file("bunny_origin.txt");// 파일 읽기
	while (!file.eof()) //파일의 끝이 아니라면!
	{
		string _line;
		float num;
		getline(file, _line);
		if (!_line.empty())
		{
			if (i >= 1 && i < 454)
			{
				stringstream ss(_line); //문자열에서 필요한 정보를 빼냄
				string k;
				while (ss >> k)
				{
					istringstream(k) >> num; // 공백기준으로..
					value.push_back(num);
				}
				dot.push_back(value);
				value.clear();
			}
		}
		i++;
	}
}
void Line()
{
	vector<int>value;
	int i = 0;

	ifstream file("bunny_origin.txt");// 파일 읽기
	while (!file.eof()) //파일의 끝이 아니라면!
	{
		string _line;
		int num;
		getline(file, _line);
		if (!_line.empty())
		{
			if (i >= 454 && i < 1402)
			{
				stringstream ss(_line); //문자열에서 필요한 정보를 빼냄
				string k;

				while (ss >> k) // 문자열에 buf가 없을때까지
				{
					istringstream(k) >> num; // 공백기준으로..
					value.push_back(num);
				}
				line.push_back(value);
				value.clear();
			}
		}
		i++;
	}
}

void ChangeSize(int w, int h)
{
	GLfloat aspectRatio;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glFrustum(-5, 5, -5, 5, 5, 100);
	//Prevent a divide by zero
	if (h == 0)
		h = 1;

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//   Establish clipping volume (left, right, bottom, top, near, far)
	aspectRatio = (GLfloat)w / (GLfloat)h;
	//aspectRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0*(float)h / (float)w, 2.0*(float)h / (float)w, -10.0, 10.0);
	else
		glOrtho(-2.0*(float)w / (float)h, 2.0 * (float)w / (float)h, -2.0, 2.0, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
		index = 1; break;
	case 'b':
		index = 2; break;
	case 'c':
		index = 3; break;
	case 'f':
		index = 4; break;
	case 'v':
		index = 5; break;
	}

	glutPostRedisplay();
}
void Normalize(point3 &p)
{
	double d = p[0] * p[0] + p[1] * p[1] + p[2] * p[2];
	if (d > 0)
	{
		float len = (float)(1.0 / sqrt(d));
		p[0] *= len;
		p[1] *= len;
		p[2] *= len;
	}
}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("CG 2013");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(keyboard);

	SetupRC();

	Dot();
	Line();
	glutMainLoop();
}