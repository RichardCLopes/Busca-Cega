#include<stdio.h>
#include<stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct caminho No;
typedef struct ordem   Notwo;
struct caminho{
int x, y, custo;
int antesx, antesy;
struct caminho *prox;
};

struct ordem{
int cx, cy;
struct ordem *prox;
};

//INSERINDO RAIZ
void insereRaiz(No **pLista, int x, int y)
{
struct caminho *aux;
aux=(No *)malloc(sizeof(No));
aux->x=x;
aux->y=y;
aux->custo=0;
aux->antesx=x;
aux->antesy=y;
aux->prox=NULL;
*pLista=aux;
}
//-------------------------------------

//INSERE PRIMEIRO NO NA LST
void insereLstfim(Notwo **pLst, int x, int y)
{
if(*pLst==NULL)
{
*pLst=(Notwo *)malloc(sizeof(Notwo));
(*pLst)->cx=x;
(*pLst)->cy=y;
(*pLst)->prox=NULL;
}
else
{
Notwo *aux3=*pLst;
*pLst=(Notwo *)malloc(sizeof(Notwo));
(*pLst)->cx=x;
(*pLst)->cy=y;
(*pLst)->cx=x;
(*pLst)->prox=aux3;
}
}

//INSERE NÓ NA LISTA
void insereLista(No **pLista, int x, int y, int ax, int ay, int custo)
{
if(*pLista==NULL)
{
*pLista=(No *)malloc(sizeof(No));
(*pLista)->x=x;
(*pLista)->y=y;
(*pLista)->antesx=ax;
(*pLista)->antesy=ay;
(*pLista)->custo=custo;
(*pLista)->prox=NULL;
}
else
{
insereLista(&(*pLista)->prox, x, y, ax, ay, custo);
}
}
//FIM INSERE NÓ ------------

//VERIFICA SE NÓ EXISTE
int verifica(No **pLista, int x, int y)
{
if(*pLista==NULL)
{
return -1;
}
else
{
if((*pLista)->x==x && (*pLista)->y==y)
{
return 1;
}
else
{
verifica(&(*pLista)->prox, x, y);
}
}
}
//FIM DO VERIFICA

//ONDE ESTAMOS X
int ondeEstamosx(No *Lista, int casa)
{
if(casa==0)
{
return Lista->x;
}
else
{
ondeEstamosx(Lista->prox, casa-1);
}
}
//FIM DO ONDE ESTAMOS X

//ONDE ESTAMOS Y
int ondeEstamosy(No *Lista, int casa)
{
if(casa==0)
{
return Lista->y;
}
else
{
ondeEstamosy(Lista->prox, casa-1);
}
}
//FIM DO ONDE ESTAMOS X

//EXPANDE NORTE
void expandeNorte(No **pLista, int x, int y, int custo)
{
int resp, auxx;
auxx=x;
auxx=auxx-1;
resp=verifica(&(*pLista), auxx, y);
if(auxx>=0 && resp==-1)
{
insereLista(&(*pLista), auxx, y, x, y, custo);
}
}
//FIM EXPANDE NORTE-------------

//EXPANDE LESTE
void expandeLeste(No **pLista, int x, int y, int custo)
{
int resp, auxy;
auxy=y;
auxy=auxy+1;
resp=verifica(&(*pLista), x, auxy);
if(auxy<=41 && resp==-1)
{
insereLista(&(*pLista), x, auxy, x, y, custo);
}
}
//FIM EXPANDE LESTE-------------

//EXPANDE SUL
void expandeSul(No **pLista, int x, int y, int custo)
{
int resp, auxx;
auxx=x;
auxx=auxx+1;
resp=verifica(&(*pLista), auxx, y);
if(auxx<=41 && resp==-1)
{
insereLista(&(*pLista), auxx, y, x, y, custo);
}
}
//FIM EXPANDE SUL-------------

//EXPANDE OESTE
void expandeOeste(No **pLista, int x, int y, int custo)
{
int resp, auxy;
auxy=y;
auxy=auxy-1;
resp=verifica(&(*pLista), x, auxy);
if(auxy>=0 && resp==-1)
{
insereLista(&(*pLista), x, auxy, x, y, custo);
}
}
//FIM EXPANDE OESTE-------------

//ACHA ANTERIOR X
int achAnteriorx(No *Lista, int x, int y)
{
if(x==Lista->x && y==Lista->y)
{
return Lista->antesx;
}
else{
achAnteriorx(Lista->prox, x, y);
}
}
//--------------------------------

//ACHA ANTERIOR Y
int achAnteriory(No *Lista, int x, int y)
{
if(x==Lista->x && y==Lista->y)
{
return Lista->antesy;
}
else{
achAnteriory(Lista->prox, x, y);
}
}
//--------------------------------

