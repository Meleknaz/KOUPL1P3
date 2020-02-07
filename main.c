#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct komsular
{

    int komsu_plaka;
    struct komsular *k_next;


};
typedef struct sehirler
{

    char sehir_adi[20];
    char bolge_adi[5];
    int plaka_kodu;
    int komsu_sayisi;
    struct sehirler *d_next;
    struct sehirler *d_prev;
    struct komsular *komsu;


} BLISTE;

BLISTE  *ilk1=NULL, *son1=NULL;

BLISTE *sehir_ara(char *komsu_adi)
{

    BLISTE *ara=ilk1;

    while(strcmp(ara->sehir_adi,komsu_adi)!=0)
    {

        ara=ara->d_next;
        if(ara==NULL)
            return NULL;


    }

    return ara;



}

BLISTE *plaka_ara(int aranan)
{

    struct sehirler *ara;
    ara=ilk1;

    while(ara)
    {
        if(aranan==ara->plaka_kodu)
            return ara;
        ara=ara->d_next;
    }
    return NULL;
}

BLISTE *bolge_ara(char *bolge_adi)
{



    BLISTE *liste=ilk1;

    while(liste!=NULL)
    {

        if(strcmp(liste->bolge_adi,bolge_adi)==0) // ilk bolge adi aranana esitse while in icine girebilsin
        {

            printf("%d,",liste->plaka_kodu);
            printf("%s,",liste->sehir_adi);
            printf("%s,",liste->bolge_adi);
            printf("%d\n",liste->komsu_sayisi);

        }
        if(liste->d_next==NULL)
        {
            return liste;
        }
        liste=liste->d_next;

    }
    return liste;

}

void sehri_dosyadan_oku()
{

    FILE *fp1;
    char birkelime[100];
    char *c;
    int plaka;
    int komsu_sayisi;
    char *sehir_adi;
    char *bolge_adi;

    fp1 = fopen("sehirler.txt","r");

    while(!feof(fp1))
    {
        c = fgets(birkelime,100,fp1); /* bir satir okuyalim */
        if(c[strlen(c)-1]=='\n')
        {
            c[strlen(c)-1]='\0';
        }
        else
        {
            c[strlen(c)]='\0';
        }
        if(birkelime[strlen(birkelime)-1]=='\n')
        {
            birkelime[strlen(birkelime)-1]='\0';
        }
        else
        {
            birkelime[strlen(birkelime)]='\0';
        }
        char temp[200];
        int k=0;
        while(birkelime[k]!='\0')
        {
            temp[k]=birkelime[k];
            k++;
        }
        temp[k]='\0';
        const char *ayrac = ",";// bosluk, nokta ve virgul, noktali virgul...

        char *kelime = strtok(c, ayrac);
        int sayac=0;


        while (kelime != NULL && sayac<4)
        {
            while(sayac<4 )
            {
                // printf("%s\n", kelime);
                //   printf("sayac:%d\n",sayac);
                if(sayac==0)
                    plaka=atoi(kelime);
                else if(sayac==1)
                    sehir_adi=kelime;
                else if(sayac==2)
                    bolge_adi=kelime;
                else if(sayac==3)
                    komsu_sayisi=atoi(kelime);


                kelime = strtok(NULL, ayrac);
                sayac++;
            }

        }
        k=0;
        komsu_sayisi=0;
        while(temp[k]!='\0')
        {
            if(temp[k]==',')
                komsu_sayisi++;
            k++;
        }
        komsu_sayisi=komsu_sayisi-2;
        dosyadan_sehir_ekle(plaka,sehir_adi,bolge_adi,komsu_sayisi);


    }
    fclose(fp1);
}

void dosyadan_sehir_ekle(int plaka_kodu, char *sehir_adi, char *bolge_adi, int komsu_sayisi )
{

    BLISTE *sehir = (struct sehirler*) malloc(sizeof(struct sehirler));

    sehir->plaka_kodu=plaka_kodu;
    strcpy(sehir->sehir_adi,sehir_adi);
    strcpy(sehir->bolge_adi,bolge_adi);
    sehir->komsu_sayisi=komsu_sayisi;
    sehir->komsu=NULL;

    if (ilk1 == NULL)
    {
        ilk1 = sehir;
        son1 = sehir;
        ilk1->d_prev = NULL;
        son1->d_next=NULL;

    }
    else
    {
        if(sehir->plaka_kodu < ilk1->plaka_kodu)  // basa ekleme
        {

            sehir->d_next=ilk1;
            ilk1->d_prev=sehir;
            ilk1=sehir;
            ilk1->d_prev=NULL;
        }
        else if(sehir->plaka_kodu > son1->plaka_kodu)  // sona ekleme
        {
            son1->d_next=sehir;
            sehir->d_prev=son1;
            son1=sehir;
            son1->d_next=NULL;

        }
        else  // araya ekleme
        {
            struct sehirler *ara;
            ara=ilk1;

            while(ara->plaka_kodu < sehir->plaka_kodu )
                ara=ara->d_next;


            sehir->d_next=ara;
            sehir->d_prev=ara->d_prev;
            ara->d_prev->d_next=sehir;
            ara->d_prev = sehir;
            /*ara->d_next=sehir;
            sehir->d_prev=ara;
            ara->d_next->d_prev=sehir;*/

        }

    }
}

