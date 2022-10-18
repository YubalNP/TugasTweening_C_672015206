#include <gl/Gl.h>
#include <gl/glut.h>
#define RATIO 1.200 // Mendefinisikan semua kebutuhan dalam program. 
//Mendefinisikan rasio dengan perbandingan 1:1.200
#define WW 100 // Mendefinisikan lebar viewport = 100
#define WH (WW/RATIO) // Mendefinisikan tinggi viewport
#define HALFX ((int)(WW/2)) // Mendefinisikan koordinat X min atau max
#define HALFY ((int)(WH/2)) // Mendefinisikan koordinat Y min atau max
#define deltat .0009 // Menambahkan nilai t
int WindowWidth; // Lebar windows (dalam pixel) 
int WindowHeight; // Tinggi windows (dalam pixel) 

void Display(){
	glLineWidth(4.0); // Membuat lebar garis.
	float StartShape[12][2] = {
				{14,0},{15,0},{25,30},{20,30},{15,20},{10,30},
				{5,30},{13,13}
				}; 
	float EndShape[12][2] = {
				{5,0},{20,0},{20,10},{10,10},{10,35},{0,35},
				}; 

float IntermediateShape[12][2]; // Dua belas titik yang disediakan untuk menampung proses perubahan bentuk dari huruf W menjadi M.
	float VertexColors[12][3]={
			{1,0,0},{1,1,0},{1,0,1},{0,1,0},{0,1,1},{0,0,1},
			{1,0.5,0},{1,0,0.5},{0.5,1,0},{0.5,0,1},{1,0,0.5},{0,1,0.5}
			}; // Pemberian warna yang berbeda di tiap titik untuk memberikan efek gradasi warna.
	static float Tween = 0.0 - deltat; // Inisialisasi nilai Tween supaya point pertama tepat (benar).
	
// Perulangan dibuat untuk menampung nilai Tween terbaru. //
	if (Tween<1)
	{
		Tween += deltat;
	}
		
	for (int Vtx = 0; Vtx<12; Vtx++)
	{
		IntermediateShape[Vtx][0] = (1.0 - Tween)*StartShape[Vtx][0] 
		+ Tween*EndShape[Vtx][0];
		IntermediateShape[Vtx][1] = (1.0 - Tween)*StartShape[Vtx][1] 
		+ Tween*EndShape[Vtx][1];
	}

// Setting pointer array untuk titik Open GL dan warna. //
	glVertexPointer(2, GL_FLOAT, 0, IntermediateShape);
	glColorPointer(3, GL_FLOAT, 0, VertexColors);

	// Perulangan dibuat besar supaya lambat. //
	for (int i = 0; i < 1000000; i++);
	glClear(GL_COLOR_BUFFER_BIT); // Membersihkan buffer.
	glDrawArrays(GL_LINE_LOOP, 0, 12); // Membentuk garis loop.
	glutSwapBuffers(); // Menampilkan frame pada layar.
	glutPostRedisplay(); // Meminta untuk menampilkan frame selanjutnya pada layar.
}
void InitGL(){
	// Memposisikan tepat di tengah. //
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-HALFX, HALFX, -HALFY, HALFY);
	glMatrixMode(GL_MODELVIEW);	
	glClearColor(0, 0, 0, 0); //background hitam

	
// Mengatur array titik. //
	glEnableClientState(GL_VERTEX_ARRAY);

	// Mengatur array warna. //
	glEnableClientState(GL_COLOR_ARRAY);
	glShadeModel(GL_SMOOTH);
	glViewport(0, 0, WindowWidth, WindowHeight);
}

void Reshape(int w, int h) //untuk mengatur pemanggilan kembali fungsi glut reshape. Pada fungsi ini, user 
//dapat mengubah rasio dari window. W menunjukkan lebar window dan H menunjukkan tinggi window.
{
	glutReshapeWindow(w, (int)(w / RATIO));
	WindowWidth = w;
	WindowHeight = (int)(w / RATIO);
	InitGL();
}
int main(int argc, char **argv)
{
	// Inisialisasi glut. //
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); 

	// Inisialisasi lebar dan tinggi window menggunakan rasio. //
	WindowWidth = (int)(glutGet((GLenum)GLUT_SCREEN_WIDTH)*.4);
	WindowHeight = (int)(WindowWidth / RATIO);

	// Membuat window. //
	glutInitWindowSize(WindowWidth, WindowHeight); 
	glutInitWindowPosition((int)(glutGet((GLenum)GLUT_SCREEN_WIDTH)*.1), 
		(glutGet((GLenum)GLUT_SCREEN_HEIGHT) / 2) - (WindowHeight / 2)); 

	// Membuat tulisan pada window. //
	glutCreateWindow("672015206");

	glutDisplayFunc(Display); // Menampilkan frame.
	glutReshapeFunc(Reshape); // Mengubah kembali ukuran window.
	InitGL(); // Inisialisasi Open GL.
	glutMainLoop(); // Memulai pemrosesan event.
}



