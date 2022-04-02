#include <iostream>
#include <GL/freeglut.h>
#include <vector>
//using vertice = std::pair<double, double>;
//using lista_vertices = std::vector<vertice>;
using aresta = std::pair<int, int>;
using lista_arestas = std::vector<aresta>;

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
	lista_arestas arestas;
};

Poligono criar_poligono(double posicao_x, double posicao_y, double posicao_z, double tamanho_lado, int num_lados);
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

Poligono pentagono;
int delay = 10;

int main(int argc, char** argv) {

	pentagono = criar_poligono(128, 128, 5, 50, 6);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE); // Double buffer

	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("3D Shapes");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard_special);

	glutReshapeFunc(reshape);
	//glutTimerFunc(10, redraw, 0);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Coloca a cor de background para preto e opaco
	glClearDepth(1.0f);                   // Define o buffer de profundidade para o mais distante possível

	glEnable(GL_DEPTH_TEST);   // Habilita o culling de profundidade
	glDepthFunc(GL_LEQUAL);    // Define o tipo de teste de profundidade

	glutMainLoop();

	return 0;
}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	desenhar(pentagono);

	glFlush();
}

void keyboard(unsigned char key, int x, int y) {
	std::cout << key;
	switch (key) {
	case 27:
		exit(0);
		break;
	case ' ':
		escalar(pentagono, 0.1, 0.1, 0.1);
		break;
	}
}

void keyboard_special(int key, int x, int y) {
	std::cout << key;
	switch (key) {
	case GLUT_KEY_DOWN:
		movimentar(pentagono, 10, (270 / 180.0) * 3.1416);
		break;

	case GLUT_KEY_UP:
		movimentar(pentagono, 10, (90 / 180.0) * 3.1416);
		break;

	case GLUT_KEY_RIGHT:
		movimentar(pentagono, 10, (0 / 180.0) * 3.1416);
		break;

	case GLUT_KEY_LEFT:
		movimentar(pentagono, 10, (180 / 180.0) * 3.1416);
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

Poligono criar_poligono(double posicao_x, double posicao_y, double posicao_z, double tamanho_lado, int num_lados) {
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

	float angulo = 0;
	float passo_angulo = ((360 / float(num_lados)) * 3.1416) / 180.0;

	float apothem = tamanho_lado / (2 * tan(3.1416 / float(num_lados)));
	posicao_x -= tamanho_lado / 2.0;
	posicao_y -= apothem;

	novo_poligono.vertices.push_back(criar_vertice(posicao_x, posicao_y, posicao_z));
	std::cout << "Vertices:\n";
	std::cout << 0 << " - " << posicao_x << " - " << posicao_y << " - " << posicao_z << "\n";
	for (int i = 1; i < num_lados; i++) {
		posicao_x = posicao_x + tamanho_lado * cos(angulo);
		posicao_y = posicao_y + tamanho_lado * sin(angulo);
		posicao_z = posicao_z + tamanho_lado * cos(angulo);
		novo_poligono.vertices.push_back(criar_vertice(posicao_x, posicao_y, posicao_z));
		std::cout << i << " - " << posicao_x << " - " << posicao_y << " - " << posicao_z << "\n";
		angulo += passo_angulo;
	}

	std::cout << "Arestas:\n";
	for (int i = 0; i < num_lados; i++) {
		novo_poligono.arestas.push_back(aresta(i, (i + 1) % num_lados));
		std::cout << i << " - " << (i + 1) % num_lados << "\n";
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
	glTranslatef(1.5f, 0.0f, -7.0f);  // Move para a direta da view o que será desenhado

	glBegin(GL_QUADS);                // Começa a desenhar o cubo
	   // Face de cima (y = 1.0f)
	   // Define os vértice em ordem anti-horário com a face apontando para cima
	glColor3f(0.0f, 1.0f, 0.0f);     // Verde
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Face de cima (y = -1.0f)
	glColor3f(1.0f, 0.5f, 0.0f);     // Laranja
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Face da frente  (z = 1.0f)
	glColor3f(1.0f, 0.0f, 0.0f);     // Vermelho
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Face de trás (z = -1.0f)
	glColor3f(1.0f, 1.0f, 0.0f);     // Amarelo
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Face esquerda (x = -1.0f)
	glColor3f(0.0f, 0.0f, 1.0f);     // Azul
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Face direita (x = 1.0f)
	glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	// Renderiza uma pirâmide com 4 triângulos
	glLoadIdentity();                  // Reseta a matriz de modelview
	glTranslatef(-1.5f, 0.0f, -6.0f);  // Move para a esquerda na tela o que será desenhado

	glBegin(GL_TRIANGLES);           // Começa a desenhar a pirâmide com  4 triângulos
	   // Frente
	glColor3f(1.0f, 0.0f, 0.0f);     // Vermelho
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Verde
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Azul
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Direita
	glColor3f(1.0f, 0.0f, 0.0f);     // Vermelho
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Azul
	glVertex3f(1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Verde
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Trás
	glColor3f(1.0f, 0.0f, 0.0f);    // Vermelho
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Verde
	glVertex3f(1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Azul
	glVertex3f(-1.0f, -1.0f, -1.0f);

	// Esquerda
	glColor3f(1.0f, 0.0f, 0.0f);       // Vermelho
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);       // Azul
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);       // Verde
	glVertex3f(-1.0f, -1.0f, 1.0f);
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
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}