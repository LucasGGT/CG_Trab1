#include <iostream>
#include <GL/freeglut.h>
#include <vector>
//using vertice = std::pair<double, double>;
//using lista_vertices = std::vector<vertice>;
using aresta = std::pair<int, int>;

struct vertice {
	double x, y, z;
};

struct Poligono {
	double tamanhoLado;
	int numLados;
	vertice posicao;
	vertice escala;
	double rotacao;
	double matriz_rotacao[3][3];
	std::vector<vertice> vertices;
	std::vector<aresta> arestas;
};

Poligono criar_cubo(double posicao_x, double posicao_y, double posicao_z, double tamanho_lado, int num_lados);
void desenhar(Poligono poligono);
void movimentar(Poligono& poligono, double distancia, double angulo);
void escalar(Poligono& poligono, double escala_x, double escala_y, double escala_z);
void rotacionar(Poligono& poligono, double angulo);

void display();
void idle();
void redraw(int value);
void keyboard(unsigned char key, int x, int y);
void keyboard_special(int key, int x, int y);
void reshape(GLsizei width, GLsizei height);

Poligono cubo;
int delay = 10;

int main(int argc, char** argv) {

	cubo = criar_cubo(128, 128, 5, 2.0f, 12);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE); // Double buffer

	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("3D Shapes");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard_special);

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
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'j':
		escalar(cubo, 1.5, 1.5, 1.5);
		break;
	case 'k':
		escalar(cubo, 0.5, 0.5, 0.5);
		break;
	}
}

void keyboard_special(int key, int x, int y) {
	std::cout << key;
	switch (key) {
	case GLUT_KEY_DOWN:
		movimentar(cubo, 10, (270 / 180.0) * 3.1416);
		break;

	case GLUT_KEY_UP:
		movimentar(cubo, 10, (90 / 180.0) * 3.1416);
		break;

	case GLUT_KEY_RIGHT:
		movimentar(cubo, 10, (0 / 180.0) * 3.1416);
		break;

	case GLUT_KEY_LEFT:
		movimentar(cubo, 10, (180 / 180.0) * 3.1416);
		break;

	}
}

void redraw(int value) {

	glutPostRedisplay();
	//rotacionar(pentagono, 0.05);
	glutTimerFunc(delay, redraw, 0);
}

void idle() {

}

vertice criar_vertice(double pos_x, double pos_y, double pos_z) {
	vertice novo_v;
	novo_v.x = pos_x;
	novo_v.y = pos_y;
	novo_v.z = pos_z;

	return novo_v;
}

Poligono criar_cubo(double posicao_x, double posicao_y, double posicao_z, double tamanho_lado, int num_lados) {
	Poligono novo_poligono;
	novo_poligono.numLados = num_lados;
	novo_poligono.posicao.x = posicao_x;
	novo_poligono.posicao.y = posicao_y;
	novo_poligono.posicao.z = posicao_z;
	novo_poligono.tamanhoLado = tamanho_lado;

	novo_poligono.escala.x = 1;
	novo_poligono.escala.y = 1;
	novo_poligono.escala.z = 1;

	novo_poligono.rotacao = 0;

	float zoom = 20.0f;
	// Vertices
	// Face da frente  (z = 1.0f)
	novo_poligono.vertices.push_back(criar_vertice(1.0f, 1.0f, 1.0f));
	novo_poligono.vertices.push_back(criar_vertice(-1.0f, 1.0f, 1.0f));
	novo_poligono.vertices.push_back(criar_vertice(-1.0f, -1.0f, 1.0f));
	novo_poligono.vertices.push_back(criar_vertice(1.0f, -1.0f, 1.0f));

	// Face de trás (z = -1.0f)
	novo_poligono.vertices.push_back(criar_vertice(1.0f, -1.0f, -1.0f));
	novo_poligono.vertices.push_back(criar_vertice(-1.0f, -1.0f, -1.0f));
	novo_poligono.vertices.push_back(criar_vertice(-1.0f, 1.0f, -1.0f));
	novo_poligono.vertices.push_back(criar_vertice(1.0f, 1.0f, -1.0f));

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
	for (int i = 0; i < num_lados; i++) {
		std::cout << novo_poligono.arestas[i].first << " - " << novo_poligono.arestas[i].second << "\n";
	}

	return novo_poligono;
}

