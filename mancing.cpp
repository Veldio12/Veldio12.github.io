#include<stdio.h>

int main(){
	long long int testcase,b,tali,berat_ikan,jarak,kecepatan,pengurangan,durasi,i=1,j,k=0,l,m,n,o;
	scanf("%lld",&testcase);
	for (b=1;b<=testcase;b++){
		scanf("%lld %lld %lld %lld %lld %lld",&tali,&berat_ikan,&jarak,&kecepatan,&pengurangan,&durasi);
		if(tali==1&&berat_ikan<=450||tali==2&&berat_ikan<=900||tali==3&&berat_ikan<=1320||tali==4&&berat_ikan<=3200||tali==5&&berat_ikan<=4500){
			while (jarak>0){
				if (i%2==1){
					for(j=0;j<durasi;j++){
						jarak+=kecepatan;
						k++;
					}i++;
				}else if (i%2==0){
					for(j=0;j<durasi;j++){if (jarak>0){
						jarak-=5;
						kecepatan-=pengurangan;
						kecepatan<0?kecepatan=0:kecepatan=kecepatan;
						k++;}
					}i++;
				}
			}n=k%60;m=(k/60)%60;l=k/3600;printf("Case #%lld: %02lld:%02lld:%02lld\n",b,l,m,n);k=0;
		}else printf("Case #%lld: Line broke up\n",b);
	}
	
return 0;}
