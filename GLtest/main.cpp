
#include <stdio.h>
#include <stdlib.h>
#include "glslprogram.h"
#include "glutils.h"
#include <glm/glm.hpp>
#include "scene.h"
#include "scenebasic.h"

void init();

SceneBasic *scene;

const float SCREEN_WIDTH = 960.f;
const float SCREEN_HEIGHT = 540.f;

static GLint MVPLocation;
static GLint ModelViewMatrixLocation;
static GLint NormalMatrixLocation;
static GLint LightPosLocation;

void multiplyMatrix(const GLfloat *m0, const GLfloat *m1, GLfloat *matrix)
{
	for (int i = 0; i < 16; ++i) {
		int j = i & ~3, k = i & 3;

		matrix[i] = m0[j + 0] * m1[0 + k]
			+ m0[j + 1] * m1[4 + k]
			+ m0[j + 2] * m1[8 + k]
			+ m0[j + 3] * m1[12 + k];
	}
}

void display(void)
{
	/* 画面クリア */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene->render();

	/* ダブルバッファリング */
	glutSwapBuffers();
}

void resize(int w, int h)
{
	/* ウィンドウ全体をビューポートにする */
	glViewport(0, 0, w, h);

	/* 変換行列の初期化 */
	glLoadIdentity();
	/* スクリーン上の表示領域をビューポートの大きさに比例させる */
	glOrtho(-w / 200.0, w / 200.0, -h / 200.0, h / 200.0, -1.0, 1.0);

	scene->resize(w,h);
	scene->update(0.0f);
}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		printf("left");
		break;
	case GLUT_MIDDLE_BUTTON:
		printf("middle");
		break;
	case GLUT_RIGHT_BUTTON:
		printf("right");
		break;
	default:
		break;
	}

	printf(" button is ");

	switch (state) {
	case GLUT_UP:
		printf("up");
		break;
	case GLUT_DOWN:
		printf("down");
		break;
	default:
		break;
	}

	printf(" at (%d, %d)\n", x, y);
}

void LoadShader() {
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	if (0 == vertShader) {
		printf("頂点シェーダ作成エラー\n");
		exit(1);
	}
	//const GLchar* shaderCode = LoadShaderAsString("basic.vert");
}

void update() {

}

void keyboard(unsigned char key, int x, int y)
{
	const float spd = 0.5f;
	const float rotate = 3.f;
	const float zoom = 1.f;
	switch (key) {
	case 'm':
		scene->getCameraPtr()->fovy += zoom;
		break;
	case 'n':
		scene->getCameraPtr()->fovy -= zoom;
		break;
	case 'w':
		scene->getCameraPtr()->angleY += rotate;
		printf("scene->getCamera() pos:[%f,%f,%f]\n", scene->getCameraPtr()->x, scene->getCameraPtr()->y, scene->getCameraPtr()->z);
		break;
	case 'a':
		scene->getCameraPtr()->angleH -= rotate;
		printf("scene->getCamera() pos:[%f,%f,%f]\n", scene->getCameraPtr()->x, scene->getCameraPtr()->y, scene->getCameraPtr()->z);
		break;
	case 's':
		scene->getCameraPtr()->angleY -= rotate;
		printf("scene->getCamera() pos:[%f,%f,%f]\n", scene->getCameraPtr()->x, scene->getCameraPtr()->y, scene->getCameraPtr()->z);
		break;
	case 'd':
		scene->getCameraPtr()->angleH += rotate;
		printf("scene->getCamera() pos:[%f,%f,%f]\n", scene->getCameraPtr()->x, scene->getCameraPtr()->y, scene->getCameraPtr()->z);
		break;
	case 'i':
		scene->getCameraPtr()->mTargetPos.z += spd;
		printf("scene->getCamera() pos:[%f,%f,%f]\n", scene->getCameraPtr()->x, scene->getCameraPtr()->y, scene->getCameraPtr()->z);
		break;
	case 'j':
		scene->getCameraPtr()->mTargetPos.x -= spd;
		printf("scene->getCamera() pos:[%f,%f,%f]\n", scene->getCameraPtr()->x, scene->getCameraPtr()->y, scene->getCameraPtr()->z);
		break;
	case 'k':
		scene->getCameraPtr()->mTargetPos.z -= spd;
		printf("scene->getCamera() pos:[%f,%f,%f]\n", scene->getCameraPtr()->x, scene->getCameraPtr()->y, scene->getCameraPtr()->z);
		break;
	case 'l':
		scene->getCameraPtr()->mTargetPos.x += spd;
		printf("scene->getCamera() pos:[%f,%f,%f]\n", scene->getCameraPtr()->x, scene->getCameraPtr()->y, scene->getCameraPtr()->z);
		break;
	case 'q':
	case 'Q':
	case '\033':  /* '\033' は ESC の ASCII コード */
		exit(0);
	default:
		break;
	}
}

void timer(int value) {
	GLfloat top = -0.9f;
	static GLboolean isUp = GL_TRUE;

	if (top > 0.9F) isUp = GL_FALSE;
	else if (top <= -0.9F) isUp = GL_TRUE;
	top += (isUp == GL_TRUE ? 0.01f : -0.01f);

	scene->update(0.f);

	glutPostRedisplay();
	glutTimerFunc(16, timer, 0);
}

int main(int argc, char *argv[])
{
	// Init
	{
		//////////////// PLUG IN SCENE HERE /////////////////
		scene = new SceneBasic();
		////////////////////////////////////////////////////

		glutInitWindowPosition(100, 100);
		glutInitWindowSize((int)SCREEN_WIDTH, (int)SCREEN_HEIGHT);
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
		glutCreateWindow(argv[0]);

		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			printf("Error initializing GLEW : %s\n", glewGetErrorString(err));
		}
		GLUtils::checkForOpenGLError(__FILE__, __LINE__);

		GLUtils::dumpGLInfo();

		init();

		scene->initScene();
	}
	scene->resize((int)SCREEN_WIDTH, (int)SCREEN_HEIGHT);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(100, timer, 0);
	glutMainLoop();

	delete scene;
	return 0;
}

void init() {
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW init error:%s\n", glewGetErrorString(err));
	}

	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *vendor = glGetString(GL_VENDOR);

	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);

	printf("GL Vendor	:%s\n", vendor);
	printf("GL Renderer	:%s\n", renderer);
	printf("GL Version (string)	:%s\n", version);
	printf("GL Version (integer)	:%d.%d\n", major, minor);
	printf("GLSL Version	:%s\n", glslVersion);

	glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}