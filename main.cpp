/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Mohini
 *
 * Created on 3 de Junho de 2018, 14:30
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include <memory>

class Texture
{
    public:
        SDL_Texture *textura;
        SDL_Rect posicao;
       

};
class Data_center: public Texture
{
public:
    SDL_Window *janela = NULL;
    SDL_Renderer *render = NULL;
    int SCREEN_HEIGHT = 640;
    int SCREEN_WIDTH = 920;
    Texture Background, Galinha;

};
class Func_teste: public Data_center
{
public:
    bool initvideo();
    bool Eventos(bool * auxsair);
    bool LoadTextureMais(Texture *ModeloMais, char * caminho);
    bool LoadMedia();
    void close();
    bool gameloop();
};

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) 
{
    Func_teste quadrado;
    if(quadrado.initvideo()){
        if(quadrado.LoadMedia())
        {
            quadrado.gameloop();
        }
    }
    SDL_Delay(2000);
    return 0;
}

bool Func_teste::initvideo()
{
    bool ok = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error ao iniciar a sdl! ");
        ok = false;
    } else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Filtragem de textura nÃ£o ativada");
        }
        janela = SDL_CreateWindow(" FreeWay MVP ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (janela == NULL) {
            printf("Error ao abrir SDL!");
            ok = false;
        } else {
            render = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (render == NULL) {
                printf("Erro ao renderizar a tela");
    
                ok = false;
            } else {
                SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
                int ImagFg = IMG_INIT_PNG;
                if (!(IMG_Init(ImagFg) & ImagFg)) {
                    printf("Biblioteca SDL_image esta bugando ao inicializar");
                    ok = false;
                }
            }
        }
    }
    return ok;
}

bool Func_teste::LoadTextureMais(Texture *ModeloMais, char * caminho) {
    SDL_Texture *newtexture;
    SDL_Surface *image = IMG_Load(caminho);
    if (image == NULL) {
        printf("\nNao foi possivel carregar a imagem definida\n");
    } else {
        SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 0, 0xFF, 0xFF));
        newtexture = SDL_CreateTextureFromSurface(render, image);
        if (newtexture == NULL) {
            printf("\n Nao foi possivel montar a textura da imagem na superficie\n");
        } else {
            ModeloMais->posicao.w = 0;
            ModeloMais->posicao.h = 0;
        }
        SDL_FreeSurface(image);
    }
    ModeloMais->textura = newtexture;
   
    return ModeloMais->textura != NULL;
}

bool Func_teste::Eventos(bool * auxsair) {
    bool OK = true;
    SDL_Event S;
   while (SDL_PollEvent(&S) != 0) 
   {
       if (S.type == SDL_QUIT)
       {
                *auxsair = true;
       }else if (S.type == SDL_KEYDOWN) 
       {
                switch (S.key.keysym.sym) {
                    /*case SDLK_LEFT:
                       Galinha.posicao.x -= 1;
                        return OK = true;
                    case SDLK_RIGHT:
                       Galinha.posicao.x += 2;
                        return OK = true;*/
                    case SDLK_DOWN:
                        Galinha.posicao.y += 2;
                       return OK = true;
                    case SDLK_UP:
                        Galinha.posicao.y -= 1;
                        return OK = true;
                    default:
                        return OK = true;
                        
                }
                        
       }else{return OK = true;}
           
           
            
        
    }
}

bool Func_teste::LoadMedia()
{
    bool ok = true;
    if(!LoadTextureMais(&Galinha,"galinha.png"))
    {
        ok = false;
    } 
    Galinha.posicao.w = SCREEN_WIDTH/6;
    Galinha.posicao.h = SCREEN_HEIGHT/6;
    Galinha.posicao.x = 245;
    Galinha.posicao.y = 560;

    return ok;
    
}

bool Func_teste::gameloop() {
    bool sair = false;
    while (!sair) {
        if(Eventos(&sair))
        {
        

      

        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderClear(render);
        SDL_RenderCopyEx(render, Galinha.textura, NULL, &Galinha.posicao, 0, NULL, SDL_FLIP_NONE);//printa a imagem da tela
        
        SDL_RenderPresent(render);
        }
    }

}


void Func_teste::close() {
    int i, j = 0;
    SDL_DestroyTexture(Galinha.textura);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(janela);
    janela = NULL;
    render = NULL;
   // Mix_FreeMusic (music);


    IMG_Quit();
    SDL_Quit();
}