void kullanici_sehir_ekle()
{


    int plaka ;
    printf("eklemek istediginiz sehrin bilgilerini giriniz:\n");
    printf("sehrin plakasi:");
    scanf("%d",&plaka);


    if(plaka_ara(plaka)==NULL)
    {

        int komsu_sayisi;
        char *sehir_adi=malloc(sizeof(char)*20);
        char *bolge_adi=NULL;


        printf("sehrin adi:");
        scanf("%s",sehir_adi);

        bolge_adi =malloc(sizeof(char)*10);

        if(bolge_adi!=NULL)
        {
            printf("sehrin bolgesi:");

            scanf("%s",bolge_adi);
        }

        printf("sehrin komsu sayisi:");
        scanf("%d",&komsu_sayisi);

        dosyadan_sehir_ekle(plaka,sehir_adi,bolge_adi,komsu_sayisi);
    }
    else
    {
        printf("eklemek istediginiz sehir zaten var..\n");
    }
}

BLISTE *sil_sehir()
{

    int plaka;
    printf("\silmek istediginiz sehrin plakasini giriniz:");
    scanf("%d",&plaka);

    BLISTE *p;

    p=plaka_ara(plaka);

    if(p==NULL)
    {
        printf("\nboyle bir sehir mevcut degil..\n");
        return NULL;
    }


    if(p==ilk1)  //ilk dugum mu
    {
        if(ilk1->d_next!=NULL)  //ILK DUGUM SILME
        {
            ilk1=p->d_next;
            ilk1->d_prev=NULL;
        }
        else  // sadece bir sehir varsa
        {
            ilk1=NULL;
            son1=NULL;
        }

    }
    else  // ilk dugum degilse
    {

        if(p==son1) // sonda ise
        {
            // printf("-----%d\n",p->plaka_kodu);
            son1->d_prev->d_next=NULL;
            // printf("****%d",son1->plaka_kodu);
            son1=p->d_prev;
            // printf("****%d",son1->plaka_kodu);

        }

        else
        {
            p->d_prev->d_next=p->d_next;
            p->d_next->d_prev=p->d_prev;  //arada ise


        }

    }

    free(p);
    return p;

}

void komsu_dosyadan_oku()
{

    FILE *fp1;
    char birkelime[100];
    char *c;
    fp1 = fopen("sehirler.txt","r");



    while(!feof(fp1))
    {
        c = fgets(birkelime,100,fp1); /* bir satir okuyalim */
        if(c[strlen(c)-1]=='\n')
        {
            c[strlen(c)-1]='\0';
        }
        else
        {
            c[strlen(c)]='\0';
        }
        const char *ayrac = ",";// bosluk, nokta ve virgul, noktali virgul...

        char *kelime = strtok(c, ayrac);
        int sayac=0;
        char *sehir_adi;

        while (kelime != NULL && sayac<3)
        {
            if(sayac==1)
                sehir_adi=kelime;
            kelime = strtok(NULL, ayrac);
            sayac++;
            // printf("sayac:%d\n",sayac);

        }

        while(kelime != NULL && c[strlen(c)-1]!='\n')
        {

            dosyadan_komsu_ekle(sehir_adi,kelime);
            kelime = strtok(NULL, ayrac);

        }
        // printf("----%s",sehir_adi);
        // printf("kelime:%s\n",kelime);



    }
    fclose(fp1);
}

