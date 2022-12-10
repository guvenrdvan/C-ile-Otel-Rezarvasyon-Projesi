#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ODA_SAYISI 100

typedef struct{
	char *musteriAdi;
	char  *musteriSoyadi;
}musteriBilgileri;

typedef struct{
	int gun;
	int ay;
	int yil;
	
}tarihBilgileri;

typedef struct{
	int kisiSayisi;
	int odaDurumu;//Oda boþ ise 0 dolu ise 1 dönücek.
	int odaNumarasi;//1-100 arasý odalarýmýz olucak.
	double fiyatBilgisi;
	musteriBilgileri musteri;
	tarihBilgileri girisTarihi;
	tarihBilgileri cikisTarihi;
}odaBilgileri;

typedef enum{
	musteri=0,personel=1
}yetkilendirme;

int gunFarkiHesapla(tarihBilgileri girisTarihi,tarihBilgileri cikisTarihi){
	if(girisTarihi.gun>cikisTarihi.gun){
		cikisTarihi.ay-=1;	
		cikisTarihi.gun+=30;
		
	}
	 if(girisTarihi.ay>cikisTarihi.ay){
		cikisTarihi.yil-=1;
		cikisTarihi.ay+=12;
		
	}
	tarihBilgileri tarihFarki;
	tarihFarki.gun=cikisTarihi.gun-girisTarihi.gun;
	tarihFarki.ay=cikisTarihi.ay-girisTarihi.ay;
	tarihFarki.yil=cikisTarihi.yil-girisTarihi.yil;
	int gunFarki=(tarihFarki.yil*365)+(tarihFarki.ay*30)+(tarihFarki.gun);
	return gunFarki;
		
}

double fiyatHesapla(odaBilgileri *odalar,int odaNumarasi){
	int gunFarki=gunFarkiHesapla(odalar[odaNumarasi-1].girisTarihi,odalar[odaNumarasi-1].cikisTarihi);
	printf("Kalacaginiz gun sayisi: %d \n",gunFarki);
	return gunFarki*300*odalar[odaNumarasi-1].kisiSayisi;//Bir odanýn fiyatýný 300 tl olarak belirledim kiþi sayýsýna göre fiyatý artacak.
}
void rezervasyonTemizle(odaBilgileri *odalar,int odaNumarasi){
	odalar[odaNumarasi-1].odaDurumu=0;//Odayý boþ hale getirdik.
	free(odalar[odaNumarasi-1].musteri.musteriAdi);
	free(odalar[odaNumarasi-1].musteri.musteriSoyadi);

	printf("\n%d numarali odanin cikis/iptal islemi basariyle gerceklesti \n",odaNumarasi);
}
void doluOdaBilgileriYaz(odaBilgileri *odalar){
	int i;
	for(i=0;i<ODA_SAYISI;i++){
		if(odalar[i].odaDurumu==1){
		    printf("--------------------------------------------------------------------\n");
		    printf("Oda Numarasi: %d \n",odalar[i].odaNumarasi);
			printf("Musteri Adi Soyadi: %s %s \n",odalar[i].musteri.musteriAdi,odalar[i].musteri.musteriSoyadi);
			printf("Kisi Sayisi: %d \n",odalar[i].kisiSayisi);
			printf("Fiyat Bilgisi: %.2lf Tl \n",odalar[i].fiyatBilgisi);
			printf("Giris Tarihi: %d:%d:%d \n",odalar[i].girisTarihi.gun,odalar[i].girisTarihi.ay,odalar[i].girisTarihi.yil);
			printf("Cikis Tarihi: %d:%d:%d \n",odalar[i].cikisTarihi.gun,odalar[i].cikisTarihi.ay,odalar[i].cikisTarihi.yil);
			printf("--------------------------------------------------------------------\n");		
		}	
	}	
}


