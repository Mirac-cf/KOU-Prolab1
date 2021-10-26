#include <stdio.h>
#include <stdlib.h>

int maxin,ogrSayi;


struct kayit{
int ogrNo;
int dersKodu;
int puan;
};


int main(int argc, char *argv[]) {    	
	printf("*** OKUL NOT SISTEMINE HOSGELDINIZ ***\n");
	indexDosyasiOlustur();
	
	while(1){
		printf("----------------------------------------");
		printf("\n1- Ogrenci kaydi ekle");
		printf("\n2- Ogrenci kaydi sil");
		printf("\n3- Ogrenci notunu guncelle");
		printf("\n4- Ogrenci kaydini bul");
		printf("\n5- Ogrenci bilgilrini goster");
		printf("\n6- Index dosyasini goster");
		printf("\n7- Index dosyasini sil");
		printf("\n8- Index dosyasi olustur");
		printf("\nCIKIS yapmak istiyorsaniz '0'a basiniz...");
		
		int islem;
		printf("\n\nYapmak istediginiz islem: ");
		scanf("%d",&islem);
		printf("\n----------------------------------------");
	
		if(islem==0){
			printf("\nCikis yapiliyor...");
			break;
		}
		else if(islem==1)
			kayitEkle();
		else if(islem==2){
			int no,dkod;
    		printf("\nDERS KODLARI : Matematik(1) , Turkce(2) , Fizik(3)\n");
    		printf("\nSilmek istediginiz ogrencinin ogrenci numarasi: ");
    		scanf("%d",&no);
    		printf("%d numarali ogrencinin Silmek istediginiz dersinin kodu: ",no);
    		scanf("%d",&dkod);
			// Ogrenci numarasi ve ders kodu kontrol ettirildi eger sistemde kayitliysa fonksiyon calistirildi 
			if(dogruMudk(no,dkod)==1)
				kayitSil(no,dkod);
			else
				printf("\n%d numarali ve %d ders kodlu ogrenci sistemde bulunmamaktadir...\n",no,dkod);
		}
		else if(islem==3){
			int no1,kod2;
    		printf("\nGuncellemek istediginiz ogrencinin numarasi: ");
    		scanf("%d",&no1);
    		printf("%d nolu ogrencinin Hangi dersini guncellmek istiyorsunuz ders kodu giriniz: ",no1);
    		scanf("%d",&kod2);
			// Ogrenci numarasi ve ders kodu kontrol ettirildi eger sistemde kayitliysa fonksiyon calistirildi
			if(dogruMudk(no1,kod2)==1)
				kayitGuncelle(no1,kod2);
			else
				printf("\n%d numarali ve %d ders kodlu ogrenci sistemde bulunmamaktadir...\n",no1,kod2);
		}
		else if(islem==4){
			int no2;
    		printf("\nAradiginiz ogrencinin ogrenci numarasi: ");
    		scanf("%d",&no2);
    		// Ogrenci numarasini kontrol ettirildi sistemde kayitliysa fonksiyon calistirildi
			if(dogruMu(no2)==1)
				kayitBul(no2);
			else
				printf("\n%d numarali ogrenci sistemde bulunmamaktadir...\n",no2);
		}
		else if(islem==5)
			veriDosyasiniGoster();
		
		else if(islem==6)
			indexDosyasiniGoster();
		
		else if(islem==7)
			indexDosyasiniSil();
			
		else if(islem==8){
			indexDosyasiOlustur();
			printf("\nindex dosyasi basariyla olusturulmustur...\n");
		}
		else
			printf("\nHatali islem girdiniz Lutfen tekrar giriniz...\n");
	}
	return 0;
}


