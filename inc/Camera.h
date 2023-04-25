#pragma once

#include "Input.h"
#include "Transform.h"

class Camera : public Component
{
	public:
		Camera();
		~Camera();
		Camera(const Camera& other);
		Camera& operator=(const Camera& other);
		void Update() override;

		glm::vec3	upDirection;
		float		sensivity;
		float		fov;
		bool		isWireFrameModeOn;
		Input*		input;

	private:
};
