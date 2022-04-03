/*
	Alunos:	
			Daniel Akira Nakamura Gullich
			Lucas Gabriel Grutka Telles
			Eduardo Loback Stefani

	Comandos:
			Esc - Sair
			WASD QE - Movimentar (Translação)
			IJKL UO - Rotacionar
			VB		- Escalar
*/

#include <iostream>
#include <GL/freeglut.h>
#include <vector>
using aresta = std::pair<int, int>;

struct vertice {
	double x, y, z;
};

struct Poligono {
	double tamanhoLado;
	int numLados;
	vertice posicao;
	vertice escala;
	double rotacao[3];
	double matriz_rotacao[3][3];
	std::vector<vertice> vertices;
	std::vector<aresta> arestas;
};

Poligono criar_cubo();
void desenhar(Poligono poligono);
void movimentar(Poligono& poligono, double distancia, double x, double y, double z);
void escalar(Poligono& poligono, double escala_x, double escala_y, double escala_z);
void rotacionar(Poligono& poligono, double angulo, double x, double y, double z);

void display();
void redraw(int value);
void keyboard(unsigned char key, int x, int y);
void reshape(GLsizei width, GLsizei height);

Poligono cubo;
int delay = 10;

static double cor[12][3] =
{
		{1.0f,0.5f,0.5f},{1.0f,0.75f,0.5f},{1.0f,1.0f,0.5f},{0.75f,1.0f,0.5f},
		{0.5f,1.0f,0.5f},{0.5f,1.0f,0.75f},{0.5f,1.0f,1.0f},{0.5f,0.75f,1.0f},
		{0.5f,0.5f,1.0f},{0.75f,0.5f,1.0f},{1.0f,0.5f,1.0f},{1.0f,0.5f,0.75f}
};

int main(int argc, char** argv) {

	cubo = criar_cubo();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE); // Double buffer

	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("3D Shapes");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutReshapeFunc(reshape);
	glutTimerFunc(10, redraw, 0);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Coloca a cor de background para preto e opaco
	glClearDepth(1.0f);                   // Define o buffer de profundidade para o mais distante possível

	glEnable(GL_DEPTH_TEST);   // Habilita o culling de profundidade
	glDepthFunc(GL_LEQUAL);    // Define o tipo de teste de profundidade

	glutMainLoop();

	return 0;
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	desenhar(cubo);

	glFlush();
}

void keyboard(unsigned char key, int x, int y) {
	std::cout << key;
	// Sair
	switch (key) {
		case 27:
			exit(0);
			break;

	// Escala
		case 'v':
			escalar(cubo, 1.25, 1.25, 1.25);
			break;
		case 'b':
			escalar(cubo, 0.75, 0.75, 0.75);
			break;
	
	// Movimento
		case 'a':
			movimentar(cubo, 1, -1, 0, 0);
			break;
		case 'w':
			movimentar(cubo, 1, 0, 1, 0);
			break;
		case 's':
			movimentar(cubo, 1, 0, -1, 0);
			break;
		case 'd':
			movimentar(cubo, 1, 1, 0, 0);
			break;
		case 'q':
			movimentar(cubo, 1, 0, 0, 1);
			break;
		case 'e':
			movimentar(cubo, 1, 0, 0, -1);
			break;

	// Rotação
		case 'i':
			rotacionar(cubo, -0.1, 1, 0, 0);
			break;
		case 'k':
			rotacionar(cubo, 0.1, 1, 0, 0);
			break;
		case 'j':
			rotacionar(cubo, -0.1, 0, 1, 0);
			break;
		case 'l':
			rotacionar(cubo, 0.1, 0, 1, 0);
			break;
		case 'u':
			rotacionar(cubo, -0.1, 0, 0, 1);
			break;
		case 'o':
			rotacionar(cubo, 0.1, 0, 0, 1);
			break;
	}
}

void redraw(int value) {

	glutPostRedisplay();
	glutTimerFunc(delay, redraw, 0);
}

vertice criar_vertice(double pos_x, double pos_y, double pos_z) {
	vertice novo_v;
	novo_v.x = pos_x;
	novo_v.y = pos_y;
	novo_v.z = pos_z;

	return novo_v;
}

