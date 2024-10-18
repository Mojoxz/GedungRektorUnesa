#include <GL/glut.h>
#include <cmath>
#include <vector>

#define PI 3.14159265358979323846

struct Warna
{
	float r, g, b, a;
	Warna(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) {}
};

const Warna LANGIT_BIRU(0.53f, 0.81f, 0.92f);
const Warna GEDUNG_BIRU(0.1f, 0.35f, 0.7f);
const Warna KACA_REKTOR(0.2f, 0.4f, 0.8f, 0.7f);
const Warna AKSEN_PUTIH(1.0f, 1.0f, 1.0f);
const Warna PUTIH(1.0f, 1.0f, 1.0f);
const Warna ABUABU(0.9f, 0.9f, 0.9f);
const Warna HIJAU(0.33f, 0.67f, 0.24f);

void init() {

	glClearColor(LANGIT_BIRU.r, LANGIT_BIRU.g, LANGIT_BIRU.b, LANGIT_BIRU.a);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

}

void setWarna(const Warna& warna) {
	glColor4f(warna.r, warna.g, warna.b, warna.a);
}

void gambarLengkung(float x, float y, float width, float height, float radius, bool topCurved = true, bool bottomCurved = true) {
	float x2 = x + width;
	float y2 = y + height;
	int segments = 20;

	glBegin(GL_POLYGON);

	// Sudut kiri bawah
	if (bottomCurved) {
		for (int i = 180; i <= 270; i++) {
			float angle = i * PI / 180;
			glVertex2f(x + radius + radius * cos(angle), y + radius + radius * sin(angle));
		}
	}
	else {
		glVertex2f(x, y);
	}

	// Sudut kanan bawah
	if (bottomCurved) {
		for (int i = 270; i <= 360; i++) {
			float angle = i * PI / 180;
			glVertex2f(x2 - radius + radius * cos(angle), y + radius + radius * sin(angle));
		}
	}
	else {
		glVertex2f(x2, y);
	}

	// Sudut kanan atas
	if (topCurved) {
		for (int i = 0; i <= 90; i++) {
			float angle = i * PI / 180;
			glVertex2f(x2 - radius + radius * cos(angle), y2 - radius + radius * sin(angle));
		}
	}
	else {
		glVertex2f(x2, y2);
	}

	// Sudut kiri atas
	if (topCurved) {
		for (int i = 90; i <= 180; i++) {
			float angle = i * PI / 180;
			glVertex2f(x + radius + radius * cos(angle), y2 - radius + radius * sin(angle));
		}
	}
	else {
		glVertex2f(x, y2);
	}

	glEnd();
}

void gambarJendela(float x, float y, float width, float height, bool curved = true) {

	setWarna(Warna(0.7f, 0.85f, 0.9f, 0.7f));
	gambarLengkung(x, y, width, height, curved ? 0.0f : 0.0f);

	setWarna(Warna(0.6f, 0.6f, 0.6f));
	glLineWidth(1.0f);
	if (curved) 
	{
		float radius = 2.0f;
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i <= 360; i++){
			float angle = i * PI / 250;
			glVertex2f(x + radius + radius + cos(angle), y + radius + radius * sin(angle));
		}
		glEnd();
	}

	else{
		glBegin(GL_LINE_LOOP);
		glVertex2f(x, y);
		glVertex2f(x + width, y);
		glVertex2f(x + width, y * height);
		glVertex2f(x, y + height);
		glEnd();
	}
}

void gambarBangunan() {
	
	glPushMatrix();
	glScalef(0.9f, 0.9f, 1.0f);  
	glTranslatef(30.0f, 20.0f, 0.0f); 


	glBegin(GL_QUADS);


	setWarna(Warna(0.33f, 0.67f, 0.24f)); 
	glVertex2f(0.0f, 150.0f);  
	glVertex2f(800.0f, 150.0f); 

	setWarna(Warna(0.1f, 0.4f, 0.1f)); 
	glVertex2f(800.0f, 0.0f);  
	glVertex2f(0.0f, 0.0f);  



	for (int i = 0; i < 4; i++) {
		setWarna(ABUABU);
		gambarLengkung(150.0f - (i * 10), 115.0f - (i * 5), 500.0f + (i * 20), 5.0f, 5.0f);
	}

	// sayap kiri rektor
	setWarna(GEDUNG_BIRU);
	gambarLengkung(150.0f, 120.0f, 150.0f, 160.0f, 2.0f);

	// sayap kanan rektor
	gambarLengkung(500.0f, 120.0f, 150.0f, 160.0f, 2.0f);

	// gedung utama rektor
	gambarLengkung(325.0f, 120.0f, 150.0f, 330.0f, 5.0f);

	// aksen putih
	setWarna(AKSEN_PUTIH);
	gambarLengkung(325.0f, 120.0f, 15.0f, 320.0f, 2.0f);
	gambarLengkung(460.0f, 120.0f, 15.0f, 330.0f, 2.0f);

	// jendela gedung utama
	for (int i = 0; i < 2; i++) {
		gambarJendela(350.0f, 270.0f + (i * 33), 100.0f, 20.0f);
	}

	// jendela sayap kiri
	gambarJendela(170.0f, 140.0f, 110.0f, 20.0f);

	// jendela sayap kanan
	gambarJendela(520.0f, 140.0f, 110.0f, 20.0f);

	// atap putih sayap rektor
	setWarna(PUTIH);
	gambarLengkung(150.0f, 260.0f, 150.0f, 20.0f, 1.0f, false, true);
	gambarLengkung(500.0f, 260.0f, 150.0f, 20.0f, 1.0f, false, true);

	// kotak logo unesa
	setWarna(Warna(0.05f, 0.2f, 0.5f));
	gambarLengkung(375.0f, 350.0f, 50.0f, 70.0f, 3.0f);

	// atap rektorat
	setWarna(Warna(0.5f, 0.5f, 0.5f));
	glBegin(GL_QUADS);
	glVertex2f(350.0f, 450.0f);
	glVertex2f(450.0f, 450.0f);
	glVertex2f(450.0f, 470.0f);
	glVertex2f(350.0f, 470.0f);
	glEnd();

	// atap segitiga
	setWarna(Warna(0.3f, 0.3f, 0.3f));
	glBegin(GL_TRIANGLES);
	glVertex2f(325.0f, 450.0f);
	glVertex2f(475.0f, 450.0f);
	glVertex2f(400.0f, 490.0f);
	glEnd();

	glPopMatrix();
}

void GradasiLangit() {
	glBegin(GL_QUADS);

	// Warna langit biru di atas
	setWarna(Warna(0.53f, 0.81f, 0.92f)); // Biru langit
	glVertex2f(0.0f, 600.0f); // Kiri atas
	glVertex2f(800.0f, 600.0f); // Kanan atas

	// Warna oranye di bawah (untuk senja)
	setWarna(Warna(1.0f, 0.6f, 0.2f)); // Oranye senja
	glVertex2f(800.0f, 0.0f); // Kanan bawah
	glVertex2f(0.0f, 0.0f); // Kiri bawah

	glEnd();
}



void layar() {
	
	glClear(GL_COLOR_BUFFER_BIT);

	GradasiLangit();

	gambarBangunan();

	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("BANGUNAN REKTOR UNESA");
	init();
	glutDisplayFunc(layar);
	glutMainLoop();
	return 0;
}