int indexDosyasiOlustur(){
    FILE *Binary = fopen("Binary.dat","w");
    FILE *Text = fopen("Text.TXT","r");

    char ch;
	maxin=0;
	
    // Satir sayisindan yola cikilarak kac ogrenci oldugu bulunup maxin degiskenine atandi
    while(feof(Text)==NULL){
        ch=getc(Text);
        if(ch=='\n'){
            maxin++;
        }
    }
    rewind(Text);
    
    char a,b;
    int i,c;
    int diziin[maxin],dizino[maxin],dizikod[maxin];

    for(i = 0 ; i<maxin ; i++){
        fscanf(Text,"%d %d %d",&dizino[i],&dizikod[i],&c);
        diziin[i] = i;  // ogrenci numaralarin indexleri tek tek diziin[] dizisine atandi
    }

    int gecici,tut,m,n;
    // Binary dosyasina kaydetmeden once ogrenci numaralari siralandi
    for(gecici=0 ; gecici<maxin ; gecici++){
        for(i=0 ; i<maxin ; i++){
            if(dizino[i] < dizino[i+1]){
                m = diziin[i];
                diziin[i] = diziin[i+1];
                diziin[i+1] = m;
                n = dizikod[i];
                dizikod[i] = dizikod[i+1];
                dizikod[i+1] = n;
                tut = dizino[i];
                dizino[i] = dizino[i+1];
                dizino[i+1] = tut;
            }
        }
    }

    //Ogrenci no ders kodu ve bulundugu indexi Binary fonksiyonuna kaydedildi
    for(i=0;i<maxin;i++){
        fprintf(Binary,"%d %d %d\n",dizino[i],dizikod[i],diziin[i]);
    }
    
	fclose(Binary);
    fclose(Text);
    
    ogrSayi = 0;
    for(i=0;i<maxin;i++){
		if(dizino[i] != dizino[i+1])
			ogrSayi++;
	}
    // ogrenci sayisi hesaplandi ve return edildi
    return maxin,ogrSayi;
}


void kayitEkle(){
    FILE *Text = fopen("Text.TXT","a");

    int i=0;
    struct kayit ogr;
	// ogr diye bir struct degiskeni olusturuldu ve tek tek kullanicidan bilgiler alindi	
    printf("\nDERS KODLARI : Matematik(1) , Turkce(2) , Fizik(3)\n\n");
    printf("Ogrenci no: ");
    scanf("%d",&ogr.ogrNo);
    printf("Ders kodu: ");
    scanf("%d",&ogr.dersKodu);
	// Ayni ogrenci ve ders kodlarini iki kez kaydetmemek icin ogrenci no ve ders kodu denetlendi
	if(dogruMudk(ogr.ogrNo,ogr.dersKodu)==1)
		printf("\nGirdiginiz ogrenci numarasi ve ders kodu sistemde zaten kayitli...\n");
	else{	
    	printf("Ders kodu %d icin puan: ",ogr.dersKodu);
    	scanf("%d",&ogr.puan);
		fprintf(Text,"%5d %2d %3d\n",ogr.ogrNo,ogr.dersKodu,ogr.puan);  
		printf("\n%d numarali ogrenci basariyla kaydedilmistir...\n",ogr.ogrNo);
		// Her ogrenci icin bir satir ayirtildi ve her satir icinde 14 byte lik yer ayirtildi 
	}
	
    fclose(Text);
    indexDosyasiOlustur(); 
	// index dosyasini tekrardan olusturarak güncellenmis oldu
}



