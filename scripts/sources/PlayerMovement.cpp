#include "../inc/PlayerMovement.h"

extern float deltaTime;

static void Move(PlayerMovement* me, Transform* t, Camera* cam);
static void Rotate(PlayerMovement* me, Transform* t, Camera* cam);

void PlayerMovement::Update()
{
	Transform* t = this->gameObject->GetComponent<Transform>();
	Camera* cam = this->gameObject->GetComponent<Camera>();

	Move(this, t, cam);
	Rotate(this, t, cam);
}

static void Rotate(PlayerMovement* me, Transform* t, Camera* cam)
{
	glm::vec2 mousePos = me->input->GetMousePos();

	static bool		isFirstTime = true;
	static float	lastX = 400.0f;
	static float	lastY = 300.0f;
	static float	cameraYaw = 0.0f;
	static float	cameraPitch = 0.0f;

	if (isFirstTime == true)
	{
		if (mousePos.x != lastX && mousePos.y != lastY)
			isFirstTime = false;
		lastX = mousePos.x;
		lastY = mousePos.y;
	}

	float xoffset =   (mousePos.x - lastX) * cam->sensivity;
	float yoffset = - (mousePos.y - lastY) * cam->sensivity;
	lastX = mousePos.x;
	lastY = mousePos.y;

	cameraYaw += xoffset;
	cameraPitch += yoffset;

	if (cameraYaw > 360.0f)
		cameraYaw -= 360.0f;
	if (cameraYaw < -360.0f)
		cameraYaw += 360.0f;
	if (cameraPitch > 89.0f)
		cameraPitch = 89.0f;
	if (cameraPitch < -89.0f)
		cameraPitch = -89.0f;

	glm::vec3 viewRad = glm::vec3(
		glm::radians(cameraYaw),
		glm::radians(cameraPitch),
		glm::radians(0.0f));
	t->quaternion = Quaternion(viewRad);
}

static void Move(PlayerMovement* me, Transform* t, Camera* cam)
{
	// Move forward
	if (me->input->GetKey(GLFW_KEY_W) == I_KEY_CONT_PRESS ||
		me->input->GetKey(GLFW_KEY_W) == I_KEY_SINGLE_PRESS) // first frame not even noticeble
		t->position += t->quaternion.Forward() * me->speed * deltaTime;
	
	// Move backwards
	if (me->input->GetKey(GLFW_KEY_S) == I_KEY_CONT_PRESS ||
		me->input->GetKey(GLFW_KEY_S) == I_KEY_SINGLE_PRESS)
		t->position += - t->quaternion.Forward() * me->speed * deltaTime;

	// Move leftwards
	if (me->input->GetKey(GLFW_KEY_A) == I_KEY_CONT_PRESS ||
		me->input->GetKey(GLFW_KEY_A) == I_KEY_SINGLE_PRESS)
		t->position += - glm::normalize(glm::cross(t->quaternion.Forward(), cam->upDirection)) * me->speed * deltaTime;
	
	// Move rightwards
	if (me->input->GetKey(GLFW_KEY_D) == I_KEY_CONT_PRESS ||
		me->input->GetKey(GLFW_KEY_D) == I_KEY_SINGLE_PRESS)
		t->position += glm::normalize(glm::cross(t->quaternion.Forward(), cam->upDirection)) * me->speed * deltaTime;
	
	// Move upwards
	if (me->input->GetKey(GLFW_KEY_SPACE) == I_KEY_CONT_PRESS ||
		me->input->GetKey(GLFW_KEY_SPACE) == I_KEY_SINGLE_PRESS)
		t->position += cam->upDirection * me->speed * deltaTime;
	
	// Move downwards
	if (me->input->GetKey(GLFW_KEY_LEFT_SHIFT) == I_KEY_CONT_PRESS ||
		me->input->GetKey(GLFW_KEY_LEFT_SHIFT) == I_KEY_SINGLE_PRESS)
		t->position += - cam->upDirection * me->speed * deltaTime;
}

