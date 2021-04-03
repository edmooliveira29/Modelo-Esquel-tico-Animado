#pragma once
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <memory>

class Scene;

class Window
{
public:
	Window(int width, int height, const char* title);
	void update();
	~Window();

	inline bool shouldClose() const {
		return m_ShouldClose;
	}

	inline void setScene(std::unique_ptr<Scene> scene) {
		m_scene = std::move(scene);
	}

private:
	GLFWwindow* m_Window;
	bool m_ShouldClose;
	std::unique_ptr<Scene> m_scene = nullptr;
	static void errorCallback(int error, const char* description);
};

