#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 500
#define MAX_STAT 100
#define STAT_DECAY_RATE 0.5f

typedef enum {
    MOOD_HAPPY,
    MOOD_NEUTRAL,
    MOOD_SAD,
    MOOD_DEAD
} Mood;

typedef struct {
    float hunger;
    float happiness;
    float health;
    float energy;
    int age;
    bool is_sleeping;
    Mood mood;
} Tamagotchi;

typedef struct {
    SDL_Rect rect;
    SDL_Color color;
    SDL_Color hover_color;
    bool is_hovered;
} Button;

void draw_tamagotchi(SDL_Renderer* renderer, Tamagotchi* tama, int x, int y) {
    // Couleur du corps selon l'humeur
    SDL_Color body_color = {100, 200, 255, 255};
    if (tama->mood == MOOD_HAPPY) body_color = (SDL_Color){100, 255, 150, 255};
    else if (tama->mood == MOOD_SAD) body_color = (SDL_Color){150, 150, 200, 255};
    else if (tama->mood == MOOD_DEAD) body_color = (SDL_Color){100, 100, 100, 255};
    
    SDL_SetRenderDrawColor(renderer, body_color.r, body_color.g, body_color.b, 255);
    
    // Corps principal (cercle)
    for (int dy = -40; dy <= 40; dy++) {
        int width = (int)(sqrt(1600 - dy * dy));
        SDL_Rect rect = {x - width, y + dy, width * 2, 2};
        SDL_RenderFillRect(renderer, &rect);
    }
    
    if (tama->mood != MOOD_DEAD) {
        // Yeux
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        if (tama->is_sleeping) {
            // Yeux fermés
            for (int i = 0; i < 3; i++) {
                SDL_RenderDrawLine(renderer, x - 20, y - 10 + i, x - 10, y - 10 + i);
                SDL_RenderDrawLine(renderer, x + 10, y - 10 + i, x + 20, y - 10 + i);
            }
            
            // "Z" de sommeil
            SDL_SetRenderDrawColor(renderer, 150, 150, 255, 255);
            SDL_RenderDrawLine(renderer, x + 50, y - 40, x + 60, y - 40);
            SDL_RenderDrawLine(renderer, x + 60, y - 40, x + 50, y - 30);
            SDL_RenderDrawLine(renderer, x + 50, y - 30, x + 60, y - 30);
        } else {
            // Yeux ouverts
            for (int dy = -5; dy <= 5; dy++) {
                int width = (int)(sqrt(25 - dy * dy));
                SDL_RenderDrawLine(renderer, x - 20 - width, y - 10 + dy, x - 20 + width, y - 10 + dy);
                SDL_RenderDrawLine(renderer, x + 20 - width, y - 10 + dy, x + 20 + width, y - 10 + dy);
            }
        }
        
        // Bouche selon l'humeur
        if (tama->mood == MOOD_HAPPY) {
            // Sourire
            for (int i = 0; i < 20; i++) {
                int dy = (int)(5 * sin(i * 3.14159f / 20));
                SDL_RenderDrawPoint(renderer, x - 10 + i, y + 20 + dy);
                SDL_RenderDrawPoint(renderer, x - 10 + i, y + 21 + dy);
            }
        } else if (tama->mood == MOOD_SAD) {
            // Bouche triste
            for (int i = 0; i < 20; i++) {
                int dy = -(int)(5 * sin(i * 3.14159f / 20));
                SDL_RenderDrawPoint(renderer, x - 10 + i, y + 25 + dy);
                SDL_RenderDrawPoint(renderer, x - 10 + i, y + 26 + dy);
            }
        } else {
            // Bouche neutre
            for (int i = 0; i < 2; i++) {
                SDL_RenderDrawLine(renderer, x - 10, y + 20 + i, x + 10, y + 20 + i);
            }
        }
    } else {
        // Yeux en X (mort)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for (int i = 0; i < 3; i++) {
            SDL_RenderDrawLine(renderer, x - 25 + i, y - 15, x - 15 + i, y - 5);
            SDL_RenderDrawLine(renderer, x - 15 + i, y - 15, x - 25 + i, y - 5);
            SDL_RenderDrawLine(renderer, x + 15 + i, y - 15, x + 25 + i, y - 5);
            SDL_RenderDrawLine(renderer, x + 25 + i, y - 15, x + 15 + i, y - 5);
        }
    }
}

void draw_stat_bar(SDL_Renderer* renderer, float value, int x, int y, int width, int height, SDL_Color color) {
    // Fond de la barre
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_Rect bg = {x, y, width, height};
    SDL_RenderFillRect(renderer, &bg);
    
    // Barre de valeur avec dégradé
    int bar_width = (int)(width * value / MAX_STAT);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_Rect bar = {x, y, bar_width, height};
    SDL_RenderFillRect(renderer, &bar);
    
    // Bordure
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &bg);
}