Poligono criar_cubo() {
	Poligono novo_poligono;
	novo_poligono.numLados = 12;
	novo_poligono.posicao.x = 0.0f;
	novo_poligono.posicao.y = 0.0f;
	novo_poligono.posicao.z = -8.0f;

	novo_poligono.escala.x = 1;
	novo_poligono.escala.y = 1;
	novo_poligono.escala.z = 1;

	novo_poligono.rotacao[0] = 0;
	novo_poligono.rotacao[1] = 0;
	novo_poligono.rotacao[2] = 0;

	// Vertices
	// Face da frente  (z = 1.0f)
	novo_poligono.vertices.push_back(criar_vertice(1.0f, 1.0f, -7.0f));
	novo_poligono.vertices.push_back(criar_vertice(-1.0f, 1.0f, -7.0f));
	novo_poligono.vertices.push_back(criar_vertice(-1.0f, -1.0f, -7.0f));
	novo_poligono.vertices.push_back(criar_vertice(1.0f, -1.0f, -7.0f));

	// Face de trás (z = -1.0f)
	novo_poligono.vertices.push_back(criar_vertice(1.0f, -1.0f, -9.0f));
	novo_poligono.vertices.push_back(criar_vertice(-1.0f, -1.0f, -9.0f));
	novo_poligono.vertices.push_back(criar_vertice(-1.0f, 1.0f, -9.0f));
	novo_poligono.vertices.push_back(criar_vertice(1.0f, 1.0f, -9.0f));

	// Arestas
	novo_poligono.arestas.push_back(aresta(0, 1));
	novo_poligono.arestas.push_back(aresta(1, 2));
	novo_poligono.arestas.push_back(aresta(2, 3));
	novo_poligono.arestas.push_back(aresta(3, 0));

	novo_poligono.arestas.push_back(aresta(7, 6));
	novo_poligono.arestas.push_back(aresta(6, 5));
	novo_poligono.arestas.push_back(aresta(5, 4));
	novo_poligono.arestas.push_back(aresta(4, 7));

	novo_poligono.arestas.push_back(aresta(0, 7));
	novo_poligono.arestas.push_back(aresta(1, 6));
	novo_poligono.arestas.push_back(aresta(2, 5));
	novo_poligono.arestas.push_back(aresta(3, 4));


	std::cout << "Vertices:\n";
	for (int i = 0; i < novo_poligono.vertices.size() ; i++) {
		std::cout << i << "-| " << novo_poligono.vertices[i].x << " | " << novo_poligono.vertices[i].y << " | " << novo_poligono.vertices[i].z << "\n";
	}

	std::cout << "Arestas:\n";
	for (int i = 0; i < novo_poligono.numLados; i++) {
		std::cout << novo_poligono.arestas[i].first << " - " << novo_poligono.arestas[i].second << "\n";
	}

	return novo_poligono;
}

void movimentar(Poligono& poligono, double distancia, double x, double y, double z) {
	poligono.posicao.x = poligono.posicao.x + (distancia * x);
	poligono.posicao.y = poligono.posicao.y + (distancia * y);
	poligono.posicao.z = poligono.posicao.z + (distancia * z);

	for (int i = 0; i < poligono.vertices.size(); i++) {
		poligono.vertices[i].x = poligono.vertices[i].x + (distancia * x);
		poligono.vertices[i].y = poligono.vertices[i].y + (distancia * y);
		poligono.vertices[i].z = poligono.vertices[i].z + (distancia * z);
	}

	std::cout << "Vertices:\n";
	for (int i = 0; i < poligono.vertices.size(); i++) {
		std::cout << i << "-| " << poligono.vertices[i].x << " | " << poligono.vertices[i].y << " | " << poligono.vertices[i].z << "\n";
	}

}

void escalar(Poligono& poligono, double escala_x, double escala_y, double escala_z) {
	poligono.escala.x = escala_x;
	poligono.escala.y = escala_y;
	poligono.escala.z = escala_z;
	for (int i = 0; i < poligono.vertices.size(); i++) {
		poligono.vertices[i].x = poligono.vertices[i].x - poligono.posicao.x;
		poligono.vertices[i].y = poligono.vertices[i].y - poligono.posicao.y;
		poligono.vertices[i].z = poligono.vertices[i].z - poligono.posicao.z;

		poligono.vertices[i].x = poligono.vertices[i].x * escala_x;
		poligono.vertices[i].y = poligono.vertices[i].y * escala_y;
		poligono.vertices[i].z = poligono.vertices[i].z * escala_z;

		poligono.vertices[i].x = poligono.vertices[i].x + poligono.posicao.x;
		poligono.vertices[i].y = poligono.vertices[i].y + poligono.posicao.y;
		poligono.vertices[i].z = poligono.vertices[i].z + poligono.posicao.z;
	}

	std::cout << "Vertices:\n";
	for (int i = 0; i < poligono.vertices.size(); i++) {
		std::cout << i << "-| " << poligono.vertices[i].x << " | " << poligono.vertices[i].y << " | " << poligono.vertices[i].z << "\n";
	}

}

