#include <sb7.h>
#include <vector>

class my_application : public sb7::application
{
public:
	void startup()
	{
		rendering_program = compile_shaders();
		glCreateVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//glPointSize(5.0f);
	}

	void render(double currentTime)
	{
		// background color
		const GLfloat color[] = { (float)sin(currentTime) * 0.5f + 0.5f, (float)cos(currentTime) * 0.5f + 0.5f, 0.0f,1.0f };
		
		glClearBufferfv(GL_COLOR, 0, color);

		glUseProgram(rendering_program);

		// vertex offset
		GLfloat attrib[] = { (float)sin(currentTime) * 0.5f, (float)cos(currentTime) * 0.6f, 0.0f, 0.0f };

		glVertexAttrib4fv(0, attrib);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void shutdown()
	{
		glDeleteVertexArrays(1, &vertex_array_object);
		glDeleteProgram(rendering_program);
	}

	GLuint compile_shaders(void)
	{
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint geometry_shader;
		GLuint tesselation_control_shader;
		GLuint tesselation_evaluation_shader;
		GLuint program;

		// vertex shader source code
		static const GLchar* vertex_shader_source[] =
		{
			"#version 450 core														\n"
			"																		\n"
			"layout (location = 0) in vec4 offset;									\n"
			"																		\n"
			"void main(void)														\n"
			"{																		\n"
			"	const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0),		\n"
			"									vec4(-0.25, -0.25, 0.5, 1.0),		\n"
			"									vec4(0.25, 0.25, 0.5, 1.0));		\n"
			"																		\n"
			"	gl_Position = vertices[gl_VertexID] + offset;						\n"
			"}																		\n"
		};

		// tesselation control shader source code
		static const GLchar* tesselation_control_shader_source[] =
		{
			"#version 450 core																	\n"
			"																					\n"
			"layout (vertices = 3) out;															\n"
			"																					\n"
			"void main(void)																	\n"
			"{																					\n"
			"    if (gl_InvocationID == 0)														\n"
			"    {																				\n"
			"        gl_TessLevelInner[0] = 5.0;												\n"
			"        gl_TessLevelOuter[0] = 5.0;												\n"
			"        gl_TessLevelOuter[1] = 5.0;												\n"
			"        gl_TessLevelOuter[2] = 5.0;												\n"
			"    }																				\n"
			"    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;		\n"
			"}																					\n"
		};

		// tesselation evaluation shader source code
		static const GLchar* tesselation_evaluation_shader_source[] =
		{
			"#version 450 core                                                                 \n"
			"                                                                                  \n"
			"layout (triangles, equal_spacing, cw) in;                                         \n"
			"                                                                                  \n"
			"void main(void)                                                                   \n"
			"{                                                                                 \n"
			"    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +                       \n"
			"                  (gl_TessCoord.y * gl_in[1].gl_Position) +                       \n"
			"                  (gl_TessCoord.z * gl_in[2].gl_Position);                        \n"
			"}                                                                                 \n"
		};

		// fragment shader source code
		static const GLchar* geometry_shader_source[] =
		{
			"#version 450 core								\n"
			"												\n"
			"layout (triangles) in;							\n"
			"layout (points, max_vertices = 3) out;			\n"
			"												\n"
			"void main(void)								\n"
			"{												\n"
			"	int i;										\n"
			"												\n"
			"	for(i = 0; i < gl_in.length(); i++)			\n"
			"	{											\n"
			"		gl_Position = gl_in[i].gl_Position;		\n"
			"		EmitVertex();							\n"
			"	}											\n"
			"}												\n"
		};

		// fragment shader source code
		static const GLchar* fragment_shader_source[] =
		{
			"#version 450 core							\n"
			"											\n"
			"out vec4 color;							\n"
			"											\n"
			"void main(void)							\n"
			"{											\n"
			"	color = vec4(sin(gl_FragCoord.x * 0.25) * 0.5 + 0.5,						\n"
			"				 cos(gl_FragCoord.y * 0.25) * 0.5 + 0.5,						\n"
			"				 sin(gl_FragCoord.x * 0.15) * cos(gl_FragCoord.y * 0.15),		\n"
			"				 1.0);															\n"			
			"}											\n"
		};

		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
		glCompileShader(vertex_shader);

		tesselation_control_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
		glShaderSource(tesselation_control_shader, 1, tesselation_control_shader_source, NULL);
		glCompileShader(tesselation_control_shader);

		tesselation_evaluation_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
		glShaderSource(tesselation_evaluation_shader, 1, tesselation_evaluation_shader_source, NULL);
		glCompileShader(tesselation_evaluation_shader);

		geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry_shader, 1, geometry_shader_source, NULL);
		glCompileShader(geometry_shader);

		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
		glCompileShader(fragment_shader);

		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		//glAttachShader(program, tesselation_control_shader);
		//glAttachShader(program, tesselation_evaluation_shader);
		//glAttachShader(program, geometry_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);
		
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		glDeleteShader(tesselation_control_shader);
		glDeleteShader(tesselation_evaluation_shader);
		glDeleteShader(geometry_shader);

		return program;
	}

private:
	GLuint rendering_program;
	GLuint vertex_array_object;
};

DECLARE_MAIN(my_application);