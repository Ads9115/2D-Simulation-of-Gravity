#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include "shaderClass.h"
#include <cmath>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/norm.hpp>

struct Body {

	glm::vec2 position;
	glm::vec2 velocity;
	float mass;
	float radius;


};


const float G = 1.0f;
const int numSegments = 100;
const float PI = 3.14159265358979323846f;




std::vector<float> numofvertices(float radius) {

	std::vector<float> vertices;
	for (int i = 0; i < numSegments; ++i) {


		float theta1 = 2.0f * PI * i / numSegments;
		float theta2 = 2.0f * PI * (i + 1) / numSegments;


		vertices.push_back(0.0f);
		vertices.push_back(0.0f);


		vertices.push_back(radius * cos(theta1));
		vertices.push_back(radius * sin(theta1));


		vertices.push_back(radius * cos(theta2));
		vertices.push_back(radius * sin(theta2));

		
	}

	return vertices;
	
}

glm::vec2 calGravitationalforce(const Body& body1,const Body& body2) {

	glm::vec2 dir = body2.position - body1.position;
	float distance = glm::length(dir);
	glm::vec2 norm = glm::normalize(dir);

	float ForceMag = G * body1.mass * body2.mass / (distance * distance + 0.01f);

	return ForceMag * norm;


}


void updateBodyMotion(Body& body, const glm::vec2& force, float dt) {
	glm::vec2 accel = force / body.mass;
	body.velocity += accel * dt;
	body.position += body.velocity * dt;

	float limit = 1.0f - body.radius;
	if (body.position.x <= -limit || body.position.x >= limit)
		body.velocity.x *= -1;

	if (body.position.y <= -limit || body.position.y >= limit)
		body.velocity.y *= -1;

	/*float limit = 1.0f - body.radius;
	body.position.x = glm::clamp(body.position.x, -limit, limit);
	body.position.y = glm::clamp(body.position.y, -limit, limit);*/

}

void renderBody(const Body& body, Shader& shader, unsigned int VAO, glm::vec3 color) {
	GLint posLoc = glGetUniformLocation(shader.ID, "u_position");
	GLint scaleLoc = glGetUniformLocation(shader.ID, "u_scale");
	GLint colorLoc = glGetUniformLocation(shader.ID, "u_color");

	glUniform2f(posLoc, body.position.x, body.position.y);
	glUniform1f(scaleLoc, body.radius);  
	glUniform3f(colorLoc, color.r, color.g, color.b);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, numSegments * 3);

}





int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1200, 1200, "Hello World", NULL, NULL);
	if (window == NULL) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader shader("default.vert", "default.frag");
	
	float G = 1.0f;

	


	float r = 0.7f;
	float mass1 = 20.0f;
	float mass2 = 1.0f;
	float orbitalSpeed = 0.95f * std::sqrt(G * mass1 / r);

	glm::vec2 velocity2 = glm::vec2(0.0f, orbitalSpeed);
	glm::vec2 velocity1 = -(velocity2 * (mass2 / mass1));  // Momentum balancing

	Body body1 = { glm::vec2(0.0f, 0.0f), velocity1, mass1, 0.3f };
	Body body2 = { glm::vec2(r, 0.0f), velocity2, mass2, 0.1f };
	std::vector<float> vertices = numofvertices(0.2f);


	glm::vec3 color1 = glm::vec3(1.0f, 0.0f, 0.3f);
	glm::vec3 color2 = glm::vec3(1.0f, 0.7f, 0.3f);
	
	


	


	/*std::vector<float> vertices;
	
	
	for (int i = 0; i < numSegments; ++i) {
		float theta1 = 2.0f * PI * i / numSegments;
		float theta2 = 2.0f * PI * (i + 1) / numSegments;

		
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);

		
		vertices.push_back(r * cos(theta1));
		vertices.push_back(r * sin(theta1));

		
		vertices.push_back(r * cos(theta2));
		vertices.push_back(r * sin(theta2));
	}*/

	




	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0);




	glViewport(0, 0, 1200, 1200);


	glDisable(GL_CULL_FACE);




	float lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		const float timeScale = 0.01f; // for realistic sun and earth motion almost same
		float scaledDeltaTime = deltaTime * timeScale;

		
		glm::vec2 force = calGravitationalforce(body1, body2);
		updateBodyMotion(body1, force, scaledDeltaTime);
		updateBodyMotion(body2, -force, scaledDeltaTime);

		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.Activate();
		renderBody(body1, shader, VAO, color1);
		renderBody(body2, shader, VAO, color2);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}





	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