void yeniMusteriEkle(odaBilgileri *odalar ){
	int sorgulanacakOda;
	char musteriAdi[25],musteriSoyadi[30],eh;
	printf("\nLutfen kayit yapmak istediginiz oda numarasini giriniz: \n");
	scanf("%d",&sorgulanacakOda);
	if(odalar[sorgulanacakOda-1].odaNumarasi==1){//Odanýn dolu olup olmadýðýný kontrol ediyorum.
	
	printf("Malesef kayit yapmak istediginiz oda (%d:%d:%d) tarihine kadar doludur. \n",odalar[sorgulanacakOda-1].cikisTarihi.gun,odalar[sorgulanacakOda-1].cikisTarihi.ay,odalar[sorgulanacakOda-1].cikisTarihi.yil);
		return ;
	}
	odalar[sorgulanacakOda-1].odaNumarasi=sorgulanacakOda;// Oda numaralarýný kayýt sýrasýnda atýyorum.
	printf("Lutfen Ad-Soyad bilgilerini giriniz:   ");
	scanf("%s%s",&musteriAdi,&musteriSoyadi);
	
	odalar[sorgulanacakOda-1].musteri.musteriAdi=(char*)malloc(sizeof(char)*strlen(musteriAdi)+1);
	odalar[sorgulanacakOda-1].musteri.musteriSoyadi=(char*)malloc(sizeof(char)*strlen(musteriSoyadi)+1);
	strcpy(odalar[sorgulanacakOda-1].musteri.musteriAdi,musteriAdi);
	strcpy(odalar[sorgulanacakOda-1].musteri.musteriSoyadi,musteriSoyadi);
	
	printf("Lutfen kac kisi kalincagini giriniz: ");
	scanf("%d",&odalar[sorgulanacakOda-1].kisiSayisi);
	
	printf("Lutfen giris yapilacak tarihi gun:ay:yil seklinde giriniz: ");
	scanf("%d %d %d",&odalar[sorgulanacakOda-1].girisTarihi.gun,&odalar[sorgulanacakOda-1].girisTarihi.ay,&odalar[sorgulanacakOda-1].girisTarihi.yil);
	fflush(stdin);
	printf("Lutfen cikis yapilacak tarihi gun:ay:yil seklinde giriniz: ");
	scanf("%d %d %d",&odalar[sorgulanacakOda-1].cikisTarihi.gun,&odalar[sorgulanacakOda-1].cikisTarihi.ay,&odalar[sorgulanacakOda-1].cikisTarihi.yil);	
	
	odalar[sorgulanacakOda-1].fiyatBilgisi=fiyatHesapla(odalar,sorgulanacakOda);
	printf("Odenecek toplam tutar: %.2lfTL \n",odalar[sorgulanacakOda-1].fiyatBilgisi);
	printf("Onaylamak icin 'E' iptal etmek icin 'H' tuslamasini yapiniz: ");
	fflush(stdin);
	eh=getchar();
	if(eh=='H'){
		rezervasyonTemizle(odalar,sorgulanacakOda);
		return;
	}
	odalar[sorgulanacakOda-1].odaDurumu=1;//Odayý dolu hale getiriyoruz.
	
}
void odaBilgisiSorgula(odaBilgileri *odalar,int odaNumarasi){
	if(odalar[odaNumarasi-1].odaNumarasi!=0){
		printf("%d numarali oda %d:%d:%d tarihine kadar doludur. \n",odalar[odaNumarasi-1].odaNumarasi,odalar[odaNumarasi-1].cikisTarihi.gun,odalar[odaNumarasi-1].cikisTarihi.ay,odalar[odaNumarasi-1].cikisTarihi.yil);	
	}
	else{
		printf("%d numarali oda su an bos durumdadir. \n",odaNumarasi);
	}	
}

