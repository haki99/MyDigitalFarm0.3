#ifndef MEDIA_H_INCLUDED
#define MEDIA_H_INCLUDED

//!Mediac.c
//!Poziciokat kezelo fuggvenyek
void SrcPosition(int x, int y, int w, int h);
void DestPosition(int x, int y, int w, int h);

//!Szovegek texturava alakitasahoz hasznalt fuggveny
void szovegkiiras( char *szoveg, int x, int y, int w, int h );

//!Menu megnyito fuggvenyek
void LoadMenu();
void LoadPlayMenu();
void LoadOptions();
void LoadNewGameMenu();

//!Ingame texturak megjelenitese
void LoadGame(int fieldx, int fieldy);
void gui(char *jatekosnev, int nevhossz);

//!Ingame texturak valtoztatasa
void ultetes(int noveny, int x, int y);

//!Az escape gomb megnyomasakor megjeleno fuggveny
void openingamemenu();

#endif // MEDIA_H_INCLUDED
