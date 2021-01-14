/*---------------------------------------------------------*/
/* ----------------   PROYECTO FINAL --------------------------*/
/*-----------------    2020-2   ---------------------------*/
/*------------- Barrientos Veana Luis Mauricio ---------------*/
/*------------- Fierro Salma    ---------------*/
/*------------- Solano Tavera Francisco Javier    ---------------*/

				//#define STB_IMAGE_IMPLEMENTATION
#include <glew.h>
#include <glfw3.h>
#include <stb_image.h>
#include <Windows.h>
#include <MMSystem.h>
#include "camera.h"
#include "Model.h"
#include <iostream>
#include <alut.h>

#define NUM_BUFFERS 2
#define NUM_SOURCES 2
#define NUM_ENVRIONMENTS 1


// Config OpenAL
ALfloat listenerPos[] = { 0.0, 0.0, 0.0 };
ALfloat listenerVel[] = { 0.0, 0.0, 0.0 };
ALfloat listenerOri[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
// Source 0
ALfloat source0Pos[] = { 0.0, 0.0, 0.0 };
ALfloat source0Vel[] = { 0.0, 0.0, 0.0 };
// Source 1
ALfloat source1Pos[] = { 0.0, 0.0, 0.0 };
ALfloat source1Vel[] = { 0.0, 0.0, 0.0 };
// Buffers
ALuint buffers[NUM_BUFFERS];
ALuint sources[NUM_SOURCES];
ALuint enviornment[NUM_ENVRIONMENTS];
// variables para inicializar audios
ALsizei size, freq;
ALenum format;
ALvoid *data;
int ch;
ALboolean loop;


// Other Libs
#include "SOIL2/SOIL2.h"


void resize(GLFWwindow *window, int width, int height);
void my_input(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);


// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWwindow *window;
GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;

//Camera
Camera camera(glm::vec3(-21.0f, 3.0f, -5.0f));//20.0f en z
//Camera camera(glm::vec3(-38.0f, 7.0f, 12.0f));
//Camera camera(glm::vec3(0.0f, 5.0f, 25.0f));

double	lastX = 0.0f,
mul = 1.0f,
lastY = 0.0f,
rot = 0.0f;
bool firstMouse = true;

///VARIABLES ANIMACION DRON
bool animacion = false;
/*float movdron_x = -35.0f,
movdron_y = 0.5f,
movdron_z = 2.0f,
dronRotY = 180.0f,
//VARIABLES PARA LAMBORGHINI
float	movAuto_z = 0.0f,
movAuto_x = 0.0f,
orienta = 180.0f;
bool	animacion = false,
recorrido1 = true,
recorrido2 = false,
recorrido3 = false,
recorrido4 = false,
recorrido5 = false,
recorrido6 = false,
recorrido7 = false,
recorrido8 = false;*/

//Timing
double	deltaTime = 0.0f,
lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 2.0f, 2.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

void myData(void);
void display(Shader, Model, Model);
void getResolution(void);
void animate(void);
void LoadTextures(void);
unsigned int generateTextures(char*, bool);
int ESTADO = 0;
//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
j = 0.0f,
movZ = -5.0f,
rotY = 0.0f,
dx = -49.0f,
dy = -1.3f,
dz = -10.0f,
//rotY = 55.0f,
rotP = 0.0f;

float movLuzX = 0.0f;

//Texture
unsigned int	t_smile,
t_toalla,
t_unam,
t_white,
t_panda,
t_cubo,
t_caja,
t_caja_brillo,
t_pared_A,
t_pared_B,
t_pared_C,

lamp,
imagen;

//For model
//bool animacion = false;
bool ro = false;
bool uno = false;
bool dos = false;
bool ho = false;
bool cam1 = false;
bool cam2 = false;
bool E1 = false;
bool E2 = false;
bool E3 = false;
bool E4 = false;
bool E5 = false;

//Keyframes 
//Variables de dibujo
float	posX = 0.0f,
posY = 10.0f,
posZ = 0.0f,
giro = 0.0f,

posAX = 0.0f,
posAY = 4.0f,
posAZ = 0.0f,
giroA = 180.0f,

posBX = 3.0f,
posBY = -2.0f,
posBZ = 2.0f,
giroB = 0.0f,

posCX = 2.0f,
posCY = -2.93f,
posCZ = 1.0f,
giroMano1 = 0.0f,
giroPieIzq = 0.0f,
giroCuerpo = -90.0f,

wing = 0.0f;

float	incX = 0.0f,
incY = 0.0f,
incZ = 0.0f,

giroaveInc = 0.0f,
giroAvionInc = 0.0f,
giroMotoInc = 0.0f,
incAX = 0.0f,
incAY = 0.0f,
incAZ = 0.0f,
incBX = 0.0f,
incBY = 0.0f,
incBZ = 0.0f,
incCX = 0.0f,
incCY = 0.0f,
incCZ = 0.0f,
incMano1 = 0.0f,
incPie = 0.0f;

float movBrazoInc = 0.0f;

#define MAX_FRAMES 10
int i_max_steps = 30;
int i_curr_steps = 0;

typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float giro;
	float giroMano1;
	float giroPieIzq;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
FRAME KeyFrame2[MAX_FRAMES];
FRAME KeyFrame3[MAX_FRAMES];
FRAME KeyFrame4[MAX_FRAMES];

int FrameIndex = 6;			//Introducir datos
bool play = false;          //Indica cuando se inicia la animacion
int playIndex = 6;

int FrameIndex2 = 6;			//Introducir datos
bool play2 = false;          //Indica cuando se inicia la animacion
int playIndex2 = 6;

int FrameIndex3 = 6;			//Introducir datos
bool play3 = false;          //Indica cuando se inicia la animacion
int playIndex3 = 6;

int FrameIndex4 = 6;			//Introducir datos
bool play4 = false;          //Indica cuando se inicia la animacion
int playIndex4 = 6;


void planeFrame(void)
{
	KeyFrame2[0].posX = 0.0f;
	KeyFrame2[0].posY = 4.0f;
	KeyFrame2[0].posZ = 0.0f;
	KeyFrame2[0].giro = 180.0f;

	KeyFrame2[1].posX = 0.0f;
	KeyFrame2[1].posY = 4.0f;
	KeyFrame2[1].posZ = -8.0f;
	KeyFrame2[1].giro = 90.0f;

	KeyFrame2[2].posX = 2.0f;
	KeyFrame2[2].posY = 4.0f;
	KeyFrame2[2].posZ = 0.0f;
	KeyFrame2[2].giro = 0.0f;

	KeyFrame2[3].posX = -10.0f;
	KeyFrame2[3].posY = 2.0f;
	KeyFrame2[3].posZ = -13.0f;
	KeyFrame2[3].giro = 0.0f;

	KeyFrame2[4].posX = -20.0f;
	KeyFrame2[4].posY = 2.0f;
	KeyFrame2[4].posZ = 0.0f;
	KeyFrame2[4].giro = 0.0f;

	KeyFrame2[5].posX = -30.0f;
	KeyFrame2[5].posY = 2.0f;
	KeyFrame2[5].posZ = 0.0f;
	KeyFrame2[5].giro = 0.0f;

}

void resetElements2(void)
{
	posAX = KeyFrame2[0].posX;
	posAY = KeyFrame2[0].posY;
	posAZ = KeyFrame2[0].posZ;
	giroA = KeyFrame2[0].giro;
}

void interpolation2(void)
{
	incAX = (KeyFrame2[playIndex + 1].posX - KeyFrame2[playIndex].posX) / i_max_steps;
	incAY = (KeyFrame2[playIndex + 1].posY - KeyFrame2[playIndex].posY) / i_max_steps;
	incAZ = (KeyFrame2[playIndex + 1].posZ - KeyFrame2[playIndex].posZ) / i_max_steps;
	giroAvionInc = (KeyFrame2[playIndex + 1].giro - KeyFrame2[playIndex].giro) / i_max_steps;
}

void personaFrame(void)
{
	KeyFrame4[0].posX = -1.0f;
	KeyFrame4[0].posY = -2.93f;
	KeyFrame4[0].posZ = 1.0f;
	KeyFrame4[0].giro = -0.0f;

	KeyFrame4[1].posX = -5.50f;
	KeyFrame4[1].posY = -2.93f;
	KeyFrame4[1].posZ = 1.0f;
	KeyFrame4[1].giro = -0.0f;
	KeyFrame4[1].giroMano1 = 60.0f;
	KeyFrame4[1].giroPieIzq = 60.0f;

	KeyFrame4[2].posX = -7.50f;
	KeyFrame4[2].posY = -2.93f;
	KeyFrame4[2].posZ = 1.0f;
	KeyFrame4[2].giro = -0.0f;
	KeyFrame4[1].giroMano1 = -60.0f;
	KeyFrame4[1].giroPieIzq = -60.0f;

	KeyFrame4[3].posX = -10.50f;
	KeyFrame4[3].posY = -2.93f;
	KeyFrame4[3].posZ = 1.0f;
	KeyFrame4[3].giro = -0.0f;
	KeyFrame4[1].giroMano1 = 60.0f;
	KeyFrame4[1].giroPieIzq = 60.0f;

	KeyFrame4[4].posX = -17.50f;
	KeyFrame4[4].posY = -2.93f;
	KeyFrame4[4].posZ = 1.0f;
	KeyFrame4[4].giro = -0.0f;
	KeyFrame4[1].giroMano1 = -60.0f;
	KeyFrame4[1].giroPieIzq = -60.0f;

	KeyFrame4[5].posX = -27.0f;
	KeyFrame4[5].posY = -2.93f;
	KeyFrame4[5].posZ = 1.0f;
	KeyFrame4[5].giro = -0.0f;
	KeyFrame4[1].giroMano1 = 60.0f;
	KeyFrame4[1].giroPieIzq = 60.0f;

}

void resetElements4(void)
{
	posCX = KeyFrame4[0].posX;
	posCY = KeyFrame4[0].posY;
	posCZ = KeyFrame4[0].posZ;
	giroCuerpo = KeyFrame4[0].giro;
	giroMano1 = KeyFrame4[0].giroMano1;
	giroPieIzq = KeyFrame4[0].giroPieIzq;
}

void interpolation4(void)
{
	incCX = (KeyFrame4[playIndex + 1].posX - KeyFrame4[playIndex].posX) / i_max_steps;
	incCY = (KeyFrame4[playIndex + 1].posY - KeyFrame4[playIndex].posY) / i_max_steps;
	incCZ = (KeyFrame4[playIndex + 1].posZ - KeyFrame4[playIndex].posZ) / i_max_steps;
	giroCuerpo = (KeyFrame4[playIndex + 1].giro - KeyFrame4[playIndex].giro) / i_max_steps;
	incMano1 = (KeyFrame4[playIndex + 1].giroMano1 - KeyFrame4[playIndex].giroMano1) / i_max_steps;
	incPie = (KeyFrame4[playIndex + 1].giroPieIzq - KeyFrame4[playIndex].giroPieIzq) / i_max_steps;

}



void motoFrame(void)
{
	KeyFrame3[0].posX = 1.0f;
	KeyFrame3[0].posY = -2.0f;
	KeyFrame3[0].posZ = 2.0f;
	KeyFrame3[0].giro = 0.0f;

	KeyFrame3[1].posX = 30.50f;
	KeyFrame3[1].posY = 0.0f;
	KeyFrame3[1].posZ = 0.0f;
	KeyFrame3[1].giro = 0.0f;

	KeyFrame3[2].posX = 7.50f;
	KeyFrame3[2].posY = 0.0f;
	KeyFrame3[2].posZ = 0.0f;
	KeyFrame3[2].giro = 0.0f;

	KeyFrame3[3].posX = 7.50f;
	KeyFrame3[3].posY = 0.0f;
	KeyFrame3[3].posZ = 0.0f;
	KeyFrame3[3].giro = 50.0f;

	KeyFrame3[4].posX = 7.50f;
	KeyFrame3[4].posY = 0.0f;
	KeyFrame3[4].posZ = 0.0f;
	KeyFrame3[4].giro = 0.0f;

	KeyFrame3[5].posX = -5.0f;
	KeyFrame3[5].posY = 0.0f;
	KeyFrame3[5].posZ = 0.0f;
	KeyFrame3[5].giro = 0.0f;

}


void resetElements3(void)
{
	posBX = KeyFrame3[0].posX;
	posBY = KeyFrame3[0].posY;
	posBZ = KeyFrame3[0].posZ;
	giroB = KeyFrame3[0].giro;
}

void interpolation3(void)
{
	incBX = (KeyFrame3[playIndex + 1].posX - KeyFrame3[playIndex].posX) / i_max_steps;
	incBY = (KeyFrame3[playIndex + 1].posY - KeyFrame3[playIndex].posY) / i_max_steps;
	incBZ = (KeyFrame3[playIndex + 1].posZ - KeyFrame3[playIndex].posZ) / i_max_steps;
	giroMotoInc = (KeyFrame3[playIndex + 1].giro - KeyFrame3[playIndex].giro) / i_max_steps;
}
void aveFrame(void) {
	KeyFrame[0].posX = -40.0f;
	KeyFrame[0].posY = 10.0f;
	KeyFrame[0].posZ = 0.0f;
	KeyFrame[0].giro = -20.0f;

	KeyFrame[1].posX = -55.0f;
	KeyFrame[1].posY = 10.0f;
	KeyFrame[1].posZ = 0.0f;
	KeyFrame[1].giro = 10.0f;

	KeyFrame[2].posX = -40.0f;
	KeyFrame[2].posY = 10.0f;
	KeyFrame[2].posZ = 15.0f;
	KeyFrame[2].giro = -20.0f;

	KeyFrame[3].posX = -55.0f;
	KeyFrame[3].posY = 10.0f;
	KeyFrame[3].posZ = 0.0f;
	KeyFrame[3].giro = 10.0f;

	KeyFrame[4].posX = -40.0f;
	KeyFrame[4].posY = 10.0f;
	KeyFrame[4].posZ = 0.0f;
	KeyFrame[4].giro = -20.0f;

	KeyFrame[5].posX = -55.0f;
	KeyFrame[5].posY = 10.0f;
	KeyFrame[5].posZ = 0.0f;
	KeyFrame[5].giro = 10.0f;

}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;
	giro = KeyFrame[0].giro;
}