void kayitBul(int no){
    FILE *Binary = fopen("Binary.dat","r");
    FILE *Text = fopen("Text.TXT","r");
  
    int i,a,b,sayi;
    int dizino[maxin],diziin[maxin];
    
    for(i = 0 ; i<maxin ; i++){
        fscanf(Binary,"%d %d %d",&dizino[i],&a,&diziin[i]);
        // Binary search yapabilmek icin bütün ogr numaralari ve indexler tek tek diziye atandi
    }
    
    int tutucu = 0;
    int boyut = maxin;  
    
    // ogrenci numaralarinda ikili arama sistemi yapildi
    while(1){
    	if(no==dizino[(tutucu+maxin)/2]){
    		sayi=no;
    		break;
		}
		else if(no>dizino[(tutucu+maxin)/2])
			maxin = (tutucu +maxin)/2; 	
			
		else if(no<dizino[(tutucu+maxin)/2])
			tutucu = (tutucu+maxin)/2;
	}
	
	maxin = boyut; // maxine tekrar eski degeri verildi  maxin = ogrenci sayisi
    int diziindex[10];
    a = 0;
    
	for(i=0;i<maxin;i++){
		if(dizino[i]==sayi){
			diziindex[a] = diziin[i]; // Buldugumuz numaralarin indexlerini diziindex[] dizisine atandi 
			a++;
		}
	}
    
    int no1,in1,d1,m;
    
	for(m=0; m<a ; m++){
		// Buldugumuz indexlere fseek ile gidip tek tek bilgileri alinip yazdirildi
    	fseek(Text,diziindex[m]*14,0);
    	fscanf(Text,"%d %d %d",&no1,&d1,&in1);
    	printf("\nOgrenci no: %d  Ders kodu: %d  Puan: %d",no1,d1,in1);
    	rewind(Text);
	}
 	printf("\n");
 	
    fclose(Binary);
    fclose(Text);
}


void kayitSil(int no,int dkod){
    FILE *Binary = fopen("Binary.dat","r");
    FILE *Text = fopen("Text.TXT","r");
    
	int i,a,b,sayi;
    int dizino[maxin],diziin[maxin];

    for(i = 0 ; i<maxin ; i++){
        fscanf(Binary,"%d %d %d",&dizino[i],&a,&diziin[i]);
    }

    int tutucu = 0;
    int boyut = maxin;

    while(1){
        if(no==dizino[(tutucu+maxin)/2]){
            sayi=no;
            break;
        }
        else if(no>dizino[(tutucu+maxin)/2])
            maxin = (tutucu +maxin)/2;

        else if(no<dizino[(tutucu+maxin)/2])
            tutucu = (tutucu+maxin)/2;
    }

    maxin = boyut;
    int diziindex[10];
    a = 0;
	// Kayit buldaki gibi index dosyasinda ikili arama yapilip bulunan indexler diziindex[] dizisine atildi
    for(i=0;i<maxin;i++){
        if(dizino[i]==sayi){
            diziindex[a] = diziin[i];
            a++;
        }
    }

    int no1,in1,d1,m;
    int index1;

    for(m=0; m<a ; m++){
        fseek(Text,diziindex[m]*14,0);
        fscanf(Text,"%d %d %d",&no1,&d1,&in1);
		        
		if(d1==dkod){  // buldugumuz indexlere gidip dogru ogrenciyi bulana kadar tek tek ders kodlarini karsilastirdik 
            rewind(Text);
            index1=diziindex[m];
            break; 
		}
        rewind(Text);
	}
        
	fclose(Binary);
    fclose(Text);


    int sno,sd,sin;
    FILE *fp=fopen("Text.TXT","r+"); 
    
    int numara[maxin],ders[maxin],puan[maxin];
	
	for(i = 0 ; i<maxin ; i++){	 	
       	fscanf(fp,"%d %d %d",&sno,&sd,&sin);
       	numara[i]=sno;
       	ders[i]=sd;
       	puan[i]=sin;
	}
	
	fclose(fp);
	FILE *file=fopen("Text.TXT","w");
	
	for(i=0 ; i<maxin ; i++){
		if(i == index1)
			continue;
		fprintf(file,"%5d %2d %3d\n",numara[i],ders[i],puan[i]);
	}
	// veri dosyasindaki tüm ogrencileri alinip tekrardan yazdirildi silinmesini istedikleri ogrenci haric
	printf("%d nolu ogrencinin %d. dersi basariyla silinmistir...\n",no,dkod);

	fclose(fp);
	indexDosyasiOlustur();
	// index dosyasi yeniden olusturularak guncellemis oldu
}


