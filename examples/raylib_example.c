#include <raylib.h>
#include <semaphore.h>
#include <string.h>
#include "../autocor.h"
#include "../fft/fft.h"

#define SAMPLE_RATE 44100
#define CHANNELS 2

#define n 512

float sample_buffer[n] = { 0 };
unsigned int sample_buffer_index = 0;
sem_t sample_buffer_mutex;

float complex sig[n];

void callback(void* data, unsigned int num_frames) {
	float* sample = (float*) data;
	sem_wait(&sample_buffer_mutex);
	for (unsigned int i = 0; i < num_frames; i++) {
		sample_buffer[sample_buffer_index] = sample[i * CHANNELS];
		sample_buffer_index += 1;
		sample_buffer_index %= n;
	}
	sem_post(&sample_buffer_mutex);
}

void update_autocor() {
	sem_wait(&sample_buffer_mutex);
	for (unsigned int i = 0; i < n; i++) {
		unsigned int idx = (sample_buffer_index + i) % n;
		sig[i] = sample_buffer[idx] + 0*I;
	}
	sem_post(&sample_buffer_mutex);
	autocor_inpl(sig, n);
}

int main(int argc, char** argv) {
	if (argc < 2) return 0;

	sem_init(&sample_buffer_mutex, 0, 1);

	InitAudioDevice();
	
	Music music = LoadMusicStream(argv[1]);
	music.looping = false;
	AttachAudioStreamProcessor(music.stream, callback);


	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_ALWAYS_RUN);
	int window_width = 3840;
	int window_height = 2160;
	InitWindow(window_width, window_height, "test");
	SetTargetFPS(120);
	int monitor = GetCurrentMonitor();
	window_width = GetMonitorWidth(monitor);
	window_height = GetMonitorHeight(monitor);
	SetWindowSize(window_width, window_height);
	ToggleFullscreen();
	HideCursor();

	while (GetTime() < 0.f && !WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		EndDrawing();
	}

	PlayMusicStream(music);

	while (!WindowShouldClose()) {
		UpdateMusicStream(music);
		update_autocor();

		BeginDrawing();
		ClearBackground(BLACK);
		
		static float bar_height[n];
		const float bar_width = (float) window_width / (float) n;
		const float persistence = 0.9f;
		const float bar_scale = 10.f * window_height / 1080.f;

		for (unsigned int i = 0; i < n; i++) {
			bar_height[i] *= persistence;
			bar_height[i] += crealf(sig[i]) * bar_scale * (1.f - persistence);

			float x = (float) i * bar_width;
			float y = (float) window_height/2.f - bar_height[i];

			Vector2 position = { x, y };
			Vector2 size = { bar_width, bar_height[i] };

			if (size.y < 0.f) {
				position.y += size.y;
				size.y *= -1;
			}

			DrawRectangleV(position, size, WHITE);

		}

		EndDrawing();
	}
	
	CloseWindow();

	UnloadMusicStream(music);
	CloseAudioDevice();

	return 0;
}
