
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<list>

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;


SDL_Texture *background,*character,*game_background,*pelotita_buena,*pelotita_mala,*gameover1;
SDL_Rect rect_background,rect_character,rect_pelotita;

void loopMenu();
void gameover(){
if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_SPACE)
                    loopMenu();
            }
            SDL_RenderCopy(renderer, gameover1, NULL, &rect_background);
            SDL_RenderPresent(renderer);
}
void loopJuego()
{
    list<float>pelotitas_x;
    pelotitas_x.push_back(0);
    pelotitas_x.push_back(100);
    pelotitas_x.push_back(200);
    pelotitas_x.push_back(300);
float sum=0;


//    bool isvisible = true;

    while(true)

    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                exit(0);
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_ESCAPE)
                    return;
            }
//            if(Event.type == SDL_MOUSEBUTTONDOWN)
//            {
//
//                    return;
//            }
            if(Event.type == SDL_MOUSEBUTTONDOWN)
            {
                int clickx,clicky;
                SDL_GetMouseState(&clickx,&clicky);
                std::cout<<clickx<<","<<clicky<<std::endl;
                for(list<float>::iterator i = pelotitas_x.begin(); i!=pelotitas_x.end(); i++)
                {
                    if(clickx<66+sum&&clickx>0+sum&&clicky<66+(*i)&&clicky>0+(*i))
                    {
                        pelotitas_x.erase(i);
                        i--;
                if(pelotitas_x.size()<1){
                gameover();
                }

                    }


                }
            }
        }

//        for(list<float>::iterator i = pelotitas_x.begin(); i!=pelotitas_x.end(); i++)
//        {
//            (*i)+=0.05;
//
//            if((*i)>=480)
//                (*i)=0;
//
//        }

        SDL_RenderCopy(renderer, game_background, NULL, &rect_background);
//        rect_pelotita.x=0;

//        SDL_RenderCopy(renderer,pelotita_mala, NULL, &rect_pelotita);
//        rect_pelotita.y=0;
//        SDL_RenderCopy(renderer,pelotita_mala, NULL, &rect_pelotita);
//        rect_pelotita.y=100;
//        SDL_RenderCopy(renderer,pelotita_mala, NULL, &rect_pelotita);
//        rect_pelotita.y=200;
//        rect_pelotita.y=300;
//        SDL_RenderCopy(renderer,pelotita_mala, NULL, &rect_pelotita);

sum+=0.05;
if(pelotitas_x.size()<4){
sum+= 0.04;
}if(pelotitas_x.size()<3){
sum+= 0.03;
}
if(pelotitas_x.size()<2){
sum+= 0.02;
}if(pelotitas_x.size()<=1){
sum+= 0.01;
}
rect_pelotita.x=sum;


if(sum>=480)
             sum=0;
 for(list<float>::iterator i = pelotitas_x.
        begin(); i!=pelotitas_x.end(); i++)
        {

            rect_pelotita.y=(*i);

            SDL_RenderCopy(renderer,pelotita_mala, NULL, &rect_pelotita);
//        SDL_RenderCopy(renderer, character, NULL, &rect_character);


        }

        SDL_RenderPresent(renderer);
    }

}
void loopMenu()
{
//Main Loop
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                exit(0);
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_d)
                    rect_character.x++;
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_w)
                    rect_character.y--;
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_s)
                    rect_character.y++;
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_a)
                    rect_character.x--;
            }
            if(rect_character.x>465||rect_character.y>215||rect_character.y<0||rect_character.x<0)
            {

                rect_character.x=0;
                rect_character.y=0;

            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_RETURN)
                    loopJuego();
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_ESCAPE)
                    loopMenu();
            }


        }

        SDL_RenderCopy(renderer, background, NULL, &rect_background);
//        SDL_RenderCopy(renderer, character, NULL, &rect_character);
        SDL_RenderPresent(renderer);
    }

}

int main( int argc, char* args[] )
{

//list<int>mi_lista;
//mi_lista.push_back(10);
//mi_lista.push_back(20);
//mi_lista.push_back(30);
//
//list<int>::iterator i=mi_lista.begin();
//for(int x = 0;x<mi_lista.size();x++)
//{
//cout<<(*i)<<endl;
//i++;
//}



    // Init SDL Corre todo el SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 500/*WIDTH*/, 400/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
//    SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

//    Init textures Carga Texturas
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"PelotitasSDL/menu.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = w;
    rect_background.h = h;

    character = IMG_LoadTexture(renderer, "personaje.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character.x = 0;
    rect_character.y = 0;
    rect_character.w = w;
    rect_character.h = h;
    gameover1= IMG_LoadTexture(renderer,"PelotitasSDL/game_over.png");
    game_background = IMG_LoadTexture(renderer,"PelotitasSDL/game_background.png");
    pelotita_buena= IMG_LoadTexture(renderer,"PelotitasSDL/pelotita_buena.png");
    pelotita_mala = IMG_LoadTexture(renderer,"PelotitasSDL/pelotita_mala.png");
    rect_pelotita.x=0;
    rect_pelotita.y=0;

    SDL_QueryTexture(pelotita_mala, NULL, NULL, &rect_pelotita.w, &rect_pelotita.h);

    loopMenu();


    return 0;
}