void movimentar(Poligono& poligono, double distancia, double angulo) {
	poligono.posicao.x = poligono.posicao.x + distancia * cos(angulo);
	poligono.posicao.y = poligono.posicao.y + distancia * sin(angulo);
	for (int i = 0; i < poligono.vertices.size(); i++) {
		poligono.vertices[i].x = poligono.vertices[i].x + distancia * cos(angulo);
		poligono.vertices[i].y = poligono.vertices[i].y + distancia * sin(angulo);
	}
}

void escalar(Poligono& poligono, double escala_x, double escala_y, double escala_z) {
	poligono.escala.x = escala_x;
	poligono.escala.y = escala_y;
	poligono.escala.z = escala_z;
	for (int i = 0; i < poligono.vertices.size(); i++) {
		//poligono.vertices[i].x = poligono.vertices[i].x -poligono.posicao.x;
		//poligono.vertices[i].y = poligono.vertices[i].y -poligono.posicao.y;
		//poligono.vertices[i].z = poligono.vertices[i].z - poligono.posicao.z;

		poligono.vertices[i].x = poligono.vertices[i].x * escala_x;
		poligono.vertices[i].y = poligono.vertices[i].y * escala_y;
		poligono.vertices[i].z = poligono.vertices[i].z * escala_z;

		//poligono.vertices[i].x = poligono.vertices[i].x + poligono.posicao.x;
		//poligono.vertices[i].y = poligono.vertices[i].y + poligono.posicao.y;
		//poligono.vertices[i].z = poligono.vertices[i].z + poligono.posicao.z;
	}

	std::cout << "Vertices:\n";
	for (int i = 0; i < poligono.vertices.size(); i++) {
		std::cout << i << "-| " << poligono.vertices[i].x << " | " << poligono.vertices[i].y << " | " << poligono.vertices[i].z << "\n";
	}

}

void rotacionar(Poligono& poligono, double angulo) {
	poligono.rotacao += angulo;

	poligono.matriz_rotacao[0][0] = cos(angulo);
	poligono.matriz_rotacao[0][1] = -sin(angulo);
	poligono.matriz_rotacao[1][0] = sin(angulo);
	poligono.matriz_rotacao[1][1] = cos(angulo);

	vertice pivo = poligono.posicao;

	for (int i = 0; i < poligono.vertices.size(); i++) {
		poligono.vertices[i].x = poligono.vertices[i].x - pivo.x;
		poligono.vertices[i].y = poligono.vertices[i].y - pivo.y;

		double matriz[2][2];

		matriz[0][0] = cos(angulo);
		matriz[0][1] = -sin(angulo);
		matriz[1][0] = sin(angulo);
		matriz[1][1] = cos(angulo);

		double aux = poligono.vertices[i].x * matriz[0][0] + poligono.vertices[i].y * matriz[0][1];
		poligono.vertices[i].y = poligono.vertices[i].x * matriz[1][0] + poligono.vertices[i].y * matriz[1][1];
		poligono.vertices[i].x = aux;

		poligono.vertices[i].x = poligono.vertices[i].x + pivo.x;
		poligono.vertices[i].y = poligono.vertices[i].y + pivo.y;
	}

}

void desenhar(Poligono poligono) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa o buffer de cor e o de profundidade
	glMatrixMode(GL_MODELVIEW);     //Operar na matriz de ModelView

	// Renderiza um cubo com 6 quads diferentes
	glLoadIdentity();                 // Reseta para a matriz identidade
	glTranslatef(0.0f, 0.0f, -10.0);  // Move para a direta da view o que será desenhado

	glRotatef(30, 1, 1, 0);//Só para teste
	//std::cout << "\nDesenhar Ativado\n";

	glBegin(GL_LINES);                // Começa a desenhar o cubo
	for (int i = 0; i < poligono.numLados; i++) {
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