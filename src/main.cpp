// -----------------------------------------
// | Title       : three_di_world          |
// | Author      : Ice-Blaze               |
// | Start date  : 10.07.2013              |
// | Poject on a plan, a 3D linear algebra |
// -----------------------------------------

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL.h>

#include "Point3D.h"
#include "Segment3D.h"
#include "Draw2D.h"
#include "Cube.h"

const int WINDOW_W = 640;
const int WINDOW_H = 480;

int main ( int argc, char** argv )
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(WINDOW_W, WINDOW_H, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    SDL_EnableKeyRepeat(1,1);
    SDL_ShowCursor(0);

    // start cube element
    int origin = 200;
    int cubeWidth = 50;

    Point3D pt1(origin,origin,0);
    Point3D pt2(origin+cubeWidth,origin,0);
    Point3D pt3(origin,origin+cubeWidth,0);
    Point3D pt4(origin,origin,cubeWidth);

    Cube cube(pt1,pt2,pt3,pt4);

    // program main loop
    int fps = 0;
    int fpsTime = SDL_GetTicks();
    int renderTime = SDL_GetTicks();

    //debug
    int vectorDebug = 1;
    Point3D *debug = &Draw2D::camera;
    float angleDebug = 1;
    SDL_WarpMouse(WINDOW_W/2, WINDOW_H/2);
    //stop debug

    Point3D cameraDirection;

    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE: done = true; break;

                    case SDLK_w:
                        cameraDirection = Point3D (0,0,-1);
                        cameraDirection.rotation(Point3D(1,0,0),-Draw2D::xangle);// x/y angle order important
                        cameraDirection.rotation(Point3D(0,1,0),-Draw2D::yangle);
                        Draw2D::camera = Draw2D::camera+cameraDirection;
                        break;

                    case SDLK_s:
                        cameraDirection = Point3D (0,0,-1);
                        cameraDirection.rotation(Point3D(1,0,0),-Draw2D::xangle); // x/y angle order important
                        cameraDirection.rotation(Point3D(0,1,0),-Draw2D::yangle);
                        Draw2D::camera = Draw2D::camera-cameraDirection;
                        break;

                    case SDLK_a:
                        cameraDirection = Point3D (0,0,-1);
                        cameraDirection.rotation(Point3D(0,1,0),-Draw2D::yangle-3.14/2);
                        Draw2D::camera = Draw2D::camera+cameraDirection;
                        break;

                    case SDLK_d:
                        cameraDirection = Point3D (0,0,-1);
                        cameraDirection.rotation(Point3D(0,1,0),-Draw2D::yangle+3.14/2);
                        Draw2D::camera = Draw2D::camera+cameraDirection;
                        break;

                    case SDLK_m: Draw2D::near+=1; break;

                    case SDLK_n: Draw2D::near-=1; break;

                    //debug
                    case SDLK_SPACE:
                        Draw2D::camera.y+=1;// juste for debug
                        break;

                    case SDLK_x:
                        Draw2D::camera.y-=1;// juste for debug
                        break;

                    default:
                        break;
                    }

                    break;
                }

            } // end switch
        } // end of message processing

        // check mouse position for rotate the camera
        int mouseX,mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        int diffX = mouseX-WINDOW_W/2;
        int diffY = mouseY-WINDOW_H/2;

        if(diffY!=0) { Draw2D::setXangle(diffY/800.0); }

        if(diffX!=0) { Draw2D::setYangle(-diffX/800.0); }

        SDL_WarpMouse(WINDOW_W/2, WINDOW_H/2);

        // ------------------------ DRAWING ZONE ------------------------
        // draw only each 16 second for optimization
        if(SDL_GetTicks()-renderTime>17)
        {
            // actulise the renderTime
            renderTime = SDL_GetTicks();
            // clear screen
            SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

            // draw the grid
            for (int i=-1000;i<1100;i+=100)
            {
                Point3D ptA(i,0,-1000);
                Point3D ptB(i,0,1000);

                Draw2D::drawSegment(screen,ptA,ptB);
                ptA = Point3D (-1000,0,i);
                ptB = Point3D (1000,0,i);

                Draw2D::drawSegment(screen,ptA,ptB);
            }

            Draw2D::drawCube(screen,cube);

            // origins
            Point3D ptOrigin1(0,0,0);
            Point3D ptOrigin2(100,0,0);
            Point3D ptOrigin3(0,0,100);
            Point3D ptOrigin4(0,100,0);
            Draw2D::drawSegment(screen,ptOrigin1,ptOrigin2,255,0,0);
            Draw2D::drawSegment(screen,ptOrigin1,ptOrigin3,0,255,0);
            Draw2D::drawSegment(screen,ptOrigin1,ptOrigin4,0,0,255);
        }

        fps++;
        if(SDL_GetTicks()-fpsTime>1000){
            char tampon [30] ;

            sprintf (tampon, "FPS : %d | WSAD move | ESC to quite", fps) ;
            SDL_WM_SetCaption(tampon,NULL);
            fpsTime = SDL_GetTicks();
            fps=0;
        }
        SDL_Flip(screen);
    } // end main loop

    // all is well ;)
    printf("Exited cleanly\n");
    char tampon [30] ;
//    sprintf (tampon, "Point3D Point3D::camera = Point3D(%f, %f, %f);\nPoint3D Point3D::viewerPos = Point3D(%f, %f, %f);\nPoint3D Point3D::theta = Point3D(%f, %f, %f);\n",
//                    Point3D::camera.x, Point3D::camera.y, Point3D::camera.z,
//                    Point3D::viewerPos.x, Point3D::viewerPos.y, Point3D::viewerPos.z,
//                    Point3D::theta.x, Point3D::theta.y, Point3D::theta.z) ;
    sprintf(tampon,"%f\n",Draw2D::far);
    printf(tampon);
    return 0;
}