void dosyadan_komsu_ekle(char *sehir_adi, char *komsu_adi)
{

    BLISTE *ara=sehir_ara(komsu_adi);

    if(ara==NULL)
    {

        int secim;
        printf("komsu olarak eklenmek istenen sehir yok eklemek ister misiniz?(e:1 h:0)");
        scanf("%d",&secim);

        if(secim==1)
        {
            kullanici_sehir_ekle();
        }

    }
    else if(ara!=NULL)
    {
        //  printf("---%s---%d--",ara->sehir_adi,ara->plaka_kodu);


        BLISTE *liste2=sehir_ara(sehir_adi);

        if(liste2!=NULL)
        {

            struct komsular *yeni=(struct  komsular*) malloc(sizeof(struct  komsular));
            yeni->komsu_plaka=ara->plaka_kodu;

            if(liste2->komsu==NULL)  // liste bos ise
            {
                liste2->komsu=yeni;
                yeni->k_next=NULL;

            }

            else
            {

                struct  komsular *sira=liste2->komsu;
                struct komsular *sira_once;
                if(yeni->komsu_plaka <= liste2->komsu->komsu_plaka)
                {
                    yeni->k_next=liste2->komsu;
                    liste2->komsu=yeni;

                }
                else
                {
                    int sayi=0;
                    while(sira->komsu_plaka < yeni->komsu_plaka)
                    {
                        sira_once=sira;
                        if(sira->k_next==NULL)
                        {
                            sayi=1;
                            break;
                        }

                        sira=sira->k_next;
                    }
                    if(sayi==1)
                    {
                        sira->k_next=yeni;
                        yeni->k_next=NULL;

                    }
                    else
                    {
                        yeni->k_next=sira;
                        sira_once->k_next=yeni;
                    }
                }
            }
        }
        else
        {
            int secim;
            printf("komsuyu ekleyeceginiz sehir yok eklemek ister misiniz?(e:1 h:0)");
            scanf("%d",&secim);
            if(secim==1)
            {
                kullanici_sehir_ekle();
            }
        }
    }

}


void kullanici_komsu_ekle()
{

    printf("komsu olarak eklemek istediginiz sehrin adini giriniz:");
    char *komsu_adi=malloc(sizeof(char)*20);
    scanf("%s",komsu_adi);

    BLISTE *ara=sehir_ara(komsu_adi);

    if(ara==NULL)
    {

        int secim;
        printf("komsu olarak eklemek istediginiz sehir yok eklemek ister misiniz?(e:1 h:0)");
        scanf("%d",&secim);

        if(secim==1)
        {
            kullanici_sehir_ekle();
        }

    }
    else if(ara!=NULL)
    {

        printf("hangi sehire komsuluk eklemek istersiniz");
        char *y_sehir_adi=malloc(sizeof(char)*20);
        scanf("%s",y_sehir_adi);

        BLISTE *liste2=sehir_ara(y_sehir_adi);

        if(liste2!=NULL)
        {



            struct komsular *yeni=(struct  komsular*) malloc(sizeof(struct  komsular));
            yeni->komsu_plaka=ara->plaka_kodu;

            if(liste2->komsu==NULL)  // liste bos ise
            {

                liste2->komsu=yeni;
                yeni->k_next=NULL;

            }


            else
            {

                struct  komsular *sira=liste2->komsu;
                struct komsular *sira_once;
                if(yeni->komsu_plaka <= liste2->komsu->komsu_plaka)
                {
                    yeni->k_next=liste2->komsu;
                    liste2->komsu=yeni;

                }
                else
                {
                    int sayi=0;
                    while(sira->komsu_plaka < yeni->komsu_plaka)
                    {
                        sira_once=sira;
                        if(sira->k_next==NULL)
                        {
                            sayi=1;
                            break;
                        }

                        sira=sira->k_next;
                    }
                    if(sayi==1)
                    {
                        sira->k_next=yeni;
                        yeni->k_next=NULL;

                    }
                    else
                    {
                        yeni->k_next=sira;
                        sira_once->k_next=yeni;
                    }
                }
            }
            liste2->komsu_sayisi++;
        }



        else
        {
            int secim;
            printf("komsuyu ekleyeceginiz sehir yok eklemek ister misiniz?(e:1 h:0)");
            scanf("%d",&secim);
            if(secim==1)
            {
                kullanici_sehir_ekle();
            }
        }

    }
}


void Listele()
{
    struct sehirler *liste=ilk1;

    while(liste!=NULL)
    {
        printf("%d,",liste->plaka_kodu);
        printf("%s,",liste->sehir_adi);
        printf("%s,",liste->bolge_adi);
        printf("%d",liste->komsu_sayisi);

        struct komsular *iter = liste->komsu;


        while(iter!=NULL)
        {
            printf(",%d",iter->komsu_plaka);
            if(iter->k_next==NULL)
                break;
            iter=iter->k_next;
        }

        liste=liste->d_next;
        printf("\n");
    }
}


