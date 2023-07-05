#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include "Shader.h"
#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "stb_image.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#define SCR_WIDTH 1920
#define SCR_HEIGHT 1080
#define MAPSIZE_X 10
#define MAPSIZE_Y 10
#define MAPSIZE_Z 10
#define GLSL_VERSION "#version 400"




float vertColTexBuffer[] =
{
	/*Top Position* /		/* Color */			/* TexCoords */
	-0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
	 0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
	/* Bottom Position */
	-0.5f,-0.5f,-0.5f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
	 0.5f,-0.5f,-0.5f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
	 0.5f, 0.5f,-0.5f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
	 0.5f, 0.5f,-0.5f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
	-0.5f, 0.5f,-0.5f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
	/* Left Position */
	-0.5f,-0.5f,-0.5f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
	-0.5f, 0.5f,-0.5f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
	/* Right Position */
	 0.5f,-0.5f,-0.5f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
	 0.5f, 0.5f,-0.5f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
	 0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
	 0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f,
	 0.5f,-0.5f,-0.5f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
	 /* Back Position */
	 -0.5f, 0.5f,-0.5f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
	  0.5f, 0.5f,-0.5f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
	  0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
	  0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
	 -0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f,
	 -0.5f, 0.5f,-0.5f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
	 /* Front Position */
	 -0.5f,-0.5f,-0.5f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
	  0.5f,-0.5f,-0.5f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
	  0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
	  0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
	 -0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f,
	 -0.5f,-0.5f,-0.5f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,

};

int main();

/* Functions */
void framebuffer_size_callback(GLFWwindow* window, int width, int height); // Protype
void userInput(GLFWwindow* window); // protype
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos); // Protype
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset); // Protype
unsigned int load_texture(const char* texture_path);
void setTransformMatrix();
void SetGUI();
void ConnectingShaderParameters();

/* Matrices */
glm::mat4 model;
glm::mat4 projection;
glm::mat4 view;

glm::mat4 t;
glm::mat4 r;
glm::mat4 s;

unsigned int VBO, VAO;


// Frames
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = float(SCR_WIDTH) / 2.0f;
float lastY = float(SCR_HEIGHT) / 2.0f;
bool isFirstMouse = true;
Shader myShader;



static float scale_value[3] = { 1.0f ,1.0f , 1.0f };
static float color_value[3] = { 1.0f,1.0f,1.0f };
static bool isTexture = false;
static float alpha = 0.2f;
static bool isColor = false;



int main()
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	/* Create a window */
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL 4.0", NULL, NULL);

	// Check window
	if (!window)
	{
		std::cout << "Failed to Create a window\n";
		glfwTerminate();
	}

	/* The most important part */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_position);
	glfwSetScrollCallback(window, mouse_scroll_position);
	//glfwSetInputMode(window, GLFW_CURSOR,GLFW_CURSOR_DISABLED);

	// check Glew 
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize Glew\n";
		glfwTerminate();
	}

	/* Options */
	glEnable(GL_DEPTH_TEST);

	/* ImGui */
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup the Platform
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(GLSL_VERSION);

	// Setup style
	ImGui::StyleColorsDark();


	/* Buffers */
	

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertColTexBuffer), &vertColTexBuffer, GL_STATIC_DRAW);

	/* Position Attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* Color Attribute*/
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* Texture Attribute */
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	/* Texture */
	stbi_set_flip_vertically_on_load(true);
	unsigned int main_Texture = load_texture("res/Texture/goldenTexture.jpg");
	unsigned int sub_Texture = load_texture("res/Texture/TextureLava.jpg");
	

	/* Shader */
	myShader = Shader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");
	myShader.use();
	myShader.setInt("main_Texture", 0);
	myShader.setInt("sub_Texture", 1);


	/* Game Loop */
	while (!glfwWindowShouldClose(window))
	{

		/* Update */
		userInput(window);
		float time = glfwGetTime();
		deltaTime = time - lastFrame;
		lastFrame = time;

		ConnectingShaderParameters();
		
		setTransformMatrix();

		glClearColor(0.9f, 0.2f, 0.3f, 1.0f); // 0.0 - 1.0
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		myShader.use();

		glBindVertexArray(VAO);
		glLineWidth(10.0f);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, main_Texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, sub_Texture);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		SetGUI();
		
		glfwSwapBuffers(window);
	
		glfwPollEvents();
	}

	/* Clear */
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	const float camera_speed = 2.5f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // To exit the program
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_TRUE) // Forward
		camera.ProcessKeyboard(FORWARD, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_TRUE) // Backward
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_TRUE) // Right
		camera.ProcessKeyboard(RIGHT, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_TRUE) // Left
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_TRUE) // Up
		camera.ProcessKeyboard(UP, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_TRUE) // Down
		camera.ProcessKeyboard(DOWN, deltaTime);

}
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
	if (isFirstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		isFirstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_TRUE)
		camera.ProcessMouseMovement(xoffset, yoffset);
}

