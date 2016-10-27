#include "display.h"
#include "shaders.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

#define WIDTH 800
#define HEIGHT 600

int main(){

    const std::string& title = "Ver6";
    int MapTexture = 0;

    display d(WIDTH, HEIGHT, title);

    /*********************************************************************************************************************************/
	//Obtain Opengl Version Info :

	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);
	const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	printf("GLSL Version : %s\n", glslVersion);

    /*********************************************************************************************************************************/
	//Check to see if graphics card supports Opengl 4

	GLint major;
	glGetIntegerv(GL_MAJOR_VERSION, &major);

	if (major >= 4){
        std::cout << "Supported Graphics!!" << std::endl;

        const float r = 0.0f;
        const float g = 0.0f;
        const float b = 0.0f;
        const float a = 1.0f;

        shaders s("./shaders/basic");   //This initialises the shader class and it takes in the path to the shaders(both vertex and fragment shader)
        vertex v[] = {vertex(glm::vec3(-0.5, -0.5, 0),  glm::vec2(0, 0)),     //Set of vertex points and corresponding texture coordinates to draw the triangle
                      vertex(glm::vec3(0, 0.5, 0),      glm::vec2(0.5, 1.0)),
                      vertex(glm::vec3(0.5, -0.5, 0),   glm::vec2(1.0, 0))};

        unsigned int indices[] = {0, 1, 2};

        mesh m(v, sizeof(v)/sizeof(v[0]), indices, sizeof(indices)/sizeof(indices[0]));      //Passing the vertex points to the mesh class i.e. the vertex shader
        //mesh m2("./models/IronMan.obj");
        mesh m2("./models/monkey.obj");
        texture t("./textures/bricks.bmp");
        Transform trans;
        //camera cam(glm::vec3(0,0,-130), 70.0f, ((float)WIDTH / (float)HEIGHT), 0.001f, 1000.0f);
        camera cam(glm::vec3(0,0,-3), 70.0f, ((float)WIDTH / (float)HEIGHT), 0.001f, 1000.0f);


        float Speedcounter = 0.0f;

    /*********************************************************************************************************************************/
        /*  MAIN GAME LOOP  */
        while(d.Running()){

            float sinCounter = sinf(Speedcounter);
            float cosCounter = cosf(Speedcounter);

            d.setFill(r,g,b,a);

            s.Bind();
            t.bindTexture(MapTexture);

            s.UpdateTransformations(trans, cam);

            m2.Draw();
            d.Update();

            trans.GetPos().x = sinCounter;
            trans.GetPos().z = cosCounter;
            trans.GetRot().x = Speedcounter * 2;
            trans.GetRot().y = Speedcounter * 4;
            trans.GetRot().z = Speedcounter * -2;
            //trans.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));

            Speedcounter += 0.00005f;
        }
	}
	else
        std::cerr << "\n\nUnsupported Graphics!! Requires Opengl Version >= 4.0 \n\n";

    return 0;
}
