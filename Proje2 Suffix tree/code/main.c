
#include <stdio.h>
#include <stdlib.h>

int uzunluk;

struct dizi{
    char katar[200];
}sonek[200],onek[200],altKatarlar[25000];


int main(int argc, char *argv[]) {
    char kelime[200];
   	printf("Kelime : ");
   	scanf("%s",&kelime);
    
	uzunluk = strlen(kelime);
	int i,j,m;
	
    agaclariOlustur(kelime);
    
	if(sonekAgaciOlusurMu(kelime) == 0)
		printf("\nGirdiginiz kelimenin sonek agaci olusturulamiyor...");
	else{
		while(1){			
			printf("\n-------------------------------------------------");
			printf("\nKelime: '%s'",kelime);
			printf("\n1- Sonek agaci olusturlan kelinenin girilen p katari geciyor mu, geciyorsa kac kez geciyor ve ilk tekrar ettigi konum ?");
			printf("\n2- Sonek agaci olusturlan kelimede tekrar eden en uzun altkatar nedir ve kac kez tekrar etmektedir ?");
			printf("\n3- Sonek agaci olusturlan kelimede en cok tekrar eden altkatar nedir ve kac kez tekrar etmektedir ?");
			printf("\nCikis yapmak icin '0' giriniz...");
			int islem;
			printf("\n-------------------------------------------------");
			printf("\nYapmak istediginiz islem: ");
			scanf("%d",&islem);
			
			if(islem==0){
				printf("\nCikis yapiliyor...");
				break;
			}
			else if(islem==1)
				varMi(kelime);
			else if(islem==2)
				enUzunAltkatar(kelime);
			else if(islem==3)
				enCokAltkatar(kelime);
			else
				printf("\nHatali islem girdiniz tekrar deneyiniz...");			
			
		}
	}
		    
    return 0;
}


void enUzunAltkatar(char kelime[]){
	int boy = (uzunluk*(uzunluk+1))/2;
	int i,sayac=0,max=0,m;
	int kontrol[boy],indeks[boy];
	
	for(i=0 ; i<boy ; i++){
		if(arama(kelime,altKatarlar[i].katar,m) > 1){
			kontrol[sayac] = strlen(altKatarlar[i].katar);
			indeks[sayac] = i;
			
			if(max<kontrol[sayac])
				max=kontrol[sayac];
			
			sayac++;
		}
	}

	for(i=0 ; i<sayac ; i++){
		if(max == kontrol[i]){
			printf("\nKelimede tekrar eden en uzun altkatar: %s  ve  tekrar sayisi: %d",
			altKatarlar[indeks[i]].katar,arama(kelime,altKatarlar[indeks[i]].katar,m));
			break;
		}
	}
	if(max==0)
		printf("\nGirdiginiz kelimede tekrar eden alt katar bulunmamaktadir...");
}


void enCokAltkatar(char kelime[]){
	int boy = (uzunluk*(uzunluk+1))/2;
	int i,m,max=0;
	
	for(i=0 ; i<boy ; i++){
		int fonk = arama(kelime,altKatarlar[i].katar,m);
		if(fonk>1){
			if(max < fonk)
				max = fonk;
		}
	}
	
	for(i=0 ; i<boy ; i++){
		if(max==arama(kelime,altKatarlar[i].katar,m)){
			printf("\nGirilen kelimede en cok tekrar eden altkatar: %s  ve  tekrar sayisi: %d",altKatarlar[i].katar,max);
			break;
		}
	}
	
}


void agaclariOlustur(char kelime[]){
	int i,j,m,n=0,y;
	int boy = (uzunluk*(uzunluk+1))/2;
	
	for(i=0 ; i<uzunluk ; i++){
        for(j=i,m=0 ; j<uzunluk ; j++,m++)
            sonek[i].katar[m]=kelime[j];        
        for(m=0 ; m<i+1 ; m++)
            onek[i].katar[m]=kelime[m];
	}
	
	for(j=0 ; j<uzunluk ; j++){
		for(i=0 ; i<strlen(sonek[j].katar) ; i++){
        	for(y=i,m=0 ; y<strlen(sonek[j].katar) ; y++,m++){
            	altKatarlar[n].katar[m] = sonek[j].katar[m];
			}
			n++;
		}
	}
	
}


int sonekAgaciOlusurMu(char kelime[]){
    int kontrol = 0,i,j;
    
    for(i= 1 ; i<uzunluk ; i++){
        for(j=0 ; j<uzunluk-1 ; j++){
            if(strcmp(sonek[i].katar,onek[j].katar) == 0){
                kontrol=1;
                break;
            }                
        }
    }
    
    if(kontrol==1)
        return 0;
    else
    	return 1; 
}


void varMi(char kelime[]){
    char aranan[uzunluk];
    printf("\nAradiginiz katar : ");
    scanf("%s",&aranan);
   	int konum=1;
    int kontrol = arama(kelime,aranan,konum);
    
    if(kontrol == 0)
        printf("Aradiginiz '%s' katari kelimede bulunmamakta...\n",aranan);
    else{
        printf("\n'%s' katari kelimede: %d kez geciyor",aranan,kontrol);
        printf("\nilk bulundugu pozisyon kelimenin %d. sonekinin %d. oneki\n",konum,strlen(aranan));
    }
}


int arama(char kelime[],char aranan[],int konum){
	int i,j;
    int kontrol=0;
    int index[uzunluk];
    
    for(i=0 ; i<uzunluk ; i++){
        int m =0;
        if(kelime[i]==aranan[m]){
            int k=i;
            int sayac=0;
            for(j = 0 ; j<strlen(aranan) ; j++){
                if(kelime[k] ==aranan[m]){
                    sayac++;
                }
                k++;
                m++;
            }
            if(sayac == strlen(aranan)){
                index[kontrol] = k-sayac;
                kontrol++;    
            }
        }
    }
   	konum = index[0] +1;
	    
    return kontrol;
}