void draw_icon_food(SDL_Renderer* renderer, int x, int y) {
    // Hamburger simplifié
    SDL_SetRenderDrawColor(renderer, 200, 150, 100, 255);
    SDL_Rect bun_top = {x + 5, y + 5, 20, 5};
    SDL_RenderFillRect(renderer, &bun_top);
    
    SDL_SetRenderDrawColor(renderer, 150, 50, 50, 255);
    SDL_Rect meat = {x + 3, y + 12, 24, 6};
    SDL_RenderFillRect(renderer, &meat);
    
    SDL_SetRenderDrawColor(renderer, 200, 150, 100, 255);
    SDL_Rect bun_bottom = {x + 5, y + 20, 20, 5};
    SDL_RenderFillRect(renderer, &bun_bottom);
}

void draw_icon_play(SDL_Renderer* renderer, int x, int y) {
    // Ballon
    SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
    for (int dy = -10; dy <= 10; dy++) {
        int width = (int)(sqrt(100 - dy * dy));
        SDL_Rect rect = {x + 15 - width, y + 15 + dy, width * 2, 2};
        SDL_RenderFillRect(renderer, &rect);
    }
}

void draw_icon_heal(SDL_Renderer* renderer, int x, int y) {
    // Croix médicale
    SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
    SDL_Rect vert = {x + 12, y + 5, 6, 20};
    SDL_RenderFillRect(renderer, &vert);
    SDL_Rect horiz = {x + 5, y + 12, 20, 6};
    SDL_RenderFillRect(renderer, &horiz);
}

void draw_icon_sleep(SDL_Renderer* renderer, int x, int y) {
    // Lune
    SDL_SetRenderDrawColor(renderer, 255, 255, 150, 255);
    for (int dy = -10; dy <= 10; dy++) {
        int width = (int)(sqrt(100 - dy * dy));
        SDL_Rect rect = {x + 10 - width, y + 15 + dy, width * 2, 2};
        SDL_RenderFillRect(renderer, &rect);
    }
    // Occulter partie droite
    SDL_SetRenderDrawColor(renderer, 30, 30, 50, 255);
    for (int dy = -8; dy <= 8; dy++) {
        int width = (int)(sqrt(64 - dy * dy));
        SDL_Rect rect = {x + 15 - width, y + 15 + dy, width * 2, 2};
        SDL_RenderFillRect(renderer, &rect);
    }
}

void update_mood(Tamagotchi* tama) {
    if (tama->health <= 0) {
        tama->mood = MOOD_DEAD;
        return;
    }
    
    float avg = (tama->hunger + tama->happiness + tama->health + tama->energy) / 4.0f;
    
    if (avg >= 70) tama->mood = MOOD_HAPPY;
    else if (avg >= 40) tama->mood = MOOD_NEUTRAL;
    else tama->mood = MOOD_SAD;
}

void feed(Tamagotchi* tama) {
    if (tama->mood == MOOD_DEAD) return;
    tama->hunger = fminf(tama->hunger + 25, MAX_STAT);
    tama->health = fminf(tama->health + 5, MAX_STAT);
}

void play(Tamagotchi* tama) {
    if (tama->mood == MOOD_DEAD || tama->is_sleeping) return;
    tama->happiness = fminf(tama->happiness + 30, MAX_STAT);
    tama->energy = fmaxf(tama->energy - 10, 0);
}

void heal(Tamagotchi* tama) {
    if (tama->mood == MOOD_DEAD) return;
    tama->health = fminf(tama->health + 40, MAX_STAT);
}

