<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100

typedef struct Music {
	char artist[MAX_NAME];
	char title[MAX_NAME];
	float duration;
	struct Music *next;
	struct Music *prev;
} Music;

typedef struct Playlist {
	char name[MAX_NAME];
	Music *start;
	Music *end;
} Playlist;

Playlist* createPlaylist(const char *name) {
	Playlist *p = (Playlist*) malloc(sizeof(Playlist));

	if(!p) {
		printf("Erro ao alocar memoria\n");
		exit(1);
	}

	strcpy(p->name, name);

	p->start = NULL;
	p->end = NULL;

	return p;
}

Music* createMusic(const char *artist, const char *title, float duration) {
	Music *m = (Music*) malloc(sizeof(Music));

	if(!m) {
		printf("Erro ao alocar memoria.\n");
		exit(1);
	}

	strcpy(m->artist, artist);
	strcpy(m->title, title);
	m->duration = duration;
	m->next = NULL;
	m->prev = NULL;

	return m;
}

void insertAtBeginning(Playlist *p, const char *artist, const char *title, float duration) {
	Music *new = createMusic(artist, title, duration);

	if(p->start == NULL) {
		p->start = p->end = new;
	} else {
		new->next = p->start;
		p->start->prev = new;
		p->start = new;
	}
}

void insertAtEnd(Playlist *p, const char *artist, const char *title, float duration) {
	Music *new = createMusic(artist, title, duration);

	if(p->end == NULL) {
		p->start = p->end = new;
	} else {
		p->end->next = new;
		new->prev = p->end;
		p->end = new;
	}
}

void removeFromBeginning(Playlist *p) {
	if(p->start == NULL) {
		printf("Playlist %s esta vazia.\n", p->name);
		return;
	}

	Music *temp = p->start;

	printf("Removida: %s - %s\n", temp->artist, temp->title);
	p->start = temp->next;

	if(p->start) {
		p->start->prev = NULL;
	} else {
		p->end = NULL;
	}

	free(temp);
}

void removeByTitle(Playlist *p, const char *title) {
	if(p->start == NULL) {
		printf("Playlist %s esta vazia.\n", p->name);
		return;
	}

	Music *current = p->start;

	while(current  != NULL && strcmp(current ->title, title) != 0) {
		current = current ->next;
	}

	if(current == NULL) {
		printf("Musica %s nao encontrada.\n", title);
		return;
	}

	printf("Removida: %s - %s\n", current->artist, current->title);

	if(current->prev) {
		current->prev->next = current->next;
	} else {
		p->start = current->next;
	}

	if(current->next) {
		current->next->prev = current->prev;
	} else {
		p->end = current->prev;
	}

	free(current);
}

void showPlaylist(Playlist *p) {
    if (p->start == NULL) {
        printf("Playlist %s vazia.\n", p->name);
        return;
    }

    printf("\n=== Playlist: %s ===\n", p->name);
    Music *current = p->start;

    while(current != NULL) {
        if(current == p->start) {
            printf("[NEXT] ");
        }

        printf("%s - %s (%.2f min)\n", current->artist, current->title, current->duration);
        current = current->next;
    }

    printf("=========================\n");
}


void freePlaylist(Playlist *p) {
	Music *current = p->start;

	while(current != NULL) {
		Music *next = current->next;
		free(current);
		current = next;
	}

	free(p);
}

int main() {
	char namePlaylist[MAX_NAME];

	printf("Informe o nome da playlist: ");
	fgets(namePlaylist, MAX_NAME, stdin);
	namePlaylist[strcspn(namePlaylist, "\n")] = '\0';

	Playlist *playlist = createPlaylist(namePlaylist);

	int opt;
	char artist[MAX_NAME], title[MAX_NAME];
	float duration;

	do {
	    printf("\n===== %s =====\n", namePlaylist);
		printf("1. Inserir musica no inicio\n");
		printf("2. Inserir musica no fim\n");
		printf("3. Remover musica da vez (primeira)\n");
		printf("4. Remover musica pelo titulo\n");
		printf("5. Exibir playlist\n");
		printf("0. Sair\n");
		printf("Escolha: ");
		scanf("%d", &opt);
		getchar();

		switch(opt) {
		case 1:
			printf("Artista: ");
			fgets(artist, MAX_NAME, stdin);
			artist[strcspn(artist, "\n")] = '\0';
			
			printf("Titulo (musica): ");
			fgets(title, MAX_NAME, stdin);
			title[strcspn(title, "\n")] = '\0';

			printf("Duracao (minutos): ");
			scanf("%f", &duration);
			getchar();

			insertAtBeginning(playlist, artist, title, duration);
			break;
		case 2:
			printf("Artista: ");
			fgets(artist, MAX_NAME, stdin);
			artist[strcspn(artist, "\n")] = '\0';
			
			printf("Titulo (musica): ");
			fgets(title, MAX_NAME, stdin);
			title[strcspn(title, "\n")] = '\0';

			printf("Duracao (minutos): ");
			scanf("%f", &duration);
			getchar();

			insertAtEnd(playlist, artist, title, duration);
			break;
		case 3:
			removeFromBeginning(playlist);
			break;
		case 4:
			printf("Digite o titulo da musica para remover: ");
			fgets(title, MAX_NAME, stdin);
			title[strcspn(title, "\n")] = '\0';

			removeByTitle(playlist, title);
			break;
		case 5:
			showPlaylist(playlist);
			break;
		case 0:
			freePlaylist(playlist);
			printf("Saiu da Playlist: %s\n", namePlaylist);
			break;
		default:
			printf("Opcao invalida.\n");
		}
	} while(opt != 0);

	
	return 0;
}
=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100