//INSERE X/Y NA LST
void insereLstxy(Notwo **pLst, int i, int j)
{
if(*pLst==NULL)
{
*pLst=(Notwo *)malloc(sizeof(Notwo));
(*pLst)->cx=i;
(*pLst)->cy=j;
(*pLst)->prox=NULL;
}
else{
Notwo *auxi=*pLst;
*pLst=(Notwo *)malloc(sizeof(Notwo));
(*pLst)->cx=i;
(*pLst)->cy=j;
(*pLst)->prox=auxi;
}
}
//-------------------------------

//PRINTA A ORDEM DO CAMINHO
void printAll(Notwo *Lst)
{
if(Lst==NULL)
{
printf("\n");
}
else{
printf("%d-%d ->\n", Lst->cx, Lst->cy);
printAll(Lst->prox);
}
}
//---------------------------------------------

//FUNÇAO QUE RETORNA CUSTO NA POSIÇAO X/Y
int custoXy(No *Lista, int x, int y)
{
if(x==Lista->x && y==Lista->y)
{
return Lista->custo;
}
else{
custoXy(Lista->prox, x, y);
}
}
//----------------------------------------

//EXISTE X/Y NO CAMINHO
int existeXy(Notwo *Lst, int x, int y)
{
if(Lst==NULL)
{
return -1;
}
else
{
if(x==Lst->cx && y==Lst->cy)
{
return 1;
}
else{
existeXy(Lst->prox, x, y);
}
}
}
//---------------------

