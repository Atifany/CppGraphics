#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include <iomanip>

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

#include "../inc/colors.h"

#include "../inc/stb_image/stb_image.h"
#include "../inc/Shader.h"
#include "../inc/Camera.h"
#include "../inc/CoreData.h"
#include "../inc/Input.h"
#include "../inc/process_input.h"
#include "../inc/Texture.h"
#include "../inc/Material.h"
#include "../inc/Component.h"
#include "../inc/GameObject.h"
#include "../inc/Renderer.h"
#include "../scripts/inc/CubeScript.h"
#include "../scripts/inc/PlayerMovement.h"

static const float fov = 90.0f;

static const std::string vertexShaderPath = "../shaders/vertex_shader.shader";
static const std::string fragmentShaderPath = "../shaders/fragment_shader.shader";
static const std::string texturePath = "../textures/GrassBlock.png";
static const std::string fontPath = "../fonts/arial/arial.ttf";

float deltaTime = 0.0f;
static float lastFrame = 0.0f;

// Setup camera
Transform *origin = new Transform();
GameObject *camera = new GameObject();

CoreData c_d;
Input* input = new Input();

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void CalculateDeltaTime();
static void PutBenchMarktoTerminal(float rendererTime);

struct Character
{
	unsigned int	textureId;
	glm::ivec2		size;
	glm::ivec2		bearing;
	unsigned int	advance;
};
std::map<char, Character> Characters;

static int InitGLFWWindow()
{
	// create context.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window.
	c_d.window = glfwCreateWindow(c_d.windowWidth, c_d.windowHeight, "ft_minecraft", NULL, NULL);
	if (c_d.window == NULL)
	{
		std::cout << "Error: failed to initialize window.\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(c_d.window);
	// Set Viewport and adjust it with window resize.
	glfwSetFramebufferSizeCallback(c_d.window, framebuffer_size_callback);
	std::cout << "Debug: window object created.\n";
	return 0;
}

static int InitGLAD()
{
	// Initialize GLAD.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Error: failed to initialize GLAD.\n";
		return -1;
	}
	std::cout << "Debug: GLAD initialized.\n";
	return 0;
}