typedef struct Music {
	char artist[MAX_NAME];
	char title[MAX_NAME];
	float duration;
	struct Music *next;
	struct Music *prev;
} Music;

typedef struct Playlist {
	char name[MAX_NAME];
	Music *start;
	Music *end;
} Playlist;


Playlist* createPlaylist(const char *name) {
	Playlist *p = (Playlist*) malloc(sizeof(Playlist));

	if(!p) {
		printf("Erro ao alocar memoria\n");
		exit(1);
	}

	strcpy(p->name, name);

	p->start = NULL;
	p->end = NULL;

	return p;
}

Music* createMusic(const char *artist, const char *title, float duration) {
	Music *m = (Music*) malloc(sizeof(Music));

	if(!m) {
		printf("Erro ao alocar memoria.\n");
		exit(1);
	}

	strcpy(m->artist, artist);
	strcpy(m->title, title);
	m->duration = duration;
	m->next = NULL;
	m->prev = NULL;

	return m;
}

void insertAtBeginning(Playlist *p, const char *artist, const char *title, float duration) {
	Music *new = createMusic(artist, title, duration);

	if(p->start == NULL) {
		p->start = p->end = new;
	} else {
		new->next = p->start;
		p->start->prev = new;
		p->start = new;
	}
}

void insertAtEnd(Playlist *p, const char *artist, const char *title, float duration) {
	Music *new = createMusic(artist, title, duration);

	if(p->end == NULL) {
		p->start = p->end = new;
	} else {
		p->end->next = new;
		new->prev = p->end;
		p->end = new;
	}
}

void removeFromBeginning(Playlist *p) {
	if(p->start == NULL) {
		printf("Playlist %s esta vazia.\n", p->name);
		return;
	}

	Music *temp = p->start;

	printf("Removida: %s - %s\n", temp->artist, temp->title);
	p->start = temp->next;

	if(p->start) {
		p->start->prev = NULL;
	} else {
		p->end = NULL;
	}

	free(temp);
}

void removeByTitle(Playlist *p, const char *title) {
	if(p->start == NULL) {
		printf("Playlist %s esta vazia.\n", p->name);
		return;
	}

	Music *current = p->start;

	while(current  != NULL && strcmp(current ->title, title) != 0) {
		current = current ->next;
	}

	if(current == NULL) {
		printf("Musica %s nao encontrada.\n", title);
		return;
	}

	printf("Removida: %s - %s\n", current->artist, current->title);

	if(current->prev) {
		current->prev->next = current->next;
	} else {
		p->start = current->next;
	}

	if(current->next) {
		current->next->prev = current->prev;
	} else {
		p->end = current->prev;
	}

	free(current);
}

void showPlaylist(Playlist *p) {
    if (p->start == NULL) {
        printf("Playlist %s vazia.\n", p->name);
        return;
    }

    printf("\n=== Playlist: %s ===\n", p->name);
    Music *current = p->start;

    while(current != NULL) {
        if(current == p->start) {
            printf("[NEXT] ");
        }

        printf("%s - %s (%.2f min)\n", current->artist, current->title, current->duration);
        current = current->next;
    }

    printf("=========================\n");
}


void freePlaylist(Playlist *p) {
	Music *current = p->start;

	while(current != NULL) {
		Music *next = current->next;
		free(current);
		current = next;
	}

	free(p);
}

int main() {
	char namePlaylist[MAX_NAME];

	printf("Informe o nome da playlist: ");
	fgets(namePlaylist, MAX_NAME, stdin);
	namePlaylist[strcspn(namePlaylist, "\n")] = '\0';

	Playlist *playlist = createPlaylist(namePlaylist);

	int opt;
	char artist[MAX_NAME], title[MAX_NAME];
	float duration;

	do {
	    printf("\n===== %s =====\n", namePlaylist);
		printf("1. Inserir musica no inicio\n");
		printf("2. Inserir musica no fim\n");
		printf("3. Remover musica da vez (primeira)\n");
		printf("4. Remover musica pelo titulo\n");
		printf("5. Exibir playlist\n");
		printf("0. Sair\n");
		printf("Escolha: ");
		scanf("%d", &opt);
		getchar();

		switch(opt) {
		case 1:
			printf("Artista: ");
			fgets(artist, MAX_NAME, stdin);
			artist[strcspn(artist, "\n")] = '\0';
			
			printf("Titulo (musica): ");
			fgets(title, MAX_NAME, stdin);
			title[strcspn(title, "\n")] = '\0';

			printf("Duracao (minutos): ");
			scanf("%f", &duration);
			getchar();

			insertAtBeginning(playlist, artist, title, duration);
			break;
		case 2:
			printf("Artista: ");
			fgets(artist, MAX_NAME, stdin);
			artist[strcspn(artist, "\n")] = '\0';
			
			printf("Titulo (musica): ");
			fgets(title, MAX_NAME, stdin);
			title[strcspn(title, "\n")] = '\0';

			printf("Duracao (minutos): ");
			scanf("%f", &duration);
			getchar();

			insertAtEnd(playlist, artist, title, duration);
			break;
		case 3:
			removeFromBeginning(playlist);
			break;
		case 4:
			printf("Digite o titulo da musica para remover: ");
			fgets(title, MAX_NAME, stdin);
			title[strcspn(title, "\n")] = '\0';

			removeByTitle(playlist, title);
			break;
		case 5:
			showPlaylist(playlist);
			break;
		case 0:
			freePlaylist(playlist);
			printf("Saiu da Playlist: %s\n", namePlaylist);
			break;
		default:
			printf("Opcao invalida.\n");
		}
	} while(opt != 0);

	return 0;
}
>>>>>>> a1add38c2a5e4cc56e7769d7244d007935f0a95a
