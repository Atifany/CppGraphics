#pragma once

// #include "../inc/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

class CoreData
{
	public:
		CoreData();
		CoreData(const CoreData&);
		~CoreData();
		CoreData& operator=(const CoreData& other);

		GLFWwindow*	window;
		int			windowWidth;
		int			windowHeight;
		bool		isWireFrameModeOn;

	private:

};

// Spread data globaly.
extern CoreData cd;
