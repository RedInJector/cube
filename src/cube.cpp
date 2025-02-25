
#define SDL_MAIN_HANDLED
#define SDL_PROJECT

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#include "objparser.h"
#include <SDL.h>

#include "Bresenham.h"
#include "Math3d.h"
#include "engine.h"

int SCREEN_W = SCREEN_WIDTH;
int SCREEN_H = SCREEN_HEIGHT;

SDL_Window *window;
SDL_Renderer *renderer;

void plotPixel(int x, int y) { SDL_RenderDrawPoint(renderer, x, y); }
void plotLinePoints(vec3f point0, vec3f point1) {
    SDL_RenderDrawLine(renderer, point0.x, point0.y, point1.x, point1.y);

  //std::function<void(int, int)> pixelPlotter = plotPixel;
  //plotLine(pixelPlotter, point0.x, point0.y, point1.x, point1.y);
}

void plotTriangle(triangle t) {
  plotLinePoints(t.p[0], t.p[1]);
  plotLinePoints(t.p[1], t.p[2]);
  plotLinePoints(t.p[2], t.p[0]);
}
void plotTriangle_SDL(triangle *t, SDL_Renderer *r) {
  SDL_RenderDrawLineF(r, t->p[0].x, t->p[0].y, t->p[1].x, t->p[1].y);
  SDL_RenderDrawLineF(r, t->p[1].x, t->p[1].y, t->p[2].x, t->p[2].y);
  SDL_RenderDrawLineF(r, t->p[0].x, t->p[0].y, t->p[2].x, t->p[2].y);
}

float fElapsedTime = 0;
double deltaTime = 0;

mat4x4f matProj;
void RenderScene(std::shared_ptr<scene_v> sc, SDL_Renderer *r) {
  SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
  SDL_RenderClear(r);
  SDL_SetRenderDrawColor(r, 255, 255, 255, 255);

  for (int i = 0; i < sc->objects.size(); i++) {
    std::shared_ptr<object3d_v> obj = sc->objects.at(i);
    if (!obj->isVisible)
      continue;
    int n = obj->triangles.size();

    mat4x4f transMatrix;
    applyTransform(obj, transMatrix);
    for (int j = 0; j < n; j++) {
      triangle triProjected, triTransformed;
      triangle t;
      t.p[0] = obj->vertices.at(obj->triangles.at(j).vertexid[0]);
      t.p[1] = obj->vertices.at(obj->triangles.at(j).vertexid[1]);
      t.p[2] = obj->vertices.at(obj->triangles.at(j).vertexid[2]);

      MultiplyMatrixTris(&t, &triTransformed, &transMatrix);

      for (int k = 0; k < 3; k++) {
        triTransformed.p[k].x += obj->transform.position.x;
        triTransformed.p[k].y += obj->transform.position.y;
        triTransformed.p[k].z += obj->transform.position.z;
      }

      MultiplyMatrixTris(&triTransformed, &triProjected, &matProj);

      triProjected.p[0].x += 1.0f;
      triProjected.p[0].y += 1.0f;
      triProjected.p[1].x += 1.0f;
      triProjected.p[1].y += 1.0f;
      triProjected.p[2].x += 1.0f;
      triProjected.p[2].y += 1.0f;

      triProjected.p[0].x *= 0.5f * (float)SCREEN_W;
      triProjected.p[0].y *= 0.5f * (float)SCREEN_H;
      triProjected.p[1].x *= 0.5f * (float)SCREEN_W;
      triProjected.p[1].y *= 0.5f * (float)SCREEN_H;
      triProjected.p[2].x *= 0.5f * (float)SCREEN_W;
      triProjected.p[2].y *= 0.5f * (float)SCREEN_H;

      plotTriangle_SDL(&triProjected, r);
      //plotTriangle(triProjected);


      //SDL_RenderGeometry(renderer, NULL, )
    }
  }

  SDL_RenderPresent(renderer);
}

Camera camera;

std::shared_ptr<scene_v> scn;
void start() {
  matProj = mat4x4f_default;

  scn = makeSceneNew();

  // scn->objects.push_back(makeCubeNew());
  // scn->objects.push_back(makeCubeNew());
  // scn->objects.push_back(makeCubeNew());

  auto obj = loadObj("manuka.obj");
  if(obj == nullptr)
      exit(1);

  obj->isVisible = true;
  std::shared_ptr<object3d_v> objs = std::move(obj);

  scn->objects.push_back(objs);

  makeDefaultCamera(&camera, SCREEN_H, SCREEN_W);

  makeProjectionMatrix(camera, matProj);
}

float fTheta = 0;
int isRotated = 1;
void loop() {
  if (isRotated)
    fTheta += 0.001 * deltaTime;

  auto object = scn->objects.at(0);

  object->transform.rotation.x = 360;
  object->transform.rotation.y = fTheta;
  object->transform.rotation.z = 0;

  object->transform.position.x = 0;
  object->transform.position.y = 0;
  object->transform.position.z = 3;

  // cube2->origin.position.x = 1;
  // cube2->transform.position.y = 1;
  // cube2->transform.position.z = 3;
  // cube2->transform.rotation.y = -fTheta * 0.8f;
  // cube2->transform.rotation.z = 0;

  //// line2->origin.position.x = 1;
  // cube3->transform.position.z = 3;
  // cube3->transform.position.y = -1;
  // cube3->transform.rotation.y = -fTheta * 1.1f;
  // cube3->transform.rotation.z = 0;

  // cube3->isVisible = false;
}

int main() {
  window = SDL_CreateWindow("Test", 200, 200, SCREEN_WIDTH, SCREEN_HEIGHT,
                            SDL_WINDOW_OPENGL);
  if (window == NULL) {
    printf("Error window creation\n");
    return 3;
  }
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
  Uint64 NOW = SDL_GetPerformanceCounter();
  Uint64 LAST = 0;

  start();

  int isRunning = 1;
  while (isRunning) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        isRunning = 0;
        continue;
      }
      if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (e.button.button == SDL_BUTTON_LEFT) {
          isRotated = !isRotated;
          continue;
        }
        if (e.button.button == SDL_BUTTON_RIGHT) {
          // cube3->isVisible = !cube3->isVisible;
          continue;
        }
      }
    }
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();
    deltaTime =
        (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

    char Title[23];
    sprintf(Title, "Cube - fps:%.6gfps", 1000 / deltaTime);
    SDL_SetWindowTitle(window, Title);

    loop();
    RenderScene(scn, renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