void kayitGuncelle(no,kod2){
    FILE *Binary = fopen("Binary.dat","r");
    FILE *Text = fopen("Text.TXT","r");
    
	int i,a,b,sayi;
    int dizino[maxin],diziin[maxin];

    for(i = 0 ; i<maxin ; i++){
        fscanf(Binary,"%d %d %d",&dizino[i],&a,&diziin[i]);
    }
	
    int tutucu = 0;
    int boyut = maxin;

    while(1){
    	if(no==dizino[(tutucu+maxin)/2]){
    		sayi=no;
    		break;
		}
		else if(no>dizino[(tutucu+maxin)/2])
			maxin = (tutucu +maxin)/2;

		else if(no<dizino[(tutucu+maxin)/2])
			tutucu = (tutucu+maxin)/2;
	}

	maxin = boyut;
    int diziindex[10];
    a = 0;

	for(i=0;i<maxin;i++){
		if(dizino[i]==sayi){
			diziindex[a] = diziin[i];
			a++;
		}
	}
	// Kayit buldaki gibi index dosyasinda ikili arama yapilip bulunan indexler diziindex[] dizisine atildi
    int no1,in1,d1,m;
    
    fclose(Binary);
    fclose(Text);

    FILE *fp=fopen("Text.TXT","r+");
    int notu;
    printf("Yeni puani giriniz: ");
    scanf("%d",&notu);
    for(m=0; m<a ; m++){
    	rewind(fp);
    	fseek(fp,diziindex[m]*14,0);
    	fscanf(fp,"%d %d %d",&no1,&d1,&in1);
    	if(kod2==d1){
            fseek(fp,(diziindex[m]*14)+9,0); 
            fprintf(fp,"%3d",notu);
            // istenilen ogrenciye ve ders koduna ulasilip puani guncellendi
            break;
    	}
	}
	printf("\nOgrenci no: %d  Ders kodu: %d  Puan: %d\n",no,kod2,notu);
	printf("Ogrencinin notu basariyla guncellendi...\n");
    
	fclose(fp);
    indexDosyasiOlustur();
    // index dosyasi yeniden olusturularak guncellemis oldu
}


void veriDosyasiniGoster(){
	FILE *Text = fopen("Text.TXT","r");
	printf("\nVERI DOSYASI");
	printf("\nDERS KODLARI : Matematik(1) , Turkce(2) , Fizik(3)\n\n");	
	int i,a,b,c;
	
	for(i=0; i<maxin ; i++){
		fscanf(Text,"%d %d %d",&a,&b,&c);
		printf("Ogrenci no: %d   Ders kodu: %d   Puan: %d\n",a,b,c);
	}
	
	printf("\nOgrenci sayisi : %d\n",ogrSayi);
	fclose(Text);	
}


void indexDosyasiniGoster(){
	FILE *fp = fopen("Binary.Dat","r");
	printf("\nINDEX DOSYASI\n\n");
	int i,a,b,c;
	
	for(i=0; i<maxin ; i++){
		fscanf(fp,"%d %d %d",&a,&b,&c);
		printf("Ogrenci no: %d  indexi: %d\n",a,c);	
	}
	
	fclose(fp);	
}



void indexDosyasiniSil(){
	remove("Binary.dat");
	printf("\nIndex dosyasi basariyla silinmistir...\n");
}


int dogruMu(int no){
	FILE *fp = fopen("Text.txt","r");
	int i,a,b,c;
	int say=0;
	// ogr no veri dosyasinda kayitli mi yoksa degil mi kontrol ettirildi 
	for(i=0 ; i<maxin ; i++){
		fscanf(fp,"%d %d %d",&a,&b,&c);
		if(no==a){
			say=1;
			break;
		}
	}
	fclose(fp);
	
	if(say==1)
		return 1;		
	
	return 0;
}


int dogruMudk(int no,int dkod){
	FILE *Text = fopen("Text.txt","r");
	int i,a,b,c;
	int sayac=0;
	// ogr no ve ders kodu veri dosyasinda kayitli mi yoksa degil mi kontrol ettirildi
	for(i=0 ; i<maxin ; i++){
		fscanf(Text,"%d %d %d",&a,&b,&c);
		if(no==a && dkod==b){
			sayac=1;
			break;
		}
	}
	fclose(Text);
	
	if(sayac==1)
		return 1;		
	
	return 0;
}













