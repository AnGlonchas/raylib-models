#include <iostream>
#include <raylib.h>

int fps = 60;
const int width = 1080;
const int height = 540;

using std::cout;
using std::endl;

class Player{
public:
    Model modplayer = LoadModel("kid.obj");
    Texture ptexture = LoadTexture("kid.png");
    Vector3 protation = {0,1,0};
    Vector3 pos = {0,0,0};
    float rotation = 0.0f;

    Player(){
    modplayer.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = ptexture;
    }

    void Update(){
        rotation = 0.0f;

        if(IsKeyDown(KEY_D)) { rotation = 90.0f; pos.x += 0.05f; }
        if(IsKeyDown(KEY_A)) { rotation = -90.0f; pos.x -= 0.05f; }
        if(IsKeyPressed(KEY_W)) pos.y += 0.01;

        DrawModelEx(modplayer,pos,protation,rotation,(Vector3){1,1,1},WHITE);
    }

    ~Player(){
        UnloadModel(modplayer);
        UnloadTexture(ptexture);
    }
};

int main(){
    SetTraceLogLevel(LOG_DEBUG);

    InitWindow(width, height, "plataformero we");
    SetTargetFPS(fps);

    Player player;
    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 1.5f, 5.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 1.5f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    while (!WindowShouldClose()){
        BeginDrawing();
            BeginMode3D(camera);
                ClearBackground(GRAY);
                player.Update();
            EndMode3D();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}