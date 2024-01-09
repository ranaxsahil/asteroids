#include "C:/raylib/raylib/src/raylib.h"
#include <math.h>
#include <time.h>

int x=100, y =100;
float velocity_y = 0, velocity_x =0;

int window_width = 800;
int window_height = 800;

int p = 0;

// here we are gonna check the 2d array for 0/1 stored value 
//and draw a circle(or star), at the j*16 and i*16 cordiante

void backgroundstars(int array[window_width/16][window_height/16]){
    int b;
    for(int i =0 ; i <window_width/16; i++){
         for(int j =0 ; j < window_height/16; j++){
            
            if( array[i][j] == 0){
                continue;
            }
            else{
                b = rand()%200;
                if ( b < 1799 ){
                    DrawCircle(i*16  , j*16 ,1, WHITE);
                }
                else{
                    DrawPixel(i*16  , j*16 , WHITE);     
                }
            }
         }
    }
}

// find the angle in degree of the mouse cursor 

float pointer(int x, int y){
    float base = GetMouseX() - x;
    if (base == 0){
        return 90;
    }
    else {
        float angle = 57.29*atan((GetMouseY() - y)/base);
        return angle;
    }
}

// Made a structure for bullets to render and wether we have to render it or not 

struct bullets
{
    int shouldrender;
    float angle;
    float x;
    float y;
    float speedx;
    float speedy;
    
}a[20];

// it is to make all the bullet entites not to render when the the starts 

 void stop_rendering_bullets(){
  for( int i = 0 ; i < 10 ; i++){
        a[i].shouldrender = 0;
    }
}

// speed of the bullet in x 

float speedx(float angle , int speed, int x ){
    angle = angle/57.29;
    int i =1;
    if (GetMouseX() < x ){
       i = -1;
    }
    return i*speed*cos(angle);
}

// speed of the bullet in y 

float speedy(float angle , int speed, int y, int x ){
    angle = angle/57.29;
    int i =1;
    if (GetMouseY() < y && GetMouseX() > x  ){
        i = 1;
    }
    else if (GetMouseY() < y|| GetMouseY() >y && GetMouseX()<x  ){
        i = -1;
    }
    return i*speed*sin(angle);
}


// it is for the the increment and decrement of spaceship velocity

void velocity_of_ship(){
    velocity_y = velocity_y - (0.3)*IsKeyDown(KEY_W) + (0.3)*IsKeyDown(KEY_S) ;
    velocity_x = velocity_x + (0.3)*IsKeyDown(KEY_D) - (0.3)*IsKeyDown(KEY_A) ;
    y = y + velocity_y;
    x = x + velocity_x;
}



// it is to limt the speed of the ship in each direction x and y 
// yes the resultant speed of x+y is more than 5 but 
//i dont wanna work on that right now will think later 

void speed_check_of_ship(){
    if ( velocity_x >= 5){
        velocity_x = 5;        
    }
    else if ( velocity_x <= -5 ){
        velocity_x = -5;
    }
    if ( velocity_y >= 5){
        velocity_y = 5;
    }
    else if ( velocity_y <= -5){
        velocity_y = -5;
    }
}



// this function just checks wether the ship has crossed the edge of the scrren and then
// teleports ship to the opposite side 
// *** i have to make the code independent of the screen size will look into later ***

void teleportation_from_one_side_to_other(){
    if ( x < -10){
        x = 810; 
    }
    else if ( x > 810){
        x = -10; 
    }
    if ( y <  -10){
        y = 810;
    }
    else if ( y > 810){
        y = -10;
    }
}


// to check if the mouse button if pressed and then make the first entity visible by setting the render function to 1
// and giving the entity the values of x, y and the speed at which it should move 

void which_bullet_to_render(){
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            a[p].shouldrender = 1;
            a[p].x = x;
            a[p].y = y;
            a[p].speedx = speedx(pointer(x,y),17,x);
            a[p].speedy = speedy(pointer(x,y),17,y,x);
            if (p == 19){ 
            p = -1;
            }
            p++;
        }
}


// for rendering the bullets , and if the should render is 0 then it will not render the entitiy and save computing power

void rendering_bullets(){
    for (int q = 0 ; q <= 19; q++ ){
        if (a[q].shouldrender == 0){
            continue;
        }
        else {
        a[q].x = a[q].x + a[q].speedx;
        a[q].y = a[q].y + a[q].speedy;
        DrawCircle(a[q].x,a[q].y,5,RAYWHITE);
        }            
    }
}


struct Asteroids
{
    float speedx;
    float speedy; 
    int x;
    int y;
    int sides;
    int shouldrender;

}b[10];



int main(){
    //InitWindow( GetScreenWidth() , GetScreenHeight() , "Asteroids");
    InitWindow( window_width, window_height , "Asteroids" );
    SetTargetFPS(60);


    // this is to make a 2d array which divides the scrren into 2x2 grids and
    // tells wether to place a star at the edge of the grid or not 

    int starplace[window_width/16][window_height/16];
    srand(time(0));
    for(int i =0 ; i <window_width/16; i++){
        for(int j =0 ; j < window_height/16; j++){
            int a = 0;
            a = rand()%40;
            if ( a < 39 ){
                starplace[i][j] = 0;
            }
            else{
                starplace[i][j] = 1;
            }
        }
    }
// it is to make all the bullet entites not to render when the game starts 
    stop_rendering_bullets();
    
    while( !WindowShouldClose()){

        velocity_of_ship();

        BeginDrawing();

        backgroundstars(starplace);

        ClearBackground( BLACK);

        speed_check_of_ship();

        teleportation_from_one_side_to_other();

        which_bullet_to_render( p );
        
        rendering_bullets();

        DrawFPS( 20,20);
        DrawRectanglePro((Rectangle){x,y,20,20},(Vector2){10,10},  pointer(x,y),RAYWHITE);
        EndDrawing();
        DrawText( TextFormat(" y:%010i \n x:%010i \n angle:%010f\np:%i", GetMouseY(), GetMouseX(), pointer(x,y), p) , 40, 40, 20 , RAYWHITE);
    }
    
    
}