void toggle_sleep(Tamagotchi* tama) {
    if (tama->mood == MOOD_DEAD) return;
    tama->is_sleeping = !tama->is_sleeping;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        return 1;
    }
    
    SDL_Window* window = SDL_CreateWindow(
        "Mon Tamagotchi",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    // Initialisation du Tamagotchi
    Tamagotchi tama = {
        .hunger = 80,
        .happiness = 80,
        .health = 100,
        .energy = 80,
        .age = 0,
        .is_sleeping = false,
        .mood = MOOD_HAPPY
    };
    
    // Boutons
    Button buttons[4] = {
        {{40, 360, 70, 70}, {100, 200, 100, 255}, {120, 220, 120, 255}, false},  // Nourrir
        {{130, 360, 70, 70}, {255, 200, 100, 255}, {255, 220, 120, 255}, false}, // Jouer
        {{220, 360, 70, 70}, {200, 100, 255, 255}, {220, 120, 255, 255}, false}, // Soigner
        {{310, 360, 70, 70}, {100, 150, 255, 255}, {120, 170, 255, 255}, false}  // Dormir
    };
    
    bool running = true;
    SDL_Event event;
    Uint64 last_time = SDL_GetPerformanceCounter();
    float time_accumulator = 0;
    
    int mouse_x = 0, mouse_y = 0;
    
    while (running) {
        Uint64 current_time = SDL_GetPerformanceCounter();
        float delta_time = (float)(current_time - last_time) / SDL_GetPerformanceFrequency();
        last_time = current_time;
        
        time_accumulator += delta_time;
        
        // Mise à jour des stats
        if (time_accumulator >= 1.0f && tama.mood != MOOD_DEAD) {
            time_accumulator = 0;
            tama.age++;
            
            if (!tama.is_sleeping) {
                tama.hunger = fmaxf(tama.hunger - STAT_DECAY_RATE, 0);
                tama.happiness = fmaxf(tama.happiness - STAT_DECAY_RATE * 0.7f, 0);
                tama.energy = fmaxf(tama.energy - STAT_DECAY_RATE * 0.3f, 0);
                
                if (tama.hunger < 20 || tama.happiness < 20 || tama.energy < 10) {
                    tama.health = fmaxf(tama.health - 1.0f, 0);
                }
            } else {
                tama.energy = fminf(tama.energy + 2.0f, MAX_STAT);
            }
            
            update_mood(&tama);
        }
        
        // Événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_MOUSEMOTION) {
                mouse_x = event.motion.x;
                mouse_y = event.motion.y;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mx = event.button.x;
                int my = event.button.y;
                
                for (int i = 0; i < 4; i++) {
                    if (mx >= buttons[i].rect.x && mx <= buttons[i].rect.x + buttons[i].rect.w &&
                        my >= buttons[i].rect.y && my <= buttons[i].rect.y + buttons[i].rect.h) {
                        if (i == 0) feed(&tama);
                        else if (i == 1) play(&tama);
                        else if (i == 2) heal(&tama);
                        else if (i == 3) toggle_sleep(&tama);
                    }
                }
            }
        }
        
        // Vérifier hover des boutons
        for (int i = 0; i < 4; i++) {
            buttons[i].is_hovered = (mouse_x >= buttons[i].rect.x && 
                                     mouse_x <= buttons[i].rect.x + buttons[i].rect.w &&
                                     mouse_y >= buttons[i].rect.y && 
                                     mouse_y <= buttons[i].rect.y + buttons[i].rect.h);
        }
        
        // Rendu
        SDL_SetRenderDrawColor(renderer, 30, 30, 50, 255);
        SDL_RenderClear(renderer);
        
        // Titre "TAMAGOTCHI"
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect title_bg = {100, 10, 200, 30};
        SDL_RenderDrawRect(renderer, &title_bg);
        
        // Dessiner le Tamagotchi
        draw_tamagotchi(renderer, &tama, WINDOW_WIDTH / 2, 140);
        
        // Barres de stats avec icônes
        int bar_y = 240;
        int bar_spacing = 35;
        
        // Faim (rouge/orange)
        draw_stat_bar(renderer, tama.hunger, 80, bar_y, 240, 20, (SDL_Color){255, 150, 100, 255});
        draw_icon_food(renderer, 40, bar_y - 5);
        
        // Bonheur (jaune)
        draw_stat_bar(renderer, tama.happiness, 80, bar_y + bar_spacing, 240, 20, (SDL_Color){255, 220, 100, 255});
        draw_icon_play(renderer, 40, bar_y + bar_spacing - 5);
        
        // Santé (vert)
        draw_stat_bar(renderer, tama.health, 80, bar_y + bar_spacing * 2, 240, 20, (SDL_Color){100, 255, 150, 255});
        draw_icon_heal(renderer, 40, bar_y + bar_spacing * 2 - 5);
        
        // Énergie (bleu)
        draw_stat_bar(renderer, tama.energy, 80, bar_y + bar_spacing * 3, 240, 20, (SDL_Color){150, 200, 255, 255});
        draw_icon_sleep(renderer, 40, bar_y + bar_spacing * 3 - 5);
        
        // Dessiner les boutons
        for (int i = 0; i < 4; i++) {
            SDL_Color color = buttons[i].is_hovered ? buttons[i].hover_color : buttons[i].color;
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
            SDL_RenderFillRect(renderer, &buttons[i].rect);
            
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &buttons[i].rect);
            
            // Dessiner icônes sur boutons
            if (i == 0) draw_icon_food(renderer, buttons[i].rect.x + 20, buttons[i].rect.y + 20);
            else if (i == 1) draw_icon_play(renderer, buttons[i].rect.x + 20, buttons[i].rect.y + 20);
            else if (i == 2) draw_icon_heal(renderer, buttons[i].rect.x + 20, buttons[i].rect.y + 20);
            else if (i == 3) draw_icon_sleep(renderer, buttons[i].rect.x + 20, buttons[i].rect.y + 20);
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}