#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"
#include <iostream>

#include "drawSub.h"
using namespace std;

class Geometric {
public:
	int start_x, start_y;
	int end_x, end_y;
public:
	void(Geometric::*callback_)() = nullptr;

	// virtual 이랑 pointer function 이랑 똑같은거임
	// pute virtual function
	//virtual void vir_fun() = 0;

	void exec() {
		if (callback_ != nullptr) {
			(this->*callback_)();
		}
		else {
			cout << "Warning" << endl;
		}
	}
	// command pattern
	void command(Geometric* test, void(Geometric::*callback)()) {
		(test->*callback)();
	} 

	void initialize(const int& _start_x, const int& _start_y, const int& _end_x, const int& _end_y) {
		start_x = _start_x;
		start_y = _start_y;
		end_x = _end_x;
		end_y = _end_y;
	}
	void drawCircle() {
		Rect(start_x, start_y, end_x, end_y);

		int k1 = start_x;
		int k2 = end_x;
		int l1 = start_y;
		int l2 = end_y;

		for (int i = k1; i <= k2; i++) {
			for (int j = l1; j <= l2; j++) {
				int r = (k2 - k1) / 2;
				int a = (i - (k1 + k2) / 2)*(i - (k1 + k2) / 2) + (j - (l1 + l2) / 2)*(j - (l1 + l2) / 2);
				if (a <= r*r && a >= (r - 8)*(r - 8)) {
					drawPixel(i, j, 1.0f, 0.0f, 0.0f);
				}
			}
		}
	}
	void drawRect() {
		Rect(start_x, start_y, end_x, end_y);

		int k1 = start_x;
		int k2 = end_x;
		int l1 = start_y;
		int l2 = end_y;

		for (int i = k1; i <= k2; i++) {
			for (int j = l1; j <= l2; j++) {
				if (!(i > k1 + 2 && i < k2 - 2 && j > l1 + 2 && j < l2 - 2)) {
					drawPixel(i, j, 1.0f, 0.0f, 0.0f);
				}
			}
		}
	}
};

Geometric *poli = new Geometric[2];

void drawOnPixelBuffer(double xpos, double ypos) {
	std::fill_n(pixels, width*height * 3, 1.0f);

	poli[0].initialize(50, 300, 200, 450);
	poli[0].callback_ = &Geometric::drawCircle;

	poli[1].initialize(250, 300, 400, 450);
	poli[1].callback_ = &Geometric::drawRect;

	poli[0].command(&poli[0], &Geometric::drawCircle);
	poli[0].command(&poli[1], &Geometric::drawRect);
}

int main(void) {


	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  //»ï°¢Çü ÁÂÇ¥
	float vertices[] =
	{
		0.0, 0.5, 0.0, //top corner
		-0.5, -0.5, 0.0, //bottom left corner
		0.5, -0.5, 0.0 //bottom right corner
	};


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		double xpos, ypos;

		glfwGetCursorPos(window, &xpos, &ypos);


		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer(xpos, ypos);


		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;

}