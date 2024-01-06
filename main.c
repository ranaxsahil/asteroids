#include "C:/raylib/raylib/src/raylib.h"
#include <math.h>
#include <time.h>

int x=100, y =100;
float velocity_y = 0, velocity_x =0;

int window_width = 800;
int window_height = 800;

// void astroidmaker(){
    
    
    
// }
// int* placingstars(){
    // int starplace[window_width/2][window_height/2];
    // srand(time(0));
    // for(int i =0 ; i <window_width/2; i++){
    //     for(int j =0 ; j < window_height/2; j++){
    //         // this rand % 2 sets the range of rand fuction to 0 to n-1 
    //         // so here it will be 0 to 1 so i will get what i want 
    //         starplace[i][j] = rand()%2;
    //     }
    // }
//     return *starplace;
// }

void backgroundstars(int array[window_width/16][window_height/16]){
    for(int i =0 ; i <window_width/16; i++){
         for(int j =0 ; j < window_height/16; j++){
            
            if( array[i][j] == 0){
                continue;
            }
            else{
                DrawCircle(i*16  , j*16 , 1, WHITE);
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
struct bullets{
    int shouldrender;
    float angle;
    float x;
    float y;
    float speedx;
    float speedy;
    
}a[10];

// it is to make all the bullet entites not to render when the the starts 
 void stoprenderingbullets(){
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



int main(){
    //InitWindow( GetScreenWidth() , GetScreenHeight() , "Asteroids");
    InitWindow( window_width, window_height , "Asteroids" );
    SetTargetFPS(60);
     int p = 0, t=0;


// this is to make a 2d array which divides the scrren into 2x2 grids and
// tells wether to place a star at the edge of the grid or not 

    int starplace[window_width/16][window_height/16];
    srand(time(0));
    for(int i =0 ; i <window_width/16; i++){
        for(int j =0 ; j < window_height/16; j++){
            // this rand % 2 sets the range of rand fuction to 0 to n-1 
            // so here it will be 0 to 1 so i will get what i want 
            
            int a = 0;
            a = rand()%40;
            if ( a < 39 ){
                starplace[i][j] = 0;
            }else{
            starplace[i][j] = 1;
            }
        }
    }
// it is to make all the bullet entites not to render when the the starts 
    stoprenderingbullets();
    
    while( !WindowShouldClose()){
        velocity_y = velocity_y - (0.3)*IsKeyDown(KEY_W) + (0.3)*IsKeyDown(KEY_S) ;
        velocity_x = velocity_x + (0.3)*IsKeyDown(KEY_D) - (0.3)*IsKeyDown(KEY_A) ;
        y = y + velocity_y;
        x = x + velocity_x;
        BeginDrawing();


        backgroundstars(starplace);
        
        ClearBackground( BLACK);
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

// to check if the mouse button if pressed and then make the first entity visible by setting the render function to 1
// and giving the entity the values of x, y and the speed at which it should move 

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            a[p].shouldrender = 1;
            a[p].x = x;
            a[p].y = y;
            a[p].speedx = speedx(pointer(x,y),17,x);
            a[p].speedy = speedy(pointer(x,y),17,y,x);
            t = 1;
            if (p == 9){ p = -1;}
            p++;
        }
        

// for rendering the bullets , and if the should render is 0 then it will not render the entitiy and save computing power
        
        for (int q = 0 ; q <= 9; q++ ){
            if (a[q].shouldrender == 0){
                continue;
            }
            else {
            a[q].x = a[q].x + a[q].speedx;
            a[q].y = a[q].y + a[q].speedy;
            DrawCircle(a[q].x,a[q].y,5,RAYWHITE);}
            
        }
        
        
                  //Rectangle rec = {10,10,10,10};
            //DrawRectangle(x , y, 10 ,10, RAYWHITE);
            DrawFPS( 20,20);
            //float angle = (180/3.14)*atan((GetMouseY()-y)/(GetMouseX() - x));
            DrawRectanglePro((Rectangle){x,y,20,20},(Vector2){10,10},  pointer(x,y),RAYWHITE);
            //DrawRectanglePro((Rectangle){x,y,10,10},(Vector2){5,5}, angle,RAYWHITE);
           // DrawRectangle(x , y, 10 ,10, RAYWHITE);
           //taninverse = atan((GetMouseY() - y)/base);
          // if ()
            //DrawFPS( 20,20);
            EndDrawing();
           DrawText( TextFormat(" y:%010i \n x:%010i \n angle:%010f\nspeedx:%010f\nspeedy:%010f", GetMouseY(), GetMouseX(), pointer(x,y), speedx(pointer(x,y),30,x), speedy(pointer(x,y),30,y,x)) , 40, 40, 20 , RAYWHITE);
    }
    
    
}