void rotacionar(Poligono& poligono, double angulo, double x, double y, double z) {

	/*
	if (x == 1) {
		poligono.rotacao[0] += angulo;
	}

	if (y == 1) {
		poligono.rotacao[1] += angulo;
	}

	if (z == 1) {
		poligono.rotacao[2] += angulo;
	}
	poligono.matriz_rotacao[0][0] = cos(angulo);
	poligono.matriz_rotacao[0][1] = -sin(angulo);
	poligono.matriz_rotacao[1][0] = sin(angulo);
	poligono.matriz_rotacao[1][1] = cos(angulo);
	*/

	vertice pivo = poligono.posicao;

	for (int i = 0; i < poligono.vertices.size(); i++) {
		
		poligono.vertices[i].x = poligono.vertices[i].x - pivo.x;
		poligono.vertices[i].y = poligono.vertices[i].y - pivo.y;
		poligono.vertices[i].z = poligono.vertices[i].z - pivo.z;
		

		if (x == 1) {
			double aux =			 cos(angulo) * poligono.vertices[i].y - sin(angulo) * poligono.vertices[i].z;
			poligono.vertices[i].z = sin(angulo) * poligono.vertices[i].y + cos(angulo) * poligono.vertices[i].z;
			poligono.vertices[i].y = aux;
		}

		if (y == 1) {
			double aux =			 cos(angulo) * poligono.vertices[i].x + sin(angulo) * poligono.vertices[i].z;
			poligono.vertices[i].z = - sin(angulo) * poligono.vertices[i].x + cos(angulo) * poligono.vertices[i].z;
			poligono.vertices[i].x = aux;
		}

		if (z == 1) {
			double aux =			 cos(angulo) * poligono.vertices[i].x - sin(angulo) * poligono.vertices[i].y;
			poligono.vertices[i].y = sin(angulo) * poligono.vertices[i].x + cos(angulo) * poligono.vertices[i].y;
			poligono.vertices[i].x = aux;
		}

		poligono.vertices[i].x = poligono.vertices[i].x + pivo.x;
		poligono.vertices[i].y = poligono.vertices[i].y + pivo.y;
		poligono.vertices[i].z = poligono.vertices[i].z + pivo.z;

	}

	std::cout << "Vertices:\n";
	for (int i = 0; i < poligono.vertices.size(); i++) {
		std::cout << i << "-| " << poligono.vertices[i].x << " | " << poligono.vertices[i].y << " | " << poligono.vertices[i].z << "\n";
	}


}

void desenhar(Poligono poligono) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa o buffer de cor e o de profundidade
	glMatrixMode(GL_MODELVIEW);     //Operar na matriz de ModelView

	// Renderiza um cubo
	glLoadIdentity();                 // Reseta para a matriz identidade
	glLineWidth(4.0);
	glBegin(GL_LINES);                // Começa a desenhar o cubo
	for (int i = 0; i < poligono.numLados; i++) {
		glColor3f(cor[i][0], cor[i][1], cor[i][2]);
		glVertex3f(poligono.vertices[poligono.arestas[i].first].x, poligono.vertices[poligono.arestas[i].first].y, poligono.vertices[poligono.arestas[i].first].z);
		glVertex3f(poligono.vertices[poligono.arestas[i].second].x, poligono.vertices[poligono.arestas[i].second].y, poligono.vertices[poligono.arestas[i].second].z);
		
	}

	glEnd();

	glutSwapBuffers();  // Double Buffer, troca o atual pelo que está aguardando
}

//Função de redesenhou prioriza o aspecto da projeção
void reshape(GLsizei width, GLsizei height) {
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspect, 0.1f, 1000.0f);
}