static int InitFT2(FT_Library* ft, FT_Face* face)
{
	if (FT_Init_FreeType(ft))
	{
		std::cout << "Error: failed to initialize FreeType library.\n";
		return -1;
	}
	if (FT_New_Face(*ft, "../fonts/arial/arial.ttf", 0, face))
	{
		std::cout << "Error: failed to load font.\n";
		return -1;
	}

	// Read pixel data by 1 byte. Default was 4 bytes.
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	FT_Set_Pixel_Sizes(*face, 0, 48);
	// load all glyphs to characters map
	for (unsigned char c = 0; c < 128; c++)
	{
		// load glyph
		int errCode = FT_Load_Char(*face, c, FT_LOAD_RENDER);
		if (errCode != 0)
		{
			std::cout << "Error: failed to load glyph " << c << " with code " << errCode << "\n";
			continue;
		}
		// generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(texture, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(texture, 0, GL_RED, (*face)->glyph->bitmap.width, (*face)->glyph->bitmap.rows, 0,
			GL_RED, GL_UNSIGNED_BYTE, (*face)->glyph->bitmap.buffer);
		
		Character character = {
			texture,
			glm::ivec2((*face)->glyph->bitmap.width, (*face)->glyph->bitmap.rows),
			glm::ivec2((*face)->glyph->bitmap_left, (*face)->glyph->bitmap_top),
			(unsigned int)(*face)->glyph->advance.x };
		Characters.insert(std::pair<char, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	// Return pixel read allignment to default 4
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	// clean
	FT_Done_Face(*face);
	FT_Done_FreeType(*ft);

	return 0;
}

int main()
{
	c_d.windowWidth = 1920;
	c_d.windowHeight = 1080;
	int errorCode = 0;

	errorCode = InitGLFWWindow();
	if (errorCode != 0)
		return errorCode;

	errorCode = InitGLAD();
	if (errorCode != 0)
		return errorCode;

	FT_Library*	ft = new FT_Library();
	FT_Face*	face = new FT_Face();
	errorCode = InitFT2(ft, face);
	if (errorCode != 0)
		return errorCode;
	FT_Set_Pixel_Sizes(*face, 0, 48);
	delete ft;
	delete face;

	Shader* shader = new Shader(vertexShaderPath, fragmentShaderPath);
	if (shader->program == 0)
		return -1;
	shader->Use();
	shader->UniformSetInt("textureToDraw", 0);

	// User input callbacks
	glfwSetKeyCallback(c_d.window, KeyCallbackSet);
	glfwSetInputMode(c_d.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(c_d.window, MouseCallbackSet);

	// Enable transparency component
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Enable Depth-tetsing
	glEnable(GL_DEPTH_TEST);

	origin->SetParent(NULL);
	Camera *cameraComp = new Camera();
	cameraComp->input = input;
	PlayerMovement* playerMoveScript = new PlayerMovement();
	playerMoveScript->input = input;
	playerMoveScript->speed = 10.0f;
	camera->AddComponent(cameraComp);
	camera->AddComponent(playerMoveScript);
	camera->GetComponent<Transform>()->position.x = -15.0f;

	Texture* grassBlockTexture = new Texture(GL_TEXTURE_2D, texturePath);
	grassBlockTexture->Load();
	Material* grassBlockMaterial = new Material(
		glm::vec3(0.8f, 0.8f, 0.8f),
		glm::vec3(0.6f, 0.6f, 0.6f),
		glm::vec3(0.0f, 0.0f, 0.0f), 32.0f);

	SpotLight *spotLight = new SpotLight(
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		1.0f, 0.0f, glm::vec3(1.0f, 0.09f, 0.032f),
		glm::vec3(0.0f, 1.0f, 0.0f), 0.91f, 0.82f);
	camera->AddComponent(spotLight);

	GameObject *lightTestObject = new GameObject();
	DirectionalLight *dirLight = new DirectionalLight(
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		0.1f, 0.0f, glm::vec3(0.0f, -1.0f, 0.0f));
	lightTestObject->AddComponent(dirLight);

	GameObject *pointLight1 = new GameObject();
	PointLight *p1 = new PointLight(
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		1.0f, 0.0f, glm::vec3(1.0f, 0.09f, 0.032f));
	pointLight1->AddComponent(p1);
	pointLight1->GetComponent<Transform>()->position = glm::vec3(15.0f, 2.5f, 15.0f);

	// GameObject* pointLight2 = new GameObject();
	// PointLight* p2 = new PointLight(
	// 	glm::vec3(1.0f, 1.0f, 1.0f),
	// 	glm::vec3(1.0f, 1.0f, 1.0f),
	// 	glm::vec3(1.0f, 1.0f, 1.0f),
	// 	1.0f, 0.0f, glm::vec3(1.0f, 0.09f, 0.032f));
	// pointLight2->AddComponent(p2);
	// pointLight2->GetComponent<Transform>()->position = glm::vec3(5.0f, 2.5f, 5.0f);

	GameObject *cube;
	for (int x = 0; x < 20; x++)
	{
		for (int z = 0; z < 20; z++)
		{
			Renderer* renderer = new Renderer(grassBlockTexture, grassBlockMaterial, shader);
			CubeScript* script = new CubeScript();
			cube = new GameObject();
			cube->AddComponent(renderer);
			cube->AddComponent(script);

			cube->GetComponent<Transform>()->position = glm::vec3(x, 0.0f, z);
		}
	}

	float rendererTime = 0.0f;
	float rendererTimeBuf = 0.0f;
	std::cout << "Debug: starting main loop.\n";
	std::cout << "\n";
	// run the app
	while (!glfwWindowShouldClose(c_d.window))
	{
		// Process callbacks and events.
		glfwPollEvents();
		
		CalculateDeltaTime();

		// Clears the window.
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->UpdateViewMatrix(camera);
		shader->UpdateProjectionMatrix(c_d, camera);

		rendererTime = 0.0f;

		LightSource *lightSource = camera->GetComponent<LightSource>();
		SpotLight *sl = dynamic_cast<SpotLight *>(lightSource);
		sl->direction = camera->GetComponent<Transform>()->quaternion.Forward();

		shader->UpdateLightUniforms();
		for (Transform *object : origin->children)
		{
			object->gameObject->CallUpdates();

			rendererTimeBuf = glfwGetTime();
			Renderer* renderer = object->gameObject->GetComponent<Renderer>();
			if (renderer != NULL)
			{
				renderer->Draw(camera);
			}
			rendererTime += glfwGetTime() - rendererTimeBuf;
		}

		// Swaps front and back screen buffers.
		glfwSwapBuffers(c_d.window);

		// User input.
		KeyReciever();
		// set values to keys.
		input->KeyCallBackProcess();

		PutBenchMarktoTerminal(rendererTime);
	}
	glfwSetInputMode(c_d.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glfwTerminate();
	std::cout << "Debug: program finished.\n";
	return 0;
}

static void PutBenchMarktoTerminal(float rendererTime)
{
	static char flasher = '|';
	static int framesElapsed = 0;
	static float lastChecked = 0.0f;

	framesElapsed++;
	float curTime = glfwGetTime();
	std::string color = GRN;

	if (curTime - lastChecked >= 1.0f)
	{
		if (flasher == '|')
			flasher = ' ';
		else
			flasher = '|';
		if (framesElapsed >= 60)
			color = GRN;
		else if (framesElapsed >= 30)
			color = YEL;
		else
			color = RED;

		lastChecked = curTime;
		std::cout << "\033[1A\033[:KDebug: FPS = " << color << framesElapsed << NC << " "
				  << "RenderTime = " << color << rendererTime * 1000 << NC << " " << flasher << "\n";
		framesElapsed = 0;
	}
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void CalculateDeltaTime()
{
	float curTime = glfwGetTime();
	deltaTime = curTime - lastFrame;
	lastFrame = curTime;
}