void fiyatBilgisiSorgula(){
	int kisiSayisi,gunFark;

	double toplamFiyat=0.0;
	tarihBilgileri girisTarihi,cikisTarihi;

	printf("Lutfen kac kisi kalacaginizi giriniz: ");
	scanf("%d",&kisiSayisi);
	
	printf("Lutfen giris tarihinizi gun:ay:yil seklinde giriniz: ");
	scanf("%d%d%d",&girisTarihi.gun,&girisTarihi.ay,&girisTarihi.yil);
	
	printf("Lutfen cikis tarihinizi gun:ay:yil seklinde giriniz: ");
	scanf("%d%d%d",&cikisTarihi.gun,&cikisTarihi.ay,&cikisTarihi.yil);
	toplamFiyat=gunFarkiHesapla(girisTarihi,cikisTarihi)*kisiSayisi*300;
	gunFark=gunFarkiHesapla(girisTarihi,cikisTarihi);
	printf("Kalacaginiz gun sayisi: %d \n",gunFark);
	printf("Odenecek toplam tutar: %.2lfTL\n\n",toplamFiyat);
	
}
void yedekKayitAlma(odaBilgileri *odalar){
	int i;
	FILE *otelKayitlari=fopen("otelKayitlari.txt","a");
	if(otelKayitlari==NULL){
		fprintf(stderr,"Yedek kayit alýnýrken bir hata meydana geldi. ");
		exit(1);
	}
	for(i=0;i<ODA_SAYISI;i++){
		if(odalar[i].odaDurumu!=0){      // Odanýn dolu olduðunu kontrol edip yazdýrýyorum.
		fprintf(otelKayitlari,"-----------------------------------------------------------------------\n");
		fprintf(otelKayitlari,"Musterinin Adi Soyadi: %s %s \n",odalar[i].musteri.musteriAdi,odalar[i].musteri.musteriSoyadi);
		fprintf(otelKayitlari,"Oda Numarasi: %d \n",odalar[i].odaNumarasi);
		fprintf(otelKayitlari,"Kalinan Kisi Sayisi: %d \n",odalar[i].kisiSayisi);
		fprintf(otelKayitlari,"Toplam Tutar: %.2lfTL \n",odalar[i].fiyatBilgisi);
		fprintf(otelKayitlari,"Giris Tarihi: %d:%d:%d \n",odalar[i].girisTarihi.gun,odalar[i].girisTarihi.ay,odalar[i].girisTarihi.yil);
		fprintf(otelKayitlari,"Cikis Tarihi: %d:%d:%d \n",odalar[i].cikisTarihi.gun,odalar[i].cikisTarihi.ay,odalar[i].cikisTarihi.yil);	
		
		}
	}
}










int main(){
	
int sifre=15978,kullaniciGiris,odaNumarasi;
yetkilendirme kullaniciYetkisi;
char ch;

odaBilgileri *odaDizisi;//Tüm bilgiler burada tutulacak.
odaDizisi=(odaBilgileri*)calloc(ODA_SAYISI,sizeof(odaBilgileri));//Bilgileri dinamik bir þekilde saklamak için kullandým.
printf("\t\t\t\t OTEL REZERVASYON MENUSUNE HOSGELDINIZ \n\n\n\n");
puts("Lutfen personel isenize sifrenizi giriniz musteri istesiniz 4 haneli bir sifre giriniz: \n");
scanf("%d",&kullaniciGiris);
if(kullaniciGiris==sifre){
	kullaniciYetkisi=personel;
}
else{
	kullaniciYetkisi=musteri;
}
do{
	printf("\n1- Yeni Musteri Eklemek Icin 'E'\n2-Oda Bilgisi Sorgulamak Icin 'S'\n3-Dolu Oda Bilgilerini Gormek Icin 'G'\n4-Fiyat Sorgulamak Icin 'F'\n");
	printf("5-Musteri Cikisi Yapmak Icin 'C'\n6-Sistemden Cikis Yapmak Icin 'Q' tuslamasini yapiniz: \n ");
	fflush(stdin);//buffer ý temizlemek için.
	ch=getchar();
	switch(ch){
		case 'E':
			if(kullaniciYetkisi==personel){
				yeniMusteriEkle(odaDizisi);
			}
			else{
				puts("Bu islemi yapmak icin yetkili degilsiniz. \n\n");
			}
			break;
		case 'S':
			printf("Lutfen sorgulamak istediginiz oda numarasini giriniz. \n");
			scanf("%d",&odaNumarasi);
			odaBilgisiSorgula(odaDizisi,odaNumarasi);
		    break;	
		case 'G':
			if(kullaniciYetkisi==personel){
				doluOdaBilgileriYaz(odaDizisi);
			}
			else{
				puts("Bu islemi yapmak icin yetkili degilsiniz. \n\n");
			}
			break;
		case 'F':
			fiyatBilgisiSorgula();
		    break;
		case 'C':
			if(kullaniciYetkisi==personel){
				printf("Musteri cikisi yapmak istediginiz oda numarasini giriniz: \n");
				scanf("%d",&odaNumarasi);
				rezervasyonTemizle(odaDizisi,odaNumarasi);
				printf("\n%d numarali odanin cikis/iptal islemi basariyla gerceklesti \n",odaDizisi[odaNumarasi-1].odaNumarasi);
			}
			else{
				puts("Bu islemi yapmak icin yetkili degilsiniz. \n\n");
			}
			break;
		case 'Q':
			yedekKayitAlma(odaDizisi);
			break;
		default:	
		    break;
	}

}while(ch!='Q');


	
}