void interpolation(void)
{
	incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;
	giroaveInc = (KeyFrame[playIndex + 1].giro - KeyFrame[playIndex].giro) / i_max_steps;
}

///////////////////////////////

unsigned int generateTextures(const char* filename, bool alfa)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

	unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		if (alfa)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		return textureID;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return 100;
	}

	stbi_image_free(data);
}

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;

	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

}

void LoadTextures()
{
	t_pared_A = generateTextures("Texturas/Textura_Pared.png", 1);
	t_pared_B = generateTextures("Texturas/Textura_pared_B.png", 1);
	t_pared_C = generateTextures("Texturas/Cortina.png", 1);
	imagen = generateTextures("Texturas/w.jpg", 0);
	lamp = generateTextures("Texturas/lamp.png", 1);

}

void myData()
{
	float vertices[] = {

		 1.0f,  1.0f, 0.0f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f, //0
		 1.0f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f, //1
		 0.0f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f, //2
		 0.0f,  1.0f, 0.0f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f, //3


	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

}

int mov_dron = 0;
float velocidad = 0;
void animate(void)
{
//ANIMACION DRON
	/*if (animacion) {
		if (mov_dron == 0)
		{
			//avionRotY = 0.0f;
			movdron_y += velocidad;
			if (movdron_y >= 35.0f) {
				mov_dron = 1;
			}
		}

		if (mov_dron == 1)
		{
			movdron_z += velocidad;
			//avionRotY = 90.0f;
			if (movdron_z >= 35.0f)
				mov_dron = 2;
		}

		if (mov_dron == 2)
		{
			movdron_x += velocidad;
			dronRotY = -90.0f;
			if (movdron_x >= 40.0f)
				mov_dron = 3;
		}

		if (mov_dron == 3)
		{
			movdron_z -= velocidad;
			dronRotY = 360.0f;
			if (movdron_z <= -60.0f)
				mov_dron = 4;
		}

		if (mov_dron == 4)
		{
			movdron_x -= velocidad;
			dronRotY = 90.0f;
			if (movdron_x <= -35.0f)
				mov_dron = 5;
		}

		if (mov_dron == 5)
		{
			dronRotY = 180.0f;
			//if (movdron_z <= 30.0f)
			mov_dron = 1;
		}
	}*/

	//ANIMACION LAMBO


	/////////////KEYFRAMES////////////////////////////////////////////////////
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("Termina animacion\n");
				playIndex = 0;

				resetElements();
				resetElements2();
				resetElements3();
				resetElements4();
				//play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter				 
				interpolation();  //Interpolation
				interpolation2();
				interpolation3();
				interpolation4();
			}
		}
		else {

			//Draw animation
			posX += incX;
			posY += incY;
			posZ += incZ;
			giro += giroaveInc;

			posAX += incAX;
			posAY += incAY;
			posAZ += incAZ;
			giroA += giroAvionInc;

			posBX += incBX;
			posBY += incBY;
			posBZ += incBZ;
			giroB += giroMotoInc;

			posCX += incCX;
			posCY += incCY;
			posCZ += incCZ;
			giroCuerpo += giroCuerpo;
			giroMano1 += incMano1;
			giroPieIzq += incPie;



			i_curr_steps++;
		}
	}



	//2/////////////////RECORRIDO 1////////////////
	if (ro) {
		E1 = true;
		if (E1)
		{
			mul += .5;
			camera.Cambio(glm::vec3(7.0f - mul, 8.0f, 2.0f), 180);
			camera.ProcessMouseMovement(0, 0);
			if (mul >= 50.0)
			{
				E1 = false;
				E2 = true;

			}
		}
		if (E2)
		{
			mul += .5;
			camera.Cambio(glm::vec3(-43.0f, 8.0f, 2.0f), 180 - mul);
			camera.ProcessMouseMovement(0, 0);
			if (mul >= 180.0)
			{
				E2 = false;
				E3 = true;
				mul = 0;
			}

		}
		if (E3)
		{
			mul += .005;
			camera.Cambio(glm::vec3(-43.0f, 8.0f - mul, 2.0f), 0);
			camera.ProcessMouseMovement(0, 0);
			if (mul >= 8.0)
			{
				E3 = false;
				E4 = true;
			}
		}
		if (E4)
		{
			mul += .0005;
			camera.Cambio(glm::vec3(-43.0f + mul, 0.0f, 2.0f), 0);
			camera.ProcessMouseMovement(0, 0);
			if (mul >= 43)
			{
				E4 = false;
				ro = false;
			}

		}
	}
	//////////////////////////////////////////////////

	//3/////////////////RECORRIDO////////////////
	if (ho) {
		E1 = true;
		if (E1)
		{
			mul += 0.5;
			camera.Cambio(glm::vec3(0.0f - mul, 0.0f, 2.0f), 0);
			camera.ProcessMouseMovement(0, 0);
			if (mul >= 40)
			{
				ho = false;
			}

		}
	}
	//////////////////////////////////////////////////


	///////////////////////////////////////////////////
	/////////////////////5////////////////////////////


}
bool flag = false;

