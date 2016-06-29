/*
 * Copyright © 2012-2015 Graham Sellers
 *
 * This code is part of the OpenGL SuperBible, 7th Edition.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <sb7.h>
#include <vmath.h>

#include <omp.h>

class ompparticles_app : public sb7::application
{
public:
    ompparticles_app()
        : frame_index(0),
          use_omp(true)
    {

    }

    void init();
    void startup();
    void render(double currentTime);
    void shutdown();

    enum
    {
        PARTICLE_COUNT          = 2048
    };

    struct PARTICLE
    {
        vmath::vec3 position;
        vmath::vec3 velocity;
    };

protected:
    GLuint      particle_buffer;
    PARTICLE *  mapped_buffer;
    PARTICLE *  particles[2];
    int         frame_index;
    GLuint      vao;
    GLuint      draw_program;
    bool        use_omp;
    
    void iniitialize_particles(void);
    void update_particles(float deltaTime);
    void update_particles_omp(float deltaTime);
    void onKey(int key, int action);
};

void ompparticles_app::init()
{
    static const char title[] = "OpenGL - zrownoleglone czasteczki";

    sb7::application::init();

    memcpy(info.title, title, sizeof(title));
}

void ompparticles_app::startup()
{
    // Bufory cz¹steczek w pamiêci g³ównej (podwójne buforowanie).
    particles[0] = new PARTICLE[PARTICLE_COUNT];
    particles[1] = new PARTICLE[PARTICLE_COUNT];

    // Utworzenie bufora GPU.
    glGenBuffers(1, &particle_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, particle_buffer);
    glBufferStorage(GL_ARRAY_BUFFER,
                    PARTICLE_COUNT * sizeof(PARTICLE),
                    nullptr,
                    GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT);
    mapped_buffer = (PARTICLE*)glMapBufferRange(
        GL_ARRAY_BUFFER,
        0,
        PARTICLE_COUNT * sizeof(PARTICLE),
        GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_FLUSH_EXPLICIT_BIT);

    iniitialize_particles();

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
    glBindVertexBuffer(0, particle_buffer, 0, sizeof(PARTICLE));
    glEnableVertexAttribArray(0);

    GLuint vs, fs;

    vs = glCreateShader(GL_VERTEX_SHADER);
    fs = glCreateShader(GL_FRAGMENT_SHADER);

    static const char* vs_source[] =
    {
        "#version 440 core\n"
        "layout (location = 0) in vec3 position;\n"
        "out vec4 particle_color;\n"
        "void main(void)\n"
        "{\n"
        "    particle_color = vec4(0.6, 0.8, 0.8, 1.0) * (smoothstep(-10.0, 10.0, position.z) * 0.6 + 0.4);\n"
        "    gl_Position = vec4(position * 0.2, 1.0);\n"
        "}\n"
    };
    glShaderSource(vs, 1, vs_source, nullptr);

    static const char* fs_source[] =
    {
        "#version 440 core\n"
        "layout (location = 0) out vec4 o_color;\n"
        "in vec4 particle_color;\n"
        "void main(void)\n"
        "{\n"
        "    o_color = particle_color;\n"
        "}\n"
    };
    glShaderSource(fs, 1, fs_source, nullptr);

    glCompileShader(vs);
    glCompileShader(fs);

    draw_program = glCreateProgram();
    glAttachShader(draw_program, vs);
    glAttachShader(draw_program, fs);
    glLinkProgram(draw_program);

    int maxThreads = omp_get_max_threads();
    omp_set_num_threads(maxThreads);
}

// Generator liczb losowych.
static unsigned int seed = 0x13371337;

static inline float random_float()
{
    float res;
    unsigned int tmp;

    seed *= 16807;

    tmp = seed ^ (seed >> 4) ^ (seed << 15);

    *((unsigned int *) &res) = (tmp >> 9) | 0x3F800000;

    return (res - 1.0f);
}

void ompparticles_app::iniitialize_particles(void)
{
    int i;

    for (i = 0; i < PARTICLE_COUNT; i++)
    {
        particles[0][i].position[0] = random_float() * 6.0f - 3.0f;
        particles[0][i].position[1] = random_float() * 6.0f - 3.0f;
        particles[0][i].position[2] = random_float() * 6.0f - 3.0f;
        particles[0][i].velocity = particles[0][i].position * 0.001f;

        mapped_buffer[i] = particles[0][i];
    }
}

void ompparticles_app::update_particles(float deltaTime)
{
    // Podwójne buforowanie — Ÿród³o i cel.
    const PARTICLE* const __restrict src = particles[frame_index & 1];
    PARTICLE* const __restrict dst = particles[(frame_index + 1) & 1];

    // Dla ka¿dej cz¹steczki w systemie...
//#pragma omp parallel for schedule (dynamic, 16)
    for (int i = 0; i < PARTICLE_COUNT; i++)
    {
        // Pobierz moje w³asne dane.
        const PARTICLE& me = src[i];
        vmath::vec3 delta_v(0.0f);

        // Dla wszystkich innych cz¹steczek...
        for (int j = 0; j < PARTICLE_COUNT; j++)
        {
            if (i != j) // ...to nie ja!
            {
                // Pobierz wektor do innej cz¹steczki.
                vmath::vec3 delta_pos = src[j].position - me.position;
                float distance = vmath::length(delta_pos);
                // Znormalizuj.
                vmath::vec3 delta_dir = delta_pos / distance;
                // To ograniczenie niweluje mo¿liwoœæ b³êdu, 
                // gdy cz¹steczki znajd¹ siê zbyt blisko siebie...
                distance = distance < 0.005f ? 0.005f : distance;
                // Aktualizacja prêdkoœci.
                delta_v += (delta_dir / (distance * distance));
            }
        }
        // Dodaj aktualn¹ prêdkoœæ do po³o¿enia.
        dst[i].position = me.position + me.velocity;
        // Oblicz now¹ prêdkoœæ na podstawie aktualnej prêdkoœci i obliczonej delty.
        dst[i].velocity = me.velocity + delta_v * deltaTime * 0.01f;
        // Zapisz dane w mapowanym buforze.
        mapped_buffer[i].position = dst[i].position;
    }

    // Policz klatki, aby w nastêpnej klatce równie¿ u¿yæ podwójnego buforowania.
    frame_index++;
}

void ompparticles_app::update_particles_omp(float deltaTime)
{
    // Podwójne buforowanie — Ÿród³o i cel.
    const PARTICLE* const __restrict src = particles[frame_index & 1];
    PARTICLE* const __restrict dst = particles[(frame_index + 1) & 1];

    // Dla ka¿dej cz¹steczki w systemie...
#pragma omp parallel for schedule (dynamic, 16)
    for (int i = 0; i < PARTICLE_COUNT; i++)
    {
        // Pobierz moje w³asne dane.
        const PARTICLE& me = src[i];
        vmath::vec3 delta_v(0.0f);

        // Dla wszystkich innych cz¹steczek...
        for (int j = 0; j < PARTICLE_COUNT; j++)
        {
            if (i != j) // ...to nie ja!
            {
                // Pobierz wektor do innej cz¹steczki.
                vmath::vec3 delta_pos = src[j].position - me.position;
                float distance = vmath::length(delta_pos);
                // Znormalizuj.
                vmath::vec3 delta_dir = delta_pos / distance;
                // To ograniczenie niweluje mo¿liwoœæ b³êdu, 
                // gdy cz¹steczki znajd¹ siê zbyt blisko siebie...
                distance = distance < 0.005f ? 0.005f : distance;
                // Aktualizacja prêdkoœci.
                delta_v += (delta_dir / (distance * distance));
            }
        }
        // Dodaj aktualn¹ prêdkoœæ do po³o¿enia.
        dst[i].position = me.position + me.velocity;
        // Oblicz now¹ prêdkoœæ na podstawie aktualnej prêdkoœci i obliczonej delty.
        dst[i].velocity = me.velocity + delta_v * deltaTime * 0.01f;
        // Zapisz dane w mapowanym buforze.
        mapped_buffer[i].position = dst[i].position;
    }

    // Policz klatki, aby w nastêpnej klatce równie¿ u¿yæ podwójnego buforowania.
    frame_index++;
}

void ompparticles_app::render(double currentTime)
{
    static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    static double previousTime = 0.0;

    // Obliczenie zmiany czasu.
    float deltaTime = (float)(currentTime - previousTime);
    previousTime = currentTime;

    // Aktualizacja po³o¿enia cz¹steczek za pomoc¹ OpenMP... lub bez tej pomocy.
    if (use_omp)
    {
        update_particles_omp(deltaTime * 0.001f);
    }
    else
    {
        update_particles(deltaTime * 0.001f);
    }

    // Czyszczenie.
    glViewport(0, 0, info.windowWidth, info.windowHeight);
    glClearBufferfv(GL_COLOR, 0, black);

    // Dowi¹zanie tablicy wierzcho³ków.
    glBindVertexArray(vao);

    // Poinformuj OpenGL o zmianie zawartoœci bufora.
    glFlushMappedBufferRange(GL_ARRAY_BUFFER, 0, PARTICLE_COUNT * sizeof(PARTICLE));

    glPointSize(3.0f);

    // Rysuj!
    glUseProgram(draw_program);
    glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);
}


void ompparticles_app::onKey(int key, int action)
{
    if (action)
    {
        switch (key)
        {
            case 'M':
                use_omp = !use_omp;
                break;
        }
    }
}

void ompparticles_app::shutdown()
{
    glBindBuffer(GL_ARRAY_BUFFER, particle_buffer);
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glDeleteBuffers(1, &particle_buffer);

    delete [] particles[1];
    delete [] particles[0];
}

DECLARE_MAIN(ompparticles_app)