void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

unsigned int load_texture(const char* texture_path)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	/* Filter Options */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(texture_path, &width, &height, &nrChannels, 0);

	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		if (nrChannels == 3) // jpg file
			format = GL_RGB;
		if (nrChannels == 4) // png file
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture\n";
	}

	stbi_image_free(data);

	return texture;
}


void setTransformMatrix() {


	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	glm::mat4 t = glm::mat4(1.0f);
	glm::mat4 r = glm::mat4(1.0f);
	glm::mat4 s = glm::mat4(1.0f);


	

	float rotation = glfwGetTime() * 30;

	t = glm::translate(t, glm::vec3(0.0f, 0.0f, -1.0f));
	r = glm::rotate(r, glm::radians(rotation), glm::vec3(1.0f, 1.0f, 0.0f));
	s = glm::scale(s, glm::vec3(scale_value[0], scale_value[1], scale_value[2]));

	model = s * r * t; // world 
	
	view = camera.GetViewMatrix();

	projection = glm::perspective(glm::radians(camera.Zoom), float(SCR_WIDTH) / float(SCR_HEIGHT), 0.1f, 1000.0f);

	myShader.setMat4("model", model);
	myShader.setMat4("view", view);
	myShader.setMat4("projection", projection);

}

void SetGUI() {

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();


	char txt_movement[] = "- Hold the right mouse button for look around.\n- Use W,A,S,D to move the camera.\n- Use mouse scroll to zoom in and out.";
	char txt_alpha[] = "- activates Sub-Texture alpha channel";
	char txt_color[] = "- activates RGB channel";
	

	ImGui::Begin("Controls");

	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(65, 253, 254, 255));
	ImGui::Text("Parameters");
	ImGui::PopStyleColor();

	ImGui::Dummy(ImVec2(0.0f, 10.0f));;

	ImGui::Checkbox("Color", &isColor);
	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 150, 150, 255));
	ImGui::Text(txt_color);
	ImGui::PopStyleColor();
	if (isColor == true)
	{
		ImGui::ColorEdit3("Color", color_value);
		ImGui::Dummy(ImVec2(0.0f, 10.0f));
	}

	ImGui::Checkbox("Texture", &isTexture);
	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 150, 150, 255));
	ImGui::Text(txt_alpha);
	ImGui::PopStyleColor();
	if (isTexture == true)
	{
		ImGui::SliderFloat("Sub-Texture alpha", &alpha, 0.0f, 1.0f);
		ImGui::Dummy(ImVec2(0.0f, 10.0f));
	}

	
	ImGui::DragFloat3("Scale", scale_value, 0.1f, 0.01f, 5.0f);
	ImGui::Dummy(ImVec2(0.0f, 30.0f));;
	
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(65, 253, 254, 255));
	ImGui::Text("How to play");
	ImGui::PopStyleColor();
	ImGui::Text(txt_movement);

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ConnectingShaderParameters() {
	myShader.setVec3("colors", color_value[0], color_value[1], color_value[2]);
	myShader.setBool("isColor", isColor);
	myShader.setBool("isTexture", isTexture);
	myShader.setFloat("alpha", alpha);
}