struct komsular *komsu_ara(BLISTE *liste, char *komsu_adi )
{

    struct komsular *ara=liste->komsu;
    BLISTE *p=sehir_ara(komsu_adi);


    if(p==NULL)
    {
        printf("sehir listede bulunamadi");
        return NULL;
    }
    else
    {

        while(ara->komsu_plaka!=p->plaka_kodu)
        {
            //printf("-----%d-----",ara->komsu_plaka);
            if(ara->k_next==NULL)
                return NULL;
            ara=ara->k_next;

        }

        return ara;
    }



}


struct komsular *sil_komsu()
{

    char *sehir_adi=malloc(sizeof(char)*20);
    printf("hangi sehirden komsuluk silmek istiyorsunuz?");
    scanf("%s",sehir_adi);

    BLISTE *liste=sehir_ara(sehir_adi);

    if(liste==NULL)
    {
        printf("boyle bir sehir mevcut degil");
        return NULL;
    }
    else
    {

        char *komsu_adi=malloc(sizeof(char)*20);
        printf("hangi sehri komsuluktan silmek istiyorsunuz?");
        scanf("%s",komsu_adi);

        struct komsular *ara=komsu_ara(liste,komsu_adi);

        if(ara==NULL)
        {

            printf("silmek istediginiz komsu sehir yok..");
            //  return NULL;
        }
        else
        {

            // printf("******ara->plaka_kodu:%d\n",ara->plaka_kodu);

            struct komsular *iter=liste->komsu;
            struct komsular *sira_once=liste->komsu;

            while(iter->komsu_plaka!=ara->komsu_plaka)
            {

                sira_once=iter;
                iter=iter->k_next;
            }

            //  printf("----iter:%d",iter->komsu_plaka);
            // printf("-----sira once:%d",sira_once->komsu_plaka);

            if(sira_once==liste->komsu)  // bastan silme
            {
                liste->komsu=iter->k_next;
            }
            else if(iter->k_next==NULL)   //sondan silme
            {
                sira_once->k_next=NULL;

            }
            else
            {
                sira_once->k_next=iter->k_next;
            }

            liste->komsu_sayisi--;
            free(iter);



        }

    }

}

void bolgeye_gore_listele()
{

    printf("hangi bolgedeki sehirleri goruntulemek istersiniz?");
    char *bolge_adi=NULL;
    bolge_adi =malloc(sizeof(char)*10);

    if(bolge_adi !=NULL)
    {
        scanf("%s",bolge_adi);
    }

    bolge_ara(bolge_adi);


}

void sehir_ismi_plaka_ile_arama()
{

    printf("sehir ismi ile mi aramak istersiniz yoksa plaka kodu ile mi?\n");
    printf("isim ile:1\nplaka ile:2\n");
    int secim;
    scanf("%d",&secim);

    if(secim==1)
    {
        printf("isimle hangi sehrin bilgilerini goruntulemek istersiniz?\n");
        char *sehir_adi=malloc(sizeof(char)*20);
        scanf("%s",sehir_adi);

        BLISTE *liste=sehir_ara(sehir_adi);

        if(liste==NULL)
        {
            printf("goruntulemek istediginiz sehir yok eklemek ister misiniz?(e:1 h:0)\n");
            int sayi;
            scanf("%d",&sayi);

            if(sayi==1)
                kullanici_sehir_ekle();

        }
        else
        {
            printf("%d,",liste->plaka_kodu);
            printf("%s,",liste->sehir_adi);
            printf("%s,",liste->bolge_adi);
            printf("%d",liste->komsu_sayisi);

            struct komsular *iter = liste->komsu;


            while(iter!=NULL)
            {
                printf(",%d",iter->komsu_plaka);
                if(iter->k_next==NULL)
                    break;
                iter=iter->k_next;
            }

            liste=liste->d_next;
            printf("\n");


        }
    }


    if(secim==2)
    {

        printf("plaka kodu ile hangi sehrin bilgilerini goruntulemek istersiniz?\n");
        int plaka;
        scanf("%d",&plaka);

        BLISTE *liste=plaka_ara(plaka);

        if(liste==NULL)
        {
            printf("goruntulemek istediginiz sehir yok eklemek ister misiniz?(e:1 h:0)\n");
            int sayi;
            scanf("%d",&sayi);

            if(sayi==1)
                kullanici_sehir_ekle();

        }
        else
        {

            printf("%d,",liste->plaka_kodu);
            printf("%s,",liste->sehir_adi);
            printf("%s,",liste->bolge_adi);
            printf("%d",liste->komsu_sayisi);

            struct komsular *iter = liste->komsu;


            while(iter!=NULL)
            {
                printf(",%d",iter->komsu_plaka);
                if(iter->k_next==NULL)
                    break;
                iter=iter->k_next;
            }

            liste=liste->d_next;
            printf("\n");

        }

    }



}