//=============================MAIN======================================
int main () {
No *Lista;
Notwo *Lst;
Lista=NULL;
Lst=NULL;
int map[42][42], origemx, origemy, destinox, destinoy, i, j, custo, casa;
int auxdi, auxdj, custotal, existe;
casa=0;
custotal=0;

//RECEBIMENTO DOS DADOS DO ARQUIVO
scanf("%d,%d", &origemx, &origemy);
scanf("%d,%d", &destinox, &destinoy);
for(i=0;i<42;i++){
	for(j=0;j<42;j++){
		scanf("%d,", &map[i][j]);
	}
}
//FIM DA INSERÇÃO

//PRINT DO MAPA NO TERMINAL
printf(ANSI_COLOR_RED     "%c Fogo\t"     ANSI_COLOR_RESET, 254);
printf(ANSI_COLOR_GREEN   "%c Plano\t"   ANSI_COLOR_RESET, 254);
printf(ANSI_COLOR_MAGENTA  "%c Montanhoso\t"  ANSI_COLOR_RESET, 254);
printf(ANSI_COLOR_BLUE    "%c Pantano\n\n"    ANSI_COLOR_RESET, 254);

for(i=0;i<42;i++){
	for(j=0;j<42;j++){
		if(map[i][j]==1){
		printf(ANSI_COLOR_GREEN   "%c "   ANSI_COLOR_RESET, 254);
		}
		if(map[i][j]==2){
		printf(ANSI_COLOR_MAGENTA   "%c "   ANSI_COLOR_RESET, 254);
		}
		if(map[i][j]==3){
		printf(ANSI_COLOR_BLUE   "%c "   ANSI_COLOR_RESET, 254);
		}
		if(map[i][j]==4){
		printf(ANSI_COLOR_RED   "%c "   ANSI_COLOR_RESET, 254);
		}
	}
printf("\n");
}

//FIM DO PRINT DO MAPA

//CHAMA FUNÇÃO INSERE RAIZ
insereRaiz(&Lista, origemx, origemy);
//-----------------------------------

i=origemx;
j=origemy;
printf("\n\t\tOrdem das Expansoes (linha-coluna)\n\n");
printf("Terreno\t\t\tNorte\t\tLeste\t\tSul\t\tOeste\n");

//GERANDO EXPANSAO ATÉ CHEGAR AO DESTINO
while(destinox!=i || destinoy!=j)
{
i=ondeEstamosx(Lista, casa);
j=ondeEstamosy(Lista, casa);
casa=casa+1;

//PRINT DAS EXPANSOES E SEUS VIZINHOS
if(i>=1 && i<=40 && j>=1 && j<=40)
{
printf("%d-%d\t\t\t%d-%d\t\t%d-%d\t\t%d-%d\t\t%d-%d\t\t\n", i, j, i-1, j, i, j+1, i+1, j, i, j-1);
}
else{
if(i==0 && j==0)
{
printf("%d-%d\t\t\t\t\t%d-%d\t\t%d-%d\t\t\n", i, j, i, j+1, i+1, j);
}
if(i==0 && j!=0 && j!=41)
{
printf("%d-%d\t\t\t\t\t%d-%d\t\t%d-%d\t\t%d-%d\n", i, j, i, j+1, i+1, j, i, j-1);
}
if(i==0 && j==41)
{
printf("%d-%d\t\t\t\t\t\t\t%d-%d\t\t%d-%d\n", i, j, i+1, j, i, j-1);
}
if(i!=0 && i!=41 && j==0)
{
printf("%d-%d\t\t\t%d-%d\t\t%d-%d\t\t%d-%d\n", i, j, i-1, j, i, j+1, i+1, j);
}
if(i==41 && j!=41 && j!=0)
{
printf("%d-%d\t\t\t%d-%d\t\t%d-%d\t\t\t\t%d-%d\n", i, j, i-1, j, i, j+1, i, j-1);
}
if(i==41 && j==0)
{
printf("%d-%d\t\t\t%d-%d\t\t%d-%d\n", i, j, i-1, j, i, j+1);
}
if(i==41 && j==41)
{
printf("%d-%d\t\t\t%d-%d\t\t\t\t\t\t%d-%d\n", i, j, i-1, j, i, j-1);
}
if(i>=1 && i<=40 && j==41)
{
printf("%d-%d\t\t\t%d-%d\t\t\t\t%d-%d\t\t%d-%d\n", i, j, i-1, j, i+1, j, i, j-1);
}
}
//--------------------------------------------------------------------------------------

//COLOCANDO CUSTO REAL NA VARIAVEL
if(map[i][j]==1){
custo=1;
}
if(map[i][j]==2){
custo=5;
}
if(map[i][j]==3){
custo=10;
}
if(map[i][j]==4){
custo=15;
}
//-------------------------------

//CHAMA EXPANDE NORTE
expandeNorte(&Lista, i, j, custo);
//CHAMA EXPANDE LESTE
expandeLeste(&Lista, i, j, custo);
//CHAMA EXPANDE SUL
expandeSul(&Lista, i, j, custo);
//CHAMA EXPANDE OESTE
expandeOeste(&Lista, i, j, custo);
}

printf("\n\nTotal de expansoes: %d\n\n", casa);

//FAZENDO CAMINHO QUE O ROBO PERCORREU E PRINT
i=destinox;
j=destinoy;
insereLstfim(&Lst, i, j);
while(i!=origemx || j!=origemy)
{
auxdi=achAnteriorx(Lista, i, j);
auxdj=achAnteriory(Lista, i, j);

insereLstxy(&Lst, auxdi, auxdj);

custotal=custoXy(Lista, i, j)+custotal;

i=auxdi;
j=auxdj;
}

printf("\nCaminho percorrido da origem ate destino:\n");
printAll(Lst);
printf("Custo do percurso:  %d\n\n", custotal);
//---------------------------------------------------------

//PRINT DO MAPA NO TERMINAL COM ROBO
printf(ANSI_COLOR_RED     "%c Fogo\t"     ANSI_COLOR_RESET, 254);
printf(ANSI_COLOR_GREEN   "%c Plano\t"   ANSI_COLOR_RESET, 254);
printf(ANSI_COLOR_MAGENTA  "%c Montanhoso\t"  ANSI_COLOR_RESET, 254);
printf(ANSI_COLOR_BLUE    "%c Pantano\t"    ANSI_COLOR_RESET, 254);
printf(ANSI_COLOR_YELLOW    "%c ROBO\n\n"    ANSI_COLOR_RESET, 254);

for(i=0;i<42;i++){
	for(j=0;j<42;j++){
existe=existeXy(Lst, i, j);
if(existe==1)
{
printf(ANSI_COLOR_YELLOW   "%c "   ANSI_COLOR_RESET, 254);
}
else{
		if(map[i][j]==1){
		printf(ANSI_COLOR_GREEN   "%c "   ANSI_COLOR_RESET, 254);
		}
		if(map[i][j]==2){
		printf(ANSI_COLOR_MAGENTA   "%c "   ANSI_COLOR_RESET, 254);
		}
		if(map[i][j]==3){
		printf(ANSI_COLOR_BLUE   "%c "   ANSI_COLOR_RESET, 254);
		}
		if(map[i][j]==4){
		printf(ANSI_COLOR_RED   "%c "   ANSI_COLOR_RESET, 254);
		}
}
	}
printf("\n");
}

/*
  printf(ANSI_COLOR_RED     "This text is RED!"     ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_GREEN   "This text is GREEN!"   ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_YELLOW  "This text is YELLOW!"  ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_BLUE    "This text is BLUE!"    ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_MAGENTA "This text is MAGENTA!" ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_CYAN    "This text is CYAN!"    ANSI_COLOR_RESET "\n");
*/
  return 0;
}
