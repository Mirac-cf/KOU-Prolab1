
#include <stdio.h>
#include <stdlib.h>

int sira;

struct dizi{
	int oncelik_id,ucak_id,talepEdilenInisSaati,inilenSaat,sayac;
}kuyruk[24];

int main(int argc, char *argv[]) {
	FILE *dosya = fopen("input.txt","r");
	FILE *output = fopen("output.txt","w");
	fclose(output);
	
	int saat,i,p;
	int a,b,c;
	sira = 0;
	
	for(saat=1 ; saat<=24 ; saat++){
		while(feof(dosya)==NULL){
			fscanf(dosya,"%d %d %d",&a,&b,&c);
			if(c==saat){
				sira++;
				kuyruga_ekle(a,b,c);
			}
		}

		rewind(dosya);
		kuyrugu_sirala();
		printf("\n************ saat: %d **************",saat);
		ucagi_indir();
		
		if(saat==24 && sira!=0){
			printf("\n\nInis pistimiz maximum kapasiteye (24) ulasmistir  kalan ucaklar Sabiha Gokce havalimanina yonlendirilecektir");
			for(p=1 ; p<=sira; p++)
				printf("\n%d id'li ucak sabihaya yonlendirildi...",kuyruk[p].ucak_id);
		}
		printf("\n-------------------------------------------------------------------------------");
		
		for(i=1 ; i<=sira ; i++){
			kuyruk[i].sayac++;
		}
	}	
	outputDosyasiniGoster();
	
	fclose(dosya);
	return 0;
}


void kuyruga_ekle(int oncelik_id,int ucak_id,int inis_saati){
	kuyruk[sira].oncelik_id = oncelik_id;
	kuyruk[sira].ucak_id = ucak_id;
	kuyruk[sira].talepEdilenInisSaati = inis_saati;
	kuyruk[sira].sayac=0;
}

void kuyrugu_sirala(){
	int i,m,a;
	
	for(m=0 ; m<sira ; m++){
		for(i=1 ; i<sira ; i++){
			if(kuyruk[i].oncelik_id >kuyruk[i+1].oncelik_id){
				swap(&kuyruk[i].oncelik_id,&kuyruk[i+1].oncelik_id);
				swap(&kuyruk[i].ucak_id,&kuyruk[i+1].ucak_id);
				swap(&kuyruk[i].talepEdilenInisSaati,&kuyruk[i+1].talepEdilenInisSaati);
				swap(&kuyruk[i].sayac,&kuyruk[i+1].sayac);	
			}	
		}
	}
}


void ucagi_indir(){
	FILE *output = fopen("output.txt","a");

	int i,j,a,m;
	int boy = sira;
	
	if(sira == 0){
		printf("\n\ninis talep eden ucak kalmamistir...");
		fclose(output);
		return;
	}
	
	for(i=1 ; i<=boy ; i++){
		if(kuyruk[i].sayac == 3){
			printf("\n\nSaat : %d inis talebinde bulunan  %d id'li  onceligi: %d olan ucak 3 kez ertelendiginden dolayi inis yapmistir",kuyruk[i].talepEdilenInisSaati,kuyruk[i].ucak_id,kuyruk[i].oncelik_id);
			kuyruk[i].inilenSaat = kuyruk[i].sayac + kuyruk[i].talepEdilenInisSaati;
			fprintf(output,"%d %d %d %d %d %d\n",kuyruk[i].oncelik_id,kuyruk[i].ucak_id,kuyruk[i].talepEdilenInisSaati,kuyruk[i].inilenSaat,kuyruk[i].sayac,kuyruk[i].inilenSaat+1);
			fclose(output);
			for(j=i ; j<=sira+1 ; j++){
				kuyruk[j].oncelik_id = kuyruk[j+1].oncelik_id;
				kuyruk[j].ucak_id = kuyruk[j+1].ucak_id;
				kuyruk[j].talepEdilenInisSaati = kuyruk[j+1].talepEdilenInisSaati;
				kuyruk[j].sayac = kuyruk[j+1].sayac;
				kuyruk[j].inilenSaat = kuyruk[j+1].inilenSaat;
			}		
			sira--;
			for(a=i ; a<=sira ; a++){
				if(kuyruk[a].sayac == 3){
					printf("\nSaat : %d inis talebinde bulunan  %d id'li  onceligi: %d olan ucak 3 den fazla ertelendigi icin Sabiha Gokce havalimanina yonlendiriliyor...",kuyruk[a].talepEdilenInisSaati,kuyruk[a].ucak_id,kuyruk[a].oncelik_id);
					for(m=a ; m<=sira+1 ; m++){
						kuyruk[m].oncelik_id = kuyruk[m+1].oncelik_id;
						kuyruk[m].ucak_id = kuyruk[m+1].ucak_id;
						kuyruk[m].talepEdilenInisSaati = kuyruk[m+1].talepEdilenInisSaati;
						kuyruk[m].sayac = kuyruk[m+1].sayac;
						kuyruk[m].inilenSaat = kuyruk[m+1].inilenSaat;
					}
					sira--;
				}
			}
			return;
		}
	}
	
	printf("\n\nSaat : %d inis talebinde bulunan  %d id'li  onceligi: %d olan ucak inis yapmistir",kuyruk[1].talepEdilenInisSaati,kuyruk[1].ucak_id,kuyruk[1].oncelik_id);
	kuyruk[1].inilenSaat = kuyruk[1].sayac + kuyruk[1].talepEdilenInisSaati;
	fprintf(output,"%d %d %d %d %d %d\n",kuyruk[1].oncelik_id,kuyruk[1].ucak_id,kuyruk[1].talepEdilenInisSaati,kuyruk[1].inilenSaat,kuyruk[1].sayac,kuyruk[1].inilenSaat+1);
	
	for(j=1 ; j<=sira ; j++){
		kuyruk[j].oncelik_id = kuyruk[j+1].oncelik_id;
		kuyruk[j].ucak_id = kuyruk[j+1].ucak_id;
		kuyruk[j].talepEdilenInisSaati = kuyruk[j+1].talepEdilenInisSaati;
		kuyruk[j].sayac = kuyruk[j+1].sayac;
		kuyruk[j].inilenSaat = kuyruk[j+1].inilenSaat;
	}
	sira--;
	
	fclose(output);
}

void outputDosyasiniGoster(){
	FILE *output = fopen("output.txt","r");
	int i,a,b,c,d,e,f;
	
	for(i=0 ; i<24 ; i++){
		fscanf(output,"%d %d %d %d %d %d",&a,&b,&c,&d,&e,&f);
		printf("\nOncelik_id: %d , ucak_id: %d , Talep edilen inis saati: %d  , inis saati: %d , gecikme suresi: %d , kalkis saati: %d",a,b,c,d,e,f);
	}
	fclose(output);
}

void swap(int *a , int *b){
	int gecici = *a;
	*a = *b;
	*b = gecici;
}