BLISTE *sayiya_gore_komsu_ara(int aranan)
{

    struct sehirler *liste;
    liste=ilk1;

    while(liste!=NULL)
    {
        if(liste->komsu_sayisi > aranan )
        {

            printf("%d,",liste->plaka_kodu);
            printf("%s,",liste->sehir_adi);
            printf("%s,",liste->bolge_adi);
            printf("%d\n",liste->komsu_sayisi);

        }
        liste=liste->d_next;
    }
    return liste;
}

void belirli_sayiya_gore_arama()
{

    printf("kactan fazla komsusu olan sehirleri aramak istiyorsunuz?");
    int sayi;
    scanf("%d",&sayi);

    sayiya_gore_komsu_ara(sayi);

}

void bonus_ara(int sayi1, int sayi2)
{

    struct sehirler *liste;
    liste=ilk1;

    char *sehir1=malloc(sizeof(char)*20);
    char *sehir2=malloc(sizeof(char)*20);

    printf("hangi illere komsu olsun?\n");
    scanf("%s",sehir1);
    scanf("%s",sehir2);

    BLISTE *ara1=sehir_ara(sehir1);
    BLISTE *ara2=sehir_ara(sehir2);

    while(liste!=NULL)
    {
        if(liste->komsu_sayisi>sayi1 && liste->komsu_sayisi<sayi2)
        {
            BLISTE *donen1=komsu_ara(ara1,liste->sehir_adi);
            BLISTE *donen2=komsu_ara(ara2,liste->sehir_adi);

            if(donen1!=NULL && donen2!=NULL)
            {

                printf("%d,",liste->plaka_kodu);
                printf("%s,",liste->sehir_adi);
                printf("%s,",liste->bolge_adi);
                printf("%d\n",liste->komsu_sayisi);

            }

        }
        liste=liste->d_next;
    }
    return liste;



}

void bonus()
{

    printf("komsu sayisi hangi aralikta olsun?\n");
    int sayi1, sayi2;
    scanf("%d",&sayi1);
    scanf("%d",&sayi2);
    bonus_ara(sayi1,sayi2);



}


void cikti()
{

    struct sehirler *p=ilk1;
    FILE *dosya=fopen("cikti.txt","w");
    if(dosya==NULL)
    {
        printf("Dosya acilamadi");
    }
    while(p!=NULL)
    {

        fprintf(dosya,"\n%d,:%s,%s,%d",p->plaka_kodu,p->sehir_adi,p->bolge_adi,p->komsu_sayisi);


        while(p->komsu!=NULL)
        {
            fprintf(dosya,"-->{%d}",p->komsu->komsu_plaka);
            if(p->komsu->k_next==NULL)
                break;
            p->komsu=p->komsu->k_next;
        }
        fprintf(dosya,"\n");
        if(p->d_next==NULL)
            break;
        p=p->d_next;

          fprintf(dosya,"   ||   ");
    }

    fclose(dosya);

}

int main()
{

    sehri_dosyadan_oku();
    komsu_dosyadan_oku();

    int secim;
    do
    {
        printf("\n 1:bolgeye gore listele\n 2:kullanici sehir ekle\n 3:sil sehir\n");
        printf(" 4:kullanici komsu ekle\n 5:sil komsu\n 6:listele\n");
        printf(" 7:sehir ismi veya plaka ile aratma\n");
        printf(" 8:belli bir sayiya gore sehir arama\n");
        printf(" 9:bonus\n 0:cikis\n");

        printf("lutfen secim yapiniz:\n");
        scanf("%d",&secim);

        switch(secim)
        {
        case 1 :
            bolgeye_gore_listele();
            break;

        case 2 :
            kullanici_sehir_ekle();
            break;
        case 3 :
            sil_sehir();
            break;
        case 4 :
            kullanici_komsu_ekle();
            break;


        case 5 :
            sil_komsu();
            break;

        case  6 :
            Listele();
            break;

        case 7 :
            sehir_ismi_plaka_ile_arama();
            break;

        case 8 :
            belirli_sayiya_gore_arama();
            break;

        case 9 :
            bonus();
            break;
        case 0 :
            printf("dosyaya yazdim..");
            cikti();
            break;
        default:
            printf("yanlis secim yaptiniz..");
            break;
        }

    }
    while(secim!=0);



    return 0;
}
