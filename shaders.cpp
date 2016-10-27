#include "shaders.h"

using namespace std;

/*******************************************************************************************************************************************************************/
static string loadShader(const string& fileName);
static void CheckShaderError(GLuint shader, GLuint flag, bool program, const string& errorMessage);
/*******************************************************************************************************************************************************************/

shaders::shaders(const std::string& fileName)
{
    program = glCreateProgram();

    vertex_shader = createShader(loadShader(fileName + ".vs"), GL_VERTEX_SHADER);
    fragment_shader = createShader(loadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

    glBindAttribLocation(program, 0, "position");
    glBindAttribLocation(program, 1, "texCoord");
    glBindAttribLocation(program, 2, "normal");

    linkProgram(program, vertex_shader);
    linkProgram(program, fragment_shader);

    uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform");
}
/*******************************************************************************************************************************************************************/

shaders::~shaders()
{
    glDetachShader(program, vertex_shader);
    glDetachShader(program, fragment_shader);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glDeleteProgram(program);
}
/*******************************************************************************************************************************************************************/

void shaders::linkProgram(GLuint program, GLuint ShaderType){
    glAttachShader(program, ShaderType);

    glLinkProgram(program);
    CheckShaderError(program, GL_LINK_STATUS, true, "Error!! Program linking failed : ");

    glValidateProgram(program);
    CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error!! Program is invalid : ");
}
/******************************************************************************************************************************/

void shaders::Bind(){
    glUseProgram(program);
}
/******************************************************************************************************************************/

void shaders::UpdateTransformations(const Transform& trans, const camera& cam){

    glm::mat4 modelProjection = cam.GetViewProjection() * trans.GetModel();
    glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GL_FALSE, &modelProjection[0][0]);
}

GLuint shaders::createShader(const std::string& text, GLenum ShaderType){
    GLuint shader = glCreateShader(ShaderType);

    if(shader == 0){
        std::cerr << "\n\nShader creation failed!!\n\n";
    }

    const GLchar* shaderSourcestrings[1];                   //Const char for storing the shader code
    GLint shaderSourcestringsLength[1];                     //Store the shader source length

    shaderSourcestrings[0] = text.c_str();                  //Storing the shader source
    shaderSourcestringsLength[0] = text.length();           //Storing the shader source length

    glShaderSource(shader, 1, shaderSourcestrings, shaderSourcestringsLength);      //hands the shader source to the shader object
    glCompileShader(shader);        //Compiling the shader

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error! Shader compilation failed: ");       //Check for compilation errors

    return shader;
}
/*******************************************************************************************************************************************************************/

static void CheckShaderError(GLuint shader, GLuint flag, bool program, const string& errorMessage){     //This is an important yet irrelevant function in opengl programming hence not commented
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(program){
        glGetProgramiv(shader, flag, &success);
    }
    else{
        glGetShaderiv(shader, flag, &success);
    }

    if(success == GL_FALSE){
        if(program){
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        }
        else{
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        }
        cerr << errorMessage << ":" << error << "'" << endl;
    }
}
/*******************************************************************************************************************************************************************/

static string loadShader(const string& fileName){

    ifstream file;
    file.open(fileName.c_str());

    string output;
    string line;

    if(file.is_open()){
        while(file.good()){
            getline(file, line);
            output.append(line + "\n");
        }
    }
    else{
        cerr << "\nUnable to load shader: " << fileName << endl;
    }

    return output;

}
/*******************************************************************************************************************************************************************/
