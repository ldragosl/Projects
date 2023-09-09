#include "CameraSpectator.h"

#include "GLFW/glfw3.h"

#include "CoreMotor/MotorGrafic.h"

void CameraSpectator::procesareInput(float timpRandareCadru) {
	CameraClasificator::procesareInput(timpRandareCadru);

	//fereastra activa
	GLFWwindow* fereastraPrincipala = MotorGrafic::obtineMotorGrafic()->obtineFereastraPrincipala();

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* modVideo = glfwGetVideoMode(monitor);
	if (fereastraPrincipala && monitor && modVideo) {
		// deplasare camera in fata (pe directia vectorului inainte)
		if (glfwGetKey(fereastraPrincipala, GLFW_KEY_W) == GLFW_PRESS) {
			pozitieCamera += obtineVectorInainte() * timpRandareCadru * vitezaMiscareJucator;
		}
		// deplasare camera in spate (pe directia opusa vectorului inainte)
		if (glfwGetKey(fereastraPrincipala, GLFW_KEY_S) == GLFW_PRESS) {
			pozitieCamera -= obtineVectorInainte() * timpRandareCadru * vitezaMiscareJucator;
		}
		// deplasare camera la dreapta (pe directia vectorului dreapta)
		if (glfwGetKey(fereastraPrincipala, GLFW_KEY_D) == GLFW_PRESS) {
			pozitieCamera += obtineVectorDreapta() * timpRandareCadru * vitezaMiscareJucator;
		}
		// deplasare camera in stanga (pe directia opusa vectorului dreapta)
		if (glfwGetKey(fereastraPrincipala, GLFW_KEY_A) == GLFW_PRESS) {
			pozitieCamera -= obtineVectorDreapta() * timpRandareCadru * vitezaMiscareJucator;
		}
		// deplasare camera in sus
		if (glfwGetKey(fereastraPrincipala, GLFW_KEY_E) == GLFW_PRESS) {
			pozitieCamera += glm::vec3(0, 1, 0) * timpRandareCadru * vitezaMiscareJucator;
		}
		// deplasare camera in jos
		if (glfwGetKey(fereastraPrincipala, GLFW_KEY_Q) == GLFW_PRESS) {
			pozitieCamera += glm::vec3(0, -1, 0) * timpRandareCadru * vitezaMiscareJucator;
		}
		// Citim pozitia mouse-ului
		double pozitieMouseX, pozitieMouseY;
		glfwGetCursorPos(fereastraPrincipala, &pozitieMouseX, &pozitieMouseY);
		glfwSetCursorPos(fereastraPrincipala, modVideo->width / 2, modVideo->height / 2);

		//modificam unghiul camerei in functie de felul in care e miscata camera
		unghiCameraOrizontal += senzitivitateMouse * timpRandareCadru * float(modVideo->width / 2 - pozitieMouseX);
		unghiCameraVertical += senzitivitateMouse * timpRandareCadru * float(modVideo->height / 2 - pozitieMouseY);

		//prevenim camera din a se da peste cap
		if (unghiCameraVertical > glm::pi<float>() / 2.f)
			unghiCameraVertical = glm::pi<float>() / 2.f;
		if (unghiCameraVertical < -glm::pi<float>() / 2.f)
			unghiCameraVertical = -glm::pi<float>() / 2.f;
	}
}