void display(Shader shader, Shader text, Model Pista, /*Model piso,*/ Model CrucePista, Model Moto, Model pci, Model edifprueba, Model edif10,
	/*Model estadio,*/ Model cielo, Model avion, Model akira, Model ave, Model alaDer, Model alaIzq, Model Cuerpo, Model BraDer, Model BraIzq, Model PieDer, Model PieIzq,
	Model casa, Model comedor,  Model alberca, Model sala, Model cocina, Model Salma, Model baño1, Model baño2, Model Javi, Model Mau, Model jardin, Model cochera) /*Model dron, Model lambo,
	Model llantas)*/
{

	//text.use();
	shader.use();
	float i = 0;


	//iluminacion SHADER MULTI LUCES SHADE_LIGHTS

	shader.setVec3("viewPos", camera.Position);

	shader.setVec3("dirLight.direction", camera.Front);
	shader.setVec3("dirLight.ambient", glm::vec3(0.6f, 0.6f, 0.6f));
	shader.setVec3("dirLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setVec3("dirLight.specular", glm::vec3(0.6f, 0.6f, 0.6f));


	shader.setFloat("material_shininess", 32.0f);



	// create transformations and Projection
	glm::mat4 temp01 = glm::mat4(1.0f);
	glm::mat4 temp02 = glm::mat4(1.0f);
	glm::mat4 temp03 = glm::mat4(1.0f);
	glm::mat4 tmp = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection
	glm::mat4 temporal = glm::mat4(1.0f);//VARIABLE TEMPORAL PARA UBICAR CENTRO DE NUESTRO ESCENARIO

	//Use "projection" to include Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix();
	//view = glm::rotate(view, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));


	// pass them to the shaders
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	shader.setMat4("projection", projection);

	///////////////////////////////////MODELADO DEL SALON////////////////////////////////////////////////////////////////////////////

	if (cam1) {
		shader.setVec3("dirLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
		shader.setVec3("dirLight.diffuse", glm::vec3(0.6f, 0.6f, 0.6f));

		shader.setVec3("pointLight[0].position", glm::vec3(-30.0f, 8.1f, 0.0f));
		shader.setVec3("pointLight[0].ambient", glm::vec3(0.07f, 0.005f, 0.0f));
		shader.setVec3("pointLight[0].diffuse", glm::vec3(0.07f, 0.005f, 0.0f));
		shader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setFloat("pointLight[0].constant", 0.2f);
		shader.setFloat("pointLight[0].linear", 0.0004f);
		shader.setFloat("pointLight[0].quadratic", 0.004f);

		shader.setVec3("pointLight[1].position", glm::vec3(-8.0f, 8.1f, 0.0f));
		shader.setVec3("pointLight[1].ambient", glm::vec3(0.07f, 0.005f, 0.0f));
		shader.setVec3("pointLight[1].diffuse", glm::vec3(0.07f, 0.005f, 0.0f));
		shader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setFloat("pointLight[1].constant", 0.2f);
		shader.setFloat("pointLight[1].linear", 0.0004f);
		shader.setFloat("pointLight[1].quadratic", 0.004f);


	}
	else {
		shader.setVec3("pointLight[0].position", glm::vec3(-30.0f, 8.1f, 0.0f));
		shader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.00f, 0.00f));
		shader.setVec3("pointLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setFloat("pointLight[0].constant", 0.5f);
		shader.setFloat("pointLight[0].linear", 0.0004f);
		shader.setFloat("pointLight[0].quadratic", 0.004f);

		shader.setVec3("pointLight[1].position", glm::vec3(8.0f, 8.1f, 0.0f));
		shader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.f, 0.0f));
		shader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setFloat("pointLight[1].constant", 0.5f);
		shader.setFloat("pointLight[1].linear", 0.0004f);
		shader.setFloat("pointLight[1].quadratic", 0.004f);

	}

	/*model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 4.0f, 1.25f));//-1.8f
	model = glm::scale(model, glm::vec3(0.007f, 0.001f, 0.0061f));
	shader.setMat4("model", model);
	piso.Draw(shader);*/

	model = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(40.0f, -47.5f, 0.0f));
	model = glm::scale(model, glm::vec3(1.4f, 0.9f, 0.7f));
	shader.setMat4("model", model);
	cielo.Draw(shader);


	glm::mat4 origin = glm::mat4(1.0f);


	glBindVertexArray(VAO);


	//////////////////////////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////MODELADO DE LOS ELEMENTOS //////////////////////////////


	temporal = model = glm::translate(glm::mat4(1.0f), glm::vec3(-25.0f, -2.0f, 5.0f));//ORIGEN DEL ESCENARIO
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));//GIRO EN X PARA PONER EL PISO ABAJO 
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
	shader.setMat4("model", model);
	casa.Draw(shader); // CASA

	model = glm::translate(temporal, glm::vec3(42.0f, 0.5f, 0.0f));
	model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
	shader.setMat4("model", model);
	alberca.Draw(shader); // ALBERCA
	
	model = glm::translate(temporal, glm::vec3(-13.0f, 0.0f, -8.0f));
	model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	sala.Draw(shader); // SALA 

	model = glm::translate(temporal, glm::vec3(13.0f, 0.0f, 2.5f));
	//model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.10f, 0.10f, 0.10f));
	shader.setMat4("model", model);
	Salma.Draw(shader); // RECAMARA SALMA

	model = glm::translate(temporal, glm::vec3(0.0f, 0.0f, -15.0f));
	model = glm::rotate(model, glm::radians(-360.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	cocina.Draw(shader); // COCINA

	model = glm::translate(temporal, glm::vec3(10.0f, 0.0f, -10.0f));
	//model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	comedor.Draw(shader); // COMEDOR

	model = glm::translate(temporal, glm::vec3(0.0f, 0.0f, 15.5f));
	model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
	shader.setMat4("model", model);
	baño1.Draw(shader); // BAÑO1

	model = glm::translate(temporal, glm::vec3(-13.0f, 0.0f, 5.0f));
	//model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	baño2.Draw(shader); // BAÑO2

	model = glm::translate(temporal, glm::vec3(29.0f, 0.0f, 5.0f));
	model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	Javi.Draw(shader); // RECAMARA JAVI

	model = glm::translate(temporal, glm::vec3(-13.0f, 0.0f, 12.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	Mau.Draw(shader); // RECAMARA MAU


	model = glm::translate(temporal, glm::vec3(40.0f, 0.5f, 15.0f));
	//model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	jardin.Draw(shader); // JARDIN

	model = glm::translate(temporal, glm::vec3(-40.8f, 0.5f, -4.5f));
	//model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
	shader.setMat4("model", model);
	cochera.Draw(shader); // COCHERA

	/*model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
	//model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(temporal, glm::vec3(movdron_x, movdron_y, movdron_z));
	model = glm::rotate(model, glm::radians(dronRotY), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	dron.Draw(shader); // DRON*/

	//Carro
	/*model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(15.0f + movAuto_x, -1.0f, movAuto_z));
	tmp = model = glm::rotate(model, glm::radians(orienta), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	shader.setMat4("model", model);
	lambo.Draw(shader);

	model = glm::translate(tmp, glm::vec3(0.85f, 0.25f, 1.29f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	shader.setMat4("model", model);
	llantas.Draw(shader);	//Izq delantera

	model = glm::translate(tmp, glm::vec3(-0.85f, 0.25f, 1.29f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	llantas.Draw(shader);	//Der delantera

	model = glm::translate(tmp, glm::vec3(-0.85f, 0.25f, -1.45f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	llantas.Draw(shader);	//Der trasera

	model = glm::translate(tmp, glm::vec3(0.85f, 0.25f, -1.45f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	shader.setMat4("model", model);
	llantas.Draw(shader);	//Izq trase
	
	/*model = glm::rotate(glm::mat4(1.0f), glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(10.0f, -2.0f, 17.0f));//Cruce entre los edificios
	model = glm::scale(model, glm::vec3(0.025f, 0.025f, 0.025f));
	shader.setMat4("model", model);
	estadio.Draw(shader); // Cruce 1*/


	if (cam2) {


		shader.setVec3("dirLight.ambient", glm::vec3(0.6f, 0.6f, 0.6f));
		shader.setVec3("dirLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setVec3("dirLight.specular", glm::vec3(0.6f, 0.6f, 0.6f));


	}
	else {

		shader.setVec3("pointLight[2].position", glm::vec3(-40.0f, 1.0f, 1.25f));
		shader.setVec3("pointLight[2].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setVec3("pointLight[2].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setVec3("pointLight[2].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setFloat("pointLight[2].constant", 1.0f);
		shader.setFloat("pointLight[2].linear", 0.0004f);
		shader.setFloat("pointLight[2].quadratic", 0.004f);

		shader.setVec3("pointLight[3].position", glm::vec3(-52.0f, -1.3f, 5.0f));
		shader.setVec3("pointLight[3].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setVec3("pointLight[3].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setVec3("pointLight[3].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setFloat("pointLight[3].constant", 0.2f);
		shader.setFloat("pointLight[3].linear", 0.004f);
		shader.setFloat("pointLight[3].quadratic", 0.04f);

		shader.setVec3("pointLight[4].position", glm::vec3(-44.0f, -1.3f, 5.0f));
		shader.setVec3("pointLight[4].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setVec3("pointLight[4].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setVec3("pointLight[4].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setFloat("pointLight[4].constant", 0.2f);
		shader.setFloat("pointLight[4].linear", 0.004f);
		shader.setFloat("pointLight[4].quadratic", 0.04f);

		shader.setVec3("pointLight[5].position", glm::vec3(-38.0f, 7.0f, 12.0f));
		shader.setVec3("pointLight[5].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setVec3("pointLight[5].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setVec3("pointLight[5].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setFloat("pointLight[5].constant", 0.2f);
		shader.setFloat("pointLight[5].linear", 0.004f);
		shader.setFloat("pointLight[5].quadratic", 0.04f);


	}

	//Avion
	model = glm::translate(glm::mat4(1.0f), glm::vec3(posAX, posAY, posAZ));
	model = glm::scale(model, glm::vec3(0.10f, 0.10f, 0.10f));
	tmp = model = glm::rotate(model, glm::radians(giroA), glm::vec3(0.0f, 1.0f, 0.0));
	shader.setMat4("model", model);
	avion.Draw(shader);

	//Moto
	model = glm::translate(glm::mat4(1.0f), glm::vec3(posBX, posBY, posBZ));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
	temp02 = model = glm::scale(model, glm::vec3(0.10f, 0.10f, 0.10f));
	//model = glm::rotate(model, glm::radians(-rotRodIzq), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	akira.Draw(shader);

	//Ave
	model = glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, posZ));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
	temp01 = model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	//model = glm::rotate(model, glm::radians(-rotRodIzq), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	ave.Draw(shader);

	//Ala Derecha
	model = glm::translate(temp01, glm::vec3(0, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(giro), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	alaDer.Draw(shader);

	//Ala Izquierda
	model = glm::translate(temp01, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-giro), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	alaIzq.Draw(shader);


	//Monito

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(posCX, posCY, posCZ));
	temp03 = model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0));
	temp03 = model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
	shader.setMat4("model", model);
	Cuerpo.Draw(shader);
	//Pierna Der
	model = glm::translate(temp03, glm::vec3(0.00f, 0.0f, -0.01f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::rotate(model, glm::radians(-giroPieIzq), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	PieDer.Draw(shader);

	model = glm::translate(temp03, glm::vec3(0.00f, 0.0f, -0.01f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::rotate(model, glm::radians(giroPieIzq), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	PieIzq.Draw(shader);

	//Brazo derecho
	model = glm::translate(temp03, glm::vec3(-0.050f, -0.05f, 0.0f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::rotate(model, glm::radians(giroMano1), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	BraDer.Draw(shader);

	model = glm::translate(temp03, glm::vec3(0.01f, -0.05f, 0.0f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::rotate(model, glm::radians(-giroMano1), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	BraIzq.Draw(shader);

	



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	glBindVertexArray(0);

	// Libreria de audio
	// openal sound data  Posicion del sonido
	source0Pos[0] = -15;
	source0Pos[1] = 10;
	source0Pos[2] = -5;
	alSourcefv(sources[0], AL_POSITION, source0Pos);
	source1Pos[0] = -15;
	source1Pos[1] = -10;
	source1Pos[2] = -5;
	alSourcefv(sources[1], AL_POSITION, source1Pos);
	// Position listener
	listenerPos[0] = camera.Position.x;
	listenerPos[1] = camera.Position.y;
	listenerPos[2] = camera.Position.z;
	alListenerfv(AL_POSITION, listenerPos);
	// Orientation listener
	listenerOri[0] = camera.Front.x;
	listenerOri[1] = camera.Front.y;
	listenerOri[2] = camera.Front.z;
	listenerOri[3] = camera.Up.x;
	listenerOri[4] = camera.Up.y;
	listenerOri[5] = camera.Up.z;
	alListenerfv(AL_ORIENTATION, listenerOri);

}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "PROYECTO CG2021-1 * Barrientos Veana Luis Mauricio *  Ramirez Fierro Salma Arelly * Solano Tavera Francisco Javier *", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);


	//To Enable capture of our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glewInit();


	// OpenAL init
	alutInit(0, nullptr);
	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);
	alGetError(); // Limpiamos los errores previos de OpenAL
	if (alGetError() != AL_NO_ERROR) {
		printf("Error al crear los buffers");
		exit(1);
	}
	else
		printf("Se crearon los buffers");

	alGenBuffers(NUM_BUFFERS, buffers);
	buffers[0] = alutCreateBufferFromFile("Noch.wav");
	buffers[1] = alutCreateBufferFromFile("Dia.wav");

	int errorAlut = alutGetError();

	if (errorAlut != ALUT_ERROR_NO_ERROR) {
		printf("Error al crear los buffers %d", errorAlut);
		exit(2);
	}
	else
		printf("Se crearon los buffers");

	glGetError();
	alGenSources(NUM_SOURCES, sources);

	if (alutGetError() != AL_NO_ERROR) {
		printf("Error al crear las fuentes de sonidos");
		exit(2);
	}
	else
		printf("Se crearon las fuentes de sonido");

	//Volumendo y distancia
	alSourcef(sources[0], AL_PITCH, 1.0f);
	alSourcef(sources[0], AL_GAIN, 4.0f);
	alSourcefv(sources[0], AL_VELOCITY, source0Vel);
	alSourcefv(sources[0], AL_POSITION, source0Pos);
	alSourcei(sources[0], AL_BUFFER, buffers[0]);
	alSourcei(sources[0], AL_LOOPING, AL_TRUE);
	alSourcei(sources[0], AL_MAX_DISTANCE, 2000);

	alSourcef(sources[1], AL_PITCH, 1.0f);
	alSourcef(sources[1], AL_GAIN, 4.0f);
	alSourcefv(sources[1], AL_VELOCITY, source0Vel);
	alSourcefv(sources[1], AL_POSITION, source1Pos);
	alSourcei(sources[1], AL_BUFFER, buffers[1]);
	alSourcei(sources[1], AL_LOOPING, AL_TRUE);
	alSourcei(sources[1], AL_MAX_DISTANCE, 2000);


	//Mis funciones
	//Datos a utilizar
	LoadTextures();
	myData();
	glEnable(GL_DEPTH_TEST);

	//Shader modelShader("Shaders/modelLoading.vs", "Shaders/modelLoading.fs");
	Shader modelShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");
	//Shader modelShader("shaders/shader_Lights.vs", "shaders/shader_texture_light_dir.fs");
	//Shader modelShader("shaders/shader_Lights.vs", "shaders/shader_texture_light_pos.fs");
	//Shader modelShader("shaders/shader_texture_light_spot.vs", "shaders/shader_texture_light_spot.fs"); //Spotlight
	Shader text("shaders/shader_texture_color.vs", "shaders/shader_texture_color.fs");
	// Load models
	Model Pista = ((char *)"Models/AutopistaFasil/Autopista1.obj");
	//Model pisoModel = ((char *)"Models/piso/piso.obj");
	Model CrucePista = ((char *)"Models/CruceAutopista/Cruce de autopostas.obj");
	Model modelMoto = ((char *)"Models/ultimis/ciudad.obj");
	Model pciModel = ((char *)"Models/PC1/pci.obj");
	Model edifprueba = ((char *)"Models/edifprueba/edifp.obj");
	
	//Model estadio = ((char *)"Models/estadio/estadio.obj");
	Model edif10 = ((char *)"Models/edif10/edif10.obj");
	Model cieloModel = ((char *)"Models/cielo/cielo.obj");
	Model avionModel = ((char *)"Models/avion/avion.obj");
	Model akiraModel = ((char *)"Models/akira/akira.obj");
	Model aveModel = ((char *)"Models/ave/aveCuerpo.obj");
	Model alaDerModel = ((char *)"Models/ave/AlaDer.obj");
	Model alaIzqModel = ((char *)"Models/ave/AlaIzq.obj");
	Model Cuerpo = ((char *)"Models/Mono/Cuerpo.obj");
	Model BrazoDer = ((char *)"Models/Mono/BrazoDer.obj");
	Model BrazoIzq = ((char *)"Models/Mono/BrazoIzq.obj");
	Model PieDer = ((char *)"Models/Mono/PieDer.obj");
	Model PieIzq = ((char *)"Models/Mono/PieIzq.obj");
	Model casa = ((char *)"Models/CASA3/CASA.obj");
	Model comedor = ((char *)"Models/COMEDOR/COMEDOR.obj");
	Model alberca = ((char *)"Models/ALBERCA/alberca.obj");
	Model sala = ((char *)"Models/SALA/sala.obj");
	Model Salma = ((char *)"Models/RECAMARASALMA/RecamaraSalma.obj");
	Model cocina = ((char *)"Models/COCINA/Cocina.obj");
	Model baño1 = ((char *)"Models/BAÑO1/BAÑO1.obj");
	Model baño2 = ((char *)"Models/BAÑO2/BAÑO2.obj");
	Model Javi = ((char *)"Models/RECAMARA JAVI/Javi.obj");
	Model Mau = ((char *)"Models/RECAMARA MAU/mau.obj");
	Model jardin = ((char *)"Models/JARDIN/Jardin.obj");
	Model cochera = ((char *)"Models/COCHERA/COCHERA.obj");
	Model dron = ((char *)"Models/DRON/Dron.obj");
	Model lambo = ((char *)"Models/Lambo/Lamborghini_Aventador.obj");
	Model llantas = ((char *)"Models/Lambo/Wheel.obj");

	//Inicialización de KeyFrames

	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].giro = 0;

		KeyFrame2[i].posX = 0;
		KeyFrame2[i].posY = 0;
		KeyFrame2[i].posZ = 0;
		KeyFrame2[i].giro = 0;

		KeyFrame3[i].posX = 0;
		KeyFrame3[i].posY = 0;
		KeyFrame3[i].posZ = 0;
		KeyFrame3[i].giro = 0;
	}


	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	// render loop
	// While the windows is not closed
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// input
		// -----
		my_input(window);
		animate();

		// render
		// Backgound color
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//display(modelShader, ourModel, llantasModel);
		display(modelShader, text, Pista, /*pisoModel*/ CrucePista, modelMoto, pciModel, edifprueba, edif10,
			cieloModel, avionModel, akiraModel, aveModel, alaDerModel, alaIzqModel, Cuerpo, BrazoDer, BrazoIzq, PieDer, PieIzq,
			casa, comedor, alberca, sala, cocina, Salma, baño1, baño2, Javi, Mau, jardin, cochera);// dron llantas

		std::cout << "Frame:" << (1 / deltaTime) << std::endl;

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		animacion = true;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
		animacion = true;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		cam1 = false;
		cam2 = false;
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		cam1 = true;
		cam2 = true;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		animacion = !animacion;
	
	}

	////////////////////CAMARAS/////////////////////
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		mul = 0.0f;
		rotP = 0.0f;
		cam1 = true;
		cam2 = false;
		ro = true;
		alSourcePlay(sources[0]);
		alSourceStop(sources[1]);
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		camera.Cambio(glm::vec3(7.0f, 8.0f, 0.0f), 180);
		cam1 = true;
		cam2 = false;
		camera.ProcessMouseMovement(0.0f, 0.0f);
		alSourcePlay(sources[0]);
		alSourceStop(sources[1]);
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		camera.Cambio(glm::vec3(-43.0f, 0.0f, 2.0f), 0);
		cam1 = true;
		cam2 = false;
		camera.ProcessMouseMovement(0.0f, 0.0f);
		alSourcePlay(sources[0]);
		alSourceStop(sources[1]);
	}
	///////////////////////////////////////////////////////
	////////////////////CAMARA PRINCIPAL//////////////////
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
		cam1 = false;
		cam2 = false;
		ro = false;
		ho = false;
		camera.Cambio(glm::vec3(-21.0f, 3.0f, 20.0f), -90);//20.0f en z
		camera.ProcessMouseMovement(0.0f, 0.0f);
		alSourceStop(sources[1]);
		alSourceStop(sources[0]);

	}
	/////////////////////////////////////////////////////
	//////////////////CAMARAS /////////////////////
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
		camera.Cambio(glm::vec3(7.0f, 8.0f, 0.0f), 180);
		camera.ProcessMouseMovement(0.0f, 0.0f);
		cam1 = false;
		cam2 = true;;
		alSourcePlay(sources[1]);
		alSourceStop(sources[0]);

	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
		mul = 0.0f;
		cam1 = false;
		cam2 = true;
		ho = true;
		alSourcePlay(sources[1]);
		alSourceStop(sources[0]);
	}
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
		camera.Cambio(glm::vec3(-43.0f, 0.0f, 2.0f), 0);
		cam1 = false;
		cam2 = true;
		camera.ProcessMouseMovement(0.0f, 0.0f);
		alSourcePlay(sources[1]);
		alSourceStop(sources[0]);
	}
	//////////////////////////////////////////////////////
	//To play KeyFrame animation 
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		if (FrameIndex < MAX_FRAMES) {
			aveFrame();
			planeFrame();
			motoFrame();
			personaFrame();

		}
		if (play == false && (FrameIndex > 1))
		{
			resetElements();
			resetElements2();
			resetElements3();
			resetElements4();
			//First Interpolation				
			interpolation();
			interpolation2();
			interpolation3();
			interpolation4();
			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{


	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top


	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}